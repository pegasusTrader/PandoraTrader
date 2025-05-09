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

/*UPDATE FLOW*/
void UpdateFlow(std::unordered_map<std::string, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos) {
	// 记录最新持仓状况（方向，数量，成本价格，开仓成本，数量）
	spePos.clear();
	for (const auto& pair : curPos) {
		std::string codeDR = pair.first;
		PositionFieldPtr positionField = pair.second;

		if (positionField->TodayPosition != 0) {
			catePortInf cateInf;
			cateInf.direction = positionField->PosiDirection; //持仓方向
			cateInf.volume = positionField->TodayPosition;//持仓数量
			cateInf.openCost = positionField->OpenCost;//开仓成本
			std::string instrumentIDWithoutDigits = std::regex_replace(positionField->InstrumentID, std::regex("\\d"), "");
			if ((futInfDict).count(instrumentIDWithoutDigits) > 0) {
				cateInf.costPrice = (positionField->OpenCost / positionField->TodayPosition / (futInfDict)[instrumentIDWithoutDigits].multiple);
			}
			else {
				std::cout << "Error: No multiple information for " << positionField->InstrumentID << std::endl;
				continue;
			}
			if (cateInf.direction == "Long") {
				cateInf.amount = cateInf.volume;
			}
			else {
				cateInf.amount = -1 * cateInf.volume;
			}
			spePos[positionField->InstrumentID] = cateInf;
		}
	}
	//用 code2data 最新的切片行情数据更新 barFlowCur & queueBar & retBar 
/*	for (const auto& [key, value] : (*factorDictCur)){
		cwFtdcInstrumentIDType code =  *key ;*/
		//}
	for (const auto& pair : factorDictCur) {
		std::string code = { pair.first };
		double factor = pair.second;
		if (code2data.count(code) > 0) {
			std::string contract = std::regex_replace(code, std::regex("\\d"), "");
			(barFlowCur)[contract].push_back(barFuture{
				code2data[code]->InstrumentID,
				code2data[code]->TradingDay,
				code2data[code]->UpdateTime,
				code2data[code]->Volume,
				code2data[code]->LastPrice,
				});
			// g.queueBar/g.retBar -> update
			double curPrice = code2data[code]->LastPrice;
			(queueBar)[contract].push_back(curPrice / factor);
			if ((queueBar)[contract].size() >= 2) {
				(retBar)[contract].push_back((curPrice / factor) / (queueBar)[contract][(queueBar)[contract].size() - 2] - 1);
			}
			else {
				(retBar)[contract].push_back(0); // 处理数据不足的情况，例如添加默认值或不添加数据
			}
			if ((queueBar)[contract].size() > 1) {
				(queueBar)[contract].erase((queueBar)[contract].begin());
				(retBar)[contract].erase((retBar)[contract].begin());
			}
		}
		else {
			std::cout << "MISS " << code << " Info >>> " << std::endl;
		}
	}
	// 需要录入的 code 不存在则会报错,  "注意休市时间是没有行情数据的"
	//cout << chrono::system_clock::now() << " - >>>" << endl;
}

/*STRATEGY PART*/
std::vector<cwOrderPtr> StrategyTick(std::unordered_map<std::string, cwMarketDataPtr> code2data/*数据*/) {
	// 当前策略设计的逻辑是对每个品种都进行单独的测试管理, 只是在仓位设置上进行等权重的去分配,所以每个品种的交易信号都应该单独做计算 

	std::vector<cwOrderPtr> ordersTar;
	std::cout << " start " << "StrategyTick " << std::endl;
	for (const std::string& contract : tarCateList) {
		try {
			std::cout << "##  " << contract << std::endl;
			cwMarketDataPtr barBook = code2data.at(codeTractCur.at(contract));

			// 计算 stdShort
			std::vector<double> retBarSubsetShort(std::prev(retBar[contract].end(), verDictCur[contract].Rs), retBar[contract].end());
			double stdShort = SampleStd(retBarSubsetShort);

			// 计算 stdLong
			std::vector<double> retBarSubsetLong(std::prev(retBar[contract].end(), verDictCur[contract].Rl), retBar[contract].end());
			double stdLong = SampleStd(retBarSubsetLong);

			// 对于每个品种直接设置 单组合固定的张数
			long posV = ((spePos).count((codeTractCur)[contract]) > 0) ? (spePos)[(codeTractCur)[contract]].volume : 0;
			long posC = posV; // 可平仓组合
			long posO = (countLimitCur)[contract] - posC; // 可开仓组合  

			std::cout << contract << " = PosC " << posC << " - PosO " << posO << "   Fac = " << (verDictCur)[contract].Fac << " >>>" << std::endl;

			// Spe Sta 0903 <可开仓位小于 0 代表已经开有多余的头寸，需要额外平仓处理， 特殊情况>
			if (posO < 0) {
				auto orders = StrategyPosSpeC(contract, barBook, posO);
				ordersTar.insert(ordersTar.end(), orders.begin(), orders.end());
				continue;
			}

			// trader 
			if (posC > 0) {
				auto orders = StrategyPosClose(contract, barBook, stdLong, stdShort);
				ordersTar.insert(ordersTar.end(), orders.begin(), orders.end());
			}

			if (posO > 0) {
				auto orders = StrategyPosOpen(contract, barBook, stdLong, stdShort);
				ordersTar.insert(ordersTar.end(), orders.begin(), orders.end());
			}
		}
		catch (const std::exception& ex) {
			std::cout << "ERROR " << contract << " ------------" << std::endl;
			std::cout << ex.what() << std::endl;
		}
	}
	return ordersTar;
}

//// 开仓交易 条件
std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
	std::vector<cwOrderPtr> orders;
	if ((queueBar)[contract].back() < (queueBar)[contract][(queueBar).size() - (verDictCur)[contract].Rs] && stdShort > stdLong) {
		int tarVolume = (countLimitCur)[contract];
		std::string key = (codeTractCur)[contract] + "=" + GetTodayDate(); // 假设存在函数 getCurrentTimeString 获取当前时间的字符串表示
		(spePos)[key] = catePortInf{ "Long",{},barBook->LastPrice,{},tarVolume };
		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '0' : '1'; // 假设 0 表示 Buy，1 表示 Sell

		//cwOrderPtr order;
		cwOrderPtr order = std::make_shared<ORDERFIELD>();
		strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
		order->Direction = DireSlc;
		strcpy(order->CombOffsetFlag, "open");
		order->VolumeTotalOriginal = tarVolume;
		order->LimitPrice = (*barBook).LastPrice;
		orders.push_back(order);
	}
	else if ((queueBar)[contract].back() > (queueBar)[contract][(queueBar).size() - 500] && stdShort > stdLong) {
		int tarVolume = (countLimitCur)[contract];
		std::string key = (codeTractCur)[contract] + "=" + GetTodayDate();
		(spePos)[key] = catePortInf{ "Short",{}, barBook->LastPrice, {},tarVolume };
		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '1' : '0';

		cwOrderPtr order = std::make_shared<ORDERFIELD>();
		strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
		order->Direction = DireSlc;
		strcpy(order->CombOffsetFlag, "open");
		order->VolumeTotalOriginal = tarVolume;
		order->LimitPrice = (*barBook).LastPrice;
		orders.push_back(order);
	}
	return orders;
}

//// 平仓交易 条件
std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
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

// 特殊平仓处理方式
std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO) {
	std::vector<cwOrderPtr> orders;
	int tarVolume = abs(static_cast<int>(posO));
	std::string dire = (spePos)[(codeTractCur)[contract]].direction;
	char DireSlc = ((spePos)[(codeTractCur)[contract]].direction == "Long") ? '1' : '0';  // 假设 1 表示 Sell，0 表示 Buy
	cwOrderPtr order = std::make_shared<ORDERFIELD>();
	strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
	order->Direction = DireSlc;
	strcpy(order->CombOffsetFlag, "Close");
	order->VolumeTotalOriginal = tarVolume;
	order->LimitPrice = (*barBook).LastPrice;
	orders.push_back(order);
	return orders;
}

//// 核心函数
std::vector<cwOrderPtr> HandBar(std::unordered_map<std::string, cwMarketDataPtr> code2data/*昨仓数据*/, std::unordered_map<std::string, PositionFieldPtr> curPos) {
	auto sTime = std::chrono::system_clock::now();
	std::vector<std::string> ff;
	for (const auto& pair : codeTractCur) {
		std::string key = pair.first;
		cwFtdcInstrumentIDType value = { *pair.second.c_str() };
		auto it = find((tarCateList).begin(), (tarCateList).end(), key);
		if (it != (tarCateList).end()) {
			ff.push_back(value);
		}
	}
	while (true) {
		bool allContained = true;
		for (const auto& code : ff) {
			if (code2data.count(code) >= 0) {
				allContained = false;
				break;
			}
		}
		if (allContained) break;
		std::cout << "Sleep for 10 seconds.";
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::cout << std::string(5, ' ') << "Count " << code2data.size() << ";";
		std::cout << std::endl;
		auto span = std::chrono::system_clock::now() - sTime;
		auto ss = std::chrono::duration_cast<std::chrono::seconds>(span).count();
		if (ss > 59) {
			return std::vector<cwOrderPtr>();
		}
	}
	UpdateFlow(code2data, curPos);
	std::cout << " --- " << "updateFLow --------------------" << std::endl;

	std::vector<cwOrderPtr> ordersTar = StrategyTick(code2data);
	std::cout << " +++ " << ordersTar.size() << std::endl;

	int i = 0;
	for (size_t i = 0; i < ordersTar.size(); ++i) {
		cwOrderPtr ord = ordersTar[i];
		/* cwOrderPtr ord = ordersTar[i];*/
		if (ord->Direction == 0) {  // 假设 0 表示 Buy
			std::string instrument = regex_replace(ord->InstrumentID, std::regex("\\d"), "");
			(*ord).LimitPrice += (futInfDict)[instrument].ticksize * 2;
		}
		else if ((*ord).Direction == 1) {  // 假设 1 表示 Sell
			std::string instrument = regex_replace((*ord).InstrumentID, std::regex("\\d"), "");
			(*ord).LimitPrice -= (futInfDict)[instrument].ticksize * 2;
		}


		try {
			if (code2data.count((*ord).InstrumentID) > 0) {
				(*ord).LimitPrice = min((*ord).LimitPrice, code2data[((*ord).InstrumentID)]->UpperLimitPrice);
				(*ord).LimitPrice = max((*ord).LimitPrice, code2data[((*ord).InstrumentID)]->LowerLimitPrice);
			}
			else {
				std::cout << "###### Miss " << (*ord).InstrumentID << " LimitPrice >>>>>>>>>>>>>>>" << std::endl;
			}
		}
		catch (const std::exception& e) {
			std::cout << "###### Miss " << (*ord).InstrumentID << " LimitPrice >>>>>>>>>>>>>>>" << std::endl;
		}


		try {
			if ((*ord).CombOffsetFlag == "Open") {
				if (code2data.count((*ord).InstrumentID) > 0) {
					double upperLower = 0.85 * code2data.at((*ord).InstrumentID)->UpperLimitPrice + 0.15 * code2data.at((*ord).InstrumentID)->LowerLimitPrice;
					double lowerUpper = 0.15 * code2data.at((*ord).InstrumentID)->UpperLimitPrice + 0.85 * code2data.at((*ord).InstrumentID)->LowerLimitPrice;


					if ((*ord).LimitPrice > upperLower && (*ord).Direction == 1) {
						ord = cwOrderPtr();
					}
					else if ((*ord).LimitPrice < lowerUpper && (*ord).Direction == 0) {
						ord = cwOrderPtr();
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cout << "###### Miss2 " << (*ord).InstrumentID << " LimitPrice >>>>>>>>>>>>>>>" << std::endl;
		}
		// 由于使用范围 for 循环，这里不需要使用索引更新，修改直接生效

	}

	return ordersTar;

}