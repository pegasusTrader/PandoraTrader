//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include <vector>
#include <string>

#include "cwCommonUtility.h"
#include "cwBasicMdSpi.h"

#ifdef _WIN64
//define something for Windows (64-bit)
#include "CTPTradeApi64\ThostFtdcMdApi.h"
#elif _WIN32
//define something for Windows (32-bit)
#include "CTPTradeApi32\ThostFtdcMdApi.h"
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
// define something for simulator   
#elif TARGET_OS_IPHONE
// define something for iphone  
#else
#define TARGET_OS_OSX 1
// define something for OSX
#endif
#elif __linux__ or _linux
// linux
#include "CTPTradeApiLinux/ThostFtdcMdApi.h"
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#define CW_USING_AUTHCODE


#ifdef WIN32
#ifdef CW_USING_AUTHCODE
#pragma comment(lib, "thostmduserapi_se.lib")
#else
#pragma comment(lib, "thostmduserapi.lib")
#endif
#endif

class cwFtdMdSpi
	: public CThostFtdcMdSpi
	, public cwBasicMdSpi
{

public:
	cwFtdMdSpi(void);
	virtual ~cwFtdMdSpi(void);

public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);
	

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
	
	inline CThostFtdcMdApi * GetUserThostFtdcMdApi() 
	{
		return m_pMarketDataUserApi;
	}

	virtual void RegisterStrategy(cwBasicStrategy * pBasicStrategy);

	void Connect(const char * pszFrontAddress, const char * pszLocalAddr = NULL);
	void DisConnect();

	void WaitForFinish();

	void SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword);
	void SetUserLoginField(CThostFtdcReqUserLoginField& reqUserLoginField);

	virtual void SubscribeMarketData(std::vector<std::string>& SubscribeInstrument);
	virtual void UnSubscribeMarketData(std::vector<std::string>& SubscribeInstrument);

private:

	CThostFtdcMdApi * m_pMarketDataUserApi;

	//User Config Data
	CThostFtdcReqUserLoginField m_ReqUserLoginField;
	char						m_szMDFrount[1024];

	//
	int							m_iRequestId;

	std::map<std::string, bool>	m_SubscribeInstrumentMap;

	int m_iMdAPIIndex;

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwFtdMdSpi);
}; 

