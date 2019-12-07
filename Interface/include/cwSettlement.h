#pragma once

#include "cwTradeCommonDefine.h"

#include <map>
#include <string>


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

	void UpdateOrder(cwOrderPtr pOrder);
	void UpdateTrade(cwTradePtr pTrade);

	//update Instrument Data
	void SetInstrumentData(std::map<std::string, cwInstrumentDataPtr>& InstrumentMap);

	std::map<std::string, cwInstrumentDataPtr>	m_InstrumentMap;


	std::map<std::string, int>					m_Position;		//key Instrumentid

	std::map<std::string, cwOrderPtr>			m_OrderList;	//key OrderRef
	std::map<std::string, cwTradePtr>			m_TradeList;	//key TradeId


	//Profit and loss Statistics
	std::map<std::string, double>				m_ProfitAndLossMap;
	std::map<std::string, std::deque<double>>	m_UnClosePositionCost;
	std::map<std::string, int>					m_TradeCountMap;

};

