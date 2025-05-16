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

	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if (IsNormalTradingTime(hour, minute))
	{
		UpdateCtx(pPriceData);
		std::map<std::string, cwPositionPtr> PositionMap;
		GetPositions(PositionMap);
		orderInfo order;

		if (PositionMap.empty())
		{
			StrategyPosOpen(pPriceData, order);
		}
		else
		{
			StrategyPosClose(pPriceData, PositionMap[pPriceData->InstrumentID], order);
		}
	}
	else if (IsClosingTime(hour, minute))
	{

		cwPositionPtr pPos = nullptr;
		std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;
		GetPositionsAndActiveOrders(pPriceData->InstrumentID, pPos, WaitOrderList);
		std::cout << "[AutoClose] 尝试平仓: " << pPriceData->InstrumentID
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
			double price = GetLastestMarketData(pPriceData->InstrumentID)->BidPrice1;
			EasyInputMultiOrder(pPriceData->InstrumentID, -lp->TotalPosition, price); // 如有多仓平多仓
		}
		if (pPos->ShortPosition->TotalPosition > 0) {
			auto& sp = pPos->ShortPosition;
			double price = GetLastestMarketData(pPriceData->InstrumentID)->AskPrice1;
			EasyInputMultiOrder(pPriceData->InstrumentID, sp->TotalPosition, price); // 如有空仓平空仓
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
	UpdateBarData();

	for (auto& futInfMng : tarFutInfo)
	{
		SubcribeKindle(futInfMng.first.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);
	};
}

void cwStrategyDemo::UpdateBarData() {

	//创建数据库连接
	sqlite3* mydb = OpenDatabase("dm.db");
	if (mydb) {
		std::string tar_contract_sql = "SELECT * FROM futureinfo;";
		sqlite3_stmt* stmt = nullptr;
		if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				std::string contract = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));//目标合约
				int multiple = sqlite3_column_int(stmt, 1);//合约乘数
				std::string Fac = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));//Fac
				int Rs = sqlite3_column_int(stmt, 3); // ...
				int Rl = sqlite3_column_int(stmt, 4); // ...
				std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)); //目标合约代码
				double accfactor = sqlite3_column_double(stmt, 6);//保证金率
				tarFutInfo[contract] = { contract, multiple, Fac, Rs, Rl, code, accfactor };
			}
		}
		else if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
			std::cerr << "SQL prepare failed: " << sqlite3_errmsg(mydb) << std::endl;
		}
		sqlite3_finalize(stmt);

		for (auto& futInfMng : tarFutInfo) {
			std::string ret_sql = std::format("SELECT ret FROM {} ORDER BY tradingday,timestamp ", futInfMng.first);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, ret_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					comBarInfo.retBar[futInfMng.first].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (auto& futInfMng : tarFutInfo) {
			std::string closeprice_sql = std::format("SELECT closeprice FROM {} ORDER BY tradingday,timestamp ", futInfMng.first);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, closeprice_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					comBarInfo.barFlow[futInfMng.first].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (auto& futInfMng : tarFutInfo) {
			std::string real_close_sql = std::format("SELECT real_close FROM {} ORDER BY tradingday,timestamp ", futInfMng.first);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, real_close_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					comBarInfo.queueBar[futInfMng.first].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (const auto& futInfMng : tarFutInfo) {
			int comboMultiple = 2;  // 组合策略做几倍杠杆
			int tarCount = tarFutInfo.size();  // 目标合约数量
			double numLimit = comboMultiple * 1000000 / tarCount / comBarInfo.barFlow[futInfMng.first].back() / futInfMng.second.multiple;  // 策略杠杆数，1000000 为策略基本资金单位， 20为目前覆盖品种的近似值， 收盘价格，保证金乘数
			countLimitCur[futInfMng.first] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // 整数 取舍一下
		}
		CloseDatabase(mydb);  // 最后关闭数据库连接
	}
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

void cwStrategyDemo::UpdateCtx(cwMarketDataPtr pPriceData)
{
	//barFolw更新
	comBarInfo.barFlow[pPriceData->InstrumentID].push_back(pPriceData->LastPrice);
	//queueBar更新

	comBarInfo.queueBar[pPriceData->InstrumentID].push_back(pPriceData->LastPrice / tarFutInfo[pPriceData->InstrumentID].accfactor);
	//ret更新
	double last = comBarInfo.queueBar[pPriceData->InstrumentID][comBarInfo.queueBar[pPriceData->InstrumentID].size() - 1];
	double secondLast = comBarInfo.queueBar[pPriceData->InstrumentID][comBarInfo.queueBar[pPriceData->InstrumentID].size() - 2];
	comBarInfo.retBar[pPriceData->InstrumentID].push_back(last / secondLast - 1);
	//删除首位元素
	comBarInfo.barFlow[pPriceData->InstrumentID].pop_front();
	comBarInfo.queueBar[pPriceData->InstrumentID].pop_front();
	comBarInfo.retBar[pPriceData->InstrumentID].pop_front();
}

orderInfo cwStrategyDemo::StrategyPosOpen(cwMarketDataPtr pPriceData, orderInfo& order) {

	// 计算标准差
	// 计算 stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// 计算 stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rl), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);

	orderInfo order;
	// 最新价格 < 短期价格 && 短期波动率 > 长期波动率
	auto& barQueue = comBarInfo.queueBar[pPriceData->InstrumentID];
	if (barQueue.back() < barQueue[barQueue.size() - tarFutInfo[pPriceData->InstrumentID].Rs] && stdShort > stdLong) {
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();

	}
	// 最新价格 > 短期价格 && 短期波动率 > 长期波动率
	else if (barQueue.back() > barQueue[barQueue.size() - 500] && stdShort > stdLong) {
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();

	}
	return order;
}

orderInfo cwStrategyDemo::StrategyPosClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos, orderInfo& order) {
	// 计算标准差
	// 计算 stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// 计算 stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);
	orderInfo order;
	auto& barQueue = comBarInfo.queueBar[pPriceData->InstrumentID];
	size_t rs = tarFutInfo[pPriceData->InstrumentID].Rs;
	std::string FacDirection;
	if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
	{
		if (pPos->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Long";
		}
		else if (pPos->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Short";
		}
	}
	else
	{
		if (pPos->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Short";
		}
		else if (pPos->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Long";
		}
	}

	//Fac方向 =买 && （最新价格 > 短期价格 || 短期波动率<=长期波动率）
	if (FacDirection == "Long" && (barQueue.back() > barQueue[barQueue.size() - rs] || stdShort <= stdLong)) {
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
	//Fac方向 =卖 && （最新价格 < 短期价格 || 短期波动率<=长期波动率）
	else if (FacDirection == "Short" && (barQueue.back() < barQueue[barQueue.size() - rs] || stdShort <= stdLong))
	{
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
	return order;
}

