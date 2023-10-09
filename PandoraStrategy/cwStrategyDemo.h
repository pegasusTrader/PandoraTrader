#pragma once
#include "cwBasicKindleStrategy.h"

class cwStrategyDemo :
	public cwBasicKindleStrategy
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
	//报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	//撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder);
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void			OnReady();

	std::string m_strCurrentUpdateTime;
};

