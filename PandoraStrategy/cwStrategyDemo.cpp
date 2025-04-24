#include "cwStrategyDemo.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include "SqlliteHelp.h"
#include "Strformatdate.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <cmath>
#include <exception>
#include "My_structs.h"
#include "sqlite3.h"


//全局变量
static sqlite3* cnn;
static sqlite3* cnnSys;
static int sendCount = 0;
static std::unordered_map<std::string, PositionFieldPtr> curPos;//这是持仓信息
static std::unordered_map<std::string, cwMarketDataPtr> code2data;//这是行情信息
static std::map<std::string, paraMng> verDictCur;// 策略参数对应信息
static std::unordered_map<mainCtrKeys, mainCtrValues> MainInf;//交易的主力合约对应信息
static std::unordered_map<std::string, cwInstrumentDataPtr> futInfTable;//这是合约信息
static std::string cursor_str; // 交易当天日期
static std::map<std::string, futInfMng> futInfDict;// 期货合约信息，键为string类型，值为futInfMng结构体
static std::map<std::string, std::string> codeTractCur; // 目标交易合约
static std::map<std::string, double> factorDictCur;// 因子数据
static std::map<std::string, std::vector<barFuture>> barFlow;// 历史行情数据，键为string类型，值为barFuture结构体的vector（相当于C#中的List）
static std::map<std::string, std::vector<double>> queueBar;// 行情数据，键为string类型，值为double类型的vector
static std::map<std::string, int> countLimitCur;// 合约对应交易数量
static std::map<std::string, std::vector<barFuture>> barFlowCur; // 新增行情数据
static std::map<std::string, std::vector<double>> retBar;// 收益率数据
static std::map<std::string, catePortInf> spePos;// 当前持仓情况，键为string类型，值为catePortInf结构体
static std::vector<std::string> tarCateList;



cwStrategyDemo::cwStrategyDemo()
{
}


cwStrategyDemo::~cwStrategyDemo()
{
}

void cwStrategyDemo::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm local_time = *std::localtime(&now_time);

	int hour = local_time.tm_hour;
	int minute = local_time.tm_min;
	int second = local_time.tm_sec;
	bool isTradingTime = (hour == 9 && minute >= 1) || (hour > 9 && hour < 10) || (hour == 10 && minute < 15) ||
		(hour == 10 && minute >= 30) || (hour > 10 && hour < 11) || (hour == 11 && minute < 30) ||
		(hour == 13 && minute >= 30) || (hour > 13 && hour < 14) || (hour == 14 && minute < 45);
	if (isTradingTime) {
		// 输出当前时间
		std::cout << "--- Tigger " << std::setfill('0') << std::setw(2) << hour << ":"
			<< std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second
			<< " ---------------" << std::endl;
		std::cout << "InstrumentID - Direction - Position - OpenPriceAvg - MktProfit  |  ExchangeMargin - OpenCost --->" << std::endl;
		for (const auto& pair : (curPos)) {
			const std::string& codeDR = pair.first;
			const PositionFieldPtr& posInfo = pair.second;
			if (posInfo->TodayPosition != 0) {
				std::cout << "=== " << posInfo->InstrumentID << "     " << posInfo->PosiDirection << "         " << posInfo->TodayPosition << std::endl;
			}
		}
		std::vector<cwOrderPtr> orders = cwStrategyDemo::HandBar(code2data/*当前持仓数据*/, curPos);
		//std::vector<cwOrderPtr> orders;
		for (const auto& order : orders) {
			// 增加 sendCount
			++sendCount;
			std::cout << "    Count=" << sendCount << "：" << order->InstrumentID << " => " << order->Direction << " " << order->CombOffsetFlag << " - Amount " << order->VolumeTotalOriginal << " Price " << order->LimitPrice << std::endl;
			std::string offsetFlag;
			if (order->CombOffsetFlag == "Open") {
				offsetFlag = "0";
			}
			else {
				auto it = (futInfTable).find(order->InstrumentID);
				if (it != (futInfTable).end() && it->second->ExchangeID == "SHFE") {
					offsetFlag = "3";
				}
				else {
					offsetFlag = "1";
				}
			}
		}
	}
	else if (!isTradingTime)
	{
		std::cout << "dfff" << std::endl;
		for (const auto& pair : curPos) {
			const std::string& codeDR = pair.first;
			const PositionFieldPtr& position = pair.second;
			if (position->TodayPosition != 0) {
				try {
					sendCount++;
					cwOrderPtr order;
					*order->InstrumentID = *position->InstrumentID;
					order->VolumeTotalOriginal = position->TodayPosition;
					cwFtdcDirectionType Long = '0';
					order->Direction = (position->PosiDirection == Long) ? CW_FTDC_D_Buy : CW_FTDC_D_Sell;
					std::string offsetFlag = (futInfTable[order->InstrumentID]->ExchangeID == "SHFE") ? "3" : "1";
					order->LimitPrice = (order->Direction == CW_FTDC_D_Buy) ? code2data[order->InstrumentID]->AskPrice1 + 2 * futInfTable[order->InstrumentID]->PriceTick : code2data[order->InstrumentID]->BidPrice1 - 2 * futInfTable[order->InstrumentID]->PriceTick;
					EasyInputOrder(order->InstrumentID, order->Direction, order->LimitPrice);
				}
				catch (const std::exception& ex) {
					std::cout << "ERROR " << codeDR << " ------------" << std::endl;
					std::cout << ex.what() << std::endl;
				}
			}
		}
	}
	else if (1)
	{
	}
	else
	{
	}
}

void cwStrategyDemo::OnRtnTrade(cwTradePtr pTrade)
{
}

void cwStrategyDemo::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
}

void cwStrategyDemo::OnOrderCanceled(cwOrderPtr pOrder)
{
}

void cwStrategyDemo::OnReady()
{
	SubScribePrice("IC2506");
	std::cout << "start:______" << std::endl;
	UpdateBarData();// 加载历史数据（行情 + 合约信息）
}



double cwStrategyDemo::ArithmeticMean(const std::vector<double>& arr) {//计算简单算数平均值
	if (arr.empty()) {
		return 0.0;
	}
	double sum = 0.0;
	for (const double num : arr) {
		sum += num;
	}
	return sum / static_cast<double>(arr.size());
}

double cwStrategyDemo::SampleStd(const std::vector<double>& arr) {
	double mean = ArithmeticMean(arr);
	double result = 0.0;
	for (const double num : arr) {
		result += pow(num - mean, 2);
	}
	return sqrt(result / (static_cast<double>(arr.size()) - 1));
}

std::string cwStrategyDemo::getTodayDate()
{
	std::time_t now = std::time(nullptr);
	std::tm localTime;

#if defined(_WIN32) || defined(_WIN64)
	// Windows
	localtime_s(&localTime, &now);
#else
	// Linux/macOS
	localtime_r(&now, &localTime);
#endif

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y%m%d");

	return oss.str();
}

/*INIT DAILY DATA*/
void cwStrategyDemo::UpdateBarData() {
	// 加载交易日信息
	std::cout << "UPDATE BAR DATA >>>>>>" << std::endl;

	// 获取60天近期交易日序列
	std::string sqlTradingDay = "select * from tradeday where tradingday	< '" + cursor_str + "' order by tradingday DESC Limit 60;";
	sqlite3_stmt* stmt = nullptr;
	std::vector<std::string> tradeDate;
	if (sqlite3_prepare_v2(cnnSys, sqlTradingDay.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			tradeDate.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		}
	}
	sqlite3_finalize(stmt);
	sort(tradeDate.begin(), tradeDate.end());
	std::string preCur_str = tradeDate.back();
	std::map<std::string, std::string> calendar;
	for (const std::string& x : tradeDate) {
		tm tm = {};
		std::istringstream ss(x);
		ss >> std::get_time(&tm, "%Y%m%d");
		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d");
		calendar[oss.str()] = x;
	}
	// 加载当天策略配置参数
	std::cout << " LOADING - verDictCur >>>" << std::endl;
	// -> g.verDictCur
	std::string sqlFacTag = "select * from facTag where tradingday='" + cursor_str + "';";
	sqlite3_stmt* stmt2 = nullptr;
	if (sqlite3_prepare_v2(cnn, sqlFacTag.c_str(), -1, &stmt2, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt2) == SQLITE_ROW) {
			std::string contract = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 0));
			std::string Fac = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
			std::string ver = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 2));
			int Rs = stoi(ver.substr(0, ver.find('-')));
			int Rl = stoi(ver.substr(ver.find('-') + 1));
			verDictCur.insert({ contract,{Fac, ver, "minute", Rs, Rl } });
			//(*verDictCur)[contract] = { Fac, ver, "minute", Rs, Rl };
		}
	}
	sqlite3_finalize(stmt2);
	for (const auto& kvp : verDictCur) {
		std::cout << kvp.first << " - " << kvp.second.ver << " " << kvp.second.Fac << ";" << std::endl;
	}
	// 需要参与交易的交易代码 
	std::vector<std::string> tarCateList;
	for (const auto& kvp : verDictCur) {
		tarCateList.push_back(kvp.first);
	}
	//
		 //g.futureinfo = 加载合约信息
	std::cout << " 加载合约信息 >>>" << std::endl;
	std::string sqlFutInfo = "select code, exchange, multiple, ticksize, marginrate from futureinfo;";
	sqlite3_stmt* stmt3 = nullptr;
	if (sqlite3_prepare_v2(cnnSys, sqlFutInfo.c_str(), -1, &stmt3, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt3) == SQLITE_ROW) {
			std::string prefix = reinterpret_cast<const char*>(sqlite3_column_text(stmt3, 0));
			(futInfDict)[prefix] = { reinterpret_cast<const char*>(sqlite3_column_text(stmt3, 1)),
								std::stoi(reinterpret_cast<const char*>(sqlite3_column_text(stmt3, 2))),
								std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt3, 3))),
								std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt3, 4))) };
		}
	}
	sqlite3_finalize(stmt3);
	//
		// g.MainInf
		// MainInf 需要调整 
	std::map<std::string, std::string> tradeSftDict;
	for (size_t i = 0; i < tradeDate.size(); ++i) {
		tradeSftDict[tradeDate[i]] = (i == tradeDate.size() - 1) ? cursor_str : tradeDate[i + 1];
	}
	//
	std::string sqlMainContract = "select tradingday, prefix, code, factor,accfactor from TraderOvk where tradingday>='" + tradeDate.front() + "' and tradingday<='" + preCur_str + "';";
	sqlite3_stmt* stmt4 = nullptr;
	if (sqlite3_prepare_v2(cnn, sqlMainContract.c_str(), -1, &stmt4, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt4) == SQLITE_ROW) {
			std::string prefix = reinterpret_cast<const char*>(sqlite3_column_text(stmt4, 1));
			if (find(tarCateList.begin(), tarCateList.end(), prefix) != tarCateList.end()) {
				mainCtrKeys key = { tradeSftDict[reinterpret_cast<const char*>(sqlite3_column_text(stmt4, 0))], prefix };
				mainCtrValues value = {
					reinterpret_cast<const char*>(sqlite3_column_text(stmt4, 2)),
					std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt4, 3))),
					std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt4, 4))) };
				MainInf[key] = value;
			}
		}
	}
	sqlite3_finalize(stmt4);
	// g.codeTarctCur = 目标交易合约
	for (const auto& sr : MainInf) {
		if (sr.first.date == cursor_str) {
			(codeTractCur)[sr.first.contract] = sr.second.code;
		}
	}
	// g.factorDictCur = 因子数据
	for (const auto& sr : MainInf) {
		if (sr.first.date == cursor_str) {
			(factorDictCur)[sr.second.code] = sr.second.accfactor;
		}
	}
	// g.barFlow
	// 加载历史分钟数据 >>>>>
	for (const std::string& date : tradeDate) {
		std::map<std::string, mainCtrValues> tmp;
		for (const auto& sr : (MainInf)) {
			if (sr.first.date == date) {
				tmp[sr.second.code] = sr.second;
			}
		}
		std::vector<std::string> codes;
		for (const auto& kv : tmp) {
			codes.push_back(kv.first);
		}
		std::string codeSql;
		for (const std::string& code : codes) {
			codeSql += "'" + code + "',";
		}
		codeSql.pop_back();  // 去掉最后的逗号

		// 从数据库中读取数据 D:/Database/Sqlite - UPS
		std::string dbPath = "D:/Database/Sqlite-UPS/his" + date.substr(0, 4) + ".db";
		sqlite3* cnnBar;
		sqlite3_open(dbPath.c_str(), &cnnBar);
		std::string qur_codes = "select code, tradingday, timestamp, volume, closeprice  from bf" + date + " where code in (" + codeSql + ") and actionday='" + date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2) + "'"
			" and timestamp>='09:01:00' and timestamp<='14:45:00';";
		sqlite3_stmt* stmt5;
		if (sqlite3_prepare_v2(cnnBar, qur_codes.c_str(), -1, &stmt5, nullptr) == SQLITE_OK) {
			while (sqlite3_step(stmt5) == SQLITE_ROW) {
				std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt5, 0));
				std::string contract = std::regex_replace(code, std::regex("\\d"), "");
				barFuture bf = { code, reinterpret_cast<const char*>(sqlite3_column_text(stmt5, 1)),
								reinterpret_cast<const char*>(sqlite3_column_text(stmt5, 2)),
								std::stoi(reinterpret_cast<const char*>(sqlite3_column_text(stmt5, 3))),
								std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt5, 4))) };
				if ((barFlow).count(contract) > 0) {
					(barFlow)[contract].push_back(bf);
				}
				else {
					(barFlow)[contract] = std::vector<barFuture>{ bf };
				}
			}
		}
		sqlite3_finalize(stmt5);
		sqlite3_close(cnnBar);
		std::cout << "### " << date << " over >>>" << std::endl;
		// g.queueBar = 对刚加载的历史分钟数据复权处理 <期货换月会跳价，所以需要复权使得数据连续>
	//queueBar
		for (const auto& pair : barFlow) {
			std::vector<barFuture> queueCtr(pair.second.begin(), pair.second.end());
			sort(queueCtr.begin(), queueCtr.end(), [](const barFuture& a, const barFuture& b) {
				if (a.tradingday == b.tradingday) {
					return a.timestamp < b.timestamp;
				}
				return a.tradingday < b.tradingday;
				});
			std::vector<double> tmpQueueBar;
			for (const barFuture& x : queueCtr) {
				mainCtrKeys key = { calendar[x.tradingday], pair.first };
				tmpQueueBar.push_back(x.price / (MainInf)[key].accfactor);
			}
			(queueBar)[pair.first] = tmpQueueBar;
		}
		// g.retBar = 对复权后的价格数据转为收益率数据
		std::map<std::string, std::vector<double>> retBar;
		for (const auto& pair : (queueBar)) {
			std::vector<double> tmpRetBar;
			tmpRetBar.push_back(0);
			for (size_t i = 1; i < pair.second.size(); ++i) {
				tmpRetBar.push_back(pair.second[i] / pair.second[i - 1] - 1);
			}
			retBar[pair.first] = tmpRetBar;
		}

		// countLimt = 更具前一天的收盘价计算当天交易每个合约对应的数量
		for (const auto& pair : (verDictCur)) {
			int comboMultiple = 2;  // 组合策略做几倍杠杆
			double numLimit = comboMultiple * 1000000 / 20 / (barFlow).at(pair.first).back().price / (futInfDict).at(pair.first).multiple;  // 策略杠杆数，1000000 为策略基本资金单位， 20为目前覆盖品种的近似值， 收盘价格，保证金乘数
			(countLimitCur)[pair.first] = (numLimit >= 1) ? static_cast<int>(numLimit) : 1;  // 整数 取舍一下
		}

		// g.barFlowCur  = 创建新的用来收录当天的行情数据
		for (const auto& pair : (factorDictCur)) {
			std::string contract = std::regex_replace(pair.first, std::regex("\\d"), "");
			(barFlowCur)[contract] = std::vector<barFuture>();
		}
		// 关闭数据库连接
		sqlite3_close(cnnSys);
		sqlite3_close(cnn);

	}


}

/*UPDATE FLOW*/
void cwStrategyDemo::UpdateFlow(std::unordered_map<std::string, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos) {
	// 记录最新持仓状况（方向，数量，成本价格，开仓成本，数量）
	(spePos).clear();
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
			(spePos)[positionField->InstrumentID] = cateInf;
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
std::vector<cwOrderPtr> cwStrategyDemo::StrategyTick(std::unordered_map<std::string, cwMarketDataPtr> code2data/*数据*/) {
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
std::vector<cwOrderPtr> cwStrategyDemo::StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
	std::vector<cwOrderPtr> orders;
	if ((queueBar)[contract].back() < (queueBar)[contract][(queueBar).size() - (verDictCur)[contract].Rs] && stdShort > stdLong) {
		int tarVolume = (countLimitCur)[contract];
		std::string key = (codeTractCur)[contract] + "=" + Strformatdate::getCurrentDateString(); // 假设存在函数 getCurrentTimeString 获取当前时间的字符串表示
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
		std::string key = (codeTractCur)[contract] + "=" + Strformatdate::getCurrentDateString();
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
std::vector<cwOrderPtr> cwStrategyDemo::StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort) {
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
std::vector<cwOrderPtr> cwStrategyDemo::StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO) {
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
std::vector<cwOrderPtr> cwStrategyDemo::HandBar(std::unordered_map<std::string, cwMarketDataPtr> code2data/*昨仓数据*/, std::unordered_map<std::string, PositionFieldPtr> curPos) {
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