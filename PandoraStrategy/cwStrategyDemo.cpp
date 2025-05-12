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
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <format>
#include "MyStructs.h"
#include "sqlite3.h"
#include "IndayStrategy.hpp"
#include "Utils.hpp"

static StrategyContext ctx = UpdateBarData();

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

	std::cout << pKindleSeries->GetInstrumentID() << std::endl;
	std::cout << pKindleSeries->GetLastKindleStick()->Close << std::endl;

	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;
	//barFolw更新
	ctx.barFlow[pKindleSeries->GetInstrumentID()].push_back(pKindleSeries->GetLastKindleStick()->Close);
	//queueBar更新
	std::string constrct_id = pKindleSeries->GetInstrumentID();
	int contract_index = findIndex<futInfMng>(ctx.tarContracInfo, [constrct_id](const futInfMng& item) {return item.contract == constrct_id; });
	ctx.queueBar[pKindleSeries->GetInstrumentID()].push_back(pKindleSeries->GetLastKindleStick()->Close / ctx.tarContracInfo[contract_index].accfactor);
	//ret更新
	double last = ctx.queueBar[pKindleSeries->GetInstrumentID()][ctx.queueBar[pKindleSeries->GetInstrumentID()].size() - 1];
	double secondLast = ctx.queueBar[pKindleSeries->GetInstrumentID()][ctx.queueBar[pKindleSeries->GetInstrumentID()].size() - 2];
	ctx.retBar[pKindleSeries->GetInstrumentID()].push_back(last / secondLast - 1);

	//删除首位元素
	ctx.barFlow[pKindleSeries->GetInstrumentID()].pop_front();
	ctx.queueBar[pKindleSeries->GetInstrumentID()].pop_front();
	ctx.retBar[pKindleSeries->GetInstrumentID()].pop_front();


	// 用code2data最新的切片行情数据更新 barFlowCur & queueBar & retBar 明天要做的内容
	// handbar 生成订单
	// 下订单
	// 临近收盘 清仓处理
	// 打印一些东西



		//std::cout << "--- 当前时间 " << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " ---------------" << std::endl;
		//std::cout << std::setfill(' ');
		//std::cout << std::left  // 左对齐
		//	<< std::setw(15) << "InstrumentID"
		//	<< std::setw(15) << "Direction"
		//	<< std::setw(15) << "Position"
		//	<< std::setw(15) << "OpenPriceAvg"
		//	<< std::setw(15) << "MktProfit"
		//	<< std::setw(20) << "ExchangeMargin"
		//	<< std::setw(15) << "OpenCost"
		//	<< "--->" << std::endl;
		//std::map<std::string, cwPositionPtr> PositionMap;
		//GetPositions(PositionMap);
		/*for (const auto& pair : PositionMap) {
			std::cout << std::left
				<< std::setw(15) << pair.first
				<< std::setw(15) << pair.second->LongPosition->PosiDirection
				<< std::setw(15) << pair.second->LongPosition->TodayPosition
				<< std::setw(15) << pair.second->LongPosition->AveragePosPrice
				<< std::setw(15) << pair.second->LongPosition->PositionProfit
				<< std::setw(20) << pair.second->LongPosition->ExchangeMargin
				<< std::setw(15) << pair.second->LongPosition->OpenCost
				<< std::endl;

		}*/


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
		//				if (order->CombOffsetFlag == "Open") {
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
		//				}
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
	for (auto& futInfMng : ctx.tarContracInfo) {
		SubcribeKindle(futInfMng.code.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);
	};
}