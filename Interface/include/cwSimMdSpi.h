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
#include "cwBasicMdSpi.h"
#include "cwBasicSimulator.h"

class cwSimMdSpi 
	: public cwBasicMdSpi
{
public:
	cwSimMdSpi();
	~cwSimMdSpi();

		///登录请求响应
	virtual void OnRspUserLogin();

	///深度行情通知
	virtual void OnRtnDepthMarketData(cwMarketDataPtr pDepthMarketData);


	virtual void RegisterStrategy(cwBasicStrategy * pBasicStrategy);

	void Connect(const char * pszFrontAddress);
	void Connect(cwBasicSimulator * pBaiscSimulator);
	void DisConnect();

	void WaitForFinish();

	void SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword);

	virtual void SubscribeMarketData(std::vector<std::string>& SubscribeInstrument);
	virtual void UnSubscribeMarketData(std::vector<std::string>& SubscribeInstrument);

	size_t		 GetDataDequeLength() { return m_DepthMarketDataDeque.size(); }
private:
	cwBasicSimulator *			m_pMarketDataUserApi;

	//User Config Data
	char						m_szMDFrount[1024];

	//
	int							m_iRequestId;

	std::map<std::string, bool>	m_SubscribeInstrumentMap;
};

