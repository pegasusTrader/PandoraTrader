
#include "cwMarketDataReceiver.h"
#include "tinyxml.h"
#include "cwTimeStamp.h"

#ifndef cwDouble_EQ
#include <limits>
#define cwDouble_EQ (std::numeric_limits<double>::epsilon())
#endif // !cwDouble_EQ

#ifndef MAX_PATH
#define MAX_PATH          260
#endif // !MAX_PATH


cwMarketDataReceiver::cwMarketDataReceiver()
	: m_StrategyLog("MarketData")
{
}


cwMarketDataReceiver::~cwMarketDataReceiver()
{
}

std::string cwMarketDataReceiver::GetStrategyName()
{
	std::string strStrategyName("MarketDataReceiver");
	if (m_strStrategyName.size() > 0)
	{
		strStrategyName.append("_");
		strStrategyName.append(m_strStrategyName);
	}
	return strStrategyName;
}

void cwMarketDataReceiver::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}
	m_strCurrentUpdateTime = pPriceData->UpdateTime;
	if ((!m_bStrategyReady))
	{
		//return;
	}

	
	int iTotalVol = 0;
	{
		auto it = m_TotalVolume.find(pPriceData->InstrumentID);
		if (it != m_TotalVolume.end())
		{
			iTotalVol = (int)it->second;
		}
	}
	double dTotalTurnOver = 0.0;
	{
		auto it = m_TotalTurnOver.find(pPriceData->InstrumentID);
		if (it != m_TotalTurnOver.end())
		{
			dTotalTurnOver = it->second;
		}
	}

	if (m_strCurrentUpdateTime.size() <= 3)
	{
		std::cout << pPriceData->InstrumentID << " " << pPriceData->UpdateTime << " UpdateTime Length is Too Small /n";
		return;
	}

	int iHour = atoi(m_strCurrentUpdateTime.substr(0, 2).c_str());

	m_StrategyLog.AddLog(cwStrategyLog::enIMMS,
		"%s,%s,%s,%s,%d,%.3f,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.3f,%.3f,%.3f",
		pPriceData->InstrumentID,
		pPriceData->TradingDay,
		pPriceData->ActionDay,
		pPriceData->UpdateTime,
		pPriceData->UpdateMillisec,
		pPriceData->LastPrice,
		(int)(pPriceData->Volume),
		(int)(pPriceData->Volume - iTotalVol),
		pPriceData->Turnover,
		pPriceData->Turnover - dTotalTurnOver,
		pPriceData->AskPrice5,
		pPriceData->AskPrice4,
		pPriceData->AskPrice3,
		pPriceData->AskPrice2,
		pPriceData->AskPrice1,
		pPriceData->BidPrice1,
		pPriceData->BidPrice2,
		pPriceData->BidPrice3,
		pPriceData->BidPrice4,
		pPriceData->BidPrice5,
		pPriceData->AskVolume5,
		pPriceData->AskVolume4,
		pPriceData->AskVolume3,
		pPriceData->AskVolume2,
		pPriceData->AskVolume1,
		pPriceData->BidVolume1,
		pPriceData->BidVolume2,
		pPriceData->BidVolume3,
		pPriceData->BidVolume4,
		pPriceData->BidVolume5,
		pPriceData->OpenInterest,
		pPriceData->UpperLimitPrice,
		pPriceData->LowerLimitPrice);

	m_TotalVolume[pPriceData->InstrumentID] = pPriceData->Volume;
	m_TotalTurnOver[pPriceData->InstrumentID] = pPriceData->Turnover;
}

void cwMarketDataReceiver::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindle)
{
}


void cwMarketDataReceiver::InitialStrategy(const char * pConfigFilePath)
{
	if (pConfigFilePath == NULL
		|| strlen(pConfigFilePath) == 0)
	{
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

		m_strConfigFileFullPath = exeFullPath;
		std::size_t found = m_strConfigFileFullPath.find_last_of("/\\");
		m_strConfigFileFullPath = m_strConfigFileFullPath.substr(0, found);
		m_strConfigFileFullPath.append("\\Instrument.xml");
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
		m_strConfigFileFullPath.append("/Instrument.xml");
#endif		
	}
	else
	{
		m_strConfigFileFullPath = pConfigFilePath;
	}

	m_strCurrentMdFilePath = m_StrategyLog.GetLogFileName();

	m_StrategyLog.AddTitle("Localtime,MD,InstrumentID,TradingDay,ActionDay,UpdateTime,UpdateMillisec,LastPrice,Volume,LastVolume,Turnover,LastTurnover,AskPrice5,AskPrice4,AskPrice3,AskPrice2,AskPrice1,BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,AskVolume5,AskVolume4,AskVolume3,AskVolume2,AskVolume1,BidVolume1,BidVolume2,BidVolume3,BidVolume4,BidVolume5,OpenInterest,UpperLimitPrice,LowerLimitPrice");
}

void cwMarketDataReceiver::OnReady()
{
	if(m_bSaveInstrument)
	{
		//创建一个XML的文档对象。
		TiXmlDocument *myDocument = new TiXmlDocument();

		TiXmlDeclaration * pDeclaration = new TiXmlDeclaration("1.0", "", "");
		myDocument->LinkEndChild(pDeclaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement = new TiXmlElement("Instruments");
		myDocument->LinkEndChild(RootElement);

		std::string Temp;

		for (auto itIns = m_InstrumentMap.begin();
			itIns != m_InstrumentMap.end(); itIns++)
		{
			//创建一个Person元素并连接。
			TiXmlElement *PersonElement = new TiXmlElement("Instrument");
			RootElement->LinkEndChild(PersonElement);

			//设置Person元素的属性。
			PersonElement->SetAttribute("ExchangeID", itIns->second->ExchangeID);
			PersonElement->SetAttribute("InstrumentID", itIns->second->InstrumentID);
			PersonElement->SetAttribute("InstrumentName", itIns->second->InstrumentName);
			PersonElement->SetAttribute("ProductID", itIns->second->ProductID);

			Temp = itIns->second->ProductClass;
			PersonElement->SetAttribute("ProductClass", Temp.c_str());

			PersonElement->SetAttribute("CreateDate", itIns->second->CreateDate);
			PersonElement->SetAttribute("OpenDate", itIns->second->OpenDate);
			PersonElement->SetAttribute("ExpireDate", itIns->second->ExpireDate);

			Temp = itIns->second->Currency;
			PersonElement->SetAttribute("Currency", Temp.c_str());
			Temp = itIns->second->OptionsType;
			PersonElement->SetAttribute("OptionsType", Temp.c_str());

			PersonElement->SetAttribute("StartDelivDate", itIns->second->StartDelivDate);
			PersonElement->SetAttribute("EndDelivDate", itIns->second->EndDelivDate);

			Temp = itIns->second->PositionType;
			PersonElement->SetAttribute("PositionType", Temp.c_str());
			Temp = itIns->second->MaxMarginSideAlgorithm;
			PersonElement->SetAttribute("MaxMarginSideAlgorithm", Temp.c_str());

			PersonElement->SetAttribute("UnderlyingInstrID", itIns->second->UnderlyingInstrID);
			PersonElement->SetDoubleAttribute("UnderlyingMultiple", itIns->second->UnderlyingMultiple);
			PersonElement->SetAttribute("DeliveryYear", itIns->second->DeliveryYear);
			PersonElement->SetAttribute("DeliveryMonth", itIns->second->DeliveryMonth);
			PersonElement->SetAttribute("MaxMarketOrderVolume", itIns->second->MaxMarketOrderVolume);
			PersonElement->SetAttribute("MinMarketOrderVolume", itIns->second->MinMarketOrderVolume);
			PersonElement->SetAttribute("MaxLimitOrderVolume", itIns->second->MaxLimitOrderVolume);
			PersonElement->SetAttribute("MinLimitOrderVolume", itIns->second->MinLimitOrderVolume);
			PersonElement->SetAttribute("IsTrading", itIns->second->IsTrading);
			PersonElement->SetAttribute("VolumeMultiple", itIns->second->VolumeMultiple);
			PersonElement->SetDoubleAttribute("PriceTick", itIns->second->PriceTick);
			PersonElement->SetDoubleAttribute("StrikePrice", itIns->second->StrikePrice);
		}
		std::string strSaveFile = m_strConfigFileFullPath;

		std::size_t found = strSaveFile.find_last_of("/\\");
		strSaveFile = strSaveFile.substr(0, found);

#ifdef _MSC_VER
		strSaveFile.append("\\Instrument.xml");
#else
		strSaveFile.append("/Instrument.xml");
#endif


		myDocument->SaveFile(strSaveFile.c_str());
	}

	//Sleep(5000);
	//Init HisPrice Data Map
	{
		std::string strSaveFile = m_strConfigFileFullPath;

		std::size_t found = strSaveFile.find_last_of("/\\");
		strSaveFile = strSaveFile.substr(0, found);

#ifdef _MSC_VER
		strSaveFile.append("\\HisMarketDataIndex.xml");
#else
		strSaveFile.append("/HisMarketDataIndex.xml");
#endif

		m_strdateIndexId = m_strAppStartDay;
		if (m_bNightMode)
		{
			m_strdateIndexId.append("1");
		}
		else
		{
			m_strdateIndexId.append("0");
		}

		TiXmlDocument doc(strSaveFile.c_str());
		bool loadOkay = doc.LoadFile(TIXML_ENCODING_LEGACY);

		if (!loadOkay)
		{
			//创建一个XML的文档对象。
			TiXmlDocument *myDocument = new TiXmlDocument();

			TiXmlDeclaration * pDeclaration = new TiXmlDeclaration("1.0", "", "");
			myDocument->LinkEndChild(pDeclaration);

			//创建一个根元素并连接。
			TiXmlElement *RootElement = new TiXmlElement("HisMDFiles");
			myDocument->LinkEndChild(RootElement);

			TiXmlElement *ChildElement = new TiXmlElement("MDFile");
			RootElement->LinkEndChild(ChildElement);

			ChildElement->SetAttribute("DateIndexId", m_strdateIndexId.c_str());
			ChildElement->SetAttribute("FilePath", m_strCurrentMdFilePath.c_str());
			myDocument->SaveFile(strSaveFile.c_str());
		}
		else
		{
			TiXmlNode* RootNode = doc.RootElement();
			if (RootNode != NULL)
			{
				std::string DataIndexid, FilePath;
				const char * pszTemp = NULL;

				TiXmlNode* ChildNode = RootNode->FirstChild("MDFile");
				while (ChildNode != NULL)
				{
					TiXmlElement * ChildElement = ChildNode->ToElement();
					pszTemp = ChildElement->Attribute("DateIndexId");
					if (pszTemp != NULL)
					{
						DataIndexid = pszTemp;
					}
					else
					{
						ChildNode = ChildNode->NextSibling("MDFile");
						continue;
					}

					FilePath = ChildElement->Attribute("FilePath");
					if (pszTemp != NULL)
					{
						FilePath = pszTemp;
					}
					else
					{
						ChildNode = ChildNode->NextSibling("MDFile");
						continue;
					}

					m_HisMdFileIndex[DataIndexid] = FilePath;

					ChildNode = ChildNode->NextSibling("MDFile");
				}

				TiXmlElement *ChildElement = new TiXmlElement("MDFile");
				RootNode->LinkEndChild(ChildElement);

				ChildElement->SetAttribute("DateIndexId", m_strdateIndexId.c_str());
				ChildElement->SetAttribute("FilePath", m_strCurrentMdFilePath.c_str());

				doc.SaveFile(strSaveFile.c_str());

				m_HisMdFileIndex[m_strdateIndexId] = m_strCurrentMdFilePath;

			}
		}
	}


	std::vector<std::string> SubscribeInstrument;

	for (auto it = m_InstrumentMap.begin(); it != m_InstrumentMap.end(); it++)
	{
		if (CW_FTDC_PC_Futures == it->second->ProductClass)
		{
			SubscribeInstrument.push_back(it->first);
		}

		if (SubscribeInstrument.size() >= 10)
		{
			SubScribePrice(SubscribeInstrument);

			SubscribeInstrument.clear();
		}
	}
	
	SubScribePrice(SubscribeInstrument);
}
