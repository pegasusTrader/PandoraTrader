#pragma once
#include <fstream>
#include "cwBasicStrategy.h"
#include <iostream>

class cwEmptyStrategy :
	public cwBasicStrategy
{
public:
	cwEmptyStrategy();
	~cwEmptyStrategy();

	std::string  GetStrategyName();

	//MarketData SPI
	///行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//Trade SPI
	///成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade) {};
	///报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	///撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) {};

	virtual void SetStrategyReady();

	std::string	m_strCurrentUpdateTime;	


	void InitialStrategy(const char * pConfigFilePath);

	///strategy parameter
	//策略运行代号
	std::string m_strStrategyName;		
	//策略是否运行
	bool		m_bStrategyRun;					

	bool		m_bShowPosition;
private:

};

