#include "cwFtdMdSpiDemo.h"
#include <limits>
#include <float.h>
#include <functional>
#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif

cwFtdMdSpiDemo::cwFtdMdSpiDemo(void)
	: cwBasicMdSpi(cwMDAPIType::cwMD_CTP)
	, m_pMarketDataUserApi(NULL)
	, m_iSubscribeCountOnce(25)
	, m_iRequestId(0)
{
	memset(&m_ReqUserLoginField, 0, sizeof(m_ReqUserLoginField));
	memset(m_szMDFrount, 0, sizeof(m_szMDFrount));

	m_iMdAPIIndex = m_iMdApiCount;
}


cwFtdMdSpiDemo::~cwFtdMdSpiDemo(void)
{
	DisConnect();
}

void cwFtdMdSpiDemo::Connect(const char * pszFrontAddress, const char * pszLocalAddr)
{
	if (pszFrontAddress != NULL)
	{
#ifdef _MSC_VER
		strncpy_s(m_szMDFrount, pszFrontAddress, strlen(pszFrontAddress));
#else
		strncpy(m_szMDFrount, pszFrontAddress, strlen(pszFrontAddress));
#endif // _MSC_VER
	}

	if (m_pMarketDataUserApi)
	{
		DisConnect();
	}
	char exeFullPath[MAX_PATH];
	struct stat buf;

#ifdef _MSC_VER

#ifdef UNICODE
	TCHAR TexeFullPath[MAX_PATH];
	::GetModuleFileName(NULL, TexeFullPath, MAX_PATH);

	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, exeFullPath, iLength, NULL, NULL);
#else
	::GetModuleFileName(NULL, exeFullPath, MAX_PATH);
#endif // UNICODE

	std::string strFullPath = exeFullPath;
	strFullPath = strFullPath.substr(0, strFullPath.rfind('\\'));
	strFullPath.append("\\Quotes\\");

	if (stat(strFullPath.c_str(), &buf) != 0)
	{
		_mkdir(strFullPath.c_str());
	}

	strFullPath.append(std::to_string(m_iMdAPIIndex));
	strFullPath.append("\\");
#else
	size_t cnt = readlink("/proc/self/exe", exeFullPath, MAX_PATH);
	if (cnt < 0 || cnt >= MAX_PATH)
	{
		printf("***Error***\n");
		exit(-1);
	}

	std::string strFullPath = exeFullPath;
	strFullPath = strFullPath.substr(0, strFullPath.rfind('/'));
	strFullPath.append("/Quotes/");

	if (stat(strFullPath.c_str(), &buf) != 0)
	{
		mkdir(strFullPath.c_str(), 0755);
	}

	strFullPath.append(std::to_string(m_iMdAPIIndex));
	strFullPath.append("/");
#endif

	if (stat(strFullPath.c_str(), &buf) != 0)
	{
#ifdef _MSC_VER
		_mkdir(strFullPath.c_str());
#else
		mkdir(strFullPath.c_str(), 0755);
#endif
	}

	m_pMarketDataUserApi = CThostFtdcMdApi::CreateFtdcMdApi(strFullPath.c_str(), false);

	if (m_pMarketDataUserApi == NULL
		|| strlen(m_szMDFrount) <= 0)
	{
#ifdef CWCOUTINFO
		m_cwShow.AddLog("Create Md Api Failed!");
#endif
		return;
	}

#ifdef CWCOUTINFO
	m_cwShow.AddLog("%s Version: %s",
		g_cwGetMdApiName(m_cwMdAPIType),
		m_pMarketDataUserApi->GetApiVersion());

	//std::cout << g_cwGetMdApiName(m_cwMdAPIType) << " Version:" << m_pMarketDataUserApi->GetApiVersion() << std::endl;
#endif
	m_pMarketDataUserApi->RegisterSpi((CThostFtdcMdSpi *)this);

	m_pMarketDataUserApi->RegisterFront(m_szMDFrount);
	m_pMarketDataUserApi->Init();
}

void cwFtdMdSpiDemo::DisConnect()
{
	if (m_pMarketDataUserApi != NULL)
	{
		m_pMarketDataUserApi->RegisterSpi(NULL);
		m_pMarketDataUserApi->Release();

		m_pMarketDataUserApi = NULL;
	}
	m_CurrentStatus = PriceServerStatus::Status_UnConnected;

}

void cwFtdMdSpiDemo::WaitForFinish()
{
	if (m_pMarketDataUserApi != nullptr)
	{
		m_pMarketDataUserApi->Join();
	}
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void cwFtdMdSpiDemo:: OnFrontConnected()
{
	if (m_pMarketDataUserApi == nullptr)
	{
		return;
	}

	m_CurrentStatus = PriceServerStatus::Status_Connected;

	int ret = m_pMarketDataUserApi->ReqUserLogin(&m_ReqUserLoginField, ++m_iRequestId);
	switch (ret)
	{
	case 0:
		//success 发送成功
		break;
	case -1:
		//Send failed because of network 网络原因发送失败
		break;
	case -2:
		//too much request to handle 未处理请求队列总数量超限
		break;
	case -3:
		//Send request too much per second 每秒发送请求超限
		break;
	default:
		break;
	}
#ifdef CWCOUTINFO
	m_cwShow.AddLog("Md: OnFrontConnected");
	//std::cout << "Md: OnFrontConnected" << std::endl;
#endif
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void cwFtdMdSpiDemo::OnFrontDisconnected(int nReason)
{
	m_bMarketDataUpdateThreadRun = false;
	while (m_CurrentStatus == PriceServerStatus::Status_Logined)
	{
		if (!m_MarketDataUpdateThread.joinable())
		{
			cwSleep(10);
		}
		else
		{
			m_MarketDataUpdateThread.detach();
			break;
		}
	}

	m_CurrentStatus = PriceServerStatus::Status_UnConnected;
	//DisConnect();

	//Sleep(3000);

	//Connect(m_szMDFrount);
#ifdef CWCOUTINFO
	m_cwShow.AddLog("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMd: OnFrontDisconnected!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << "Md: OnFrontDisconnected!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

	for (auto it = m_SubscribeInstrumentMap.begin(); it != m_SubscribeInstrumentMap.end(); it++)
	{
		it->second = false;
	}
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void cwFtdMdSpiDemo::OnHeartBeatWarning(int nTimeLapse)
{
}
	

///登录请求响应
void cwFtdMdSpiDemo::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo && pRspInfo->ErrorID == 0)
	{
		m_CurrentStatus = PriceServerStatus::Status_Logined;

		std::vector<std::string> WantToSubscribeIns;
		std::map<std::string, bool>::iterator it = m_SubscribeInstrumentMap.begin();
		for (; it != m_SubscribeInstrumentMap.end(); it++)
		{
			//if (!it->second)
			//{
				WantToSubscribeIns.push_back(it->first);
			//}
		}

		SubscribeMarketData(WantToSubscribeIns);
	}
}

	///登出请求响应
void cwFtdMdSpiDemo::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

	///错误应答
void cwFtdMdSpiDemo::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

}

	///订阅行情应答
 void cwFtdMdSpiDemo::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
 {
	 if (pSpecificInstrument != NULL)
	 {
#ifdef CWCOUTINFO
		 m_cwShow.AddLog("OnRspSubMarketData: %d %s", nRequestID, pSpecificInstrument->InstrumentID);
#endif
		// std::cout << nRequestID << " OnRspSubMarketData: " << pSpecificInstrument->InstrumentID << std::endl;
		 if (pRspInfo != NULL
			 && pRspInfo->ErrorID == 0)
		 {
			 m_SubscribeInstrumentMap[pSpecificInstrument->InstrumentID] = true;
		 }
	 }
 }

	///取消订阅行情应答
void cwFtdMdSpiDemo::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pSpecificInstrument != NULL)
	{
#ifdef CWCOUTINFO
		m_cwShow.AddLog("OnRspUnSubMarketData: %d %s", nRequestID, pSpecificInstrument->InstrumentID);
#endif
		//std::cout << nRequestID << " OnRspUnSubMarketData: " << pSpecificInstrument->InstrumentID << std::endl;
		if (pRspInfo != NULL
			&& pRspInfo->ErrorID == 0)
		{
			if (m_SubscribeInstrumentMap.find(pSpecificInstrument->InstrumentID) != m_SubscribeInstrumentMap.end())
			{
				m_SubscribeInstrumentMap.erase(pSpecificInstrument->InstrumentID);
			}
		}
	}
}

	///订阅询价应答
void cwFtdMdSpiDemo::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

}

	///取消订阅询价应答
void cwFtdMdSpiDemo::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
}

	///深度行情通知
void cwFtdMdSpiDemo::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) 
{
	cwMarketDataPtr dataPtr = CreateMarketData();
	if (dataPtr.get() == NULL)
	{
		return;
	}

	memset(dataPtr.get(), 0, sizeof(cwFtdcDepthMarketDataField));
#ifdef _MSC_VER
	memcpy_s(dataPtr->ExchangeID, sizeof(dataPtr->ExchangeID), pDepthMarketData->ExchangeID, sizeof(pDepthMarketData->ExchangeID));
	memcpy_s(dataPtr->TradingDay, sizeof(dataPtr->TradingDay), pDepthMarketData->TradingDay, sizeof(pDepthMarketData->TradingDay));
	memcpy_s(dataPtr->ActionDay, sizeof(dataPtr->ActionDay), pDepthMarketData->ActionDay, sizeof(pDepthMarketData->ActionDay));
	memcpy_s(dataPtr->UpdateTime, sizeof(dataPtr->UpdateTime), pDepthMarketData->UpdateTime, sizeof(pDepthMarketData->UpdateTime));
	memcpy_s(dataPtr->InstrumentID, sizeof(dataPtr->InstrumentID), pDepthMarketData->InstrumentID, sizeof(pDepthMarketData->InstrumentID));
#else
	memcpy(dataPtr->ExchangeID, pDepthMarketData->ExchangeID, sizeof(pDepthMarketData->ExchangeID));
	memcpy(dataPtr->TradingDay, pDepthMarketData->TradingDay, sizeof(pDepthMarketData->TradingDay));
	memcpy(dataPtr->ActionDay, pDepthMarketData->ActionDay, sizeof(pDepthMarketData->ActionDay));
	memcpy(dataPtr->UpdateTime, pDepthMarketData->UpdateTime, sizeof(pDepthMarketData->UpdateTime));
	memcpy(dataPtr->InstrumentID, pDepthMarketData->InstrumentID, sizeof(pDepthMarketData->InstrumentID));
#endif
	dataPtr->UpdateMillisec = pDepthMarketData->UpdateMillisec;

	dataPtr->BidPrice1 = pDepthMarketData->BidPrice1;
	dataPtr->BidPrice2 = pDepthMarketData->BidPrice2;
	dataPtr->BidPrice3 = pDepthMarketData->BidPrice3;
	dataPtr->BidPrice4 = pDepthMarketData->BidPrice4;
	dataPtr->BidPrice5 = pDepthMarketData->BidPrice5;

	dataPtr->BidVolume1 = pDepthMarketData->BidVolume1;
	dataPtr->BidVolume2 = pDepthMarketData->BidVolume2;
	dataPtr->BidVolume3 = pDepthMarketData->BidVolume3;
	dataPtr->BidVolume4 = pDepthMarketData->BidVolume4;
	dataPtr->BidVolume5 = pDepthMarketData->BidVolume5;

	dataPtr->AskPrice1 = pDepthMarketData->AskPrice1;
	dataPtr->AskPrice2 = pDepthMarketData->AskPrice2;
	dataPtr->AskPrice3 = pDepthMarketData->AskPrice3;
	dataPtr->AskPrice4 = pDepthMarketData->AskPrice4;
	dataPtr->AskPrice5 = pDepthMarketData->AskPrice5;

	dataPtr->AskVolume1 = pDepthMarketData->AskVolume1;
	dataPtr->AskVolume2 = pDepthMarketData->AskVolume2;
	dataPtr->AskVolume3 = pDepthMarketData->AskVolume3;
	dataPtr->AskVolume4 = pDepthMarketData->AskVolume4;
	dataPtr->AskVolume5 = pDepthMarketData->AskVolume5;

	dataPtr->LastPrice = pDepthMarketData->LastPrice;
	dataPtr->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
	dataPtr->PreClosePrice = pDepthMarketData->PreClosePrice;
	dataPtr->PreOpenInterest = pDepthMarketData->PreOpenInterest;
	dataPtr->PreDelta = pDepthMarketData->PreDelta;

	dataPtr->Volume = pDepthMarketData->Volume;
	dataPtr->Turnover = pDepthMarketData->Turnover;
	dataPtr->OpenInterest = pDepthMarketData->OpenInterest;

	dataPtr->OpenPrice = pDepthMarketData->OpenPrice;
	dataPtr->HighestPrice = pDepthMarketData->HighestPrice;
	dataPtr->LowestPrice = pDepthMarketData->LowestPrice;
	dataPtr->ClosePrice = pDepthMarketData->ClosePrice;
	dataPtr->SettlementPrice = pDepthMarketData->SettlementPrice;
	dataPtr->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
	dataPtr->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;

	dataPtr->CurrDelta = pDepthMarketData->CurrDelta;
	dataPtr->AveragePrice = pDepthMarketData->AveragePrice;

	ResetInvalidLevel(dataPtr);

	if (m_pTradeSpi != NULL)
	{
		m_pTradeSpi->PriceUpdate(dataPtr);
	}
	if (m_pBasicStrategy != NULL)
	{
		m_pBasicStrategy->_PriceUpdate(dataPtr);
	}

	m_LastestMarketDataMap[dataPtr->InstrumentID] = dataPtr;

}

	///询价通知
void cwFtdMdSpiDemo::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) 
{
}

void cwFtdMdSpiDemo::RegisterStrategy(cwBasicStrategy * pBasicStrategy)
{
	m_pBasicStrategy = pBasicStrategy;
	if (m_pBasicStrategy != NULL)
	{
		m_pBasicStrategy->_SetMdSpi(m_cwMdAPIType, dynamic_cast<cwBasicMdSpi*>(this));
	}
}


void cwFtdMdSpiDemo::SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword)
{
#ifdef _MSC_VER
	strcpy_s(m_ReqUserLoginField.UserProductInfo, INTERFACENAME);
#else
	strcpy(m_ReqUserLoginField.UserProductInfo, INTERFACENAME);
#endif // _MSC_VER

	if (szBrokerID != NULL)
	{
#ifdef _MSC_VER
		strcpy_s(m_ReqUserLoginField.BrokerID, szBrokerID);
#else
		strcpy(m_ReqUserLoginField.BrokerID, szBrokerID);
#endif // _MSC_VER
	}
	if (szUserID != NULL)
	{
#ifdef _MSC_VER
		strcpy_s(m_ReqUserLoginField.UserID, szUserID);
#else
		strcpy(m_ReqUserLoginField.UserID, szUserID);
#endif // _MSC_VER
	}
	if (szPassword != NULL)
	{
#ifdef _MSC_VER
		strcpy_s(m_ReqUserLoginField.Password, szPassword);
#else
		strcpy(m_ReqUserLoginField.Password, szPassword);
#endif // _MSC_VER		
	}
}

void cwFtdMdSpiDemo::SetUserLoginField(CThostFtdcReqUserLoginField& reqUserLoginField)
{
#ifdef _MSC_VER
	memcpy_s(&m_ReqUserLoginField, sizeof(m_ReqUserLoginField), &reqUserLoginField, sizeof(reqUserLoginField));
#else
	memcpy(&m_ReqUserLoginField, &reqUserLoginField, sizeof(reqUserLoginField));
#endif
}

void cwFtdMdSpiDemo::SubscribeMarketData(std::vector<std::string>& SubscribeInstrument)
{
	std::vector<std::string> FailedIns;
	if (m_CurrentStatus == PriceServerStatus::Status_Logined)
	{
		int iLength = (int)SubscribeInstrument.size();
		char ** pArrayOfConracts = new char *[iLength];
		for (int n = 0; n < iLength; n++)
		{
			pArrayOfConracts[n] = new char[InstrumentIDLength];
			memset(pArrayOfConracts[n], 0, InstrumentIDLength);
			
			if (SubscribeInstrument[n].length() > InstrumentIDLength - 1)
			{
				FailedIns.push_back(SubscribeInstrument[n]);
				continue;
			}
			//SubscribeInstrument[n].copy(pArrayOfConracts[n], SubscribeInstrument[n].length());
#ifdef _MSC_VER
			memcpy_s(pArrayOfConracts[n], InstrumentIDLength, SubscribeInstrument[n].c_str(), SubscribeInstrument[n].size());
#else
			memcpy(pArrayOfConracts[n], SubscribeInstrument[n].c_str(), SubscribeInstrument[n].size());
#endif // _MSC_VER

		}

		if (m_pMarketDataUserApi != nullptr)
		{
			m_pMarketDataUserApi->SubscribeMarketData(pArrayOfConracts, iLength);
		}

		for (int n = 0; n < iLength; n++)
		{
			delete [] pArrayOfConracts[n];
		}
		delete[] pArrayOfConracts;
	}
	else
	{
		for (size_t n = 0; n < SubscribeInstrument.size(); n++)
		{
			m_SubscribeInstrumentMap.insert(std::pair<std::string, bool>(SubscribeInstrument[n].c_str(), false));
		}
	}
	SubscribeInstrument = move(FailedIns);
}

void cwFtdMdSpiDemo::UnSubscribeMarketData(std::vector<std::string>& SubscribeInstrument)
{
	std::vector<std::string> FailedIns;
	std::map<std::string, bool>::iterator it;
	for (size_t n = 0; n < SubscribeInstrument.size(); n++)
	{
		it = m_SubscribeInstrumentMap.find(SubscribeInstrument[n]);
		if (it != m_SubscribeInstrumentMap.end())
		{
			if (it->second)
			{
				FailedIns.push_back(SubscribeInstrument[n]);
			}
			m_SubscribeInstrumentMap.erase(it);
		}
	}

	if (m_CurrentStatus == PriceServerStatus::Status_Logined)
	{
		int iLength = (int)FailedIns.size();
		char ** pArrayOfConracts = new char *[iLength];
		for (int n = 0; n < iLength; n++)
		{
			pArrayOfConracts[n] = new char[InstrumentIDLength];
			memset(pArrayOfConracts[n], 0, InstrumentIDLength);

			if (SubscribeInstrument[n].length() > InstrumentIDLength - 1)
			{
				FailedIns.push_back(SubscribeInstrument[n]);
				continue;
			}
			//SubscribeInstrument[n].copy(pArrayOfConracts[n], SubscribeInstrument[n].length());
#ifdef _MSC_VER
			memcpy_s(pArrayOfConracts[n], InstrumentIDLength, SubscribeInstrument[n].c_str(), SubscribeInstrument[n].size());
#else
			memcpy(pArrayOfConracts[n], SubscribeInstrument[n].c_str(), SubscribeInstrument[n].size());
#endif // _MSC_VER

		}

		if (m_pMarketDataUserApi != nullptr)
		{
			m_pMarketDataUserApi->UnSubscribeMarketData(pArrayOfConracts, iLength);
		}

		for (int n = 0; n < iLength; n++)
		{
			delete pArrayOfConracts[n];
		}
		delete[] pArrayOfConracts;
	}
	
}
