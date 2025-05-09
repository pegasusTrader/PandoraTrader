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
	//�������ݿ�����
	static std::vector<futInfMng> tarContracInfo; // Ŀ���Լ�ṹ��
	static std::map<std::string, std::vector<double>> retBar; // Ŀ���Լ��ʵ����������
	static std::map<std::string, std::vector<double>> barFlow;// Ŀ���Լ��ʵÿ�����̼�
	static std::map<std::string, int> countLimitCur;// ��Լ��Ӧ��������

	sqlite3* mydb = OpenDatabase("dm.db");
	if (mydb) {
		std::string tar_contract_sql = "SELECT * FROM futureinfo;";
		sqlite3_stmt* stmt = nullptr;
		if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				std::string contract = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));//��Լ
				int multiple = sqlite3_column_int(stmt, 1);//��Լ����
				double Rs = sqlite3_column_double(stmt, 2); //����
				double Rl = sqlite3_column_double(stmt, 3); //��֤����
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
			int comboMultiple = 2;  // ��ϲ����������ܸ�
			double numLimit = comboMultiple * 1000000 / 20 / barFlow[futInfMng.contract].back() / futInfMng.multiple;  // ���Ըܸ�����1000000 Ϊ���Ի����ʽ�λ�� 20ΪĿǰ����Ʒ�ֵĽ���ֵ�� ���̼۸񣬱�֤�����
			countLimitCur[futInfMng.contract] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // ���� ȡ��һ��
		}
		CloseDatabase(mydb);  // ���ر����ݿ�����
	}

	return retBar;
}


