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
#include <map>
#include <unordered_map>
#include "cwTradeCommonDefine.h"
#include "cwMutex.h"

#ifndef NO_TRADEINFO_LOG
//#define TRADEINFO_LOG
#endif // !NO_TRADEINFO_LOG

#ifdef TRADEINFO_LOG
#include <fstream>
#endif // TRADEINFO_LOG


class cwTickTradeManager
{
public:
	cwTickTradeManager(bool bNeedStatic = false);
	~cwTickTradeManager();

	void Reset();

	//update Instrument Data
	void SetInstrumentData(std::unordered_map<std::string, cwInstrumentDataPtr>& InstrumentMap);

	//update Price values
	void UpdatePrice(cwMarketDataPtr pPriceData);

	//Get this tick's trade volume
	std::map<int64_t, uint32_t>& GetCurrentTradeMap() 
	{
		cwAUTOMUTEX mt(m_CurrentTradeMutex, true);
		return m_CurrentTradeMap; 
	}
	uint32_t GetCurrentBuyVolume()
	{
		cwAUTOMUTEX mt(m_CurrentTradeMutex, true);
		return m_iCurrentBuyVolume;

	}
	uint32_t GetCurrentSellVolume()
	{
		cwAUTOMUTEX mt(m_CurrentTradeMutex, true);
		return m_iCurrentSellVolume;
	}

	void SaveTotalTradeMap();
	std::map<int64_t, uint64_t>&GetTotalTradeMap() { return m_TotalTradeMap; }
	void ResetTotalTradeMap() { m_TotalTradeMap.clear(); }

	void SaveTotalTradeVolumeNumMap();
	std::map<uint64_t, uint32_t>& GetTotalTradeVolumeNumMap() { return m_TotalTradeVolumeNumMap; }
	void ResetTotalTradeVolumeNumMap() { m_TotalTradeVolumeNumMap.clear(); }

	void SaveTotalTickVolumeNumMap();
	std::map<uint64_t, uint32_t>& GetTotalTickVolumeNumMap() { return m_TotalTickVolumeNumMap; }
	void ResetTotalTickVolumeNumMap() { m_TotalTickVolumeNumMap.clear(); }

	std::map<uint32_t, uint32_t> GetLevelChange(cwMarketDataPtr pPrePriceData, cwMarketDataPtr pCurPriceData);					
private:
	std::unordered_map<std::string, cwInstrumentDataPtr>	m_InstrumentMap;
	std::map<std::string, cwMarketDataPtr>		m_PreMarketDataMap;

	//price update
	//Key:Price*1000 value:TradeVolume
	std::map<int64_t, uint32_t> m_CurrentTradeMap;
	cwMUTEX						 m_CurrentTradeMutex;

	uint32_t					 m_iCurrentBuyVolume;
	uint32_t					 m_iCurrentSellVolume;

	//static Update
	//Key:Price*1000 value:TradeVolume	
	std::map<int64_t, uint64_t> m_TotalTradeMap;
	//Key:TradeVolume value:how many times appear
	std::map<uint64_t, uint32_t> m_TotalTradeVolumeNumMap;

	//key:TickVolume value:how many times appear
	std::map<uint64_t, uint32_t> m_TotalTickVolumeNumMap;

	//Total Average Price
	double		m_dbAvgPrice;
	uint32_t	m_iTotalVolume;

	//TotalAverage Volume
	double		m_dbAvgVolume;
	uint32_t	m_iVolumeCnt;

	bool		m_bNeedStatic;
	void		Static();

#ifdef TRADEINFO_LOG
	//Price Log
	std::ofstream	m_Price_log;
#endif // TRADEINFO_LOG

};

