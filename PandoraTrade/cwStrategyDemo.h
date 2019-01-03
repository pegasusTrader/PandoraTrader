#pragma once
#include "cwBasicStrategy.h"

class cwStrategyDemo :
	public cwBasicStrategy
{
public:
	cwStrategyDemo();
	~cwStrategyDemo();

	//MarketData SPI
	///行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//Trade SPI
	///成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade);

	///错误应答
	virtual void OnRspError(cwFtdcRspInfoField *pRspInfo);
	///报单录入请求响应
	virtual void OnRspOrderInsert(cwOrderPtr pOrder, cwFtdcRspInfoField *pRspInfo);
	///报单操作请求响应
	virtual void OnRspOrderCancel(cwOrderPtr pOrder, cwFtdcRspInfoField *pRspInfo);

	std::string m_strCurrentUpdateTime;
};

