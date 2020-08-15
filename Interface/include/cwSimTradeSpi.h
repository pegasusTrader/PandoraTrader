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
#include "cwBasicTradeSpi.h"
#include "cwBasicSimulator.h"
#include "cwBasicCout.h"

class cwSimTradeSpi
	: public cwBasicTradeSpi
{
public:
	cwSimTradeSpi();
	~cwSimTradeSpi();

	virtual void RegisterBasicStrategy(cwBasicStrategy * pBasicStrategy, void * pSpi = NULL);

	///请求响应
	virtual void OnRspQryPosition(std::map<std::string, cwPositionPtr>& position);
	virtual void OnRspQryOrders(std::map<std::string, cwOrderPtr>	orders);
	virtual void OnRspQryTrade(std::map<std::string, cwTradePtr> trades);

	virtual void OnRspQryInstrument(std::unordered_map<std::string, cwInstrumentDataPtr>& InstrumentData);


	//User Trader Method
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);
	
	///报单通知
	void OnRtnOrder(cwOrderPtr pOrder);

	///成交通知
	virtual void OnRtnTrade(cwTradePtr pTrade);

	///账户通知
	virtual void OnRtnAccount(cwAccountPtr pAccount);

	///报单录入请求响应
	virtual void OnRspOrderInsert(cwOrderPtr pInputOrder, cwRspInfoPtr pRspInfo);

	///报单操作请求响应
	virtual void OnRspOrderAction(cwOrderPtr pInputOrderAction, cwRspInfoPtr pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnSimulationPartEnd();
	virtual void OnSimulationFinished();

	virtual	cwOrderPtr InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
	virtual cwOrderPtr InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
	virtual cwOrderPtr InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
	virtual void CancelOrder(const char * szLocalOrderID);
	virtual void CancelOrder(cwOrderPtr pOrder);

	cwOrderPtr GetcwOrderPtr(const char * szExchangeID, const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price, cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);

	void Connect(const char * pszFrontAddress);
	void Connect(cwBasicSimulator * pBaiscSimulator);
	void DisConnect();

	void WaitForFinish();

	void SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword, const char * szUserProductInfo = INTERFACENAME);

private:
	cwBasicSimulator *			m_pMarketDataUserApi;

	//User Config Data
	char						m_szMDFrount[1024];
	std::string					m_strUserID;
	std::string					m_strInvestorID;
	std::string					m_strBrokerID;
	std::string					m_strPassWord;

	//
	int							m_iRequestId;

	std::unordered_map<std::string, cwMarketDataPtr>		m_LastestPriceDataMap;

#ifdef CWCOUTINFO
	cwBasicCout					m_cwShow;
#endif
};

