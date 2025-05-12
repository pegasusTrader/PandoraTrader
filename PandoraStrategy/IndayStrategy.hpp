#pragma once
#include "cwBasicKindleStrategy.h"
#include <iostream>
#include <format>
#include <algorithm>
#include <map>
#include <regex>
#include "sqlite3.h"
#include "MyStructs.h"
#include "SQLiteHelp.hpp"
#include "Utils.hpp"

StrategyContext  UpdateBarData() {
	StrategyContext ctx;
	//创建数据库连接
	sqlite3* mydb = OpenDatabase("dm.db");
	if (mydb) {
		std::string tar_contract_sql = "SELECT * FROM futureinfo;";
		sqlite3_stmt* stmt = nullptr;
		if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				std::string contract = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));//合约
				int multiple = sqlite3_column_int(stmt, 1);//合约乘数
				double Rs = sqlite3_column_double(stmt, 2); //跳价
				double Rl = sqlite3_column_double(stmt, 3); //保证金率
				std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); //目标合约代码
				double accfactor = sqlite3_column_double(stmt, 5);
				ctx.tarContracInfo.push_back({ contract, multiple, Rs, Rl, code, accfactor });
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


