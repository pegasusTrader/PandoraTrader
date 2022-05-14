#include "cwChasingRisingStrategy.h"
#include "tinyxml.h"


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
}

void cwChasingRisingStrategy::OnReady()
{
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
		double dbTemp;
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

