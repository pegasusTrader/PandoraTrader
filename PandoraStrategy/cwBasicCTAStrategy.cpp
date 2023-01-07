#include "cwBasicCTAStrategy.h"



cwBasicCTAStrategy::cwBasicCTAStrategy(const char* szStrategyName)
	: m_strStrategyName(szStrategyName)
	, m_StrategyLog("TradeList", szStrategyName)
{
	m_StrategyLog.AddTitle("Localtime,MD,InstrumentID,DateTime,Position,price");
}

void cwBasicCTAStrategy::_OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	cwKindleStickPtr pKindle = pKindleSeries->GetLastKindleStick();
	m_dLastPrice = pKindle->Open;
	m_iLastIndex = pKindleSeries->GetKindleSize();

	OnBar(bFinished, iTimeScale, pKindleSeries);
}

void cwBasicCTAStrategy::SetStrategyPosition(int iPosition, char* szInstrumentID)
{
	std::string InstrumentID;
	if (szInstrumentID == nullptr)
	{
		InstrumentID = m_strDealInstrument;
	}
	else
	{
		InstrumentID = szInstrumentID;
	}
	auto it = m_iStrategyPositionMap.insert(std::pair<std::string, int>(InstrumentID, iPosition));
	if (it.second)
	{
		if (iPosition != 0)
		{
			m_dEntryPrice[InstrumentID] = m_dLastPrice;
			m_iEntryIndex[InstrumentID] = m_iLastIndex;
		}
	}
	else
	{
		if (iPosition == it.first->second)
		{
			return;
		}
		if (it.first->second == 0
			&& iPosition != 0)
		{
			m_dEntryPrice[InstrumentID] = m_dLastPrice;
			m_iEntryIndex[InstrumentID] = m_iLastIndex;
		}
		it.first->second = iPosition;
	}

	m_StrategyLog.AddLog(cwStrategyLog::enIMMS, "%s, %s, %d, %.2f",
		InstrumentID.c_str(), m_strLastUpdateTime.c_str(), iPosition, m_dLastPrice);
}

int cwBasicCTAStrategy::GetStrategyPosition(char* szInstrumentID)
{
	std::string InstrumentID;
	if (szInstrumentID == nullptr)
	{
		InstrumentID = m_strDealInstrument;
	}
	else
	{
		InstrumentID = szInstrumentID;
	}
	return m_iStrategyPositionMap[std::move(InstrumentID)];
}

double cwBasicCTAStrategy::GetEntryPrice(std::string InstrumentID)
{
	auto it = m_dEntryPrice.find(std::move(InstrumentID));
	if (it != m_dEntryPrice.end())
	{
		return it->second;
	}
	return 0.0;
}

int cwBasicCTAStrategy::GetEntryIndex(std::string InstrumentID)
{
	auto it = m_iEntryIndex.find(std::move(InstrumentID));
	if (it != m_iEntryIndex.end())
	{
		return it->second;
	}
	return 0;
}
