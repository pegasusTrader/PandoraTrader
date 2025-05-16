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
static std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList; // �ҵ��б�ȫ�֣�



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

	timePara _timePara = IsTradingTime();
	auto hour = _timePara.hour;
	auto minute = _timePara.minute;
	auto second = _timePara.second;

	if (IsNormalTradingTime(hour, minute))
	{
		UpdateCtx(pPriceData);
		std::map<std::string, cwPositionPtr> PositionMap;
		GetPositions(PositionMap);
		orderInfo order;

		if (PositionMap.empty())
		{
			StrategyPosOpen(pPriceData, order);
		}
		else
		{
			StrategyPosClose(pPriceData, PositionMap[pPriceData->InstrumentID], order);
		}
	}
	else if (IsClosingTime(hour, minute))
	{
		cwPositionPtr pPos = nullptr;
		std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;
		GetPositionsAndActiveOrders(pPriceData->InstrumentID, pPos, WaitOrderList); // ��ȡָ���ֲֺ͹ҵ��б�

		if (pPos != 0 && WaitOrderList.empty())  //�гֲ�&&�޹ҵ� ִ���߼�
		{
			if (pPos->LongPosition->TotalPosition > 0) {
				EasyInputMultiOrder(pPriceData->InstrumentID, -pPos->LongPosition->TotalPosition, pPriceData->BidPrice1);
			}
			if (pPos->ShortPosition->TotalPosition > 0) {
				EasyInputMultiOrder(pPriceData->InstrumentID, pPos->ShortPosition->TotalPosition, pPriceData->AskPrice1);
			}
			std::cout << "�ȴ��ҵ��ɽ���" << WaitOrderList.size() << " ��ʣ�ࡣ" << std::endl;
		}
		else if (pPos == 0)
		{
			std::cout << "�ֲ�ȫ����ջ�û�гֲ�" << std::endl;
			return;
		}
		else //�гֲ�&&�йҵ�
		{
			std::cout << "�ֲ�δ��գ�" << WaitOrderList.size() << " ��ʣ�ࡣ" << std::endl;
			cwSleep(5000);
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
	if (pOrder == nullptr) return;
	// ����ҵ��� key
	cwActiveOrderKey key(pOrder->OrderRef, pOrder->InstrumentID);

	// ����ֻ������ WaitOrderList ��׷�ٵĹҵ�
	auto it = WaitOrderList.find(key);
	if (it == WaitOrderList.end()) return;


	auto status = pOrder->OrderStatus;// ����״̬����Ҫ�ж��Ƿ������
	auto submitStatus = pOrder->OrderSubmitStatus;// �����ύ״̬����Ҫ�ж��Ƿ������

	if (status == CW_FTDC_OST_AllTraded ||   // ȫ���ɽ�
		status == CW_FTDC_OST_Canceled)    // ����     
	{
		// ��־��¼
		std::cout << "Order Finished - InstrumentID: " << pOrder->InstrumentID
			<< ", Ref: " << pOrder->OrderRef
			<< ", Status: " << status << std::endl;

		// �Ƴ��ùҵ�
		WaitOrderList.erase(it);
	}
	else if (submitStatus == CW_FTDC_OSS_InsertRejected)// �ܵ�
	{
		// ��־��¼
		std::cout << "Order Finished - InstrumentID: " << pOrder->InstrumentID
			<< ", Ref: " << pOrder->OrderRef
			<< ", Status: " << submitStatus << std::endl;
	}
	else {
		// ��ѡ����Ҳ���Ը��¸ùҵ�����Ϣ�����ֳɽ������ȣ�
	}



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
	UpdateBarData();

	for (auto& futInfMng : tarFutInfo)
	{
		SubcribeKindle(futInfMng.first.c_str(), cwKINDLE_TIMESCALE_1MIN, 50);
	};
}

void cwStrategyDemo::UpdateBarData() {

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

void cwStrategyDemo::AutoCloseAllPositionsLoop() {

	//����map�����ڱ���ֲ���Ϣ 
	std::map<std::string, cwPositionPtr> CurrentPosMap;
	//����map�����ڱ���ҵ���Ϣ 
	std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;

	int waitCount = 0;
	const int maxWait = 60;

	while (waitCount++ < maxWait)
	{
		GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);
		if (!CurrentPosMap.empty() && WaitOrderList.empty())//�гֲ�&&�޹ҵ� ִ���߼�
		{
			for (auto& [id, pos] : CurrentPosMap) {
				auto md = GetLastestMarketData(id);
				if (!md) continue;

				if (pos->LongPosition->TotalPosition > 0) {
					double price = md->BidPrice1;
					if (price > 1e-6) { EasyInputMultiOrder(id.c_str(), -pos->LongPosition->TotalPosition, price); }// ƽ���

				}
				if (pos->ShortPosition->TotalPosition > 0) {
					double price = md->AskPrice1;
					if (price > 1e-6) { EasyInputMultiOrder(id.c_str(), pos->ShortPosition->TotalPosition, price); }// ƽ���
				}
			}
		}
		else if (CurrentPosMap.empty())
		{
			std::cout << "�ֲ�ȫ����ջ�û�гֲ�" << std::endl;
			break;
		}
		else
		{
			std::cout << "�ȴ��ҵ��ɽ���" << WaitOrderList.size() << " ��ʣ�ࡣ" << std::endl;
			cwSleep(5000);
			continue;
		}
	}
}

void cwStrategyDemo::UpdateCtx(cwMarketDataPtr pPriceData)
{
	//barFolw����
	comBarInfo.barFlow[pPriceData->InstrumentID].push_back(pPriceData->LastPrice);
	//queueBar����

	comBarInfo.queueBar[pPriceData->InstrumentID].push_back(pPriceData->LastPrice / tarFutInfo[pPriceData->InstrumentID].accfactor);
	//ret����
	double last = comBarInfo.queueBar[pPriceData->InstrumentID][comBarInfo.queueBar[pPriceData->InstrumentID].size() - 1];
	double secondLast = comBarInfo.queueBar[pPriceData->InstrumentID][comBarInfo.queueBar[pPriceData->InstrumentID].size() - 2];
	comBarInfo.retBar[pPriceData->InstrumentID].push_back(last / secondLast - 1);
	//ɾ����λԪ��
	comBarInfo.barFlow[pPriceData->InstrumentID].pop_front();
	comBarInfo.queueBar[pPriceData->InstrumentID].pop_front();
	comBarInfo.retBar[pPriceData->InstrumentID].pop_front();
}

orderInfo cwStrategyDemo::StrategyPosOpen(cwMarketDataPtr pPriceData, orderInfo& order) {

	// �����׼��
	// ���� stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// ���� stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rl), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);

	orderInfo order;
	// ���¼۸� < ���ڼ۸� && ���ڲ����� > ���ڲ�����
	auto& barQueue = comBarInfo.queueBar[pPriceData->InstrumentID];
	if (barQueue.back() < barQueue[barQueue.size() - tarFutInfo[pPriceData->InstrumentID].Rs] && stdShort > stdLong) {
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();

	}
	// ���¼۸� > ���ڼ۸� && ���ڲ����� > ���ڲ�����
	else if (barQueue.back() > barQueue[barQueue.size() - 500] && stdShort > stdLong) {
		int tarVolume = countLimitCur[pPriceData->InstrumentID];
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();

	}
	return order;
}

orderInfo cwStrategyDemo::StrategyPosClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos, orderInfo& order) {
	// �����׼��
	// ���� stdShort
	std::vector<double> retBarSubsetShort(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdShort = SampleStd(retBarSubsetShort);

	// ���� stdLong
	std::vector<double> retBarSubsetLong(std::prev(comBarInfo.retBar[pPriceData->InstrumentID].end(), tarFutInfo[pPriceData->InstrumentID].Rs), comBarInfo.retBar[pPriceData->InstrumentID].end());
	double stdLong = SampleStd(retBarSubsetLong);
	orderInfo order;
	auto& barQueue = comBarInfo.queueBar[pPriceData->InstrumentID];
	size_t rs = tarFutInfo[pPriceData->InstrumentID].Rs;
	std::string FacDirection;
	if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
	{
		if (pPos->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Long";
		}
		else if (pPos->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Short";
		}
	}
	else
	{
		if (pPos->LongPosition->PosiDirection == CW_FTDC_D_Buy) {
			std::string FacDirection = "Short";
		}
		else if (pPos->ShortPosition->PosiDirection == CW_FTDC_D_Sell)
		{
			std::string FacDirection = "Long";
		}
	}

	//Fac���� =�� && �����¼۸� > ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
	if (FacDirection == "Long" && (barQueue.back() > barQueue[barQueue.size() - rs] || stdShort <= stdLong)) {
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
	//Fac���� =�� && �����¼۸� < ���ڼ۸� || ���ڲ�����<=���ڲ����ʣ�
	else if (FacDirection == "Short" && (barQueue.back() < barQueue[barQueue.size() - rs] || stdShort <= stdLong))
	{
		if (tarFutInfo[pPriceData->InstrumentID].Fac == "Mom_std_bar_re_dym")
		{
			order.volume = countLimitCur[pPriceData->InstrumentID];
		}
		else
		{
			order.volume = -countLimitCur[pPriceData->InstrumentID];
		}
		order.szInstrumentID = pPriceData->InstrumentID;
		order.price = comBarInfo.barFlow[pPriceData->InstrumentID].back();
	}
	return order;
}

