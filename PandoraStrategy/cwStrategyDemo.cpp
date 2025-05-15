#include "cwStrategyDemo.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <cmath>
#include <exception>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <format>
#include "myStructs.h"
#include "sqlite3.h"
#include "IndayStrategy.hpp"
#include "utils.hpp"

static StrategyContext ctx = UpdateBarData();

cwStrategyDemo::cwStrategyDemo()
{
}


cwStrategyDemo::~cwStrategyDemo()
{
}

void cwStrategyDemo::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}
}

void cwStrategyDemo::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {
	if (pPriceData.get() == NULL)
	{
		return;
	}

	std::string currentContract = pPriceData->InstrumentID;

	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if ((hour == 9 && minute >= 1) || (hour > 9 && hour < 10) || (hour == 10 && minute < 15) ||
		(hour == 10 && minute >= 30) || (hour > 10 && hour < 11) || (hour == 11 && minute < 30) ||
		(hour == 13 && minute >= 30) || (hour > 13 && hour < 14) || (hour == 14 && minute < 45))
	{
		//barFolw更新
		ctx.barFlow[currentContract].push_back(pPriceData->LastPrice);
		//queueBar更新
		std::string constrct_id = currentContract;
		int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [constrct_id](const futInfMng& item) {return item.contract == constrct_id; });
		ctx.queueBar[currentContract].push_back(pPriceData->LastPrice / ctx.tarContracInfo[contractIndex].accfactor);
		//ret更新
		double last = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 1];
		double secondLast = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 2];
		ctx.retBar[currentContract].push_back(last / secondLast - 1);

		//删除首位元素
		ctx.barFlow[currentContract].pop_front();
		ctx.queueBar[currentContract].pop_front();
		ctx.retBar[currentContract].pop_front();

		// 计算标准差
		// 计算 stdShort
		std::vector<double> retBarSubsetShort(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rs), ctx.retBar[currentContract].end());
		double stdShort = SampleStd(retBarSubsetShort);

		// 计算 stdLong
		std::vector<double> retBarSubsetLong(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rl), ctx.retBar[currentContract].end());
		double stdLong = SampleStd(retBarSubsetLong);

		std::map<std::string, cwPositionPtr> PositionMap;
		GetPositions(PositionMap);

		if (PositionMap.empty())
		{
			StrategyPosOpen(currentContract, ctx, stdLong, stdShort);
		}
		else
		{
			StrategyPosClose(currentContract, PositionMap[currentContract], ctx, stdLong, stdShort);
		}
	}
	else if ((hour == 14 && minute >= 45) || (hour == 15 && minute == 0))
	{
		//全部清仓

	}
	else if ((hour == 15 && minute >= 0 && minute < 10))
	{
		std::cout << "----------------- TraderOver ----------------" << std::endl;
		std::cout << "--------------- StoreBaseData ---------------" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
	else
	{
		if (minute == 0 || minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50)
		{
			std::cout << "waiting" << hour << "::" << minute << "::" << second << std::endl;
		}
	}
	//开多仓信号
	//开空仓信号
	// 临近收盘 清仓处理
	// 打印一些东西
};

void cwStrategyDemo::OnRtnTrade(cwTradePtr pTrade)
{
}

void cwStrategyDemo::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
}

void cwStrategyDemo::OnOrderCanceled(cwOrderPtr pOrder)
{
}

void cwStrategyDemo::OnReady()
{
	
	AutoCloseAllPositionsLoop();

	for (auto& futInfMng : ctx.tarContracInfo)
	{
		SubcribeKindle(futInfMng.code.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);

	};
}


void cwStrategyDemo::AutoCloseAllPositionsLoop() {

	//定义map，用于保存持仓信息 
	std::map<std::string, cwPositionPtr> CurrentPosMap;
	//定义map，用于保存挂单信息 
	std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;

	while (true) {
		GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);
		if (CurrentPosMap.empty()) {
			std::cout << "没有持仓" << std::endl;
			break;
		}

		for (auto& [id, pos] : CurrentPosMap) {
			if (pos->LongPosition->TotalPosition > 0) {
				auto& lp = pos->LongPosition;
				double price = GetLastestMarketData(id)->BidPrice1;
				EasyInputMultiOrder(id.c_str(), -lp->YdPosition, price); // 平昨多
			}
			if (pos->ShortPosition->TotalPosition > 0) {
				auto& sp = pos->ShortPosition;
				double price = GetLastestMarketData(id)->AskPrice1;
				EasyInputMultiOrder(id.c_str(), sp->YdPosition, price); // 平昨空
			}
		}

		// 等待所有订单完成
		while (true) {
			if (!WaitOrderList.empty()) {
				cwSleep(1000);
				GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList); // 更新
			}
			else {
				std::cout << "订单全部成交&没有昨日订单" << std::endl;
				break;
			}
		}
	}
}