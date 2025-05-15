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

	std::string currentContract = pPriceData->InstrumentID;

	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if ((hour == 9 && minute >= 1) || (hour > 9 && hour < 10) || (hour == 10 && minute < 15) ||
		(hour == 10 && minute >= 30) || (hour > 10 && hour < 11) || (hour == 11 && minute < 30) ||
		(hour == 13 && minute >= 30) || (hour > 13 && hour < 14) || (hour == 14 && minute < 45))
	{
		//barFolw����
		ctx.barFlow[currentContract].push_back(pPriceData->LastPrice);
		//queueBar����
		std::string constrct_id = currentContract;
		int contractIndex = findIndex<futInfMng>(ctx.tarContracInfo, [constrct_id](const futInfMng& item) {return item.contract == constrct_id; });
		ctx.queueBar[currentContract].push_back(pPriceData->LastPrice / ctx.tarContracInfo[contractIndex].accfactor);
		//ret����
		double last = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 1];
		double secondLast = ctx.queueBar[currentContract][ctx.queueBar[currentContract].size() - 2];
		ctx.retBar[currentContract].push_back(last / secondLast - 1);

		//ɾ����λԪ��
		ctx.barFlow[currentContract].pop_front();
		ctx.queueBar[currentContract].pop_front();
		ctx.retBar[currentContract].pop_front();

		// �����׼��
		// ���� stdShort
		std::vector<double> retBarSubsetShort(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rs), ctx.retBar[currentContract].end());
		double stdShort = SampleStd(retBarSubsetShort);

		// ���� stdLong
		std::vector<double> retBarSubsetLong(std::prev(ctx.retBar[currentContract].end(), ctx.tarContracInfo[contractIndex].Rl), ctx.retBar[currentContract].end());
		double stdLong = SampleStd(retBarSubsetLong);

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
	else if ((hour == 14 && minute >= 45) || (hour == 15 && minute == 0))
	{
		//ȫ�����

	}
	else if ((hour == 15 && minute >= 0 && minute < 10))
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
	//������ź�
	//���ղ��ź�
	// �ٽ����� ��ִ���
	// ��ӡһЩ����
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
	//����map�����ڱ���ֲ���Ϣ 
	std::map<std::string, cwPositionPtr> CurrentPosMap;
	//����map�����ڱ���ҵ���Ϣ 
	std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;

	while (true)
	{
		//��ȡ�ҵ���  ��ǰ�ֲ���Ϣ
		GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);
		if (!CurrentPosMap.empty())
		{
			for (const auto& [instrumentID, pos] : CurrentPosMap)
			{
				if (pos->LongPosition->TotalPosition > 0) {
					auto& p = pos->LongPosition;
					std::cout << "LONG:\t" << instrumentID << std::endl;
					std::cout << "L_volume:\t" << p->TotalPosition << std::endl;
					EasyInputMultiOrder(instrumentID.c_str(), -p->YdPosition, GetLastestMarketData(instrumentID)->BidPrice1);

				}
				else if (pos->ShortPosition->TotalPosition > 0)
				{
					std::cout << "SHORT:\t" << instrumentID << std::endl;
					std::cout << "S_volume:\t" << p->YdPosition << std::endl;
					EasyInputMultiOrder(instrumentID.c_str(), p->TotalPosition, GetLastestMarketData(instrumentID)->AskPrice1);
				}
			}
			while (true)
			{
				if (!WaitOrderList.empty())
				{
					cwSleep(1000); // ÿ�εȴ�1000����
					continue;
				}
				else
				{
					std::cout << "����ȫ���ɽ�&û�����ն���" << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << "û�гֲ�" << std::endl;
			break;
		}

	}

	for (auto& futInfMng : ctx.tarContracInfo)
	{
		SubcribeKindle(futInfMng.code.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);

	};
}



//std::cout << "--- ��ǰʱ�� " << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " ---------------" << std::endl;
	//std::cout << std::setfill(' ');
	//std::cout << std::left  // �����