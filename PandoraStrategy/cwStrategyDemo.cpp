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

//清仓所需全局变量
static std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;           // 挂单列表（全局）
static std::unordered_map<std::string, bool> instrumentCloseFlag;      // 是否触发收盘平仓
static std::unordered_map<std::string, int> lastCloseAttemptTime;      // 合约->上次清仓尝试时间戳（秒）
static std::unordered_map<std::string, int> closeAttemptCount;         // 用于控制重挂频率（每个合约）

//交易所需全局变量
static std::unordered_map<std::string, orderInfo> cwOrderInfo;

cwStrategyDemo::cwStrategyDemo()
{
}

cwStrategyDemo::~cwStrategyDemo()
{
}

void cwStrategyDemo::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL) { return; }

	auto [hour, minute, second] = IsTradingTime();

	if (IsNormalTradingTime(hour, minute)) {
		std::string instrument = pPriceData->InstrumentID;

		auto it = cwOrderInfo.find(instrument);
		if (it == cwOrderInfo.end()) return; // 没有信号

		orderInfo& info = it->second;

		cwPositionPtr pPos = nullptr;
		GetPositionsAndActiveOrders(pPriceData->InstrumentID, pPos, WaitOrderList); // 获取指定持仓和挂单列表

		bool hasOrder = IsPendingOrder(pPriceData->InstrumentID);

		int now = GetCurrentTimeInSeconds();

		if (lastCloseAttemptTime[pPriceData->InstrumentID] == 0 || now - lastCloseAttemptTime[pPriceData->InstrumentID] >= 5) //挂单超时撤单判断是单一的：5秒设置根据合约活跃度动态调整时间；或者基于盘口价差判断是否撤单更具优势。
		{
			lastCloseAttemptTime[pPriceData->InstrumentID] = now;

			bool result = (info.volume == pPos->LongPosition->TodayPosition) ? true : (info.volume == pPos->ShortPosition->TodayPosition) ? true : false;

			if (result) {
				cwOrderInfo.erase(instrument);
				closeAttemptCount.erase(instrument);
			}
			else {
				if (!hasOrder) {
					EasyInputOrder(info.szInstrumentID.c_str(), info.volume, info.price);
					//cwOrderInfo.erase(instrument); //这个好像不能在这里erase
					return;
				}
				else if (hasOrder)
				{
					if (++closeAttemptCount[pPriceData->InstrumentID] > 3) {
						std::cout << "[" << pPriceData->InstrumentID << "] 超过最大次数，还未挂上单子，请人工检查。" << std::endl;
						return;
					}
					else
					{
						for (auto& [key, order] : WaitOrderList) {
							if (key.InstrumentID == pPriceData->InstrumentID) {
								CancelOrder(order);
							}
						}
						std::cout << "[" << pPriceData->InstrumentID << "] 撤销未成交挂单，准备重新挂单..." << std::endl;
						if (pPos) { TryAggressiveClose(pPriceData, pPos); }
						int count = std::count_if(WaitOrderList.begin(), WaitOrderList.end(), [&](const auto& pair) { return pair.first.InstrumentID == pPriceData->InstrumentID; });
						std::cout << "[" << pPriceData->InstrumentID << "] 等待挂单成交中，挂单数：" << count << std::endl;
					}
				}
			}
		}
	}

	if (IsClosingTime(hour, minute) && !instrumentCloseFlag[pPriceData->InstrumentID])
	{
		int now = GetCurrentTimeInSeconds();

		if (lastCloseAttemptTime[pPriceData->InstrumentID] == 0 || now - lastCloseAttemptTime[pPriceData->InstrumentID] >= 5)
		{
			lastCloseAttemptTime[pPriceData->InstrumentID] = now;                       // 更新尝试时间

			cwPositionPtr pPos = nullptr;

			GetPositionsAndActiveOrders(pPriceData->InstrumentID, pPos, WaitOrderList); // 获取指定持仓和挂单列表

			bool hasPos = (pPos && (pPos->LongPosition->TotalPosition > 0 || pPos->ShortPosition->TotalPosition > 0));
			bool hasOrder = IsPendingOrder(pPriceData->InstrumentID);

			// 情况 1：无持仓 + 无挂单 => 清仓完毕
			if (!hasPos && !hasOrder)
			{
				std::cout << "[" << pPriceData->InstrumentID << "] 持仓清空完毕。" << std::endl;
				instrumentCloseFlag[pPriceData->InstrumentID] = true;
				closeAttemptCount.erase(pPriceData->InstrumentID);
				return;
			}
			// 情况 2：有持仓 + 无挂单 => 初次挂清仓单
			else if (hasPos && !hasOrder)
			{
				TryAggressiveClose(pPriceData, pPos);
				std::cout << "[" << pPriceData->InstrumentID << "] 清仓指令已发送。" << std::endl;
				return;
			}
			// 情况 3：有挂单 或 有持仓 => 撤单 + 重新挂清仓单
			else
			{
				if (++closeAttemptCount[pPriceData->InstrumentID] > 3) {
					std::cout << "[" << pPriceData->InstrumentID << "] 超过最大等待次数，可能仍有未清仓持仓，请人工检查。" << std::endl;
					instrumentCloseFlag[pPriceData->InstrumentID] = true;
					return;
				}
				else
				{
					for (auto& [key, order] : WaitOrderList) {
						if (key.InstrumentID == pPriceData->InstrumentID) {
							CancelOrder(order);
						}
					}
					std::cout << "[" << pPriceData->InstrumentID << "] 撤销未成交挂单，准备重新挂单..." << std::endl;
					if (pPos) { TryAggressiveClose(pPriceData, pPos); }
					int count = std::count_if(WaitOrderList.begin(), WaitOrderList.end(), [&](const auto& pair) { return pair.first.InstrumentID == pPriceData->InstrumentID; });
					std::cout << "[" << pPriceData->InstrumentID << "] 等待挂单成交中，挂单数：" << count << std::endl;
				}
			}
		}
	}
}

void cwStrategyDemo::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {
	if (pPriceData.get() == NULL) { return; }

	auto [hour, minute, second] = IsTradingTime();

	if (IsNormalTradingTime(hour, minute))
	{
		UpdateCtx(pPriceData);

		cwPositionPtr pPos = nullptr;

		GetPositionsAndActiveOrders(pPriceData->InstrumentID, pPos, WaitOrderList); // 获取指定持仓和挂单列表


		if (!pPos)
		{
			StrategyPosOpen(pPriceData, cwOrderInfo);
		}
		else
		{
			StrategyPosClose(pPriceData, pPos, cwOrderInfo);
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
	if (pOrder == nullptr) return;
	// 构造挂单的 key
	cwActiveOrderKey key(pOrder->OrderRef, pOrder->InstrumentID);

	// 我们只关心在 WaitOrderList 中追踪的挂单
	auto it = WaitOrderList.find(key);
	if (it == WaitOrderList.end()) return;


	auto status = pOrder->OrderStatus;// 报单状态（主要判断是否结束）
	auto submitStatus = pOrder->OrderSubmitStatus;// 报单提交状态（主要判断是否结束）

	if (status == CW_FTDC_OST_AllTraded ||   // 全部成交
		status == CW_FTDC_OST_Canceled)    // 撤单     
	{
		// 日志记录
		std::cout << "Order Finished - InstrumentID: " << pOrder->InstrumentID
			<< ", Ref: " << pOrder->OrderRef
			<< ", Status: " << status << std::endl;

		// 移除该挂单
		WaitOrderList.erase(it);
	}
	else if (submitStatus == CW_FTDC_OSS_InsertRejected)// 拒单
	{
		// 日志记录
		std::cout << "Order Finished - InstrumentID: " << pOrder->InstrumentID
			<< ", Ref: " << pOrder->OrderRef
			<< ", Status: " << submitStatus << std::endl;
	}
	else {
		// 可选：你也可以更新该挂单的信息（部分成交数量等）
	}

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
	if (mydb)
	{
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
	for (const auto& futInfMng : tarFutInfo) { instrumentCloseFlag[futInfMng.first] = false; }
}

void cwStrategyDemo::AutoCloseAllPositionsLoop() {
	std::map<std::string, cwPositionPtr> CurrentPosMap; //定义map，用于保存持仓信息 
	std::map<std::string, int> pendingRetryCounter;     // 合约 -> 活跃挂单保留轮数
	std::map<std::string, bool> instrumentCloseFlag;    // 是否触发收盘平仓

	GetPositions(CurrentPosMap);
	for (auto& [id, pos] : CurrentPosMap) { instrumentCloseFlag[id] = false; }

	while (true)
	{
		if (!AllInstrumentClosed(instrumentCloseFlag))
		{
			auto [hour, minute, second] = IsTradingTime();
			GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);

			for (auto& [id, pos] : CurrentPosMap)
			{
				if (instrumentCloseFlag[id]) continue;
				auto md = GetLastestMarketData(id);
				if (!md) { std::cout << "[" << id << "] 无有效行情数据，跳过。" << std::endl;continue; }

				bool noLong = pos->LongPosition->TotalPosition == 0;
				bool noShort = pos->ShortPosition->TotalPosition == 0;
				bool noOrder = !IsPendingOrder(id);

				// 情况 1: 无持仓 + 无挂单 => 清仓完毕
				if (noLong && noShort && noOrder)
				{
					std::cout << "[" << id << "] 持仓清空完毕。" << std::endl;
					instrumentCloseFlag[id] = true;
					continue;
				}
				//情况 2: 有持仓 + 无挂单 => 发出平仓单
				else if ((!noLong || !noShort) && noOrder) {
					TryAggressiveClose(md, CurrentPosMap[id]);
					std::cout << "[" << md->InstrumentID << "] 清仓指令已发送。" << std::endl;
				}
				// 情况 3: 有挂单 或 有持仓 => 撤单 + 重新挂清仓单
				else
				{
					if (pendingRetryCounter[id] >= 3) {
						std::cout << "[" << id << "] 超过最大尝试次数，清仓失败。" << std::endl;
						instrumentCloseFlag[id] = true;
						continue;
					}
					else {
						++pendingRetryCounter[id];
						std::cout << "[" << id << "] 存在挂单，撤单重挂（尝试第 " << pendingRetryCounter[id] << " 次）" << std::endl;

						for (auto& [key, order] : WaitOrderList) { if (key.InstrumentID == id) { CancelOrder(order); } }// 撤单
						if (CurrentPosMap[id]) { TryAggressiveClose(md, CurrentPosMap[id]); }//重挂
					}
				}
			}
			cwSleep(5000);
		}
		else
		{
			std::cout << "所有持仓已清空，无挂单。退出清仓循环。" << std::endl;
			break;
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

void cwStrategyDemo::TryAggressiveClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos)
{
	double aggressiveBid = pPriceData->BidPrice1 + GetTickSize(pPriceData->InstrumentID);
	double aggressiveAsk = pPriceData->AskPrice1 - GetTickSize(pPriceData->InstrumentID);
	if (pPos->LongPosition->TotalPosition > 0 && aggressiveBid > 1e-6)
	{
		EasyInputMultiOrder(pPriceData->InstrumentID, -pPos->LongPosition->TotalPosition, aggressiveBid);
		std::cout << "[" << pPriceData->InstrumentID << "] 平多仓 -> 数量: " << pPos->LongPosition->TotalPosition << ", 价格: " << aggressiveBid << std::endl;
	}// 重新挂 Bid
	if (pPos->ShortPosition->TotalPosition > 0 && aggressiveAsk > 1e-6)
	{
		EasyInputMultiOrder(pPriceData->InstrumentID, pPos->ShortPosition->TotalPosition, aggressiveAsk);
		std::cout << "[" << pPriceData->InstrumentID << "] 平空仓 -> 数量: " << pPos->ShortPosition->TotalPosition << ", 价格: " << aggressiveAsk << std::endl;
	}// 重新挂 Ask
}

void cwStrategyDemo::StrategyPosOpen(cwMarketDataPtr pPriceData, std::unordered_map<std::string, orderInfo>& cwOrderInfo)
{
	// 计算 stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// 计算 stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rl), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);

	// 最新价格 < 短期价格 && 短期波动率 > 长期波动率
	auto& barQueue = comBarInfo.queueBar[pPriceData->InstrumentID];
	if (barQueue.back() < barQueue[barQueue.size() - tarFutInfo[pPriceData->InstrumentID].Rs] && stdShort > stdLong)
	{
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = -countLimitCur[pPriceData->InstrumentID];
		}
		cwOrderInfo[pPriceData->InstrumentID].szInstrumentID = pPriceData->InstrumentID;
		cwOrderInfo[pPriceData->InstrumentID].price = comBarInfo.barFlow[pPriceData->InstrumentID].back();

	}
	// 最新价格 > 短期价格 && 短期波动率 > 长期波动率
	else if (barQueue.back() > barQueue[barQueue.size() - 500] && stdShort > stdLong)
	{
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = -countLimitCur[pPriceData->InstrumentID];
		}
		cwOrderInfo[pPriceData->InstrumentID].szInstrumentID = pPriceData->InstrumentID;
		cwOrderInfo[pPriceData->InstrumentID].price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
}

void cwStrategyDemo::StrategyPosClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos, std::unordered_map<std::string, orderInfo>& cwOrderInfo)
{
	// 计算标准差
	// 计算 stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// 计算 stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);
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
			cwOrderInfo[pPriceData->InstrumentID].volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = -countLimitCur[pPriceData->InstrumentID];
		}
		cwOrderInfo[pPriceData->InstrumentID].szInstrumentID = pPriceData->InstrumentID;
		cwOrderInfo[pPriceData->InstrumentID].price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
	//Fac方向 =卖 && （最新价格 < 短期价格 || 短期波动率<=长期波动率）
	else if (FacDirection == "Short" && (barQueue.back() < barQueue[barQueue.size() - rs] || stdShort <= stdLong))
	{
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			cwOrderInfo[pPriceData->InstrumentID].volume = -countLimitCur[pPriceData->InstrumentID];
		}
		cwOrderInfo[pPriceData->InstrumentID].szInstrumentID = pPriceData->InstrumentID;
		cwOrderInfo[pPriceData->InstrumentID].price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
}

bool cwStrategyDemo::IsPendingOrder(std::string instrumentID)
{
	for (auto& [key, order] : WaitOrderList) {
		if (key.InstrumentID == instrumentID) {
			return true;
		}
	}
	return false;
}