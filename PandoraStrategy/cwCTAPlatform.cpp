#include "cwCTAPlatform.h"
#include "cwStrategyCommon.h"
#include "tinyxml.h"

#ifndef cwDouble_EQ
#include <limits>
#define cwDouble_EQ (std::numeric_limits<double>::epsilon())
#endif // !cwDouble_EQ


std::string cwCTAPlatform::GetStrategyVersion()
{
	return "20221111_v1";
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
	m_strCurrentUpdateTime = pPriceData->UpdateTime;

	auto Insit = m_InsCTAStrategyList.find(pPriceData->InstrumentID);
	if (Insit != m_InsCTAStrategyList.end())
	{
		for (auto Listit = Insit->second.begin();
			Listit != Insit->second.end(); Listit++)
		{
			cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries = GetKindleSeries(pPriceData->InstrumentID, Listit->first);
			for (auto it = Listit->second.begin();
				it != Listit->second.end(); it++)
			{
				(*it)->_pStrategy->m_strLastUpdateTime = pPriceData->ActionDay;
				(*it)->_pStrategy->m_strLastUpdateTime.append("_");
				(*it)->_pStrategy->m_strLastUpdateTime.append(pPriceData->UpdateTime);

				(*it)->_pStrategy->_OnBar(false, Listit->first, pKindleSeries);;
			}
		}
	}

	MergeStrategyPosition(pPriceData->InstrumentID);

	if (!GetParameter(pPriceData->InstrumentID))
	{
		return;
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
		m_pAgentData->pPositionAgent->SetAgentWorking(false);
	}
	else
	{
		if (iClose > 1)
		{
			m_pAgentData->pPositionAgent->SetAgentWorking(true);
		}
		else
		{
			m_pAgentData->pPositionAgent->SetAgentWorking(false);
		}
	}

	int iExpecetedPosition = GetExpectedPosition(pPriceData->InstrumentID);
	m_pAgentData->pPositionAgent->SetExpectPosition(iExpecetedPosition);

}

void cwCTAPlatform::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	auto Insit = m_InsCTAStrategyList.find(pKindleSeries->GetInstrumentID());
	if (Insit != m_InsCTAStrategyList.end())
	{
		auto Listit = Insit->second.find(iTimeScale);
		if (Listit != Insit->second.end())
		{
			for (auto it = Listit->second.begin();
				it != Listit->second.end(); it++)
			{
				cwKindleStickPtr pKindle = pKindleSeries->GetLastKindleStick();
				(*it)->_pStrategy->m_strLastUpdateTime = pKindle->szStartTime;

				(*it)->_pStrategy->_OnBar(pKindleSeries->m_bIsNewKindle, iTimeScale, pKindleSeries);
			}
		}
	}

	MergeStrategyPosition(pKindleSeries->GetInstrumentID());

	if (!GetParameter(pPriceData->InstrumentID)
		|| m_strCurrentUpdateTime.size() <= 0)
	{
		return;
	}

	int iExpecetedPosition = GetExpectedPosition(pPriceData->InstrumentID);
	m_pAgentData->pPositionAgent->SetExpectPosition(iExpecetedPosition);

}

void cwCTAPlatform::OnReady()
{
	SetAgentManager(dynamic_cast<cwAgentManager*>(&m_PandoraAgentManager));
	unsigned int folioId = 0;
	for (auto it = m_TradeParameterMap.begin();
		it != m_TradeParameterMap.end(); it++)
	{
		m_pAgentData = m_PandoraAgentManager.RegisterAgent(it->second->InstrumentID, cwPandoraAgentManager::Enum_Agent_Postion);
		if (m_pAgentData.get() != NULL
			&& m_pAgentData->pPositionAgent.get() != NULL)
		{
			m_cwAgentDataMap[it->second->InstrumentID] = m_pAgentData;

			//设置算法参数
			m_pAgentData->pPositionAgent->InsLargeOrderVolume = 100;
			m_pAgentData->pPositionAgent->InsLittleOrderVolume = 5;
			m_pAgentData->pPositionAgent->InsAskBidGap = 1;

			m_pAgentData->pPositionAgent->SetAgentWorking(false);
		}
		SetPortfolioId(it->second->InstrumentID.c_str(), folioId++);
	}
	//m_pAgentData = m_PandoraAgentManager.RegisterAgent(it->second->Instrument, cwPandoraAgentManager::Enum_Agent_Postion);
	//if (m_pAgentData.get() != NULL
	//	&& m_pAgentData->pPositionAgent.get() != NULL)
	//{
	//	m_cwAgentDataMap[it->second->Instrument] = m_pAgentData;

	//	//设置算法参数
	//	m_pAgentData->pPositionAgent->InsLargeOrderVolume = 100;
	//	m_pAgentData->pPositionAgent->InsLittleOrderVolume = 5;
	//	m_pAgentData->pPositionAgent->InsAskBidGap = 1;

	//	m_pAgentData->pPositionAgent->SetAgentWorking(false);

	//	//m_pAgentData->pPositionAgent->SetExpectPosition(GetNetPosition(it->second->Instrument));
	//}

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

	cwBasicCTAStrategy* pStrategy = nullptr;
	for (auto it = m_StrategyParameterMap.begin();
		it != m_StrategyParameterMap.end(); it++)
	{
		if (it->second->StrategyName == "DualTrust")
		{
			pStrategy = dynamic_cast<cwBasicCTAStrategy*>(new cwDualTrust(it->second->StrategyID.c_str()));
		}
		//Add Your Strategy Initial here!

		if (pStrategy == nullptr)
		{
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
		pStrategy->InitialStrategy();

		AddStrategyToPools(it->second->StrategyID.c_str(), pStrategy, it->second);
		SetKindle(it->second->StrategyID.c_str(),
			it->second->bIndex,
			it->second->InstrumentID.c_str(),
			it->second->iTimeScale,
			100);
	}

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
	int iCount = pKindle->GetKindleSize();
	m_cwShow.AddLog("Get %s HisKindle Count:%d", pKindle->GetInstrumentID(), iCount);
//	cwMarketDataPtr dataPtr = std::make_shared<cwFtdcDepthMarketDataField>();;
//
//	{
//		cwInstrumentDataPtr pIns = GetInstrumentData(pKindle->GetInstrumentID());
//		
//		memset(dataPtr.get(), 0, sizeof(cwFtdcDepthMarketDataField));
//#ifdef _MSC_VER
//		if (pIns.get() != nullptr)
//		{
//			memcpy_s(dataPtr->ExchangeID, sizeof(dataPtr->ExchangeID), pIns->ExchangeID, sizeof(pIns->ExchangeID));
//		}
//		//memcpy_s(dataPtr->TradingDay, sizeof(dataPtr->TradingDay), pDepthMarketData->TradingDay, sizeof(pDepthMarketData->TradingDay));
//		//memcpy_s(dataPtr->ActionDay, sizeof(dataPtr->ActionDay), pDepthMarketData->ActionDay, sizeof(pDepthMarketData->ActionDay));
//		//memcpy_s(dataPtr->UpdateTime, sizeof(dataPtr->UpdateTime), pDepthMarketData->UpdateTime, sizeof(pDepthMarketData->UpdateTime));
//		memcpy_s(dataPtr->InstrumentID, sizeof(dataPtr->InstrumentID), pKindle->GetInstrumentID(), sizeof(pKindle->GetInstrumentID()));
//#else
//		if (pIns.get() != nullptr)
//		{
//			memcpy(dataPtr->ExchangeID, pDepthMarketData->ExchangeID, sizeof(pIns->ExchangeID));
//		}
//		//memcpy(dataPtr->TradingDay, pDepthMarketData->TradingDay, sizeof(pDepthMarketData->TradingDay));
//		//memcpy(dataPtr->ActionDay, pDepthMarketData->ActionDay, sizeof(pDepthMarketData->ActionDay));
//		//memcpy(dataPtr->UpdateTime, pDepthMarketData->UpdateTime, sizeof(pDepthMarketData->UpdateTime));
//		memcpy(dataPtr->InstrumentID, pKindle->GetInstrumentID(), sizeof(pKindle->GetInstrumentID()));
//#endif
//		//dataPtr->UpdateMillisec = pDepthMarketData->UpdateMillisec;
//
//		//dataPtr->BidPrice1 = pDepthMarketData->BidPrice1;
//		//dataPtr->BidPrice2 = pDepthMarketData->BidPrice2;
//		//dataPtr->BidPrice3 = pDepthMarketData->BidPrice3;
//		//dataPtr->BidPrice4 = pDepthMarketData->BidPrice4;
//		//dataPtr->BidPrice5 = pDepthMarketData->BidPrice5;
//
//		dataPtr->BidVolume1 = 0;
//		//dataPtr->BidVolume2 = pDepthMarketData->BidVolume2;
//		//dataPtr->BidVolume3 = pDepthMarketData->BidVolume3;
//		//dataPtr->BidVolume4 = pDepthMarketData->BidVolume4;
//		//dataPtr->BidVolume5 = pDepthMarketData->BidVolume5;
//
//		//dataPtr->AskPrice1 = pDepthMarketData->AskPrice1;
//		//dataPtr->AskPrice2 = pDepthMarketData->AskPrice2;
//		//dataPtr->AskPrice3 = pDepthMarketData->AskPrice3;
//		//dataPtr->AskPrice4 = pDepthMarketData->AskPrice4;
//		//dataPtr->AskPrice5 = pDepthMarketData->AskPrice5;
//
//		dataPtr->AskVolume1 = 0;
//		//dataPtr->AskVolume2 = pDepthMarketData->AskVolume2;
//		//dataPtr->AskVolume3 = pDepthMarketData->AskVolume3;
//		//dataPtr->AskVolume4 = pDepthMarketData->AskVolume4;
//		//dataPtr->AskVolume5 = pDepthMarketData->AskVolume5;
//
//		//dataPtr->LastPrice = pDepthMarketData->LastPrice;
//		//dataPtr->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
//		//dataPtr->PreClosePrice = pDepthMarketData->PreClosePrice;
//		//dataPtr->PreOpenInterest = pDepthMarketData->PreOpenInterest;
//		//dataPtr->PreDelta = pDepthMarketData->PreDelta;
//
//		//dataPtr->Volume = pDepthMarketData->Volume;
//		//dataPtr->Turnover = pDepthMarketData->Turnover;
//		//dataPtr->OpenInterest = pDepthMarketData->OpenInterest;
//
//		//dataPtr->OpenPrice = pDepthMarketData->OpenPrice;
//		//dataPtr->HighestPrice = pDepthMarketData->HighestPrice;
//		//dataPtr->LowestPrice = pDepthMarketData->LowestPrice;
//		//dataPtr->ClosePrice = pDepthMarketData->ClosePrice;
//		//dataPtr->SettlementPrice = pDepthMarketData->SettlementPrice;
//		//dataPtr->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
//		//dataPtr->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
//
//		//dataPtr->CurrDelta = pDepthMarketData->CurrDelta;
//		//dataPtr->AveragePrice = pDepthMarketData->AveragePrice;
//
//	}
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
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_OnBar(false, iTimeScale, pHisKindle);


		pTmpKindle->Close = pTmpKindle->Low = pkindleStick->Low;
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_OnBar(false, iTimeScale, pHisKindle);

		pTmpKindle->Close = pTmpKindle->High = pkindleStick->High;
		pHisKindle->UpdateKindle(pTmpKindle);
		pStrategyInfo->_pStrategy->_OnBar(false, iTimeScale, pHisKindle);

		pHisKindle->UpdateKindle(pkindleStick);

		pStrategyInfo->_pStrategy->_OnBar(true, iTimeScale, pHisKindle);

		//OnBar(dataPtr, iTimeScale, pHisKindle);

	}
}

int cwCTAPlatform::MergeStrategyPosition(std::string InstrumentID)
{
	int iPosition = 0;
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
					m_cwStrategyPositionMap[InstrumentID][(*it)->_StrategyID]
						= Posit->second * (*it)->_pParameter->dMultiple;
					iPosition += Posit->second * (*it)->_pParameter->dMultiple;
				}
			}
		}
	}
	return iPosition;
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

bool cwCTAPlatform::GetParameter(const char * szInstrumentID)
{
	if (!m_bStrategyReady)
	{
		return false;
	}
	cwAUTOMUTEX mt(m_ParameterMutex, true);

	auto it	= m_TradeParameterMap.find(szInstrumentID);
	if (it == m_TradeParameterMap.end()
		|| it->second.get() == NULL)
	{
		return false;
	}
	m_cwTradeParameter = *(it->second);

	auto AgentIt = m_cwAgentDataMap.find(szInstrumentID);
	if (AgentIt == m_cwAgentDataMap.end()
		|| AgentIt->second.get() == nullptr)
	{
		return false;
	}
	m_pAgentData = AgentIt->second;

	return true;
}

int cwCTAPlatform::GetExpectedPosition(std::string InstrumentID)
{

	int iExpectedMaintain = 0;

	std::string SignalInstrumentID = m_cwTradeParameter.SignalInstrumentID;
	//Get ExpectedMaintain
	auto StrategySignalPosIt = m_cwStrategyPositionMap.find(SignalInstrumentID);
	if (StrategySignalPosIt != m_cwStrategyPositionMap.end())
	{
		double dbInsPos = 0;
		double dbExpectionMaintain = 0.0;
		for (auto it = StrategySignalPosIt->second.begin();
			it != StrategySignalPosIt->second.end(); it++)
		{
			dbInsPos = it->second * m_cwTradeParameter.Ratio;

			StrategyInstrumentUnion StrategyInsUnion;
			StrategyInsUnion.StrategyName = it->first;
			StrategyInsUnion.InstrumentID = InstrumentID;

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
		if (m_cwTradeParameter.Mod)
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

