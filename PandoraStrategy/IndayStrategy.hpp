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

/*UPDATE FLOW*/
void UpdateFlow(std::unordered_map<std::string, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos) {
	// ��¼���³ֲ�״���������������ɱ��۸񣬿��ֳɱ���������
	spePos.clear();
	for (const auto& pair : curPos) {
		std::string codeDR = pair.first;
		PositionFieldPtr positionField = pair.second;

		if (positionField->TodayPosition != 0) {
			catePortInf cateInf;
			cateInf.direction = positionField->PosiDirection; //�ֲַ���
			cateInf.volume = positionField->TodayPosition;//�ֲ�����
			cateInf.openCost = positionField->OpenCost;//���ֳɱ�
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
	//�� code2data ���µ���Ƭ�������ݸ��� barFlowCur & queueBar & retBar 
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
				(retBar)[contract].push_back(0); // �������ݲ����������������Ĭ��ֵ���������
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
	// ��Ҫ¼��� code ��������ᱨ��,  "ע������ʱ����û���������ݵ�"
	//cout << chrono::system_clock::now() << " - >>>" << endl;
}

/*STRATEGY PART*/
std::vector<cwOrderPtr> StrategyTick(std::unordered_map<std::string, cwMarketDataPtr> code2data/*����*/) {
	// ��ǰ������Ƶ��߼��Ƕ�ÿ��Ʒ�ֶ����е����Ĳ��Թ���, ֻ���ڲ�λ�����Ͻ��е�Ȩ�ص�ȥ����,����ÿ��Ʒ�ֵĽ����źŶ�Ӧ�õ��������� 

	std::vector<cwOrderPtr> ordersTar;
	std::cout << " start " << "StrategyTick " << std::endl;
	for (const std::string& contract : tarCateList) {
		try {
			std::cout << "##  " << contract << std::endl;
			cwMarketDataPtr barBook = code2data.at(codeTractCur.at(contract));

			// ���� stdShort
			std::vector<double> retBarSubsetShort(std::prev(retBar[contract].end(), verDictCur[contract].Rs), retBar[contract].end());
			double stdShort = SampleStd(retBarSubsetShort);

			// ���� stdLong
			std::vector<double> retBarSubsetLong(std::prev(retBar[contract].end(), verDictCur[contract].Rl), retBar[contract].end());
			double stdLong = SampleStd(retBarSubsetLong);

			// ����ÿ��Ʒ��ֱ������ ����Ϲ̶�������
			long posV = ((spePos).count((codeTractCur)[contract]) > 0) ? (spePos)[(codeTractCur)[contract]].volume : 0;
			long posC = posV; // ��ƽ�����
			long posO = (countLimitCur)[contract] - posC; // �ɿ������  

			std::cout << contract << " = PosC " << posC << " - PosO " << posO << "   Fac = " << (verDictCur)[contract].Fac << " >>>" << std::endl;

			// Spe Sta 0903 <�ɿ���λС�� 0 �����Ѿ����ж����ͷ�磬��Ҫ����ƽ�ִ��� �������>
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

//// ���ֽ��� ����
std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
	std::vector<cwOrderPtr> orders;
	if ((queueBar)[contract].back() < (queueBar)[contract][(queueBar).size() - (verDictCur)[contract].Rs] && stdShort > stdLong) {
		int tarVolume = (countLimitCur)[contract];
		std::string key = (codeTractCur)[contract] + "=" + GetTodayDate(); // ������ں��� getCurrentTimeString ��ȡ��ǰʱ����ַ�����ʾ
		(spePos)[key] = catePortInf{ "Long",{},barBook->LastPrice,{},tarVolume };
		char DireSlc = (verDictCur)[contract].Fac == "Mom_std_bar_re_dym" ? '0' : '1'; // ���� 0 ��ʾ Buy��1 ��ʾ Sell

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

//// ƽ�ֽ��� ����
std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
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

// ����ƽ�ִ���ʽ
std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO) {
	std::vector<cwOrderPtr> orders;
	int tarVolume = abs(static_cast<int>(posO));
	std::string dire = (spePos)[(codeTractCur)[contract]].direction;
	char DireSlc = ((spePos)[(codeTractCur)[contract]].direction == "Long") ? '1' : '0';  // ���� 1 ��ʾ Sell��0 ��ʾ Buy
	cwOrderPtr order = std::make_shared<ORDERFIELD>();
	strcpy(order->InstrumentID, (codeTractCur)[contract].c_str());
	order->Direction = DireSlc;
	strcpy(order->CombOffsetFlag, "Close");
	order->VolumeTotalOriginal = tarVolume;
	order->LimitPrice = (*barBook).LastPrice;
	orders.push_back(order);
	return orders;
}

//// ���ĺ���
std::vector<cwOrderPtr> HandBar(std::unordered_map<std::string, cwMarketDataPtr> code2data/*�������*/, std::unordered_map<std::string, PositionFieldPtr> curPos) {
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
		if (ord->Direction == 0) {  // ���� 0 ��ʾ Buy
			std::string instrument = regex_replace(ord->InstrumentID, std::regex("\\d"), "");
			(*ord).LimitPrice += (futInfDict)[instrument].ticksize * 2;
		}
		else if ((*ord).Direction == 1) {  // ���� 1 ��ʾ Sell
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
		// ����ʹ�÷�Χ for ѭ�������ﲻ��Ҫʹ���������£��޸�ֱ����Ч

	}

	return ordersTar;

}