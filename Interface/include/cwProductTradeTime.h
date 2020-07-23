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
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "cwMarketTime.h"

//品种交易时间

class cwProductTradeTime
{

public:
	cwProductTradeTime();
	~cwProductTradeTime();

	enum cwTradeTimeSpace
	{
		NoTrading = 0										//非交易时段
		, NightPartOne										//夜盘
		, AMPartOne											//上午第一阶段
		, AMPartTwo											//上午第二阶段
		, PMPartOne											//下午第一阶段
		, TradeTimeSpaceCnt
	};

	typedef struct tagProductTradeTime
	{
		cwTradeTimeSpace TradeTimeSpace;

		cwMarketTimePtr BeginTime;
		cwMarketTimePtr EndTime;

	}ProductTradeTime;
	typedef std::shared_ptr<ProductTradeTime> TradeTimePtr;

	bool GetTradeTimeSpace(std::string ProductId, std::string updatetime,
		cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);
	int	 GetPreTimeSpaceInterval(std::string ProductId, cwTradeTimeSpace iTradeIndex);
	int	 GetTimeSpaceInterval(std::string productId, std::string starttime, std::string endTime);

private:
	std::unordered_map<std::string, std::vector<TradeTimePtr>> m_ProductTradeTimeMap;
	void InitialTradeTimeMap();
};

