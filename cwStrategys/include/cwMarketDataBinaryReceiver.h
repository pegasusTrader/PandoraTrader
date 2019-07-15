#pragma once
#include <fstream>
#include "cwBasicStrategy.h"
#include "tinyxml.h"

#include <fstream>
#include <iostream>
#include <thread>

class cwMarketDataBinaryReceiver :
	public cwBasicStrategy
{
public:
	cwMarketDataBinaryReceiver();
	~cwMarketDataBinaryReceiver();

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
	std::string						m_strCurrentMdFilePath;
	std::string						m_strdateIndexId;

	bool							m_bNightMode;
	std::string						m_strAppStartDay;
	std::string						m_strAppStartNextDay;
	std::string						m_strAppStartTime;

	std::map<std::string, uint64_t>	m_TotalVolume;
	std::map<std::string, double>	m_TotalTurnOver;

	std::map<std::string, bool>		m_bHasFirstQuotes;

	std::map<std::string, std::string>	m_HisMdFileIndex;

	std::ofstream					m_MarketDataFile;

	std::thread			m_WatchDogThread;
	volatile bool		m_bWatchDogThreadRun;
	volatile int		m_iWatchDogTimeOut;
	void				WatchDogThread();

};

