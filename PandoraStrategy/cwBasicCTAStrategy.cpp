#include "cwBasicCTAStrategy.h"



cwBasicCTAStrategy::cwBasicCTAStrategy(const char* szStrategyName)
	: m_strStrategyName(szStrategyName)
#ifdef CW_NEED_STRATEGY_LOG
	, m_StrategyLog("StrategyLog", szStrategyName)
#endif // CW_NEED_STRATEGY_LOG
	, m_StrategyTradeListLog("TradeList", szStrategyName)
{
	m_StrategyTradeListLog.AddTitle("Localtime,MD,InstrumentID,DateTime,Position,price");
}

void cwBasicCTAStrategy::_OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	cwKindleStickPtr pKindle = pKindleSeries->GetLastKindleStick();
	if (pKindle.get() != nullptr)
	{
		m_strLastUpdateTime = pKindle->szStartTime;

		if (pKindleSeries->m_bIsNewKindle)
		{
			m_dLastPrice = pKindle->Open;
		}
		else
		{
			m_dLastPrice = pKindle->Close;
		}

	}
	else
	{
		return;
	}
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
	auto ret = m_iStrategyPositionMap.insert(std::pair<std::string, int>(InstrumentID, iPosition));
	if (ret.second)
	{
		if (iPosition != 0)
		{
			m_dEntryPrice[InstrumentID] = m_dLastPrice;
			m_iEntryIndex[InstrumentID] = m_iLastIndex;
			m_strEntryTime[InstrumentID] = m_strLastUpdateTime;
		}
	}
	else
	{
		if (iPosition == ret.first->second)
		{
			return;
		}

		if (ret.first->second * iPosition < 0)
		{
			ret.first->second = 0;
			m_StrategyTradeListLog.AddLog(cwStrategyLog::enIMMS, "%s, %s, %d, %.2f",
				InstrumentID.c_str(), m_strLastUpdateTime.c_str(), 0, m_dLastPrice);
		}

		if (ret.first->second == 0
			&& iPosition != 0)
		{
			m_dEntryPrice[InstrumentID] = m_dLastPrice;
			m_iEntryIndex[InstrumentID] = m_iLastIndex;
			m_strEntryTime[InstrumentID] = m_strLastUpdateTime;
		}
		ret.first->second = iPosition;
	}

	m_StrategyTradeListLog.AddLog(cwStrategyLog::enIMMS, "%s, %s, %d, %.2f",
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
	auto it = m_iStrategyPositionMap.find(std::move(InstrumentID));
	if (it == m_iStrategyPositionMap.end())
	{
		return 0;
	}
	return it->second;
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

const char * cwBasicCTAStrategy::GetEntryTime(std::string InstrumentID)
{
	auto it = m_strEntryTime.find(std::move(InstrumentID));
	if (it != m_strEntryTime.end())
	{
		return it->second.c_str();
	}
	return "";
}
