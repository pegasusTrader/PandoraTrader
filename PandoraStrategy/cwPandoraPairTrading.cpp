#include "cwPandoraPairTrading.h"
#include <algorithm>


cwPandoraPairTrading::cwPandoraPairTrading()
{
	m_MainInstrumentID = "au2012";
	m_SubMainInstrumentID = "au2010";

	m_dBuyThreadHold = 1.6;
	m_dSellThreadHold = 1.72;

	m_dVolumeCoefficient = -1;

	m_cwMainOpenCloseMode = CloseTodayThenYd;
	m_cwSubMainOpenCloseMode = CloseTodayThenYd;

	m_iPositionLimit = 1;
	m_iOrderVolume = 1;
}


cwPandoraPairTrading::~cwPandoraPairTrading()
{
}

void cwPandoraPairTrading::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}

	m_strCurrentUpdateTime = pPriceData->UpdateTime;

	//更新行情数据
	if (m_MainInstrumentID == (std::string)pPriceData->InstrumentID)
	{
		m_cwMainMarketData = pPriceData;
	}

	if (m_SubMainInstrumentID == (std::string)pPriceData->InstrumentID)
	{
		m_cwSubMainMarketData = pPriceData;
	}

	//确定行情数据是否已经都有效
	if (m_cwSubMainMarketData.get() == NULL
		|| m_cwMainMarketData.get() == NULL)
	{
		return;
	}

	//确定初始化完成
	if ((!m_bStrategyReady))
	{
		return;
	}

	DoManualSpread();

	if (m_pAgentData.get() != NULL
		&& m_pAgentData->pPositionAgent.get() != NULL)
	{
		m_pAgentData->pPositionAgent->SetExpectPosition(-1 * GetNetPosition(m_SubMainInstrumentID));
	}
	
}

void cwPandoraPairTrading::OnReady()
{
	SetAgentManager(dynamic_cast<cwAgentManager*>(&m_PandoraAgentManager));
	m_pAgentData = m_PandoraAgentManager.RegisterAgent(m_MainInstrumentID, cwPandoraAgentManager::Enum_Agent_Postion);
	if (m_pAgentData.get() != NULL
		&& m_pAgentData->pPositionAgent.get() != NULL)
	{
		//设置算法参数
		m_pAgentData->pPositionAgent->InsLargeOrderVolume = 100;
		m_pAgentData->pPositionAgent->InsLittleOrderVolume = 5;
		m_pAgentData->pPositionAgent->InsAskBidGap = 1;

		m_pAgentData->pPositionAgent->SetExpectPosition(-1 * GetNetPosition(m_SubMainInstrumentID));
	}

	//订阅行情
	std::vector<std::string> SubscribeInstrument;

	SubscribeInstrument.push_back(m_MainInstrumentID);
	SubscribeInstrument.push_back(m_SubMainInstrumentID);

	SubScribePrice(SubscribeInstrument);
}

void cwPandoraPairTrading::DoManualSpread()
{
	cwEasyStrategyLog log(m_StrategyLog, "DoManualSpread");

	bool bStrategyCanOpen = true;

	//获取主力和次主力合约的最小变动
	double dMainTickSize = GetTickSize(m_MainInstrumentID.c_str());
	if (dMainTickSize < 0)
	{
		return;
	}
	double dSubMainTickSize = GetTickSize(m_SubMainInstrumentID.c_str());
	if (dSubMainTickSize < 0)
	{
		return;
	}

	//获取撤单次数
	int iSubMainCancelCount = GetInstrumentCancelCount(m_SubMainInstrumentID);
	//定义需要处理的double精度
	const double dInsEQ = (double)(std::min)(dMainTickSize, dSubMainTickSize) / 10.0;


	//每个交易时段开收盘一小段时间不交易
	{
		cwProductTradeTime::cwTradeTimeSpace TradeTimeSpace;
		int iOpen = 0, iClose = 0;

		bool bRet = GetTradeTimeSpace(m_SubMainInstrumentID.c_str(), m_strCurrentUpdateTime.c_str(),
			TradeTimeSpace, iOpen, iClose);

		if (!bRet)
		{
			bStrategyCanOpen = false;
		}
		else
		{
			switch (TradeTimeSpace)
			{
			case cwProductTradeTime::NoTrading:
				bStrategyCanOpen = false;
				break;
			case cwProductTradeTime::AMPartOne:
				if (iOpen < 1
					|| iClose < 5)
				{
					bStrategyCanOpen = false;
				}
				break;
			case cwProductTradeTime::AMPartTwo:
				if (iOpen < 1
					|| iClose < 5)
				{
					bStrategyCanOpen = false;
				}
				break;
			case cwProductTradeTime::PMPartOne:

				if (iOpen < 1)
				{
					bStrategyCanOpen = false;
				}
				break;
			case cwProductTradeTime::NightPartOne:
				if (iOpen < 1)
				{
					bStrategyCanOpen = false;
				}
				break;

			default:
				break;
			}
		}

	}

	if (!bStrategyCanOpen)
	{
		std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
		std::map<std::string, cwOrderPtr> WaitOrderList;
		GetActiveOrders(WaitOrderList);

		for (WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			if (m_SubMainInstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
			{
				CancelOrder(WaitOrderIt->second);
			}
		}
		return;
	}

	std::map<std::string, cwPositionPtr> CurrentPosMap;
	std::map<std::string, cwOrderPtr> WaitOrderList;
	GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);

	int iMainPosition = 0, iSubMainPosition = 0;
	auto PosIt = CurrentPosMap.find(m_MainInstrumentID);
	if (PosIt != CurrentPosMap.end())
	{
		iMainPosition = PosIt->second->GetLongTotalPosition() - PosIt->second->GetShortTotalPosition();
	}
	else
	{
		iMainPosition = 0;
	}

	log.AddLog(cwStrategyLog::enMsg, "MainIns:%s Maintain:%d", m_MainInstrumentID.c_str(), iMainPosition);

	PosIt = CurrentPosMap.find(m_SubMainInstrumentID);
	if (PosIt != CurrentPosMap.end())
	{
		iSubMainPosition = PosIt->second->GetLongTotalPosition() - PosIt->second->GetShortTotalPosition();
	}
	else
	{
		iSubMainPosition = 0;
	}

	log.AddLog(cwStrategyLog::enMsg, "SubIns:%s SubMaintain:%d", m_SubMainInstrumentID.c_str(), iSubMainPosition);

	if (m_cwMainMarketData->UpperLimitPrice - m_cwMainMarketData->BidPrice1 < 3 * dMainTickSize + dInsEQ
		|| m_cwMainMarketData->AskPrice1 - m_cwMainMarketData->LowerLimitPrice < 3 * dMainTickSize + dInsEQ)
	{
		return;
	}
	if (m_cwSubMainMarketData->UpperLimitPrice - m_cwSubMainMarketData->BidPrice1 < 3 * dSubMainTickSize + dInsEQ
		|| m_cwSubMainMarketData->AskPrice1 - m_cwSubMainMarketData->LowerLimitPrice < 3 * dSubMainTickSize + dInsEQ)
	{
		return;
	}
	double dSubMainAskBidGap = m_cwSubMainMarketData->AskPrice1 - m_cwSubMainMarketData->BidPrice1;

	log.AddLog(cwStrategyLog::enMsg, "MainBid1:%.2f, SubMainBid1:%.2f", m_cwMainMarketData->BidPrice1, m_cwSubMainMarketData->BidPrice1);
	log.AddLog(cwStrategyLog::enMsg, "MainAsk1:%.2f, SubMainAsk1:%.2f", m_cwMainMarketData->AskPrice1, m_cwSubMainMarketData->AskPrice1);

#ifdef _MSC_VER
#pragma region BearSpread
#endif
	///熊市套利，做多远期合约。当前价差大于均值
	if (iSubMainPosition< 0)
	{
		///当前净持仓为空仓，则平仓, 用平仓参数，平仓条件低于开仓条件

		bool bNeedCancel = false;
		bool bCanOpen = false;
		//先检查挂单
		int iSubMainWaitLongOrder = 0;
		for (auto WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			bNeedCancel = true;
			if (m_SubMainInstrumentID == (std::string)WaitOrderIt->second->InstrumentID
				&& CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
			{
				if (bNeedCancel
					&& m_cwMainMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > m_dSellThreadHold - dInsEQ)
				{
					bNeedCancel &= false;
				}

				//
				if (bNeedCancel
					|| m_cwSubMainMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > 2 * dSubMainTickSize - dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
						WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
				iSubMainWaitLongOrder += WaitOrderIt->second->VolumeTotal;
			}
		}

		//买平仓
		if (bCanOpen
			|| m_cwMainMarketData->BidPrice1 - m_cwSubMainMarketData->AskPrice1 > m_dSellThreadHold - dInsEQ)
		{
			bCanOpen |= true;
		}

		if (bCanOpen
			&& iSubMainWaitLongOrder == 0)
		{
			double dbOrderPrice = m_cwSubMainMarketData->AskPrice1;

			int iVol = - (iSubMainWaitLongOrder + iSubMainPosition);
			if (iVol > m_iOrderVolume)
			{
				iVol = m_iOrderVolume;
			}

			cwOrderPtr orderptr = EasyInputOrder(m_SubMainInstrumentID.c_str(), iVol, dbOrderPrice, m_cwSubMainOpenCloseMode);
			if (orderptr.get() != NULL)
			{
				log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
					orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
			}
		}
	}
	else
	{
		///用开仓参数
		bool bNeedCancel = true;
		bool bCanOpen = false;
		//先检查挂单
		int iSubMainWaitLongOrder = 0;
		for (auto WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			bNeedCancel = true;
			if (m_SubMainInstrumentID == (std::string)WaitOrderIt->second->InstrumentID
				&& CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
			{
				if (bNeedCancel
					&& m_cwMainMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > m_dSellThreadHold - dInsEQ)
				{
					bNeedCancel &= false;
				}

				if (bNeedCancel
					|| m_cwSubMainMarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > 2 * dSubMainTickSize - dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
						WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
				iSubMainWaitLongOrder += WaitOrderIt->second->VolumeTotal;

			}
		}

		//买开仓
		if (bCanOpen
			|| (m_cwMainMarketData->BidPrice1 - m_cwSubMainMarketData->AskPrice1 > m_dSellThreadHold - dInsEQ))
		{
			bCanOpen |= true;
		}

		if (bCanOpen
			&& iSubMainWaitLongOrder == 0
			&& iSubMainPosition + iSubMainWaitLongOrder < m_iPositionLimit)
		{
			double dbOrderPrice = m_cwSubMainMarketData->AskPrice1;

			int iVol = m_iPositionLimit - (iSubMainWaitLongOrder + iSubMainPosition);
			if (iVol > m_iOrderVolume)
			{
				iVol = m_iOrderVolume;
			}

			cwOrderPtr orderptr = EasyInputOrder(m_SubMainInstrumentID.c_str(), iVol, dbOrderPrice, m_cwSubMainOpenCloseMode);
			if (orderptr.get() != NULL)
			{
				log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
					orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
			}
		}
	}
#ifdef _MSC_VER
#pragma endregion
#endif

#ifdef _MSC_VER
#pragma region BullSpread
#endif
	///牛市套利，做空远期合约。
	if (iSubMainPosition > 0)
	{
		///当前净持仓为多仓，则平仓, 用平仓参数，平仓条件低于开仓条件
		bool bNeedCancel = false;
		bool bCanOpen = false;
		//先检查挂单
		int iSubMainWaitShortOrder = 0;
		for (auto WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			bNeedCancel = true;
			if (m_SubMainInstrumentID == (std::string)WaitOrderIt->second->InstrumentID
				&& CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
			{
				if (bNeedCancel
					&& m_cwMainMarketData->AskPrice1 - WaitOrderIt->second->LimitPrice < m_dBuyThreadHold + dInsEQ)
				{
					bNeedCancel &= false;
				}

				if (bNeedCancel
					|| WaitOrderIt->second->LimitPrice - m_cwSubMainMarketData->AskPrice1 > 2 * dSubMainTickSize - dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
						WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
				iSubMainWaitShortOrder -= WaitOrderIt->second->VolumeTotal;
			}
		}

		//卖平仓
		if (bCanOpen
			|| (m_cwMainMarketData->AskPrice1 - m_cwSubMainMarketData->BidPrice1 < m_dBuyThreadHold + dInsEQ))
		{
			bCanOpen |= true;
		}

		if (bCanOpen
			&& iSubMainWaitShortOrder == 0)
		{
			double dbOrderPrice = m_cwSubMainMarketData->BidPrice1;

			int iVol = iSubMainPosition + iSubMainWaitShortOrder;
			if (iVol > m_iOrderVolume)
			{
				iVol = m_iOrderVolume;
			}
			cwOrderPtr orderptr = EasyInputOrder(m_SubMainInstrumentID.c_str(), iVol * (-1), dbOrderPrice, m_cwSubMainOpenCloseMode);
			if (orderptr.get() != NULL)
			{
				log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
					orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
			}
		}
	}
	else
	{
		///用开仓参数
		bool bNeedCancel = true;
		bool bCanOpen = false;
		//先检查挂单
		int iSubMainWaitShortOrder = 0;
		for (auto WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			bNeedCancel = true;
			if (m_SubMainInstrumentID == (std::string)WaitOrderIt->second->InstrumentID
				&& CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
			{
				if (bNeedCancel
					&& m_cwMainMarketData->AskPrice1 - WaitOrderIt->second->LimitPrice < m_dBuyThreadHold + dInsEQ)
				{
					bNeedCancel &= false;
				}

				if (bNeedCancel
					|| WaitOrderIt->second->LimitPrice - m_cwSubMainMarketData->AskPrice1 > 2 * dSubMainTickSize - dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					log.AddLog(cwStrategyLog::enCO, "%s, Ref:%s, P:%.2f, V:%d %s", WaitOrderIt->second->InstrumentID, WaitOrderIt->second->OrderRef,
						WaitOrderIt->second->LimitPrice, WaitOrderIt->second->VolumeTotal, WaitOrderIt->second->Direction == CW_FTDC_D_Buy ? "B" : "S");
				}
				iSubMainWaitShortOrder -= WaitOrderIt->second->VolumeTotal;

			}
		}

		//卖开仓
		if (bCanOpen
			|| (m_cwMainMarketData->AskPrice1 - m_cwSubMainMarketData->BidPrice1 < m_dBuyThreadHold + dInsEQ))
		{
			bCanOpen |= true;
		}

		if (bCanOpen
			&& iSubMainWaitShortOrder == 0
			&& iSubMainPosition + iSubMainWaitShortOrder > m_iPositionLimit * -1)
		{
			double dbOrderPrice = m_cwSubMainMarketData->BidPrice1;

			int iVol = iSubMainPosition + iSubMainWaitShortOrder + m_iPositionLimit;
			if (iVol > m_iOrderVolume)
			{
				iVol = m_iOrderVolume;
			}

			cwOrderPtr orderptr = EasyInputOrder(m_SubMainInstrumentID.c_str(), iVol * (-1), dbOrderPrice, m_cwSubMainOpenCloseMode);
			if (orderptr.get() != NULL)
			{
				log.AddLog(cwStrategyLog::enIO, "%s, Ref:%s, P:%.2f, V:%d %s", orderptr->InstrumentID, orderptr->OrderRef,
					orderptr->LimitPrice, orderptr->VolumeTotal, orderptr->Direction == CW_FTDC_D_Buy ? "B" : "S");
			}
		}
	}

#ifdef _MSC_VER
#pragma endregion
#endif

}