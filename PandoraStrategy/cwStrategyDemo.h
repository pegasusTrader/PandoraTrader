#pragma once
#include "cwBasicKindleStrategy.h"
#include "sqlite3.h"
#include "myStructs.h"

class cwStrategyDemo :
	public cwBasicKindleStrategy
{
public:
	cwStrategyDemo();
	~cwStrategyDemo();

	//MarketData SPI
	///行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//当生成一根新K线的时候，会调用该回调
	virtual void OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);

	//Trade SPI
	///成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade);
	//报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	//撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder);
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void OnReady();
	//初始化策略上下文
	void UpdateBarData();
	// 自动平昨仓函数
	void AutoCloseAllPositionsLoop();
	//当前时间
	std::string m_strCurrentUpdateTime;
	// sqlLiteHelp
	void UpdateCtx(cwMarketDataPtr pPriceData,StrategyContext &ctx, std::string& currentContract);
	
	// 开仓交易 条件
	orderInfo StrategyPosOpen(std::string contract, std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur);

	// 平仓交易 条件
	orderInfo StrategyPosClose(std::string contract, cwPositionPtr pPos, std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur);
};