#include "cwStrategyDemo.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include "Class1.h"

using namespace MyTrade;


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
	//定义全局变量
	static std::unordered_map<std::string, PositionFieldPtr> curPos;//这是持仓信息
	static std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data;//这是行情信息
	static std::unordered_map<cwFtdcInstrumentIDType, cwInstrumentDataPtr> futInfTable;//这是合约信息
	static int sendCount = 0;


	// 获取当前时间
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

		std::vector<cwOrderPtr> orders = Class1::HandBar(code2data/*当前持仓数据*/, curPos);
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
					cwFtdcDirectionType Long;
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
}

