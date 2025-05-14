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
StrategyContext  UpdateBarData() {
	StrategyContext ctx;
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
			int comboMultiple = 2;  // ��ϲ����������ܸ�
			int tarCount = ctx.tarContracInfo.size();  // Ŀ���Լ����
			double numLimit = comboMultiple * 1000000 / tarCount / ctx.barFlow[futInfMng.contract].back() / futInfMng.multiple;  // ���Ըܸ�����1000000 Ϊ���Ի����ʽ�λ�� 20ΪĿǰ����Ʒ�ֵĽ���ֵ�� ���̼۸񣬱�֤�����
			ctx.countLimitCur[futInfMng.contract] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // ���� ȡ��һ��
		}
		CloseDatabase(mydb);  // ���ر����ݿ�����
	}

	return ctx;
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
orderInfo StrategyPosClose(std::string contract, StrategyContext ctx, double stdLong, double stdShort) {
	std::vector<cwOrderPtr> orders;
	std::string code = (codeTractCur)[contract];// ��ǰ�ֲִ���
	std::string dire = (spePos)[code].direction; // ��ǰ�ֲַ���
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
	std::string FacDirection = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? dire : DireREFunc(dire);//���ݲ������͵������׷���Fac
	//Fac���� =�� && �����¼۸� > ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
	if (FacDirection == "Long" && ((queueBar)[contract].back() > (queueBar)[contract][(queueBar)[contract].size() - (verDictCur)[contract].Rs] || stdShort <= stdLong)) {
		int tarVolume = (spePos)[code].volume;
		(spePos).erase(code);

		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '1' : '0';  // ���� 1 ��ʾ Sell��0 ��ʾ Buy
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
		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '0' : '1';  // ���� 1 ��ʾ Sell��0 ��ʾ Buy
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







