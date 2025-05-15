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
orderInfo StrategyPosOpen(std::string contract, StrategyContext ctx, double stdLong, double stdShort) {
	orderInfo order;
	int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [contract](const futInfMng& item) {return item.contract == contract; });
	auto& barQueue = ctx.queueBar[contract];
	size_t rs = ctx.tarContracInfo[contractIndex].Rs;
	// ���¼۸� < ���ڼ۸� && ���ڲ����� > ���ڲ�����
	if (barQueue.back() < barQueue[barQueue.size() - rs] && stdShort > stdLong) {
		int tarVolume = ctx.countLimitCur[contract];
		//std::string key = (codeTractCur)[contract] + "=" + Strformatdate::getCurrentDateString(); // ������ں��� getCurrentTimeString ��ȡ��ǰʱ����ַ�����ʾ
		//(spePos)[key] = catePortInf{ "Long",{},barBook->LastPrice,{},tarVolume };
		//char DireSlc = ctx.tarContracInfo[contractIndex].Fac == "Mom_std_bar_re_dym" ? '0' : '1'; // ���� 0 ��ʾ Buy��1 ��ʾ Sell
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
	// ���¼۸� > ���ڼ۸� && ���ڲ����� > ���ڲ�����
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

//// ƽ�ֽ��� ����
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

	//Fac���� =�� && �����¼۸� > ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
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
	//Fac���� =�� && �����¼۸� < ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
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







