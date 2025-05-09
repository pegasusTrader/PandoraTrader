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

std::map<std::string, std::vector<double>> UpdateBarData() {
	//创建数据库连接
	static std::vector<futInfMng> tarContracInfo; // 目标合约结构体
	static std::map<std::string, std::vector<double>> retBar; // 目标合约真实收益率数据
	static std::map<std::string, std::vector<double>> barFlow;// 目标合约真实每日收盘价
	static std::map<std::string, int> countLimitCur;// 合约对应交易数量

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
				tarContracInfo.push_back({ contract, multiple, Rs, Rl });
			}
		}
		sqlite3_finalize(stmt);

		for (auto& futInfMng : tarContracInfo) {
			std::string ret_sql = std::format("SELECT ret FROM {} ORDER BY tradingday,timestamp ", futInfMng.contract);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, ret_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					retBar[futInfMng.contract].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (auto& futInfMng : tarContracInfo) {
			std::string closeprice_sql = std::format("SELECT closeprice FROM {} ORDER BY tradingday,timestamp ", futInfMng.contract);
			sqlite3_stmt* stmt = nullptr;
			if (sqlite3_prepare_v2(mydb, closeprice_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					barFlow[futInfMng.contract].push_back(sqlite3_column_double(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}

		for (const auto& futInfMng : tarContracInfo) {
			int comboMultiple = 2;  // 组合策略做几倍杠杆
			double numLimit = comboMultiple * 1000000 / 20 / barFlow[futInfMng.contract].back() / futInfMng.multiple;  // 策略杠杆数，1000000 为策略基本资金单位， 20为目前覆盖品种的近似值， 收盘价格，保证金乘数
			countLimitCur[futInfMng.contract] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // 整数 取舍一下
		}
		CloseDatabase(mydb);  // 最后关闭数据库连接
	}

	return retBar;
}


