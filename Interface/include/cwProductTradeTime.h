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
#include <map>
#include <vector>
#include "cwMarketTime.h"

//品种交易时间
class cwProductTradeTime
{

public:
	cwProductTradeTime();
	cwProductTradeTime(const char* filename);
	~cwProductTradeTime();

	enum cwTradeTimeSpace
	{
		NoTrading = 0										//非交易时段
		, NightPartOne = 1									//夜盘
		, AMPartOne = 2									    //上午第一阶段
		, AMPartTwo = 3									    //上午第二阶段
		, PMPartOne = 4									    //下午第一阶段
		, AMCallAuctionOrderingOpen = 5					    //集合竞价报单（上午开盘）
		, AMCallAuctionMatchOpen = 6						//集合竞价撮合（上午开盘）
		, NightCallAuctionOrderingOpen = 7					//集合竞价报单（夜盘开盘）
		, NightCallAuctionMatchOpen = 8					    //集合竞价撮合（夜盘开盘）
		, CallAuctionOrderingClose = 9					    //集合竞价报单（收盘）
		, CallAuctionMatchClose = 10					    //集合竞价撮合（收盘）
		, TradeTimeSpaceCnt
	};

	enum cwRangeOpenClose
	{
		cwLeftOpenRightOpen = 0,							//(a,b)： 左开右开区间
		cwLeftOpenRightClose = 1,							//(a,b]： 左开右闭区间
		cwLeftCloseRightOpen = 2,							//[a,b)： 左闭右开区间
		cwLeftCloseRightClose = 3							//[a,b]： 左闭右闭区间
	};

	typedef struct tagProductTradeTime
	{
		cwTradeTimeSpace TradeTimeSpace;
		cwRangeOpenClose RangeOpenClose;

		cwMarketTimePtr BeginTime;
		cwMarketTimePtr EndTime;

	}ProductTradeTime;
	typedef std::shared_ptr<ProductTradeTime> TradeTimePtr;

	//根据品种ID,和时间获取交易时段
	bool GetTradeTimeSpace(std::string ProductId, std::string updatetime,
		cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);
	bool GetTradeTimeSpace(std::string ProductId, uint32_t hour, uint32_t minute, uint32_t second,
		cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);

	TradeTimePtr GetTradeTime(std::string ProductId, cwTradeTimeSpace iTradeIndex);

	//获取到前一个交易时段的时间差
	int	 GetPreTimeSpaceInterval(std::string ProductId, cwTradeTimeSpace iTradeIndex);
	int	 GetTimeSpaceInterval(std::string productId, std::string starttime, std::string endTime);

	void InitialTradeTimeMap();
	void InitialTradeTimeMapFromFile(const char* filename);
	bool GenerateTradeTimeToFile(const char* filename);
private:
	std::map<std::string, std::vector<TradeTimePtr>> m_ProductTradeTimeMap;
};

