#include "cwStrategyDemo.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <cmath>
#include <exception>
#include "MyStructs.h"
#include "sqlite3.h"
#include <format>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include "Utils.hpp"


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
}

void cwStrategyDemo::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {
	if (pPriceData.get() == NULL)
	{
		return;
	}

	code2data[pPriceData->InstrumentID] = pPriceData;
	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	//if ((hour == 9 && minute >= 1) || (hour > 9 && hour < 10) || (hour == 10 && minute < 15) ||
	//	(hour == 10 && minute >= 30) || (hour > 10 && hour < 11) || (hour == 11 && minute < 30) ||
	//	(hour == 13 && minute >= 30) || (hour > 13 && hour < 14) || (hour == 14 && minute < 45)) {
	//	// 输出当前时间
	//	std::cout << "当前时间:需要填写" << std::endl;
	//	std::cout << "--- Tigger " << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " ---------------" << std::endl;
	//	std::cout << "InstrumentID - Direction - Position - OpenPriceAvg - MktProfit  |  ExchangeMargin - OpenCost --->" << std::endl;

	//	//输出当前持仓情况
	//	for (const auto& pair : curPos) {
	//		double OpenPriceAvg = curPos[pair.first]->AveragePosPrice;
	//		double absMktProfit = curPos[pair.first]->PositionProfit;
	//		double MktProfit = curPos[pair.first]->PosiDirection == CW_FTDC_D_Buy ? absMktProfit : -1 * absMktProfit;
	//		if (curPos[pair.first]->TodayPosition != 0) {
	//			std::cout << "=====" << curPos[pair.first]->InstrumentID << "     " << curPos[pair.first]->PosiDirection << "     " << curPos[pair.first]->TodayPosition
	//				<< OpenPriceAvg << "     " << MktProfit << "     " << curPos[pair.first]->ExchangeMargin << "     " << curPos[pair.first]->ExchangeMargin << "     "
	//				<< curPos[pair.first]->OpenCost << "     " << std::endl;
	//		}
	//	}

	//	std::vector<cwOrderPtr> orders = cwStrategyDemo::HandBar(code2data/*当前持仓数据*/, curPos);
	//	for (const auto& order : orders) {
	//		// 增加 sendCount
	//		++sendCount;
	//		std::cout << "    Count=" << sendCount << "：" << order->InstrumentID << " => " << order->Direction << " " << order->CombOffsetFlag << " - Amount " << order->VolumeTotalOriginal << " Price " << order->LimitPrice << std::endl;
	//		std::string offsetFlag;
	//		/*		if (order->CombOffsetFlag == "Open") {
	//					offsetFlag = "0";
	//				}
	//				else {
	//					auto it = futInfTable.find(order->InstrumentID);
	//					if (it != futInfTable.end() && it->second->ExchangeID == "SHFE") {
	//						offsetFlag = "3";
	//					}
	//					else {
	//						offsetFlag = "1";
	//					}
	//				}*/
	//		EasyInputMultiOrder(order->InstrumentID, order->VolumeTotalOriginal, order->LimitPrice);
	//		if (orders.size() > 0) {
	//			std::cout << "--- SUBMIT ORDERS ===========" << std::endl;
	//		}
	//		std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // 等待 5 秒
	//		std::cout << "--- Update curPosInfo ===========" << std::endl; // 更新持仓信息
	//	}
	//}
	//else if ((hour == 14 && minute >= 45) || (hour == 15 && minute == 0))
	//{
	//	std::cout << "dfff" << std::endl;
	//	for (const auto& pair : curPos) {
	//		const std::string& codeDR = pair.first;
	//		const PositionFieldPtr& position = pair.second;
	//		if (position->TodayPosition != 0) {
	//			try {
	//				sendCount++;
	//				cwOrderPtr order;
	//				*order->InstrumentID = *position->InstrumentID;
	//				order->VolumeTotalOriginal = position->TodayPosition;
	//				cwFtdcDirectionType Long = '0';
	//				order->Direction = (position->PosiDirection == Long) ? CW_FTDC_D_Buy : CW_FTDC_D_Sell;
	//				std::string offsetFlag = (futInfTable[order->InstrumentID]->ExchangeID == "SHFE") ? "3" : "1";
	//				order->LimitPrice = (order->Direction == CW_FTDC_D_Buy) ? code2data[order->InstrumentID]->AskPrice1 + 2 * futInfTable[order->InstrumentID]->PriceTick : code2data[order->InstrumentID]->BidPrice1 - 2 * futInfTable[order->InstrumentID]->PriceTick;
	//				EasyInputOrder(order->InstrumentID, order->Direction, order->LimitPrice);
	//			}
	//			catch (const std::exception& ex) {
	//				std::cout << "ERROR " << codeDR << " ------------" << std::endl;
	//				std::cout << ex.what() << std::endl;
	//			}
	//		}
	//	}
	//}
	//else if ((hour == 15 && minute >= 0 && minute < 10))
	//{
	//	std::cout << "----------------- TraderOver ----------------" << std::endl;
	//	std::cout << "--------------- StoreBaseData ---------------" << std::endl;
	//	std::cout << "---------------------------------------------" << std::endl;
	//}
	//else
	//{
	//	if (minute == 0 || minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50) {
	//		std::cout << "waiting" << hour << "::" << minute << "::" << second << std::endl;
	//	}
	//}
};

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
	/*SubScribePrice("IC2506");
	std::cout << "start:______" << std::endl;*/
	//UpdateBarData();// 加载历史数据（行情 + 合约信息）
	auto kSeries = SubcribeKindle("IF2506", cwKINDLE_TIMESCALE_1MIN, 50);
}