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

//// ����������
void UpdateBarData(std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur) {

	//�������ݿ�����
	sqlite3* mydb = OpenDatabase("dm.db");
	if (mydb) {
		std::string tar_contract_sql = "SELECT * FROM futureinfo;";
		sqlite3_stmt* stmt = nullptr;
		if (sqlite3_prepare_v2(mydb, tar_contract_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				std::string contract = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));//Ŀ���Լ
				int multiple = sqlite3_column_int(stmt, 1);//��Լ����
				std::string Fac = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));//Fac
				int Rs = sqlite3_column_int(stmt, 3); // ...
				int Rl = sqlite3_column_int(stmt, 4); // ...
				std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)); //Ŀ���Լ����
				double accfactor = sqlite3_column_double(stmt, 6);//��֤����
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
			int comboMultiple = 2;  // ��ϲ����������ܸ�
			int tarCount = tarFutInfo.size();  // Ŀ���Լ����
			double numLimit = comboMultiple * 1000000 / tarCount / comBarInfo.barFlow[futInfMng.first].back() / futInfMng.second.multiple;  // ���Ըܸ�����1000000 Ϊ���Ի����ʽ�λ�� 20ΪĿǰ����Ʒ�ֵĽ���ֵ�� ���̼۸񣬱�֤�����
			countLimitCur[futInfMng.first] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // ���� ȡ��һ��
		}
		CloseDatabase(mydb);  // ���ر����ݿ�����
	}
}

//// ���ֽ��� ����
orderInfo StrategyPosOpen(std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur) {

	// �����׼��
	// ���� stdShort
	std::vector<double> retBarSubsetShort(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rs), ctx.retBar[currentContract].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// ���� stdLong
	std::vector<double> retBarSubsetLong(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rl), ctx.retBar[currentContract].end());
	double stdLong = SampleStd(retBarSubsetLong);

	orderInfo order;
	auto& barQueue = comBarInfo.queueBar[contract];
	size_t rs = tarFutInfo[contract].Rs;
	// ���¼۸� < ���ڼ۸� && ���ڲ����� > ���ڲ�����
	if (barQueue.back() < barQueue[barQueue.size() - rs] && stdShort > stdLong) {
		int tarVolume = countLimitCur[contract];
		if (tarFutInfo[contract].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[contract];
		}
		else
		{
			order.volume = -countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = comBarInfo.barFlow[contract].back();

	}
	// ���¼۸� > ���ڼ۸� && ���ڲ����� > ���ڲ�����
	else if (barQueue.back() > barQueue[barQueue.size() - 500] && stdShort > stdLong) {
		int tarVolume = countLimitCur[contract];
		if (tarFutInfo[contract].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[contract];
		}
		else
		{
			order.volume = -countLimitCur[contract];
		}
		order.szInstrumentID = contract;
		order.price = comBarInfo.barFlow[contract].back();

	}
	return order;
}

//// ƽ�ֽ��� ����
orderInfo StrategyPosClose(std::map<std::string, futInfMng>& tarFutInfo, barInfo& comBarInfo, std::map<std::string, int>& countLimitCur) {
	// �����׼��
	// ���� stdShort
	std::vector<double> retBarSubsetShort(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rs), ctx.retBar[currentContract].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// ���� stdLong
	std::vector<double> retBarSubsetLong(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rl), ctx.retBar[currentContract].end());
	double stdLong = SampleStd(retBarSubsetLong);
	orderInfo order;
	auto& barQueue = comBarInfo.queueBar[contract];
	size_t rs = tarFutInfo[contract].Rs;
	std::string FacDirection;
	if (tarFutInfo[contract].Fac == "Mom_std_bar_re_dym")
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

	//Fac���� =�� && �����¼۸� > ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
	if (FacDirection == "Long" && (barQueue.back() > barQueue[barQueue.size() - rs] || stdShort <= stdLong)) {
		if (tarFutInfo[contract].Fac == "Mom_std_bar_re_dym")
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
	//Fac���� =�� && �����¼۸� < ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
	else if (FacDirection == "Short" && (barQueue.back() < barQueue[barQueue.size() - rs] || stdShort <= stdLong))
	{
		if (tarFutInfo[contract].Fac == "Mom_std_bar_re_dym")
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







