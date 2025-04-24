#pragma once
#include "cwBasicKindleStrategy.h"
#include "sqlite3.h"
#include "My_structs.h"

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

	static double ArithmeticMean(const std::vector<double>& arr); //计算简单算数平均值

	static double SampleStd(const std::vector<double>& arr); //计算样本标准差

	static std::string getTodayDate();

	static void UpdateBarData();// 加载历史信息

	static void UpdateFlow(std::unordered_map<std::string, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos);// 记录最新持仓状况（方向，数量，成本价格，开仓成本，数量）

	static std::vector<cwOrderPtr> StrategyTick(std::unordered_map<std::string, cwMarketDataPtr> code2data/*数据*/);

	static std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

	static std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

	static std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO);

	static std::vector<cwOrderPtr> HandBar(std::unordered_map<std::string, cwMarketDataPtr> code2data/*昨仓数据*/, std::unordered_map<std::string, PositionFieldPtr> curPos);
	
};