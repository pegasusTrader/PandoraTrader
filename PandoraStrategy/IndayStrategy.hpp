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
StrategyContext  UpdateBarData() {
	StrategyContext ctx;
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
				ctx.tarContracInfo.push_back({ contract, multiple, Fac ,Rs, Rl, code, accfactor });
			}
		}
		else if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
			std::cerr << "SQL prepare failed: " << sqlite3_errmsg(mydb) << std::endl;
		}
		sqlite3_finalize(stmt);

		for (auto& futInfMng : ctx.tarContracInfo) {
			std::string ret_sql = std::format("SELECT ret FROM {} ORDER BY tradingday,timestamp ", futInfMng.contract);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, ret_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					ctx.retBar[futInfMng.contract].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (auto& futInfMng : ctx.tarContracInfo) {
			std::string closeprice_sql = std::format("SELECT closeprice FROM {} ORDER BY tradingday,timestamp ", futInfMng.contract);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, closeprice_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					ctx.barFlow[futInfMng.contract].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (auto& futInfMng : ctx.tarContracInfo) {
			std::string real_close_sql = std::format("SELECT real_close FROM {} ORDER BY tradingday,timestamp ", futInfMng.contract);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, real_close_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					ctx.queueBar[futInfMng.contract].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (const auto& futInfMng : ctx.tarContracInfo) {
			int comboMultiple = 2;  // 组合策略做几倍杠杆
			int tarCount = ctx.tarContracInfo.size();  // 目标合约数量
			double numLimit = comboMultiple * 1000000 / tarCount / ctx.barFlow[futInfMng.contract].back() / futInfMng.multiple;  // 策略杠杆数，1000000 为策略基本资金单位， 20为目前覆盖品种的近似值， 收盘价格，保证金乘数
			ctx.countLimitCur[futInfMng.contract] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // 整数 取舍一下
		}
		CloseDatabase(mydb);  // 最后关闭数据库连接
	}

	return ctx;
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
orderInfo StrategyPosClose(std::string contract, StrategyContext ctx, double stdLong, double stdShort) {
	std::vector<cwOrderPtr> orders;
	std::string code = (codeTractCur)[contract];// 当前持仓代码
	std::string dire = (spePos)[code].direction; // 当前持仓方向
	auto DireREFunc = [](const std::string& x) -> std::string {
		if (x == "Long") {
			return "Short";
		}
		else if (x == "Short") {
			return "Long";
		}
		else {
			return "Miss";
		}
		};
	std::string FacDirection = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? dire : DireREFunc(dire);//根据策略类型调整交易方向Fac
	//Fac方向 =买 && （最新价格 > 短期价格 || 短期波动率<=长期波动率）
	if (FacDirection == "Long" && ((queueBar)[contract].back() > (queueBar)[contract][(queueBar)[contract].size() - (verDictCur)[contract].Rs] || stdShort <= stdLong)) {
		int tarVolume = (spePos)[code].volume;
		(spePos).erase(code);

		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '1' : '0';  // 假设 1 表示 Sell，0 表示 Buy
		cwOrderPtr order = std::make_shared<ORDERFIELD>();
		strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
		order->Direction = DireSlc;
		strcpy(order->CombOffsetFlag, "Close");
		order->VolumeTotalOriginal = tarVolume;
		order->LimitPrice = (*barBook).LastPrice;
		orders.push_back(order);
	}
	else if (FacDirection == "Short" && ((queueBar)[contract].back() < (queueBar)[contract][(queueBar)[contract].size() - (verDictCur)[contract].Rs] || stdShort <= stdLong)) {
		int tarVolume = (spePos)[code].volume;
		(spePos).erase(code);
		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '0' : '1';  // 假设 1 表示 Sell，0 表示 Buy
		cwOrderPtr order = std::make_shared<ORDERFIELD>();
		strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
		order->Direction = DireSlc;
		strcpy(order->CombOffsetFlag, "Close");
		order->VolumeTotalOriginal = tarVolume;
		order->LimitPrice = (*barBook).LastPrice;
		orders.push_back(order);
	}
	return orders;
}







