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
#include "CTPTradeApiMacOS/ThostFtdcMdApi.h"
#endif
#elif __linux__ or _linux
// linux
#include "CTPTradeApiLinux/ThostFtdcMdApi.h"
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#ifdef WIN32
#pragma comment(lib, "thostmduserapi_se.lib")
#endif

class cwFtdMdSpi
	: public CThostFtdcMdSpi
	, public cwBasicMdSpi
{

public:
	cwFtdMdSpi(void);
	virtual ~cwFtdMdSpi(void);

public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);
	

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����ѯ��Ӧ��
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///ѯ��֪ͨ
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

	CThostFtdcMdApi *				m_pMarketDataUserApi;

	//User Config Data
	CThostFtdcReqUserLoginField		m_ReqUserLoginField;
	char							m_szMDFrount[1024];

	//һ�ζ��ĺ�Լ����
	const int						m_iSubscribeCountOnce;

	//
	int								m_iRequestId;

	std::map<std::string, bool>		m_SubscribeInstrumentMap;

	int								m_iMdAPIIndex;

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwFtdMdSpi);
}; 

