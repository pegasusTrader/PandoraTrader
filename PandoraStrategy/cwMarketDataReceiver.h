//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on June.26th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <fstream>
#include "cwBasicKindleStrategy.h"
#include "cwStrategyLog.h"
#include <iostream>
#include "tinyxml.h"

class cwMarketDataReceiver :
	public cwBasicKindleStrategy
{
public:
	cwMarketDataReceiver();
	~cwMarketDataReceiver();

	std::string  GetStrategyName();

	//MarketData SPI
	///行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);

	//Trade SPI
	///成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade) {};
	///报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	///撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) {};

	virtual void OnReady();

	void InitialStrategy(const char * pConfigFilePath);


	std::string	m_strCurrentUpdateTime;

	///strategy parameter
	//策略运行代号
	std::string m_strStrategyName;		
	//策略是否运行
	bool		m_bStrategyRun;					

	bool												m_bSaveInstrument = true;
private:
	cwStrategyLog										m_StrategyLog;

	std::unordered_map<std::string, uint64_t>			m_TotalVolume;
	std::unordered_map<std::string, double>				m_TotalTurnOver;

	std::unordered_map<std::string, bool>				m_bHasFirstQuotes;

	std::map<std::string, std::string>					m_HisMdFileIndex;

	std::string											m_strCurrentMdFilePath;
	std::string											m_strdateIndexId;
};

