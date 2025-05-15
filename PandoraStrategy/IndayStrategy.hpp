#pragma once
#include "cwBasicKindleStrategy.h"
#include <iostream>
#include <format>
#include <algorithm>
#include <map>
#include <regex>
#include "sqlite3.h"
#include "myStructs.h"
#include "sqlLiteHelp.hpp"
#include "utils.hpp"

//// 策略上下文
void UpdateBarData(std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur) {

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

//// 开仓交易 条件
orderInfo StrategyPosOpen(std::string contract, StrategyContext ctx, double stdLong, double stdShort) {
	orderInfo order;
	int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [contract](const futInfMng& item) {return item.contract == contract; });
	auto& barQueue = ctx.queueBar[contract];
	size_t rs = ctx.tarContracInfo[contractIndex].Rs;
	// 最新价格 < 短期价格 && 短期波动率 > 长期波动率
	if (barQueue.back() < barQueue[barQueue.size() - rs] && stdShort > stdLong) {
		int tarVolume = ctx.countLimitCur[contract];
		//std::string key = (codeTractCur)[contract] + "=" + Strformatdate::getCurrentDateString(); // 假设存在函数 getCurrentTimeString 获取当前时间的字符串表示
		//(spePos)[key] = catePortInf{ "Long",{},barBook->LastPrice,{},tarVolume };
		//char DireSlc = ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym" ? '0' : '1'; // 假设 0 表示 Buy，1 表示 Sell
		if (ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = ctx.countLimitCur[contract];
		}
		else
		{
			order.volume = -ctx.countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = ctx.barFlow[contract].back();

	}
	// 最新价格 > 短期价格 && 短期波动率 > 长期波动率
	else if (barQueue.back() > barQueue[barQueue.size() - 500] && stdShort > stdLong) {
		int tarVolume = ctx.countLimitCur[contract];
		/*std::string key = (codeTractCur)[contract] + "=" + Strformatdate::getCurrentDateString();
		(spePos)[key] = catePortInf{ "Short",{}, barBook->LastPrice, {},tarVolume };*/
		//char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '1' : '0';
		if (ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = ctx.countLimitCur[contract];
		}
		else
		{
			order.volume = -ctx.countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = ctx.barFlow[contract].back();

	}
	return order;
}

//// 平仓交易 条件
orderInfo StrategyPosClose(std::string contract, cwPositionPtr& pPosition, StrategyContext ctx, double stdLong, double stdShort) {
	orderInfo order;
	int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [contract](const futInfMng& item) {return item.contract == contract; });
	auto& barQueue = ctx.queueBar[contract];
	size_t rs = ctx.tarContracInfo[contractIndex].Rs;
	std::string FacDirection;
	if (ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym")
	{
		if (pPosition->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Long";
		}
		else if (pPosition->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Short";
		}
	}
	else
	{
		if (pPosition->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Short";
		}
		else if (pPosition->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Long";
		}
	}

	//Fac方向 =买 && （最新价格 > 短期价格 || 短期波动率<=长期波动率）
	if (FacDirection == "Long" && (barQueue.back() > barQueue[barQueue.size() - rs] || stdShort <= stdLong)) {
		if (ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = ctx.countLimitCur[contract];
		}
		else
		{
			order.volume = -ctx.countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = ctx.barFlow[contract].back();
	}
	//Fac方向 =卖 && （最新价格 < 短期价格 || 短期波动率<=长期波动率）
	else if (FacDirection == "Short" && (barQueue.back() < barQueue[barQueue.size() - rs] || stdShort <= stdLong))
	{
		if (ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = ctx.countLimitCur[contract];
		}
		else
		{
			order.volume = -ctx.countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = ctx.barFlow[contract].back();
	}
	return order;
}







