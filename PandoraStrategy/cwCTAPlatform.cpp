#include "cwCTAPlatform.h"
#include "cwStrategyCommon.h"
#include "tinyxml.h"
#include "cwTimeStamp.h"

#ifndef cwDouble_EQ
#include <limits>
#define cwDouble_EQ (std::numeric_limits<double>::epsilon())
#endif // !cwDouble_EQ


std::string cwCTAPlatform::GetStrategyVersion()
{
	return "20230302_v1";
}

std::string cwCTAPlatform::GetStrategyName()
{
	std::string strStrategyName("cwCTAPlatform");
	if (m_strStrategyName.size() > 0)
	{
		strStrategyName.append("_");
		strStrategyName.append(m_strStrategyName);
	}
	return strStrategyName;
}

void cwCTAPlatform::PriceUpdate(cwMarketDataPtr pPriceData)
{
	cwEasyStrategyLog log(m_StrategyLog, "PriceUpdate");

	m_strCurrentUpdateTime = pPriceData->UpdateTime;

	auto Insit = m_InsCTAStrategyList.find(pPriceData->InstrumentID);
	if (Insit != m_InsCTAStrategyList.end())
	{
		for (auto Listit = Insit->second.begin();
			Listit != Insit->second.end(); Listit++)
		{
			cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries = GetKindleSeries(pPriceData->InstrumentID, Listit->first);
			if (pKindleSeries.get() != nullptr)
			{
				for (auto it = Listit->second.begin();
					it != Listit->second.end(); it++)
				{
					(*it)->_pStrategy->m_strLastUpdateTime = pPriceData->ActionDay;
					(*it)->_pStrategy->m_strLastUpdateTime.append("_");
					(*it)->_pStrategy->m_strLastUpdateTime.append(pPriceData->UpdateTime);

					(*it)->_pStrategy->_PreOnBar(false, Listit->first, pKindleSeries);
					(*it)->_pStrategy->OnBar(false, Listit->first, pKindleSeries);
				}
			}
		}
	}


	TradeParameter									cwTradeParameter;
	cwPandoraAgentManager::cwAgentDataPtr			pAgentData;
	
	if (!GetParameter(pPriceData->InstrumentID, cwTradeParameter, pAgentData))
	{
		return;
	}

	MergeStrategyPosition(cwTradeParameter.SignalInstrumentID);


	int iExpecetedPosition = GetExpectedPosition(pPriceData->InstrumentID, cwTradeParameter);
	if (pAgentData->pPositionAgent->m_iExpectPosition != iExpecetedPosition)
	{
		log.AddLog(cwStrategyLog::enIMMS, "%s PositionChange %d => %d", pPriceData->InstrumentID,
			pAgentData->pPositionAgent->m_iExpectPosition, iExpecetedPosition);

		m_cwShow.AddLog("%s PositionChange %d => %d", pPriceData->InstrumentID,
			pAgentData->pPositionAgent->m_iExpectPosition, iExpecetedPosition);

		pAgentData->pPositionAgent->SetExpectPosition(iExpecetedPosition);
		
		WriteSignalToFile();
	}

	cwProductTradeTime::cwTradeTimeSpace TradeTimeSpace = cwProductTradeTime::NoTrading;
	int iOpen = 0, iClose = 0;
	bool bRet = GetTradeTimeSpace(pPriceData->InstrumentID, m_strCurrentUpdateTime.c_str(),
		TradeTimeSpace, iOpen, iClose);
	if (!bRet
		|| TradeTimeSpace == cwProductTradeTime::NoTrading
		|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionMatchOpen
		|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionOrderingOpen
		|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionMatchOpen
		|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionOrderingOpen
		|| TradeTimeSpace == cwProductTradeTime::CallAuctionMatchClose
		|| TradeTimeSpace == cwProductTradeTime::CallAuctionOrderingClose)
	{
		pAgentData->pPositionAgent->SetAgentWorking(false);
	}
	else
	{
		if (iClose > 1)
		{
			pAgentData->pPositionAgent->SetAgentWorking(true);
		}
		else
		{
			pAgentData->pPositionAgent->SetAgentWorking(false);
		}
	}

}

void cwCTAPlatform::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	cwEasyStrategyLog log(m_StrategyLog, "OnBar");

	auto Insit = m_InsCTAStrategyList.find(pKindleSeries->GetInstrumentID());
	if (Insit != m_InsCTAStrategyList.end())
	{
		auto Listit = Insit->second.find(iTimeScale);
		if (Listit != Insit->second.end())
		{
			for (auto it = Listit->second.begin();
				it != Listit->second.end(); it++)
			{
				//cwKindleStickPtr pKindle = pKindleSeries->GetLastKindleStick();
				//if (pKindle.get() != nullptr)
				//{
				//	(*it)->_pStrategy->m_strLastUpdateTime = pKindle->szStartTime;
				//}
				(*it)->_pStrategy->_PreOnBar(pKindleSeries->m_bIsNewKindle, iTimeScale, pKindleSeries);
				(*it)->_pStrategy->OnBar(pKindleSeries->m_bIsNewKindle, iTimeScale, pKindleSeries);
				//if (pKindleSeries->m_bIsNewKindle)
				//{
				//	log.AddLog(cwStrategyLog::enIMMS, "%s OnBar %d count:%d", pPriceData->InstrumentID,
				//		iTimeScale, pKindleSeries->GetKindleSize());

				//}
			}
		}
	}

	TradeParameter									cwTradeParameter;
	cwPandoraAgentManager::cwAgentDataPtr			pAgentData;

	if (!GetParameter(pPriceData->InstrumentID, cwTradeParameter, pAgentData)
		|| m_strCurrentUpdateTime.size() <= 0)
	{
		return;
	}

	MergeStrategyPosition(cwTradeParameter.SignalInstrumentID);


	int iExpecetedPosition = GetExpectedPosition(pPriceData->InstrumentID, cwTradeParameter);
	if (pAgentData->pPositionAgent->m_iExpectPosition != iExpecetedPosition)
	{
		log.AddLog(cwStrategyLog::enIMMS, "%s PositionChange %d => %d", pPriceData->InstrumentID,
			pAgentData->pPositionAgent->m_iExpectPosition, iExpecetedPosition);

		m_cwShow.AddLog("%s PositionChange %d => %d", pPriceData->InstrumentID,
			pAgentData->pPositionAgent->m_iExpectPosition, iExpecetedPosition);

		pAgentData->pPositionAgent->SetExpectPosition(iExpecetedPosition);

		WriteSignalToFile();
	}
}


void cwCTAPlatform::OnReady()
{
	cwEasyStrategyLog log(m_StrategyLog, "OnReady");

	SetTimer(1, 5000);

	int iunFixPositionCnt = 0;
	m_cwShow.AddLog(" Unfix Position: ");
	log.AddLog(cwStrategyLog::enMsg, " Unfix Position : ");

	SetAgentManager(dynamic_cast<cwAgentManager*>(&m_PandoraAgentManager));
	unsigned int folioId = 0;
	for (auto it = m_TradeParameterMap.begin();
		it != m_TradeParameterMap.end(); it++)
	{
		auto pAgentData = m_PandoraAgentManager.RegisterAgent(it->second->InstrumentID, cwPandoraAgentManager::Enum_Agent_Postion);
		if (pAgentData.get() != NULL
			&& pAgentData->pPositionAgent.get() != NULL)
		{
			m_cwAgentDataMap[it->second->InstrumentID] = pAgentData;

			//设置算法参数
			pAgentData->pPositionAgent->InsLargeOrderVolume = 200;
			pAgentData->pPositionAgent->InsLittleOrderVolume = 100;
			pAgentData->pPositionAgent->InsAskBidGap = 3;
		}
		//SetPortfolioId(it->second->InstrumentID.c_str(), folioId++);

		TradeParameter									cwTradeParameter;
		if (!GetParameter(it->second->InstrumentID.c_str(), cwTradeParameter, pAgentData))
		{
			return;
		}

		pAgentData->pPositionAgent->InsLargeOrderVolume = cwTradeParameter.InsLargeOrderVolume;
		pAgentData->pPositionAgent->InsLittleOrderVolume = cwTradeParameter.InsLittleOrderVolume;
		pAgentData->pPositionAgent->InsAskBidGap = cwTradeParameter.InsAskBidGap;


		MergeStrategyPosition(cwTradeParameter.SignalInstrumentID);


		int iExpecetedPosition = GetExpectedPosition(it->second->InstrumentID, cwTradeParameter);

		int iMaintain = GetNetPosition(it->second->InstrumentID);
		double dPosImbalance = iExpecetedPosition - iMaintain;
		int iPosiImbalance = dPosImbalance > 0 ? (int)(dPosImbalance + 0.4) : (int)(dPosImbalance - 0.4);

		if (iPosiImbalance != 0)
		{
			iunFixPositionCnt++;
			m_cwShow.AddLog("%s  Unfix:%d  Current Position:%d Signal Position:%d Ratio:%f",
				it->second->InstrumentID.c_str(), iPosiImbalance, iMaintain, iExpecetedPosition, cwTradeParameter.Ratio);
			log.AddLog(cwStrategyLog::enIMMS, "%s  Unfix:%d  Current Position:%d Signal Position:%d Ratio:%f",
				it->second->InstrumentID.c_str(), iPosiImbalance, iMaintain, iExpecetedPosition, cwTradeParameter.Ratio);
		}
		else
		{
			log.AddLog(cwStrategyLog::enMsg, "%s  Current Position:%d Signal Position:%d Ratio:%f",
				it->second->InstrumentID.c_str(), iMaintain, iExpecetedPosition, cwTradeParameter.Ratio);
		}

		if (pAgentData->pPositionAgent->m_iExpectPosition != iExpecetedPosition)
		{
			pAgentData->pPositionAgent->SetExpectPosition(iExpecetedPosition);
		}
	}

	m_cwShow.AddLog("%d Instrument's Positions is Unfix!", iunFixPositionCnt);
	log.AddLog(iunFixPositionCnt > 0 ? cwStrategyLog::enIMMS: cwStrategyLog::enMsg,
		"%d Instrument's Positions is Unfix!", iunFixPositionCnt);

	WriteSignalToFile();
}

void cwCTAPlatform::OnStrategyTimer(int iTimerId, const char * szInstrumentID)
{
	if (iTimerId == 1
		&& m_strConfigFileFullPath.size() > 0)
	{
		ReadXmlConfigFile(m_strConfigFileFullPath.c_str());
	}
}

void cwCTAPlatform::InitialStrategy(const char* pConfigFilePath)
{
	cwEasyStrategyLog log(m_StrategyLog, "InitialStrategy");

	log.AddLog(cwStrategyLog::enIMMS, "%s StrategyVersion: %s", GetStrategyName().c_str(), GetStrategyVersion().c_str());
	m_cwShow.AddLog("%s StrategyVersion: %s", GetStrategyName().c_str(), GetStrategyVersion().c_str());

	if (pConfigFilePath == nullptr
		|| strlen(pConfigFilePath) == 0)
	{
		char exeFullPath[MAX_PATH];
		memset(exeFullPath, 0, MAX_PATH);
#ifdef WIN32
		TCHAR TexeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, TexeFullPath, MAX_PATH);

		int iLength;
		//获取字节长度   
		iLength = WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, NULL, 0, NULL, NULL);
		//将tchar值赋给_char    
		WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, exeFullPath, iLength, NULL, NULL);

		m_strConfigFileFullPath = exeFullPath;
		std::size_t found = m_strConfigFileFullPath.find_last_of("/\\");
		m_strConfigFileFullPath = m_strConfigFileFullPath.substr(0, found);
		m_strConfigFileFullPath.append("\\CTAPlatformConfig.xml");
#else
		size_t cnt = readlink("/proc/self/exe", exeFullPath, MAX_PATH);
		if (cnt < 0 || cnt >= MAX_PATH)
		{
			printf("***Error***\n");
			exit(-1);
		}

		m_strConfigFileFullPath = exeFullPath;
		std::size_t found = m_strConfigFileFullPath.find_last_of("/\\");
		m_strConfigFileFullPath = m_strConfigFileFullPath.substr(0, found);
		m_strConfigFileFullPath.append("/CTAPlatformConfig.xml");
#endif		
	}
	else
	{
		m_strConfigFileFullPath = pConfigFilePath;
	}

	if (!cwBasicStrategy::InitalInstrumentData())
	{
		m_cwShow.AddLog("Can not Init InstrumentData From File, please Check!");
		m_cwShow.AddLog("The Program will shut down in 5 seconds!");
		int nCnt = 0;
		while (nCnt < 5)
		{
			cwSleep(1000);
			m_cwShow.AddLog("%d .", nCnt);
			nCnt++;
		}
		exit(-1);
	}

	ReadXmlConfigFile(m_strConfigFileFullPath.c_str());

	for (auto it = m_StrategyParameterMap.begin();
		it != m_StrategyParameterMap.end(); it++)
	{
		cwBasicCTAStrategy* pStrategy = nullptr;

		do
		{
			if (it->second->StrategyName == "DualTrust")
			{
				pStrategy = dynamic_cast<cwBasicCTAStrategy*>(new cwDualTrust(it->second->StrategyID.c_str()));
				break;
			}
			//Add Your Strategy Initial here!

		} while (false);

		if (pStrategy == nullptr)
		{
			m_cwShow.AddLog("UnDefine Strategy:%s Please Cheak!", it->second->StrategyName.c_str());
			continue;
		}

		for (int i = 0; i < 50; i++)
		{
			pStrategy->m_StrategyPara.ParaList[i] = it->second->ParaList[i];
		}

		if (it->second->bIndex)
		{
			pStrategy->m_pInstrument = GetFirstInstrumentData(it->second->InstrumentID.c_str());
		}
		else
		{
			pStrategy->m_pInstrument = GetInstrumentData(it->second->InstrumentID.c_str());
		}
		if (pStrategy->m_pInstrument.get() == nullptr)
		{
			m_cwShow.AddLog("Can NOT Find Instrument:%s%s Check, Please!", 
				it->second->InstrumentID.c_str(), it->second->bIndex ? "(IsIndex)" :"");
			log.AddLog(cwStrategyLog::enIMMS, 
				"Can NOT Find Instrument:%s. Check, Please!", it->second->InstrumentID.c_str());
			continue;
		}
		pStrategy->InitialStrategy();

		AddStrategyToPools(it->second->StrategyID.c_str(), pStrategy, it->second);
		SetKindle(it->second->StrategyID.c_str(),
			it->second->bIndex,
			it->second->InstrumentID.c_str(),
			it->second->iTimeScale,
			100);

		log.AddLog(cwStrategyLog::enIMMS, "%s Last: %s %d", it->second->StrategyID.c_str(), 
			pStrategy->m_strLastUpdateTime.c_str(),pStrategy->GetStrategyPosition());

		//log.AddLog(cwStrategyLog::enMsg, "%s Index:%s", it->second->bIndex ? "true" : "false");

	}

	MergeStrategyPosition(std::string());
	//{
	//	cwDualTrust * strategy = new cwDualTrust("DualTrust_hc");
	//	strategy->m_StrategyPara.CTAPara1 = 5;
	//	strategy->m_StrategyPara.CTAPara2 = 3;
	//	strategy->m_StrategyPara.CTAPara3 = 5;

	//	strategy->InitialStrategy();

	//	AddStrategyToPools("DualTrust_hc", dynamic_cast<cwBasicCTAStrategy*>(strategy));
	//	SetKindle("DualTrust_hc", true, "hc", cwKINDLE_TIMESCALE_15MIN, 100);

	//}

	//{
	//	cwJackCStrategy * strategy = new cwJackCStrategy("JackC_MA");

	//	strategy->m_StrategyPara.CTAPara1 = 300;	//Length_MAC(300)
	//	strategy->m_StrategyPara.CTAPara2 = 10;		//LENGTH_EMAC(10);
	//	strategy->m_StrategyPara.CTAPara3 = 20;		//ATRLength(20);
	//	strategy->m_StrategyPara.CTAPara4 = 1;		//RiskRatio(1)
	//	strategy->m_StrategyPara.CTAPara5 = 1;		//STOPLOSS(1);
	//	strategy->m_StrategyPara.CTAPara6 = 3;		//DarkBack(3)

	//	strategy->m_pInstrument = GetInstrumentData("MA209");
	//	strategy->InitialStrategy();

	//	AddStrategyToPools("JackC_MA", dynamic_cast<cwBasicCTAStrategy*>(strategy));
	//	SetKindle("JackC_MA", true, "MA", cwKINDLE_TIMESCALE_15MIN, 100);

	//}

}

bool cwCTAPlatform::IsNearDeliverDateWarning(const char* szInstrumentID)
{
	int iDaysWarning = GetTradingDayRemainWarning(szInstrumentID);

	int iRemain = 0;
	cwInstrumentTradeDateSpace DateSpace;

	if (GetBuisnessDayRemain(szInstrumentID, DateSpace, iRemain))
	{
		if (iRemain <= iDaysWarning)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

int cwCTAPlatform::GetTradingDayRemainWarning(const char* szInstrumentID)
{
	auto pProductID = GetProductID(szInstrumentID);
	return cwPandoraTrader::GetcwTradingDayRemainWarning(pProductID == nullptr ? "" : (std::string)(pProductID));
}

bool cwCTAPlatform::ReadXmlConfigFile(const char * pConfigFilePath, bool bNeedDisPlay/*= true*/)
{
	cwEasyStrategyLog log(m_StrategyLog, "ReadXmlConfigFile");

	if (strlen(pConfigFilePath) == 0)
	{
		m_cwShow.AddLog("Open ConfigFilePath Failed !! The configFilePath is empty.");
		log.AddLog(cwStrategyLog::enErr, "Open ConfigFilePath Failed !! The configFilePath is empty.", false);
		return false;
	}

	//check config File has been changed or not
	struct stat statbuf;
	int Rst = stat(pConfigFilePath, &statbuf);
	if (Rst == 0)
	{
		if (m_tLastestGetConfigTime == statbuf.st_mtime)
		{
			//file has not been changed!
			return true;
		}
		else
		{
			if (m_bFirstGetConfig)
			{
				m_cwShow.AddLog(" First Get Config File!\n FilePath: %s", pConfigFilePath);
				log.AddLog(cwStrategyLog::enIMMS, "First Get Config File.", false);
				log.AddLog(cwStrategyLog::enIMMS, pConfigFilePath, false);
			}
			else
			{
				m_cwShow.AddLog("Strategy Config File has been changed!");
				log.AddLog(cwStrategyLog::enMsg, "Config File has been changed.", false);
			}
		}
	}
	else
	{
		m_cwShow.AddLog("Open ConfigFilePath Failed !! Make SURE the ConfigFile exits.");
		log.AddLog(cwStrategyLog::enErr, "Open ConfigFilePath Failed !! Make SURE the ConfigFile exits.", false);

		return false;
	}

	if (m_bFirstGetConfig)
	{
		m_bFirstGetConfig = false;
		bNeedDisPlay = false;
	}

	TiXmlDocument doc(pConfigFilePath);
	bool loadOkay = doc.LoadFile(TIXML_ENCODING_LEGACY);

	if (!loadOkay)
	{
		m_cwShow.AddLog("Strategy: Open ConfigFilePath Failed !! Parse XML File Failed.");
		log.AddLog(cwStrategyLog::enErr, "Open ConfigFilePath Failed !! Parse XML File Failed.", false);

		return false;
	}

	TiXmlNode* RootNode = doc.RootElement();
	if (RootNode != NULL)
	{
		//Save config file Lastest Changed time
		m_tLastestGetConfigTime = statbuf.st_mtime;

		TiXmlElement * RootElement = RootNode->ToElement();
		if (TIXML_SUCCESS != RootElement->QueryBoolAttribute("Run", &loadOkay))
		{
			m_bStrategyRun = false;
		}
		else
		{
			if (loadOkay != m_bStrategyRun)
			{
				if (bNeedDisPlay)
				{
					m_cwShow.AddLog("m_bStrategyRun: %s ==> %s !",
						(m_bStrategyRun ? "true" : "false"),
						(loadOkay ? "true" : "false"));
				}
				log.AddLog(cwStrategyLog::enIMMS, "m_bStrategyRun : %s ==> %s !", (m_bStrategyRun ? "true" : "false"), (loadOkay ? "true" : "false"));
				m_bStrategyRun = loadOkay;
			}
		}

		if (TIXML_SUCCESS != RootElement->QueryBoolAttribute("ShowPosition", &loadOkay))
		{
			m_bShowPosition = false;
		}
		else
		{
			if (loadOkay != m_bShowPosition)
			{
				if (bNeedDisPlay)
				{
					m_cwShow.AddLog("m_bShowPosition: %s ==> %s !",
						(m_bShowPosition ? "true" : "false"),
						(loadOkay ? "true" : "false"));
				}
				log.AddLog(cwStrategyLog::enIMMS, "m_bShowPosition : %s ==> %s !", (m_bShowPosition ? "true" : "false"), (loadOkay ? "true" : "false"));
				m_bShowPosition = loadOkay;
			}
		}

		m_strStrategyName = RootElement->Attribute("Name");

		cwAUTOMUTEX mt(m_ParameterMutex, true);

		int iTemp;
		double dbTemp;
		std::string strTemp;

		//Read General
		TiXmlNode* ChildNode = RootNode->FirstChild("CTAStrategy");
		if (ChildNode != NULL)
		{
			{
				TiXmlElement* Element = ChildNode->ToElement();
				const char* pszTemp = Element->Attribute("BeginTime");
				if (pszTemp != NULL
					&& strlen(pszTemp) >= 19)
				{
					int year = 2000, month = 1, day = 1, hour = 8, minute = 0, second = 0;
#ifdef _MSC_VER
					sscanf_s(pszTemp, "%d_%d_%d_%d:%d:%d",
						&year, &month, &day,
						&hour, &minute, &second);
#else
					sscanf(pszTemp, "%d_%d_%d_%d:%d:%d",
						&year, &month, &day,
						&hour, &minute, &second);
#endif // _MSC_VER

					cwTimeStamp t;
					t.SetYear(year);
					t.SetMonth(month);
					t.SetDay(day);
					t.SetHour(hour);
					t.SetMinute(minute);
					t.SetSecond(second);

					if (t.GetYear() == year
						&& year > 2000
						&& t.GetMonth() == month
						&& t.GetDay() == day
						&& t.GetHour() == hour
						&& t.GetMinute() == minute
						&& t.GetSecond() == second)
					{
						m_iKindleBeginTime = t.GetTotalMicrosecond();

						m_cwShow.AddLog("Kindel Start Time Set: %4d%02d%02d_%02d:%02d:%02d",
							year, month, day, hour, minute, second);

					}
				}
				

			}
			StrategyParaPtr ParaPtr;

			TiXmlNode* SubChildNode = ChildNode->FirstChild("Strategy");
			while (SubChildNode != NULL)
			{
				TiXmlElement * Element = SubChildNode->ToElement();
				const char * pszTemp = Element->Attribute("Name");
				if (pszTemp != NULL)
				{
					strTemp = pszTemp;
				}
				else
				{
					SubChildNode = SubChildNode->NextSibling("Strategy");
					continue;
				}

				ParaPtr.reset(new StrategyParameter());
				ParaPtr->StrategyName = std::move(strTemp);

				TiXmlNode* TempNode = SubChildNode->FirstChild("Kindle");
				if (TempNode != NULL)
				{
					TiXmlElement * Element = TempNode->ToElement();

					pszTemp = Element->Attribute("Instrument");
					if (pszTemp != NULL)
					{
						ParaPtr->InstrumentID = pszTemp;
					}
					else
					{
						continue;
					}

					if (TIXML_SUCCESS != Element->QueryIntAttribute("TimeScale", &iTemp))
					{
						continue;
					}
					else
					{
						if (iTemp != ParaPtr->iTimeScale)
						{
							ParaPtr->iTimeScale = iTemp;
						}
					}

					ParaPtr->StrategyID = ParaPtr->StrategyName;
					ParaPtr->StrategyID.append("_");
					ParaPtr->StrategyID.append(ParaPtr->InstrumentID);
					ParaPtr->StrategyID.append("_");
					ParaPtr->StrategyID.append(std::to_string(ParaPtr->iTimeScale));


					if (TIXML_SUCCESS != Element->QueryBoolAttribute("Index", &loadOkay))
					{
						ParaPtr->bIndex = false;
					}
					else
					{
						if (loadOkay != ParaPtr->bIndex)
						{
							if (bNeedDisPlay)
							{
								m_cwShow.AddLog("%s bIndex: %s ==> %s !",
									ParaPtr->StrategyID.c_str(),
									(ParaPtr->bIndex ? "true" : "false"),
									(loadOkay ? "true" : "false"));
							}
							log.AddLog(cwStrategyLog::enIMMS, "bIndex : %s ==> %s !", (ParaPtr->bIndex ? "true" : "false"), (loadOkay ? "true" : "false"));
							ParaPtr->bIndex = loadOkay;
						}
					}
				}

				auto it = m_StrategyParameterMap.find(ParaPtr->StrategyID);
				if (it == m_StrategyParameterMap.end()
					|| it->second.get() == NULL)
				{
					it = m_StrategyParameterMap.insert(std::pair<std::string, StrategyParaPtr>(ParaPtr->StrategyID, ParaPtr)).first;
				}
				else
				{
					ParaPtr = it->second;
				}

				TempNode = SubChildNode->FirstChild("multiple");
				if (TempNode != NULL)
				{
					TiXmlElement * Element = TempNode->ToElement();

					if (TIXML_SUCCESS != Element->QueryDoubleAttribute("value", &dbTemp))
					{
						ParaPtr->dMultiple = 1.0;
					}
					else
					{
						if (dbTemp != ParaPtr->dMultiple)
						{
							if (bNeedDisPlay)
							{
								m_cwShow.AddLog("%s dMultiple: %.3f ==> %.3f!",
									ParaPtr->StrategyID.c_str(),
									ParaPtr->dMultiple,
									dbTemp);
							}
							log.AddLog(cwStrategyLog::enIMMS, "%s dMultiple: %.3f ==> %.3f !",
								ParaPtr->StrategyID.c_str(),
								ParaPtr->dMultiple,
								dbTemp);
							ParaPtr->dMultiple = dbTemp;
						}
					}
				}

				TempNode = SubChildNode->FirstChild("ParaField");
				if (TempNode != NULL)
				{
					TiXmlElement * Element = TempNode->ToElement();
					for (int i = 1; i < 50; i++)
					{
						strTemp = "P";
						strTemp += std::to_string(i);

						if (TIXML_SUCCESS != Element->QueryDoubleAttribute(strTemp.c_str(), &dbTemp))
						{
							ParaPtr->ParaList[i - 1] = 0.0;
						}
						else
						{
							if (dbTemp != ParaPtr->ParaList[i - 1])
							{
								if (bNeedDisPlay)
								{
									m_cwShow.AddLog("%s %s: %.3f ==> %.3f!",
										ParaPtr->StrategyID.c_str(),
										strTemp.c_str(),
										ParaPtr->ParaList[i - 1],
										dbTemp);
								}
								log.AddLog(cwStrategyLog::enIMMS, "%s %s: %.3f ==> %.3f !",
									ParaPtr->StrategyID.c_str(),
									strTemp.c_str(),
									ParaPtr->ParaList[i - 1],
									dbTemp);
								ParaPtr->ParaList[i - 1] = dbTemp;
							}
						}
					}
				}

				SubChildNode = SubChildNode->NextSibling("Strategy");
			}
		}
			
		ChildNode = RootNode->FirstChild("Subscription");
		if (ChildNode != NULL)
		{
			TradeParaPtr ParaPtr;

			TiXmlNode* SubChildNode = ChildNode->FirstChild("Instrument");
			while (SubChildNode != NULL)
			{
				TiXmlElement * Element = SubChildNode->ToElement();
				const char * pszTemp = Element->Attribute("ID");
				if (pszTemp != NULL)
				{
					strTemp = pszTemp;
				}
				else
				{
					SubChildNode = SubChildNode->NextSibling("Instrument");
					continue;
				}

				auto it = m_TradeParameterMap.find(strTemp);
				if (it == m_TradeParameterMap.end()
					|| it->second.get() == NULL)
				{
					ParaPtr.reset(new TradeParameter());
					it = m_TradeParameterMap.insert(std::pair<std::string, TradeParaPtr>(strTemp, ParaPtr)).first;
				}
				else
				{
					ParaPtr = it->second;
				}
				ParaPtr->InstrumentID = strTemp;

				pszTemp = Element->Attribute("SignalID");
				if (pszTemp != NULL)
				{
					strTemp = pszTemp;
					if (strTemp != ParaPtr->SignalInstrumentID)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s  SignalID: %s ==> %s", it->first.c_str(), ParaPtr->SignalInstrumentID.c_str(), strTemp.c_str());
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s SignalID : %s ==> %s !", it->first.c_str(), ParaPtr->SignalInstrumentID.c_str(), strTemp.c_str());
						ParaPtr->SignalInstrumentID = strTemp;
					}
				}
				else
				{
					ParaPtr->SignalInstrumentID = ParaPtr->InstrumentID;
				}

				if (Element->Attribute("Ratio", &dbTemp) != NULL)
				{
					if (dbTemp != ParaPtr->Ratio)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s Ratio:%.3f ==> %.3f",
								it->first.c_str(), ParaPtr->Ratio, dbTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s Ratio : %.2f ==> %.2f !", it->first.c_str(), ParaPtr->Ratio, dbTemp);
						ParaPtr->Ratio = dbTemp;
					}
				}

				if (TIXML_SUCCESS != Element->QueryBoolAttribute("Mod", &loadOkay))
				{
					ParaPtr->Mod = false;
				}
				else
				{
					if (loadOkay != ParaPtr->Mod)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s Mod: %s ==> %s !",
								it->first.c_str(),
								(ParaPtr->Mod ? "true" : "false"),
								(loadOkay ? "true" : "false"));
						}
						log.AddLog(cwStrategyLog::enIMMS, "Mod : %s ==> %s !", (ParaPtr->Mod ? "true" : "false"), (loadOkay ? "true" : "false"));
						ParaPtr->Mod = loadOkay;
					}
				}

				if (Element->Attribute("OpenClose", &iTemp) != NULL)
				{
					if (iTemp != (int)ParaPtr->InsOpenCloseMode)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsOpenCloseMode:%d ==> %d",
								it->first.c_str(), ParaPtr->InsOpenCloseMode, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsOpenCloseMode : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsOpenCloseMode, iTemp);
						ParaPtr->InsOpenCloseMode = (cwOpenCloseMode)iTemp;
					}
				}

				if (Element->Attribute("AddTick", &iTemp) != NULL)
				{
					if (iTemp != ParaPtr->InsAddTick)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsAddTick:%d ==> %d",
								it->first.c_str(), ParaPtr->InsAddTick, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsAddTick : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsAddTick, iTemp);
						ParaPtr->InsAddTick = iTemp;
					}
				}

				if (Element->Attribute("LargeOrderVolume", &iTemp) != NULL)
				{
					if (iTemp != ParaPtr->InsLargeOrderVolume
						&& iTemp >= 0)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsLargeOrderVolume:%d ==> %d",
								it->first.c_str(), ParaPtr->InsLargeOrderVolume, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsLargeOrderVolume : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsLargeOrderVolume, iTemp);
						ParaPtr->InsLargeOrderVolume = iTemp;
					}
				}

				if (Element->Attribute("LittleOrderVolume", &iTemp) != NULL)
				{
					if (iTemp != ParaPtr->InsLittleOrderVolume
						&& iTemp >= 0)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsLittleOrderVolume:%d ==> %d",
								it->first.c_str(), ParaPtr->InsLittleOrderVolume, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsLittleOrderVolume : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsLittleOrderVolume, iTemp);
						ParaPtr->InsLittleOrderVolume = iTemp;
					}
				}

				if (Element->Attribute("AskBidGap", &iTemp) != NULL)
				{
					if (iTemp != ParaPtr->InsAskBidGap)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsAskBidGap:%d ==> %d",
								it->first.c_str(), ParaPtr->InsAskBidGap, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsAskBidGap : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsAskBidGap, iTemp);
						ParaPtr->InsAskBidGap = iTemp;
					}
				}

				if (Element->Attribute("WaitInterval", &iTemp) != NULL)
				{
					if (iTemp != ParaPtr->InsWaitInterval)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s InsWaitInterval:%d ==> %d",
								it->first.c_str(), ParaPtr->InsWaitInterval, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s InsWaitInterval : %d ==> %d !", it->first.c_str(), (int)ParaPtr->InsWaitInterval, iTemp);
						ParaPtr->InsWaitInterval = iTemp;
					}
				}

				if (TIXML_SUCCESS != Element->QueryBoolAttribute("Pause", &loadOkay))
				{
					ParaPtr->Pause = false;
				}
				else
				{
					if (loadOkay != ParaPtr->Pause)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s Pause: %s ==> %s !",
								it->first.c_str(),
								(ParaPtr->Pause ? "true" : "false"),
								(loadOkay ? "true" : "false"));
						}
						log.AddLog(cwStrategyLog::enIMMS, "Pause : %s ==> %s !", (ParaPtr->Pause ? "true" : "false"), (loadOkay ? "true" : "false"));
						ParaPtr->Pause = loadOkay;
					}
				}

				SubChildNode = SubChildNode->NextSibling("Instrument");
			}
		}

		//ChildNode = RootNode->FirstChild("ManualIntervention");
		//if (ChildNode != NULL)
		//{
		//	ManualInterventionPtr ParaPtr;
		//	StrategyInstrumentUnion StrategyInsUnion;

		//	TiXmlNode* SubChildNode = ChildNode->FirstChild("Strategy");
		//	while (SubChildNode != NULL)
		//	{
		//		TiXmlElement * Element = SubChildNode->ToElement();
		//		const char * pszTemp = Element->Attribute("name");
		//		if (pszTemp != NULL)
		//		{
		//			strTemp = pszTemp;
		//		}
		//		else
		//		{
		//			SubChildNode = SubChildNode->NextSibling("Strategy");
		//			continue;
		//		}
		//		StrategyInsUnion.StrategyName = strTemp;

		//		pszTemp = Element->Attribute("InstrumentID");
		//		if (pszTemp != NULL)
		//		{
		//			strTemp = pszTemp;
		//		}
		//		else
		//		{
		//			SubChildNode = SubChildNode->NextSibling("Strategy");
		//			continue;
		//		}
		//		StrategyInsUnion.InstrumentID = strTemp;

		//		auto it = m_ManualinterventionMap.find(StrategyInsUnion);
		//		if (it == m_ManualinterventionMap.end()
		//			|| it->second.get() == NULL)
		//		{
		//			ParaPtr.reset(new ManualIntervention());
		//			it = m_ManualinterventionMap.insert(std::pair<StrategyInstrumentUnion, ManualInterventionPtr>(StrategyInsUnion, ParaPtr)).first;
		//		}
		//		else
		//		{
		//			ParaPtr = it->second;
		//		}

		//		ParaPtr->InstrumentID = StrategyInsUnion.InstrumentID;
		//		ParaPtr->StrategyName = StrategyInsUnion.StrategyName;

		//		if (TIXML_SUCCESS != Element->QueryBoolAttribute("Manual", &loadOkay))
		//		{
		//			ParaPtr->Manual = false;
		//		}
		//		else
		//		{
		//			if (loadOkay != ParaPtr->Manual)
		//			{
		//				if (bNeedDisPlay)
		//				{
		//					m_cwShow.AddLog("%s %s Manual:  ParaPtr->Manual : %s ==> %s !",
		//						it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->Manual ? "true" : "false"), (loadOkay ? "true" : "false"));

		//					//std::cout << it->first.StrategyName.c_str() << " " << it->first.InstrumentID.c_str()
		//					//	<< " Manual: " << (ParaPtr->Manual ? "true ==> " : "false ==>") << (loadOkay ? "true !" : "false !") << std::endl;
		//				}
		//				log.AddLog(cwStrategyLog::enIMMS, "%s %s Manual:  ParaPtr->Manual : %s ==> %s !",
		//					it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->Manual ? "true" : "false"), (loadOkay ? "true" : "false"));
		//				ParaPtr->Manual = loadOkay;
		//			}
		//		}
		//		if (Element->Attribute("ExpectedPosition", &iTemp) != NULL)
		//		{
		//			if (iTemp != ParaPtr->ExpectedPosition)
		//			{
		//				if (bNeedDisPlay)
		//				{
		//					m_cwShow.AddLog("%s %s ExpectedPosition : %d ==> %d !",
		//						it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (int)ParaPtr->ExpectedPosition, iTemp);

		//					//std::cout << it->first.StrategyName.c_str() << " " << it->first.InstrumentID.c_str()
		//					//	<< " ExpectedPosition: " << ParaPtr->ExpectedPosition << " ==>" << iTemp << std::endl;
		//				}
		//				log.AddLog(cwStrategyLog::enIMMS, "%s %s ExpectedPosition : %d ==> %d !",
		//					it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (int)ParaPtr->ExpectedPosition, iTemp);
		//				ParaPtr->ExpectedPosition = iTemp;
		//			}
		//		}

		//		SubChildNode = SubChildNode->NextSibling("Strategy");
		//	}
		//}

		//ChildNode = RootNode->FirstChild("DirectionMask");
		//if (ChildNode != NULL)
		//{
		//	DirectionMaskPtr ParaPtr;
		//	StrategyInstrumentUnion StrategyInsUnion;

		//	TiXmlNode* SubChildNode = ChildNode->FirstChild("Strategy");
		//	while (SubChildNode != NULL)
		//	{
		//		TiXmlElement * Element = SubChildNode->ToElement();
		//		const char * pszTemp = Element->Attribute("name");
		//		if (pszTemp != NULL)
		//		{
		//			strTemp = pszTemp;
		//		}
		//		else
		//		{
		//			SubChildNode = SubChildNode->NextSibling("Strategy");
		//			continue;
		//		}
		//		StrategyInsUnion.StrategyName = strTemp;

		//		pszTemp = Element->Attribute("InstrumentID");
		//		if (pszTemp != NULL)
		//		{
		//			strTemp = pszTemp;
		//		}
		//		else
		//		{
		//			SubChildNode = SubChildNode->NextSibling("Strategy");
		//			continue;
		//		}
		//		StrategyInsUnion.InstrumentID = strTemp;

		//		auto it = m_DirectionMaskMap.find(StrategyInsUnion);
		//		if (it == m_DirectionMaskMap.end()
		//			|| it->second.get() == NULL)
		//		{
		//			ParaPtr.reset(new DirectionMask());
		//			it = m_DirectionMaskMap.insert(std::pair<StrategyInstrumentUnion, DirectionMaskPtr>(StrategyInsUnion, ParaPtr)).first;
		//		}
		//		else
		//		{
		//			ParaPtr = it->second;
		//		}

		//		ParaPtr->InstrumentID = StrategyInsUnion.InstrumentID;
		//		ParaPtr->StrategyName = StrategyInsUnion.StrategyName;

		//		if (TIXML_SUCCESS != Element->QueryDoubleAttribute("Ratio", &dbTemp))
		//		{
		//			ParaPtr->StrategyInsRatio = 1;
		//		}
		//		else
		//		{
		//			if (dbTemp != ParaPtr->StrategyInsRatio)
		//			{
		//				if (bNeedDisPlay)
		//				{
		//					m_cwShow.AddLog("%s %s StrategyInsRatio:%.3f ==> %.3f",
		//						StrategyInsUnion.StrategyName.c_str(), StrategyInsUnion.InstrumentID.c_str(),
		//						ParaPtr->StrategyInsRatio, dbTemp);

		//					//std::cout << it->first.c_str() << " Ratio: " << ParaPtr->Ratio << " ==>" << dbTemp << std::endl;
		//				}
		//				log.AddLog(cwStrategyLog::enIMMS, " %s %s StrategyInsRatio : %.2f ==> %.2f !",
		//					StrategyInsUnion.StrategyName.c_str(), StrategyInsUnion.InstrumentID.c_str(),
		//					ParaPtr->StrategyInsRatio, dbTemp);
		//				ParaPtr->StrategyInsRatio = dbTemp;
		//			}
		//		}

		//		if (TIXML_SUCCESS != Element->QueryBoolAttribute("NoLong", &loadOkay))
		//		{
		//			ParaPtr->NoLong = false;
		//		}
		//		else
		//		{
		//			if (loadOkay != ParaPtr->NoLong)
		//			{
		//				if (bNeedDisPlay)
		//				{
		//					m_cwShow.AddLog("%s %s NoLong:  ParaPtr->NoLong : %s ==> %s !",
		//						it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->NoLong ? "true" : "false"), (loadOkay ? "true" : "false"));

		//					//std::cout << it->first.StrategyName.c_str() << " " << it->first.InstrumentID.c_str()
		//					//	<< " NoLong: " << (ParaPtr->NoLong ? "true ==> " : "false ==>") << (loadOkay ? "true !" : "false !") << std::endl;
		//				}
		//				log.AddLog(cwStrategyLog::enIMMS, "%s %s NoLong:  ParaPtr->NoLong : %s ==> %s !",
		//					it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->NoLong ? "true" : "false"), (loadOkay ? "true" : "false"));
		//				ParaPtr->NoLong = loadOkay;
		//			}
		//		}

		//		if (TIXML_SUCCESS != Element->QueryBoolAttribute("NoShort", &loadOkay))
		//		{
		//			ParaPtr->NoShort = false;
		//		}
		//		else
		//		{
		//			if (loadOkay != ParaPtr->NoShort)
		//			{
		//				if (bNeedDisPlay)
		//				{
		//					m_cwShow.AddLog("%s %s NoShort:  ParaPtr->NoShort : %s ==> %s !",
		//						it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->NoShort ? "true" : "false"), (loadOkay ? "true" : "false"));

		//					//std::cout << it->first.StrategyName.c_str() << " " << it->first.InstrumentID.c_str() 
		//					//	<< " NoShort: " << (ParaPtr->NoShort ? "true ==> " : "false ==>") << (loadOkay ? "true !" : "false !") << std::endl;
		//				}
		//				log.AddLog(cwStrategyLog::enIMMS, "%s %s NoShort:  ParaPtr->NoShort : %s ==> %s !",
		//					it->first.StrategyName.c_str(), it->first.InstrumentID.c_str(), (ParaPtr->NoShort ? "true" : "false"), (loadOkay ? "true" : "false"));
		//				ParaPtr->NoShort = loadOkay;
		//			}
		//		}

		//		SubChildNode = SubChildNode->NextSibling("Strategy");
		//	}
		//}

	}

	return true;
}

bool cwCTAPlatform::AddStrategyToPools(std::string strStrategyID, cwBasicCTAStrategy * pCTAStrategy, StrategyParaPtr pPara)
{
	CTAStrategyInfoPtr pStrategyInfo(new CTAStrategyInfo());

	pStrategyInfo->_pStrategy = pCTAStrategy;
	pStrategyInfo->_StrategyID = strStrategyID;
	pStrategyInfo->_pParameter = pPara;

	auto ret = m_NameCTAStrategy.insert(std::pair<std::string, CTAStrategyInfoPtr>(strStrategyID, pStrategyInfo));
	m_cwShow.AddLog("Add Strategy:%s To Pools", strStrategyID.c_str());
	return ret.second;
}

void cwCTAPlatform::SetKindle(std::string strStrategyID, bool bIndex, const char* szInstrumentID, int iTimeScale, int HisKindleCount)
{
	cwEasyStrategyLog log(m_StrategyLog, "SetKindle");

	CTAStrategyInfoPtr pStrategyInfo;
	{
		auto it = m_NameCTAStrategy.find(strStrategyID);
		if (it == m_NameCTAStrategy.end())
		{
			m_cwShow.AddLog("Can not find StrategyID:%s ", strStrategyID.c_str());
			return;
		}
		else
		{
			pStrategyInfo = it->second;
		}
	}

	cwBasicKindleStrategy::cwKindleSeriesPtr pKindle;
	if(bIndex)
	{
		pKindle = SubcribeIndexKindle(szInstrumentID, iTimeScale, HisKindleCount);
		if (pKindle.get() == NULL)
		{
			log.AddLog(cwStrategyLog::enErr, "%s Init Kindle Faild! Please Chech Instrument File!", szInstrumentID);
			m_cwShow.AddLog("%s Init Kindle Faild! Please Chech Instrument File!", szInstrumentID);
			m_cwShow.AddLog("The Program will shut down in 5 seconds!");
			int nCnt = 0;
			while (nCnt < 5)
			{
				cwSleep(1000);
				m_cwShow.AddLog("%d .", nCnt);
				nCnt++;
			}
			exit(-1);
		}
		m_InsCTAStrategyList[pKindle->GetInstrumentID()][iTimeScale].push_back(pStrategyInfo);
	}
	else
	{
		pKindle = SubcribeKindle(szInstrumentID, iTimeScale, HisKindleCount);
		if (pKindle.get() == NULL)
		{
			m_cwShow.AddLog("Init Kindle Faild! Please Chech Instrument File!");
			m_cwShow.AddLog("The Program will shut down in 5 seconds!");
			int nCnt = 0;
			while (nCnt < 5)
			{
				cwSleep(1000);
				m_cwShow.AddLog("%d .", nCnt);
				nCnt++;
			}
			exit(-1);
		}
		m_InsCTAStrategyList[pKindle->GetInstrumentID()][iTimeScale].push_back(pStrategyInfo);
	}

	if (pStrategyInfo->_pStrategy->m_strDealInstrument.size() == 0)
	{
		pStrategyInfo->_pStrategy->m_strDealInstrument = pKindle->GetInstrumentID();
	}

	if (m_iKindleBeginTime > 0)
	{
		pKindle->RemoveKinldeBeforeTime(m_iKindleBeginTime);
	}

	cwBasicKindleStrategy::cwKindleSeriesPtr pHisKindle(new cwKindleStickSeries());

	if (bIndex)
	{
		pHisKindle->InitialKindleStickSeries(pKindle->GetInstrumentID(), szInstrumentID,
			cwKindleStickSeries::cwKindleTypeMinute, iTimeScale);
	}
	else
	{
		pHisKindle->InitialKindleStickSeries(pKindle->GetInstrumentID(), GetProductID(szInstrumentID),
			cwKindleStickSeries::cwKindleTypeMinute, iTimeScale);
	}
	int iCount = (int)pKindle->GetKindleSize();

	cwKindleStickPtr pTmpKindle  = std::make_shared<cwKindleStick>();

	for (int i = 0; i < iCount; i++)
	{
		cwKindleStickPtr pkindleStick = pKindle->GetKindleStick(i);

		//dataPtr->Volume = pkindleStick->TotalVolume;
		//dataPtr->Turnover = pkindleStick->TotalTurnOver;
		//dataPtr->OpenInterest = pkindleStick->OpenInterest;

		//dataPtr->LastPrice = pkindleStick->Close;

		pStrategyInfo->_pStrategy->m_strLastUpdateTime = pkindleStick->szStartTime;
#ifdef _MSC_VER
		memcpy_s(pTmpKindle.get(), sizeof(cwKindleStick), pkindleStick.get(), sizeof(cwKindleStick));
#else
		memcpy(pTmpKindle.get(), pkindleStick.get(), sizeof(cwKindleStick));
#endif
		pTmpKindle->Close = pTmpKindle->High = pTmpKindle->Low = pTmpKindle->Open;
		pTmpKindle->LastVolume = pTmpKindle->LastTurnOver = 0;
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_PreOnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);
		pStrategyInfo->_pStrategy->OnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);


		pTmpKindle->Close = pTmpKindle->Low = pkindleStick->Low;
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_PreOnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);
		pStrategyInfo->_pStrategy->OnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);

		pTmpKindle->Close = pTmpKindle->High = pkindleStick->High;
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_PreOnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);
		pStrategyInfo->_pStrategy->OnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);

		pHisKindle->UpdateKindle(pkindleStick);

		pStrategyInfo->_pStrategy->_PreOnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);
		pStrategyInfo->_pStrategy->OnBar(pHisKindle->m_bIsNewKindle, iTimeScale, pHisKindle);
	}
	//log.AddLog(cwStrategyLog::enIMMS, "%s HisKindle Count:%d Last: %s %d", strStrategyID.c_str(), iCount,
	//	pStrategyInfo->_pStrategy->m_strLastUpdateTime.c_str(), pStrategyInfo->_pStrategy->GetStrategyPosition());
	m_cwShow.AddLog("%s HisKindle Count:%d Last: %s %d", strStrategyID.c_str(), iCount,
		pStrategyInfo->_pStrategy->m_strLastUpdateTime.c_str(), pStrategyInfo->_pStrategy->GetStrategyPosition());

}

double cwCTAPlatform::MergeStrategyPosition(std::string InstrumentID)
{
	double dPosition = 0;
	if (InstrumentID.size() == 0)
	{
		for (auto Insit = m_InsCTAStrategyList.begin();
			Insit != m_InsCTAStrategyList.end(); Insit++)
		{
			for (auto Listit = Insit->second.begin();
				Listit != Insit->second.end(); Listit++)
			{
				for (auto it = Listit->second.begin();
					it != Listit->second.end(); it++)
				{
					//auto Posit = (*it)->_pStrategy->m_iStrategyPositionMap.find(InstrumentID);
					for(auto Posit = (*it)->_pStrategy->m_iStrategyPositionMap.begin();
						Posit != (*it)->_pStrategy->m_iStrategyPositionMap.end(); Posit++)
					{
						double dPos = Posit->second * (*it)->_pParameter->dMultiple;
						m_cwStrategyPositionMap[Posit->first][(*it)->_StrategyID]
							= dPos;
						dPosition += dPos;
					}
				}
			}
		}
	}
	else
	{
		auto Insit = m_InsCTAStrategyList.find(InstrumentID);
		if (Insit != m_InsCTAStrategyList.end())
		{
			for (auto Listit = Insit->second.begin();
				Listit != Insit->second.end(); Listit++)
			{
				for (auto it = Listit->second.begin();
					it != Listit->second.end(); it++)
				{
					auto Posit = (*it)->_pStrategy->m_iStrategyPositionMap.find(InstrumentID);
					if (Posit != (*it)->_pStrategy->m_iStrategyPositionMap.end())
					{
						double dPos = Posit->second * (*it)->_pParameter->dMultiple;
						m_cwStrategyPositionMap[InstrumentID][(*it)->_StrategyID]
							= dPos;
						dPosition += dPos;
					}
				}
			}
		}
	}
	return dPosition;
}

cwInstrumentDataPtr cwCTAPlatform::GetFirstInstrumentData(std::string ProductID)
{
	for (auto it = m_InstrumentMap.begin();
		it != m_InstrumentMap.end(); it++)
	{
		if (it->second->ProductClass == CW_FTDC_PC_Futures
			&& it->second->ProductID == ProductID)
		{
			return it->second;
		}
	}

	return cwInstrumentDataPtr();
}

void cwCTAPlatform::WriteSignalToFile()
{
	std::ofstream wfile;//写文件流;

	cwAUTOMUTEX mt(m_ParameterMutex, true);

	wfile.open("SignalPosition.log", std::ios::trunc);
	wfile << m_strCurrentUpdateTime.c_str() << "InstrumentID,StrategyName,Position\n";
	if (wfile.is_open())
	{
		for (auto InsIt = m_cwStrategyPositionMap.begin();
			InsIt != m_cwStrategyPositionMap.end(); InsIt++)
		{
			double dPos = 0.0;
			for (auto it = InsIt->second.begin();
				it != InsIt->second.end(); it++)
			{
				wfile << InsIt->first.c_str() << ","
					<< it->first.c_str() << ","
					<< it->second << '\n';
				dPos += it->second;

				m_cwShow.AddLog("%s %s %.1f", InsIt->first.c_str(), it->first.c_str(), it->second);
			}

			wfile << InsIt->first.c_str() << ","
				<< "Total,"
				<< dPos << '\n';

		}

		wfile << std::endl;
		wfile.close();
	}

}


bool cwCTAPlatform::GetParameter(const char * szInstrumentID,
	TradeParameter& para, cwPandoraAgentManager::cwAgentDataPtr& pAgent)
{
	if (!m_bStrategyReady)
	{
		return false;
	}
	cwAUTOMUTEX mt(m_ParameterMutex, true);

	auto it = m_TradeParameterMap.find(szInstrumentID);
	if (it == m_TradeParameterMap.end()
		|| it->second.get() == NULL)
	{
		return false;
	}
	para = *(it->second);

	auto AgentIt = m_cwAgentDataMap.find(szInstrumentID);
	if (AgentIt == m_cwAgentDataMap.end()
		|| AgentIt->second.get() == nullptr)
	{
		return false;
	}
	pAgent = AgentIt->second;

	return true;
}

int cwCTAPlatform::GetExpectedPosition(std::string InstrumentID, TradeParameter& cwTradeParameter)
{

	int iExpectedMaintain = 0;

	std::string SignalInstrumentID = cwTradeParameter.SignalInstrumentID;
	//Get ExpectedMaintain
	auto StrategySignalPosIt = m_cwStrategyPositionMap.find(SignalInstrumentID);
	if (StrategySignalPosIt != m_cwStrategyPositionMap.end())
	{
		double dbInsPos = 0;
		double dbExpectionMaintain = 0.0;
		for (auto it = StrategySignalPosIt->second.begin();
			it != StrategySignalPosIt->second.end(); it++)
		{
			dbInsPos = it->second * cwTradeParameter.Ratio;

			//StrategyInstrumentUnion StrategyInsUnion;
			//StrategyInsUnion.StrategyName = it->first;
			//StrategyInsUnion.InstrumentID = InstrumentID;

			//auto Manualit = m_ManualinterventionMap.find(StrategyInsUnion);
			//if (Manualit != m_ManualinterventionMap.end()
			//	&& Manualit->second.get() != NULL
			//	&& Manualit->second->Manual)
			//{
			//	iExpectedMaintain += Manualit->second->ExpectedPosition;
			//}
			//else
			//{
			//	auto MaskIt = m_DirectionMaskMap.find(StrategyInsUnion);
			//	if (MaskIt != m_DirectionMaskMap.end()
			//		&& MaskIt->second.get() != NULL)
			//	{
			//		if (dbInsPos > 0
			//			&& MaskIt->second->NoLong)
			//		{
			//			dbInsPos = 0;
			//		}
			//		if (dbInsPos < 0
			//			&& MaskIt->second->NoShort)
			//		{
			//			dbInsPos = 0;
			//		}

			//		dbInsPos = dbInsPos * MaskIt->second->StrategyInsRatio;
			//	}

			//	dbExpectionMaintain += dbInsPos;
			//}
			dbExpectionMaintain += dbInsPos;

		}
		if (cwTradeParameter.Mod)
		{
			if (dbExpectionMaintain > cwDouble_EQ)
			{
				iExpectedMaintain += (int)(dbExpectionMaintain);
			}
			else
			{
				iExpectedMaintain += ((int)(-1 * dbExpectionMaintain)) * -1;
			}
		}
		else
		{
			if (dbExpectionMaintain > cwDouble_EQ)
			{
				iExpectedMaintain += (dbExpectionMaintain - (int)(dbExpectionMaintain) > cwDouble_EQ) ? (int)(dbExpectionMaintain)+1 : (int)(dbExpectionMaintain);
			}
			else
			{
				iExpectedMaintain += ((int)(dbExpectionMaintain)-dbExpectionMaintain > cwDouble_EQ) ? (int)(dbExpectionMaintain)-1 : (int)(dbExpectionMaintain);
			}
		}
	}
	else
	{
		iExpectedMaintain = 0;
	}

	return iExpectedMaintain;
}

