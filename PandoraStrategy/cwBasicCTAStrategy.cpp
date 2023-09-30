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

cwBasicCTAStrategy::~cwBasicCTAStrategy()
{
}

void cwBasicCTAStrategy::_PreOnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	cwKindleStickPtr pKindle = pKindleSeries->GetLastKindleStick();
	if (pKindle.get() == nullptr)
	{
		return ;
	}
	m_strLastUpdateTime = pKindle->szStartTime;

	if (pKindleSeries->m_bIsNewKindle)
	{
		m_dLastPrice = pKindle->Open;
	}
	else
	{
		m_dLastPrice = pKindle->Close;
	}
	m_iLastIndex = pKindleSeries->GetKindleSize();

	if (bFinished)
	{
		//更新权益
		m_cwSettlement.SettlementPrice(pKindleSeries->GetInstrumentID(), m_dLastPrice, m_pInstrument->VolumeMultiple);

		UpdateEvaluator(m_cwSettlement.m_dMaxFundOccupied, m_cwSettlement.m_dBalance, m_strLastUpdateTime, pKindle->StartTime, 0.05);

		//存储更新权益
		TimeBalanceDataPtr tbdPtr = std::make_shared<TimeBalanceData>();
		tbdPtr->strDateTime = m_strLastUpdateTime;
		tbdPtr->iTimeStamp = pKindle->StartTime;
		tbdPtr->dBalance = m_cwSettlement.m_dBalance;
		tbdPtr->dMaxFundOccupied = m_cwSettlement.m_dMaxFundOccupied;
		tbdPtr->dNetAsset = m_cwEvaluator.m_dCurNetAsset;

		m_dTimeBalanceDQ.push_back(tbdPtr);
	}
}

//策略评价更新函数
void cwBasicCTAStrategy::UpdateEvaluator(double dCurrentMoneyUsed, double dCurrentTotalProfit, std::string str_time, std::uint64_t timeStamp, double dExpectedRet)
{
	m_cwEvaluator.UpdateNetValueByTotalPNL(timeStamp, dCurrentTotalProfit, dCurrentMoneyUsed);
	
	//copy 数据
	EvaluatorTimeSeriesData tsd;

	tsd.iTimeStamp = m_cwEvaluator.m_iTimeStamp;
	tsd.dNetAsset = m_cwEvaluator.m_dCurNetAsset;
	tsd.dTradingYears = m_cwEvaluator.m_dTradingYears;
	tsd.dIRR = m_cwEvaluator.m_dIRR;
	tsd.dAR = m_cwEvaluator.m_dAR;

	tsd.dVolatility = m_cwEvaluator.m_dVolatility;
	tsd.dVolatilityDownward = m_cwEvaluator.m_dVolatilityDownward;

	tsd.dDrawDownRatio = m_cwEvaluator.m_dDrawDownRatio;
	tsd.dMaxDrawDownRatio = m_cwEvaluator.m_dMaxDrawDownRatio;
	tsd.dAverageDDR = m_cwEvaluator.m_dAverageDDR;
	tsd.dSharpeRatio = m_cwEvaluator.m_dSharpeRatio;
	tsd.dSortinoRatio = m_cwEvaluator.m_dSortinoRatio;
	tsd.dCalmarRatio = m_cwEvaluator.m_dCalmarRatio;
	tsd.dSterlingRatio = m_cwEvaluator.m_dSterlingRatio;

	m_dEvaluatorDQ.push_back(tsd);
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

			m_cwSettlement.UpdateTrade(InstrumentID, m_dLastPrice, iPosition, m_pInstrument->VolumeMultiple);
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
			m_cwSettlement.UpdateTrade(InstrumentID, m_dLastPrice, -1 * ret.first->second, m_pInstrument->VolumeMultiple);

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

		m_cwSettlement.UpdateTrade(InstrumentID, m_dLastPrice, iPosition - ret.first->second, m_pInstrument->VolumeMultiple);

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

size_t cwBasicCTAStrategy::GetEntryIndex(std::string InstrumentID)
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
