#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "cwMarketTime.h"



class cwProductTradeTime
{

public:
	cwProductTradeTime();
	~cwProductTradeTime();

	enum cwTradeTimeSpace
	{
		NoTrading = 0
		, NightPartOne
		, AMPartOne
		, AMPartTwo
		, PMPartOne
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
	std::map<std::string, std::vector<TradeTimePtr>> m_ProductTradeTimeMap;
	void InitialTradeTimeMap();
};

