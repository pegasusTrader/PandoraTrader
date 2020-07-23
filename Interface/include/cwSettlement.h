//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cwTradeCommonDefine.h"
#include "cwMutex.h"

#include <map>
#include <unordered_map>
#include <string>
#include <deque>

class cwSettlement
{
public:
	cwSettlement();
	~cwSettlement();

#ifdef _MSC_VER
#pragma region CommenDefine
#endif // _MSC_VER



#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

	void UpdatePrice(cwMarketDataPtr pMdData);

	void SettlementPrice(std::string instrumentid, double price);

	void UpdateOrder(cwOrderPtr pOrder);
	void UpdateTrade(cwTradePtr pTrade);

	//入金
	void Deposit(double ddeposit)
	{
		m_dPreBalance += ddeposit;
		m_dBalance += ddeposit;
	}

	//update Instrument Data
	void SetInstrumentData(std::unordered_map<std::string, cwInstrumentDataPtr>& InstrumentMap);

	cwMUTEX										m_ProcessMutex;

	std::unordered_map<std::string, cwInstrumentDataPtr>	m_InstrumentMap;	//kye Isntrumentid, value: InstrumentData

	std::map<std::string, cwMarketDataPtr>		m_LastPriceMap;					//Key Insrumentid,	value: MarketData

	std::map<std::string, int>					m_Position;						//key Instrumentid	value: NetPosition

	std::map<std::string, cwOrderPtr>			m_OrderList;					//key OrderRef		value: orders
	std::map<std::string, cwTradePtr>			m_TradeList;					//key TradeId		value: trades

	std::map<std::string, int>					m_CancelCount;					//key Instrumentid	value: Cancel Count

	//Profit and loss Statistics
	std::map<std::string, double>				m_CloseProfitMap;				//key:InstrumentID, value: This Instrument ClosePrifit
	std::map<std::string, double>				m_PositionProfitMap;			//key:InstrumentID, value: This Instrument PositionProfit
	std::map<std::string, double>				m_FeeMap;						//key:InstrumentID, value: This Instrument Fee

	std::map<std::string, std::deque<double>>	m_UnClosePositionCost;			//key:InstrumentID, value: Position Cost deque
	std::map<std::string, int>					m_TradeCountMap;				//key:InstrumentID, value: TradeCount

	std::map<std::string, double>				m_dInsMaxBalanceMap;			//key:InstrumentID, value: Instrument Max Balance For Max Drop Down
	std::map<std::string, double>				m_dInsMaxDropDownMap;			//Key:InstrumentID, value: Max Drop Down

	double										m_dPreBalance;					//初始权益
	double										m_dBalance;						//当前权益

	double										m_dPositionProfit;				//持仓盈亏
	double										m_dCloseProfit;					//平仓盈亏
	double										m_dFee;							//手续费

	double										m_dCurMaxBalance;				//截止目前最高权益，计算最大回撤用
	double										m_dMaxDropDown;					//最大回撤
};

