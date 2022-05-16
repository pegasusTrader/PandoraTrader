#include "cwChasingRisingStrategy.h"
#include "tinyxml.h"
#include "cwTimeStamp.h"


std::string cwChasingRisingStrategy::GetStrategyVersion()
{
	return "V0.0.1_20220510";
}


std::string cwChasingRisingStrategy::GetStrategyName()
{
	std::string strStrategyName("ChasingRisingStrategy");
	if (m_strStrategyName.size() > 0)
	{
		strStrategyName.append("_");
		strStrategyName.append(m_strStrategyName);
	}
	return strStrategyName;

}

void cwChasingRisingStrategy::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}
	m_strCurrentUpdateTime = pPriceData->UpdateTime;
	if ((!m_bStrategyReady))
	{
		return;
	}

	ReadXmlConfigFile(m_strConfigFileFullPath.c_str());

	if (!GetParameter(pPriceData->InstrumentID))
	{
		return;
	}

	m_cwRunningParaPtr->LastMarketData = pPriceData;

	ChasingRising();
}

void cwChasingRisingStrategy::OnReady()
{
	m_iDoChasingRisingCount = 0;

	std::vector<std::string> SubscribeInstrument;

	for (auto it = m_StrategyParameterMap.begin();
		it != m_StrategyParameterMap.end(); it++)
	{
		SubscribeInstrument.push_back(it->second->Instrument);
	}

	SubScribePrice(SubscribeInstrument);

}

void cwChasingRisingStrategy::InitialStrategy(const char* pConfigFilePath)
{
	cwEasyStrategyLog log(m_StrategyLog, "InitialStrategy");

	log.AddLog(cwStrategyLog::enIMMS, "%s StrategyVersion: %s", GetStrategyName().c_str(), GetStrategyVersion().c_str());
	m_cwShow.AddLog("%s StrategyVersion: %s", GetStrategyName().c_str(), GetStrategyVersion().c_str());

	char exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);

#ifdef _MSC_VER
	TCHAR TexeFullPath[MAX_PATH];
	::GetModuleFileName(NULL, TexeFullPath, MAX_PATH);

	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, exeFullPath, iLength, NULL, NULL);

	m_strExeFolderPath = exeFullPath;
	std::size_t found = m_strExeFolderPath.find_last_of("/\\");
	m_strExeFolderPath = m_strExeFolderPath.substr(0, found);
#else
	size_t cnt = readlink("/proc/self/exe", exeFullPath, MAX_PATH);
	if (cnt < 0 || cnt >= MAX_PATH)
	{
		printf("***Error***\n");
		exit(-1);
	}

	m_strExeFolderPath = exeFullPath;
	std::size_t found = m_strExeFolderPath.find_last_of("/\\");
	m_strExeFolderPath = m_strExeFolderPath.substr(0, found);
#endif		

	if (pConfigFilePath == NULL
		|| strlen(pConfigFilePath) == 0)
	{
		m_strConfigFileFullPath = m_strExeFolderPath;
		m_strConfigFileFullPath.append("\\cwChasingRisingStrategy.xml");
	}
	else
	{
		m_strConfigFileFullPath = pConfigFilePath;
	}

	cwBasicStrategy::InitalInstrumentData();

	ReadXmlConfigFile(m_strConfigFileFullPath.c_str());

}

bool cwChasingRisingStrategy::ReadXmlConfigFile(const char* pConfigFilePath, bool bNeedDisPlay)
{
	cwEasyStrategyLog log(m_StrategyLog, "ReadXmlConfigFile");

	if (strlen(pConfigFilePath) == 0)
	{
		m_cwShow.AddLog("Open ConfigFilePath Failed !! ConfigFilePath is empty.");
		log.AddLog(cwStrategyLog::enErr, "Open ConfigFilePath Failed !! ConfigFilePath is empty.", false);
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
		m_cwShow.AddLog("Open Strategy config failed, Please make sure the config file is EXIST!");
		return false;
	}

	TiXmlDocument doc(pConfigFilePath);
	bool loadOkay = doc.LoadFile(TIXML_ENCODING_LEGACY);

	if (!loadOkay)
	{
		m_cwShow.AddLog("Strategy: Open ConfigFilePath Failed !! Parse XML File Failed.");
		log.AddLog(cwStrategyLog::enErr, "Strategy: Open ConfigFilePath Failed !! Parse XML File Failed.", false);

		return false;
	}

	if (m_bFirstGetConfig)
	{
		m_bFirstGetConfig = false;
		bNeedDisPlay = false;
	}

	TiXmlNode* RootNode = doc.RootElement();
	if (RootNode != NULL)
	{
		//Save config file Lastest Changed time
		m_tLastestGetConfigTime = statbuf.st_mtime;

		TiXmlElement* RootElement = RootNode->ToElement();
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

		m_strStrategyName = RootElement->Attribute("Name");

		//Read General
		int iTemp;
		//double dbTemp;
		std::string strTemp;
		const char* pszTemp = NULL;
		StrategyParaPtr ParaPtr;
		cwRunningParaPtr RunningParaPtr;
		std::map<std::string, StrategyParaPtr>::iterator it;

		TiXmlNode* ChildNode = RootNode->FirstChild("ChasingRisingStrategy");
		while (ChildNode != NULL)
		{
			TiXmlElement* ChildElement = NULL;

			TiXmlNode* ChasingRisingStrategyChildNode = ChildNode->FirstChild("Instrument");
			if (ChasingRisingStrategyChildNode != NULL)
			{
				TiXmlElement* Element = ChasingRisingStrategyChildNode->ToElement();
				if (Element == NULL)
				{
					goto continueLoop;
				}
				pszTemp = Element->Attribute("ID");
				if (pszTemp != NULL)
				{
					strTemp = pszTemp;
				}
				else
				{
					goto continueLoop;
				}
				it = m_StrategyParameterMap.find(strTemp);
				if (it == m_StrategyParameterMap.end()
					|| it->second.get() == NULL)
				{
					ParaPtr.reset(new StrategyParameter());
					it = m_StrategyParameterMap.insert(std::pair<std::string, StrategyParaPtr>(strTemp, ParaPtr)).first;

					it->second = ParaPtr;
				}
				else
				{
					ParaPtr = it->second;
				}

				ParaPtr->Instrument = it->first;

				{
					auto RunningIt = m_cwRunningParameterMap.find(strTemp);
					if (RunningIt == m_cwRunningParameterMap.end()
						|| RunningIt->second.get() == nullptr)
					{
						RunningParaPtr.reset(new RunningParameter());
						RunningIt = m_cwRunningParameterMap.insert(std::pair<std::string, cwRunningParaPtr>(strTemp, RunningParaPtr)).first;

						RunningIt->second = RunningParaPtr;

					}
					else
					{
						RunningParaPtr = RunningIt->second;
					}
				}

				if (TIXML_SUCCESS == Element->QueryIntAttribute("OpenClose", &iTemp))					
				{
					if (iTemp != (int)ParaPtr->OpenCloseMode)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s OpenCloseMode:%d ==> %d",
								it->first.c_str(), ParaPtr->OpenCloseMode, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s OpenCloseMode : %d ==> %d !", it->first.c_str(), (int)ParaPtr->OpenCloseMode, iTemp);
						ParaPtr->OpenCloseMode = (cwOpenCloseMode)iTemp;
					}
				}
				else
				{
					ParaPtr->OpenCloseMode = CloseTodayThenYd;
				}

				if (TIXML_SUCCESS == Element->QueryIntAttribute("OpenCancelLimit", &iTemp))
				{
					if (iTemp != ParaPtr->OpenCancelLimit)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s OpenCancelLimit:%d ==> %d",
								it->first.c_str(), ParaPtr->OpenCancelLimit, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s CancelLimit : %d ==> %d !", it->first.c_str(), (int)ParaPtr->OpenCancelLimit, iTemp);
						ParaPtr->OpenCancelLimit = iTemp;
					}
				}
				else
				{
					ParaPtr->OpenCancelLimit = 350;
				}

				if (TIXML_SUCCESS == Element->QueryIntAttribute("CloseCancelLimit", &iTemp))
				{
					if (iTemp != ParaPtr->CloseCancelLimit)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s CloseCancelLimit:%d ==> %d",
								it->first.c_str(), ParaPtr->CloseCancelLimit, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s CloseCancelLimit : %d ==> %d !", it->first.c_str(), (int)ParaPtr->CloseCancelLimit, iTemp);
						ParaPtr->CloseCancelLimit = iTemp;
					}
				}
				else
				{
					ParaPtr->CloseCancelLimit = 380;
				}
			}
			else
			{
				goto continueLoop;
			}



			ChasingRisingStrategyChildNode = ChildNode->FirstChild("TotalPositionLimit");
			if (ChasingRisingStrategyChildNode != NULL)
			{
				TiXmlElement* Element = ChasingRisingStrategyChildNode->ToElement();
				if (TIXML_SUCCESS == Element->QueryIntAttribute("value", &iTemp))
				{
					if (iTemp != ParaPtr->TotalPositionLimit)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s TotalPositionLimit:%d ==> %d",
								it->first.c_str(), ParaPtr->TotalPositionLimit, iTemp);

							//std::cout << it->first.c_str() << " TotalPositionLimit: " << ParaPtr->TotalPositionLimit << " ==>" << iTemp << std::endl;
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s TotalPositionLimit : %d ==> %d !", it->first.c_str(), (int)ParaPtr->TotalPositionLimit, iTemp);
						ParaPtr->TotalPositionLimit = iTemp;
					}
				}
				else
				{
					ParaPtr->TotalPositionLimit = 0;
				}
			}

			ChasingRisingStrategyChildNode = ChildNode->FirstChild("OrderVolume");
			if (ChasingRisingStrategyChildNode != NULL)
			{
				TiXmlElement* Element = ChasingRisingStrategyChildNode->ToElement();
				if (TIXML_SUCCESS == Element->QueryIntAttribute("value", &iTemp))
				{
					if (iTemp != ParaPtr->OrderVolume)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s OrderVolume:%d ==> %d",
								it->first.c_str(), ParaPtr->OrderVolume, iTemp);

							//std::cout << it->first.c_str() << " OrderVolume: " << ParaPtr->OrderVolume << " ==>" << iTemp << std::endl;
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s OrderVolume : %d ==> %d !", it->first.c_str(), (int)ParaPtr->OrderVolume, iTemp);
						ParaPtr->OrderVolume = iTemp;
					}
				}
				else
				{
					ParaPtr->OrderVolume = 1;
				}
			}

			ChildElement = ChildNode->ToElement();
			if (ChildElement != NULL)
			{
				if (TIXML_SUCCESS != ChildElement->QueryBoolAttribute("Manual", &loadOkay))
				{
					ParaPtr->Manual = false;
				}
				else
				{
					if (loadOkay != ParaPtr->Manual)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s Manual: %s ==> %s !",
								it->first.c_str(),
								(ParaPtr->Manual ? "true" : "false"),
								(loadOkay ? "true" : "false"));

						}
						log.AddLog(cwStrategyLog::enIMMS, "%s Manual:  ParaPtr->Manual : %s ==> %s !", it->first.c_str(), (ParaPtr->Manual ? "true" : "false"), (loadOkay ? "true" : "false"));
						ParaPtr->Manual = loadOkay;
					}
				}

				if (TIXML_SUCCESS != ChildElement->QueryIntAttribute("Portfolio", &iTemp))
				{
					ParaPtr->Portfolio = m_iDefaultWorkBenchId;
				}
				else
				{
					if (iTemp != ParaPtr->Portfolio)
					{
						if (bNeedDisPlay)
						{
							m_cwShow.AddLog("%s Portfolio:%d ==> %d",
								it->first.c_str(), ParaPtr->Portfolio, iTemp);
						}
						log.AddLog(cwStrategyLog::enIMMS, " %s Portfolio : %d ==> %d !", it->first.c_str(), (int)ParaPtr->Portfolio, iTemp);
						ParaPtr->Portfolio = iTemp;
					}
				}

			}
		continueLoop:
			ChildNode = ChildNode->NextSibling("ChasingRisingStrategy");
		}
	}

	return true;
}

bool cwChasingRisingStrategy::GetParameter(const char* szInstrumentID)
{
	std::string InstrumentID(szInstrumentID);

	auto it = m_StrategyParameterMap.find(InstrumentID);
	if (it == m_StrategyParameterMap.end()
		|| it->second.get() == NULL)
	{
		return false;
	}
	m_cwStrategyParameter = *(it->second);

	auto RunningIt = m_cwRunningParameterMap.find(InstrumentID);
	if (RunningIt == m_cwRunningParameterMap.end()
		|| RunningIt->second.get() == nullptr)
	{
		return false;
	}
	m_cwRunningParaPtr = RunningIt->second;

	return true;
}

void cwChasingRisingStrategy::ChasingRising()
{
	cwEasyStrategyLog log(m_StrategyLog, "ChasingRising", NULL);

	m_iDoChasingRisingCount++;

	if (!m_bStrategyRun)
	{
		return;
	}

	if (m_cwStrategyParameter.Manual)
	{
		//手动干预
		std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
		std::map<std::string, cwOrderPtr> WaitOrderList;
		GetActiveOrders(WaitOrderList);

		for (WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			if (m_cwStrategyParameter.Instrument == (std::string)WaitOrderIt->second->InstrumentID
				&& m_iDoChasingRisingCount % 20 == 0)
			{
				if (WaitOrderIt->second->Direction == CW_FTDC_D_Buy)
				{
					m_cwShow.AddLog("%s B %.3f Ranking:%d",
						m_cwStrategyParameter.Instrument.c_str(),
						WaitOrderIt->second->LimitPrice,
						WaitOrderIt->second->iRanked);
				}
				else
				{
					m_cwShow.AddLog("%s S %.3f Ranking:%d",
						m_cwStrategyParameter.Instrument.c_str(),
						WaitOrderIt->second->LimitPrice,
						WaitOrderIt->second->iRanked);
				}
			}
		}
		return;
	}

	double dTickSize = GetTickSize(m_cwStrategyParameter.Instrument.c_str());
	if (dTickSize < 0)
	{
		return;
	}

	const double dInsEQ = dTickSize / 10;

	std::map<std::string, cwPositionPtr> CurrentPosMap;
	std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
	std::map<std::string, cwOrderPtr> WaitOrderList;
	GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);

	int iMaintain = 0, iOrderCount = 0;
	double dbMainPosPrice = 0, dbSubMainPosPrice = 0;
	std::map<std::string, cwPositionPtr>::iterator PosIt;
	PosIt = CurrentPosMap.find(m_cwStrategyParameter.Instrument);
	if (PosIt != CurrentPosMap.end())
	{
		iMaintain = PosIt->second->GetLongTotalPosition() - PosIt->second->GetShortTotalPosition();

		if (iMaintain > 0)
		{
			dbMainPosPrice = PosIt->second->GetLongAveragePosPrice();
		}
		else
		{
			if (iMaintain < 0)
			{
				dbMainPosPrice = PosIt->second->GetShortAveragePosPrice();
			}
		}
	}
	else
	{
		iMaintain = 0;
	}

	if (m_cwRunningParaPtr->baseTime == 0)
	{
		if (m_cwRunningParaPtr->LastMarketData.get() == NULL)
		{
			return;
		}

		//没有记录的,先赋值
		m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
		m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
		m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;

		m_cwRunningParaPtr->dHighPx = m_cwRunningParaPtr->dLowPx = m_cwRunningParaPtr->LastMarketData->LastPrice;
		m_cwRunningParaPtr->oldTime = m_cwRunningParaPtr->baseTime;
	}
	else
	{
		double d_open = 0.008, d_stop = 0.005;
		if (m_cwRunningParaPtr->bFirst) {
			d_open = m_cwStrategyParameter.dStep;
			d_stop = d_open;
		}
		else {
			d_open = m_cwStrategyParameter.dStep - 0.001;
			d_stop = d_open;
		}

		if (m_cwRunningParaPtr->LastMarketData->LastPrice > m_cwRunningParaPtr->dHighPx)
		{
			m_cwRunningParaPtr->dHighPx = m_cwRunningParaPtr->LastMarketData->LastPrice;
		}

		if (m_cwRunningParaPtr->LastMarketData->LastPrice < m_cwRunningParaPtr->dLowPx)
		{
			m_cwRunningParaPtr->dLowPx = m_cwRunningParaPtr->LastMarketData->LastPrice;
		}

		double upPrice, downPrice;
		if (m_cwRunningParaPtr->bFirst)
		{
			upPrice = m_cwRunningParaPtr->basePrice * (1 + d_open);
			downPrice = m_cwRunningParaPtr->basePrice * (1 - d_open);
		}
		else
		{
			upPrice = m_cwRunningParaPtr->dLowPx * (1 + d_open);
			downPrice = m_cwRunningParaPtr->dHighPx * (1 - d_open);
		}

		//Insert Long
		if (iMaintain < 0)
		{
			
			///当前净持仓为空仓，则平仓, 用平仓参数，平仓条件低于开仓条件
			bool bNeedCancel = false;
			bool bCanOpen = false;

			double dbOrderPrice = dTickSize;

			if (m_cwRunningParaPtr->LastMarketData->LastPrice < m_cwRunningParaPtr->basePrice - dInsEQ)
			{
				//update
				m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
				m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
				m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;

			}
			else
			{
				///最低点反弹则止损止盈 空单
				double upPrice = m_cwRunningParaPtr->dLowPx * (1 + d_stop);

				if (m_cwRunningParaPtr->LastMarketData->LastPrice > upPrice + dInsEQ)
				{
					int64_t Now = TimeToint64(m_cwRunningParaPtr->LastMarketData);

					if (Now - m_cwRunningParaPtr->oldTime > (int64_t)30 * (int64_t)1000000)
					{
						bCanOpen = true;
						dbOrderPrice = m_cwRunningParaPtr->LastMarketData->AskPrice1;

						m_cwRunningParaPtr->bFirst = false;
					}


					//update
					m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
					m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
					m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;

					m_cwRunningParaPtr->dLowPx = m_cwRunningParaPtr->dHighPx = m_cwRunningParaPtr->LastMarketData->LastPrice;
					m_cwRunningParaPtr->oldTime = Now;
				}

			}


			//先检查挂单
			int iSubMainWaitLongOrder = 0;
			for (WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				bNeedCancel = true;
				if (m_cwStrategyParameter.Instrument == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
				{
					bNeedCancel = false;

					if (bNeedCancel
						|| m_cwRunningParaPtr->LastMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
							WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
					}
					iSubMainWaitLongOrder += WaitOrderIt->second->VolumeTotal;
				}
			}

			if (bCanOpen
				&& iSubMainWaitLongOrder == 0
				&& iMaintain + iSubMainWaitLongOrder < 0
				&& dbOrderPrice < m_cwRunningParaPtr->LastMarketData->UpperLimitPrice + dInsEQ
				&& dbOrderPrice > m_cwRunningParaPtr->LastMarketData->LowerLimitPrice - dInsEQ)
			{

				int iVol = -1 * (iSubMainWaitLongOrder + iMaintain);
				if (iVol > m_cwStrategyParameter.OrderVolume)
				{
					iVol = m_cwStrategyParameter.OrderVolume;
				}

				auto orderlist = EasyInputMultiOrder(m_cwStrategyParameter.Instrument.c_str(),
					iVol, dbOrderPrice, m_cwStrategyParameter.OpenCloseMode
					, cwInsertOrderType::cwInsertLimitOrder
				);
				for (auto it = orderlist.begin();
					it != orderlist.end(); it++)
				{
					cwOrderPtr orderptr = *it;
					if (orderptr.get() != NULL)
					{
						WaitOrderList.insert(std::pair<std::string, cwOrderPtr>(orderptr->OrderRef, orderptr));

						log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d, %s, Close", orderptr->InstrumentID, orderptr->OrderRef,
							orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");

					}
				}
			}

		}
		else
		{
			///用开仓参数
			bool bNeedCancel = true;
			bool bCanOpen = false;

			double dbOrderPrice = dTickSize;

			//先检查挂单
			int iSubMainWaitLongOrder = 0;
			for (WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				bNeedCancel = true;
				if (m_cwStrategyParameter.Instrument == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
				{
					if (m_cwRunningParaPtr->LastMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice <= 3 * dTickSize + dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
							WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
					}

					iSubMainWaitLongOrder += WaitOrderIt->second->VolumeTotal;
				}
			}

			if (m_cwRunningParaPtr->LastMarketData->LastPrice > upPrice - dInsEQ)
			{
				dbOrderPrice = m_cwRunningParaPtr->LastMarketData->AskPrice1;
				bCanOpen = true;

				//update
				m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
				m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
				m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;
			}


			if (bCanOpen
				&& iSubMainWaitLongOrder == 0
				&& iMaintain + iSubMainWaitLongOrder < m_cwStrategyParameter.TotalPositionLimit
				&& m_cwRunningParaPtr->LastMarketData->BidPrice1 - m_cwRunningParaPtr->LastMarketData->LowerLimitPrice > dTickSize * 2
				&& m_cwRunningParaPtr->LastMarketData->UpperLimitPrice - m_cwRunningParaPtr->LastMarketData->AskPrice1 > dTickSize * 2
				&& dbOrderPrice < m_cwRunningParaPtr->LastMarketData->UpperLimitPrice + dInsEQ
				&& dbOrderPrice > m_cwRunningParaPtr->LastMarketData->LowerLimitPrice - dInsEQ)
			{
				cwOrderPtr orderptr = EasyInputOrder(m_cwStrategyParameter.Instrument.c_str(),
					m_cwStrategyParameter.OrderVolume, dbOrderPrice, m_cwStrategyParameter.OpenCloseMode);
				if (orderptr.get() != NULL)
				{
					log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
						orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
			}	
		}

		//Insert Short
		if (iMaintain > 0)
		{
			///当前净持仓为空仓，则平仓, 用平仓参数，平仓条件低于开仓条件
			bool bNeedCancel = false;
			bool bCanOpen = false;

			double dbOrderPrice = dTickSize;

			if (m_cwRunningParaPtr->LastMarketData->LastPrice > m_cwRunningParaPtr->basePrice + dInsEQ)
			{
				//update
				m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
				m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
				m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;

			}
			else
			{
				//最高点回落则止损止盈 多单
				double downPrice = m_cwRunningParaPtr->dHighPx * (1 - d_stop);
				if (m_cwRunningParaPtr->LastMarketData->LastPrice < downPrice - dInsEQ)
				{
					int64_t Now = TimeToint64(m_cwRunningParaPtr->LastMarketData);

					if (Now - m_cwRunningParaPtr->oldTime > (int64_t)30 * (int64_t)1000000)
					{
						bCanOpen = true;
						dbOrderPrice = m_cwRunningParaPtr->LastMarketData->BidPrice1;

						m_cwRunningParaPtr->bFirst = false;
					}


					//update
					m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
					m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
					m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;

					m_cwRunningParaPtr->dLowPx = m_cwRunningParaPtr->dHighPx = m_cwRunningParaPtr->LastMarketData->LastPrice;
					m_cwRunningParaPtr->oldTime = Now;
				}

			}

			//先检查挂单
			int iSubMainWaitShortOrder = 0;
			for (WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				bNeedCancel = true;
				if (m_cwStrategyParameter.Instrument == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
				{
					bNeedCancel = false;

					if (bNeedCancel
						|| (WaitOrderIt->second->LimitPrice - m_cwRunningParaPtr->LastMarketData->AskPrice1 > dInsEQ)
						)
					{
						CancelOrder(WaitOrderIt->second);
						log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
							WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
					}
					iSubMainWaitShortOrder -= WaitOrderIt->second->VolumeTotal;
				}
			}

			if (bCanOpen
				&& iSubMainWaitShortOrder == 0
				&& iMaintain + iSubMainWaitShortOrder > 0
				&& dbOrderPrice < m_cwRunningParaPtr->LastMarketData->UpperLimitPrice + dInsEQ
				&& dbOrderPrice > m_cwRunningParaPtr->LastMarketData->LowerLimitPrice - dInsEQ)
			{

				int iVol = iMaintain + iSubMainWaitShortOrder;
				if (iVol > m_cwStrategyParameter.OrderVolume)
				{
					iVol = m_cwStrategyParameter.OrderVolume;
				}

				auto orderlist = EasyInputMultiOrder(m_cwStrategyParameter.Instrument.c_str(),
					iVol * (-1), dbOrderPrice, m_cwStrategyParameter.OpenCloseMode
					, cwInsertOrderType::cwInsertLimitOrder
				);
				for (auto it = orderlist.begin();
					it != orderlist.end(); it++)
				{
					cwOrderPtr orderptr = *it;
					if (orderptr.get() != NULL)
					{
						WaitOrderList.insert(std::pair<std::string, cwOrderPtr>(orderptr->OrderRef, orderptr));

						log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d, %s, Close", orderptr->InstrumentID, orderptr->OrderRef,
							orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");

					}
				}
			}
		}
		else
		{
			///用开仓参数
			bool bNeedCancel = true;
			bool bCanOpen = false;

			double dbOrderPrice = dTickSize;

			//先检查挂单
			int iSubMainWaitShortOrder = 0;
			for (WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				bNeedCancel = true;
				if (m_cwStrategyParameter.Instrument == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
				{
					if (WaitOrderIt->second->LimitPrice - m_cwRunningParaPtr->LastMarketData->AskPrice1 <= 3 * dTickSize + dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
							WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
					}

					iSubMainWaitShortOrder -= WaitOrderIt->second->VolumeTotal;
				}
			}

			if (m_cwRunningParaPtr->LastMarketData->LastPrice < downPrice + dInsEQ)
			{
				dbOrderPrice = m_cwRunningParaPtr->LastMarketData->BidPrice1;
				bCanOpen = true;

				//update
				m_cwRunningParaPtr->strBaseTime = m_cwRunningParaPtr->LastMarketData->UpdateTime;
				m_cwRunningParaPtr->baseTime = TimeToint64(m_cwRunningParaPtr->LastMarketData);
				m_cwRunningParaPtr->basePrice = m_cwRunningParaPtr->LastMarketData->LastPrice;
			}

			if (bCanOpen
				&& iSubMainWaitShortOrder == 0
				&& iMaintain + iSubMainWaitShortOrder > m_cwStrategyParameter.TotalPositionLimit * -1
				&& m_cwRunningParaPtr->LastMarketData->BidPrice1 - m_cwRunningParaPtr->LastMarketData->LowerLimitPrice > dTickSize * 2
				&& m_cwRunningParaPtr->LastMarketData->UpperLimitPrice - m_cwRunningParaPtr->LastMarketData->AskPrice1 > dTickSize * 2
				&& dbOrderPrice <  m_cwRunningParaPtr->LastMarketData->UpperLimitPrice + dInsEQ
				&& dbOrderPrice >  m_cwRunningParaPtr->LastMarketData->LowerLimitPrice - dInsEQ)
			{
				cwOrderPtr orderptr = EasyInputOrder(m_cwStrategyParameter.Instrument.c_str(),
					m_cwStrategyParameter.OrderVolume * (-1), dbOrderPrice, m_cwStrategyParameter.OpenCloseMode);
				if (orderptr.get() != NULL)
				{
					log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
						orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
			}
		}
	}
}

int64_t cwChasingRisingStrategy::TimeToint64(cwMarketDataPtr pData)
{

	cwTimeStamp time;

	std::string ActionDay = pData->ActionDay;
	std::string tradingTime = pData->UpdateTime;

	time.SetYear(atoi(ActionDay.substr(0, 4).c_str()));
	time.SetMonth(atoi(ActionDay.substr(4, 2).c_str()));
	time.SetDay(atoi(ActionDay.substr(6, 2).c_str()));

	int hour = 0, minute = 0, second = 0;
#ifdef _MSC_VER
	sscanf_s(pData->UpdateTime, "%d:%d:%d", &hour, &minute, &second);
#else
	sscanf(pData->UpdateTime, "%d:%d:%d", &hour, &minute, &second);
#endif // _MSC_VER

	time.SetHour(hour);
	time.SetMinute(minute);
	time.SetSecond(second);
	time.SetMicrosecond(pData->UpdateMillisec * 1000);

	return (int64_t)(time.GetTotalMicrosecond());
}

