#pragma once
#include <fstream>
#include "cwBasicStrategy.h"
#include "cwStrategyLog.h"
#include <iostream>
#include "tinyxml.h"

class cwMarketDataReceiver :
	public cwBasicStrategy
{
public:
	cwMarketDataReceiver();
	~cwMarketDataReceiver();

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


private:
	bool							m_bNightMode;
	std::string						m_strAppStartDay;
	std::string						m_strAppStartNextDay;
	std::string						m_strAppStartTime;

	cwStrategyLog					m_StrategyLog;

	std::map<std::string, uint64_t>	m_TotalVolume;
	std::map<std::string, double>	m_TotalTurnOver;

	std::map<std::string, bool>		m_bHasFirstQuotes;
};

