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
#include "FemasTradeApi64\USTPFtdcMduserApi.h"
#elif _WIN32
//define something for Windows (32-bit)
#include "FemasTradeApi32\USTPFtdcMduserApi.h"
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
#include "FemasTradeApiLinux/USTPFtdcMduserApi.h"
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif


#ifdef WIN32
#pragma comment(lib, "USTPmduserapiAF.lib")
#endif

class cwFemasMdSpi
	: public CUstpFtdcMduserSpi
	, public cwBasicMdSpi
{

public:
	cwFemasMdSpi(void);
	virtual ~cwFemasMdSpi(void);

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

	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo) {};

	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo) {};


	///错误应答
	virtual void OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///风控前置系统用户登录应答
	virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户退出应答
	virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pDepthMarketData);

	///订阅合约的相关信息
	virtual void OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///退订合约的相关信息
	virtual void OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///获取行情主题信息应答
	virtual void OnRspGetMarketTopic(CUstpFtdcRspMarketTopicField *pRspMarketTopic, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///获取行情快照应答
	virtual void OnRspGetMarketData(CUstpFtdcRspDepthMarketDataField *pRspDepthMarketData, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	inline CUstpFtdcMduserApi * GetUserThostFtdcMdApi()
	{
		return m_pMarketDataUserApi;
	}

	virtual void RegisterStrategy(cwBasicStrategy * pBasicStrategy);

	void Connect(const char * pszFrontAddress, const char * pszLocalAddr = NULL);
	void DisConnect();

	void WaitForFinish();

	void SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword);
	void SetUserLoginField(CUstpFtdcReqUserLoginField& reqUserLoginField);

	virtual void SubscribeMarketData(std::vector<std::string>& SubscribeInstrument);
	virtual void UnSubscribeMarketData(std::vector<std::string>& SubscribeInstrument);

private:

	CUstpFtdcMduserApi *			m_pMarketDataUserApi;

	//User Config Data
	CUstpFtdcReqUserLoginField		m_ReqUserLoginField;
	char							m_szMDFrount[1024];

	//一次订阅合约次数
	const int						m_iSubscribeCountOnce;

	//
	int								m_iRequestId;

	std::map<std::string, bool>		m_SubscribeInstrumentMap;

	int								m_iMdAPIIndex;

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwFemasMdSpi);
}; 

