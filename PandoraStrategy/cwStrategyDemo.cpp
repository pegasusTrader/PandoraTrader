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

static std::map<std::string, futInfMng> tarFutInfo; // 策略上下文
static barInfo comBarInfo;                          // barINfo
static std::map<std::string, int> countLimitCur;    // 合约对应交易数量

cwStrategyDemo::cwStrategyDemo()
{
}


cwStrategyDemo::~cwStrategyDemo()
{
}

void cwStrategyDemo::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL) { return; }
}

void cwStrategyDemo::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {
	if (pPriceData.get() == NULL) { return; }

	std::string currentContract = pPriceData->InstrumentID;
	int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [currentContract](const futInfMng& item) {return item.contract == currentContract; });
	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if (IsNormalTradingTime(hour, minute))
	{
		UpdateCtx(pPriceData, ctx, currentContract);

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
	else if (IsClosingTime(hour, minute))
	{

		cwPositionPtr pPos = nullptr;
		std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;
		GetPositionsAndActiveOrders(currentContract, pPos, WaitOrderList);
		std::cout << "[AutoClose] 尝试平仓: " << currentContract
			<< " LongYd=" << pPos->LongPosition->YdPosition
			<< " LongTd=" << pPos->LongPosition->TodayPosition
			<< " ShortYd=" << pPos->ShortPosition->YdPosition
			<< " ShortTd=" << pPos->ShortPosition->TodayPosition << std::endl;

		if (pPos == nullptr)
		{
			std::cout << "没有持仓" << std::endl;
			return;
		}
		if (pPos->LongPosition->TotalPosition > 0) {
			auto& lp = pPos->LongPosition;
			double price = GetLastestMarketData(currentContract)->BidPrice1;
			EasyInputMultiOrder(currentContract.c_str(), -lp->TotalPosition, price); // 如有多仓平多仓
		}
		if (pPos->ShortPosition->TotalPosition > 0) {
			auto& sp = pPos->ShortPosition;
			double price = GetLastestMarketData(currentContract)->AskPrice1;
			EasyInputMultiOrder(currentContract.c_str(), sp->TotalPosition, price); // 如有空仓平空仓
		}
	}
	else if (IsAfterMarket(hour, minute))
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
};

void cwStrategyDemo::OnRtnTrade(cwTradePtr pTrade)
{
}

void cwStrategyDemo::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
	
}

	void cwStrategyDemo::OnOrderCanceled(cwOrderPtr pOrder)
	{
		if (pOrder->OrderStatus == '5') { // 拒单
			std::cout << "[AutoClose] 拒单: " << pOrder->InstrumentID << std::endl;
			//pendingContracts.erase(pOrder->InstrumentID); // 强制移除，避免阻塞
		}

	}

	void cwStrategyDemo::OnReady()
	{

		AutoCloseAllPositionsLoop();
		UpdateBarData(tarFutInfo, comBarInfo, countLimitCur);

		for (auto& futInfMng : tarFutInfo)
		{
			SubcribeKindle(futInfMng.first.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);
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
					EasyInputMultiOrder(id.c_str(), -lp->TotalPosition, price); // 平昨多
				}
				if (pos->ShortPosition->TotalPosition > 0) {
					auto& sp = pos->ShortPosition;
					double price = GetLastestMarketData(id)->AskPrice1;
					EasyInputMultiOrder(id.c_str(), sp->TotalPosition, price); // 平昨空
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

	void cwStrategyDemo::UpdateCtx(cwMarketDataPtr pPriceData, StrategyContext & ctx, std::string & currentContract)
	{
		//barFolw更新
		ctx.barFlow[currentContract].push_back(pPriceData->LastPrice);
		//queueBar更新
		int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [currentContract](const futInfMng& item) {return item.contract == currentContract; });
		ctx.queueBar[currentContract].push_back(pPriceData->LastPrice / ctx.tarContracInfo[contractIndex].accfactor);
		//ret更新
		double last = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 1];
		double secondLast = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 2];
		ctx.retBar[currentContract].push_back(last / secondLast - 1);
		//删除首位元素
		ctx.barFlow[currentContract].pop_front();
		ctx.queueBar[currentContract].pop_front();
		ctx.retBar[currentContract].pop_front();
	}



