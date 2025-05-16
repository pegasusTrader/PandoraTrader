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
#include "myStructs.h"
#include "sqlite3.h"
#include "IndayStrategy.hpp"
#include "utils.hpp"

static std::map<std::string, futInfMng> tarFutInfo; // ����������
static barInfo comBarInfo;                          // barINfo
static std::map<std::string, int> countLimitCur;    // ��Լ��Ӧ��������

cwStrategyDemo::cwStrategyDemo()
{
}


cwStrategyDemo::~cwStrategyDemo()
{
}

void cwStrategyDemo::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL) { return; }
}

void cwStrategyDemo::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {
	if (pPriceData.get() == NULL) { return; }

	std::string currentContract = pPriceData->InstrumentID;
	int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [currentContract](const futInfMng& item) {return item.contract == currentContract; });
	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if (IsNormalTradingTime(hour, minute))
	{
		UpdateCtx(pPriceData, ctx, currentContract);

		std::map<std::string, cwPositionPtr> PositionMap;
		GetPositions(PositionMap);

		if (PositionMap.empty())
		{
			StrategyPosOpen(currentContract, ctx, stdLong, stdShort);
		}
		else
		{
			StrategyPosClose(currentContract, PositionMap[currentContract], ctx, stdLong, stdShort);
		}
	}
	else if (IsClosingTime(hour, minute))
	{

		cwPositionPtr pPos = nullptr;
		std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;
		GetPositionsAndActiveOrders(currentContract, pPos, WaitOrderList);
		std::cout << "[AutoClose] ����ƽ��: " << currentContract
			<< " LongYd=" << pPos->LongPosition->YdPosition
			<< " LongTd=" << pPos->LongPosition->TodayPosition
			<< " ShortYd=" << pPos->ShortPosition->YdPosition
			<< " ShortTd=" << pPos->ShortPosition->TodayPosition << std::endl;

		if (pPos == nullptr)
		{
			std::cout << "û�гֲ�" << std::endl;
			return;
		}
		if (pPos->LongPosition->TotalPosition > 0) {
			auto& lp = pPos->LongPosition;
			double price = GetLastestMarketData(currentContract)->BidPrice1;
			EasyInputMultiOrder(currentContract.c_str(), -lp->TotalPosition, price); // ���ж��ƽ���
		}
		if (pPos->ShortPosition->TotalPosition > 0) {
			auto& sp = pPos->ShortPosition;
			double price = GetLastestMarketData(currentContract)->AskPrice1;
			EasyInputMultiOrder(currentContract.c_str(), sp->TotalPosition, price); // ���пղ�ƽ�ղ�
		}
	}
	else if (IsAfterMarket(hour, minute))
	{
		std::cout << "----------------- TraderOver ----------------" << std::endl;
		std::cout << "--------------- StoreBaseData ---------------" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
	else
	{
		if (minute == 0 || minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50)
		{
			std::cout << "waiting" << hour << "::" << minute << "::" << second << std::endl;
		}
	}
};

void cwStrategyDemo::OnRtnTrade(cwTradePtr pTrade)
{
}

void cwStrategyDemo::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
	
}

	void cwStrategyDemo::OnOrderCanceled(cwOrderPtr pOrder)
	{
		if (pOrder->OrderStatus == '5') { // �ܵ�
			std::cout << "[AutoClose] �ܵ�: " << pOrder->InstrumentID << std::endl;
			//pendingContracts.erase(pOrder->InstrumentID); // ǿ���Ƴ�����������
		}

	}

	void cwStrategyDemo::OnReady()
	{

		AutoCloseAllPositionsLoop();
		UpdateBarData(tarFutInfo, comBarInfo, countLimitCur);

		for (auto& futInfMng : tarFutInfo)
		{
			SubcribeKindle(futInfMng.first.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);
		};
	}


	void cwStrategyDemo::AutoCloseAllPositionsLoop() {

		//����map�����ڱ���ֲ���Ϣ 
		std::map<std::string, cwPositionPtr> CurrentPosMap;
		//����map�����ڱ���ҵ���Ϣ 
		std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;

		while (true) {
			GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);
			if (CurrentPosMap.empty()) {
				std::cout << "û�гֲ�" << std::endl;
				break;
			}

			for (auto& [id, pos] : CurrentPosMap) {
				if (pos->LongPosition->TotalPosition > 0) {
					auto& lp = pos->LongPosition;
					double price = GetLastestMarketData(id)->BidPrice1;
					EasyInputMultiOrder(id.c_str(), -lp->TotalPosition, price); // ƽ���
				}
				if (pos->ShortPosition->TotalPosition > 0) {
					auto& sp = pos->ShortPosition;
					double price = GetLastestMarketData(id)->AskPrice1;
					EasyInputMultiOrder(id.c_str(), sp->TotalPosition, price); // ƽ���
				}
			}

			// �ȴ����ж������
			while (true) {
				if (!WaitOrderList.empty()) {
					cwSleep(1000);
					GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList); // ����
				}
				else {
					std::cout << "����ȫ���ɽ�&û�����ն���" << std::endl;
					break;
				}
			}
		}
	}

	void cwStrategyDemo::UpdateCtx(cwMarketDataPtr pPriceData, StrategyContext & ctx, std::string & currentContract)
	{
		//barFolw����
		ctx.barFlow[currentContract].push_back(pPriceData->LastPrice);
		//queueBar����
		int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [currentContract](const futInfMng& item) {return item.contract == currentContract; });
		ctx.queueBar[currentContract].push_back(pPriceData->LastPrice / ctx.tarContracInfo[contractIndex].accfactor);
		//ret����
		double last = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 1];
		double secondLast = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 2];
		ctx.retBar[currentContract].push_back(last / secondLast - 1);
		//ɾ����λԪ��
		ctx.barFlow[currentContract].pop_front();
		ctx.queueBar[currentContract].pop_front();
		ctx.retBar[currentContract].pop_front();
	}



