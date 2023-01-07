#include "cwPandoraPositionAgent.h"



cwPandoraPositionAgent::cwPandoraPositionAgent()
{
	m_bAgentWorking = true;

	m_iExpectPosition = 0;

	OpenCloseMode = cwBasicStrategy::cwOpenCloseMode::CloseTodayThenYd;

	InsLargeOrderVolume = 200;
	InsLittleOrderVolume = 5;

	InsAskBidGap = 1;
}


cwPandoraPositionAgent::~cwPandoraPositionAgent()
{
}

void cwPandoraPositionAgent::PriceUpdate(cwMarketDataPtr pPriceData)
{
	m_strCurrentUpdateTime = pPriceData->UpdateTime;

	if (m_bAgentWorking)
	{
		cwProductTradeTime::cwTradeTimeSpace TradeTimeSpace = cwProductTradeTime::NoTrading;
		int iOpen = 0, iClose = 0;
		bool bDeal = false;
		bool bRet = GetTradeTimeSpace(pPriceData->InstrumentID, m_strCurrentUpdateTime.c_str(),
			TradeTimeSpace, iOpen, iClose);
		if (!bRet
			|| TradeTimeSpace == cwProductTradeTime::NoTrading
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionMatchClose
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionOrderingClose)
		{
			return;
		}
		else
		{
			if (iClose > 2)
			{
				bDeal = true;
			}
			else
			{
				return;
			}
		}

		if (bDeal)
		{
			DealExpectedPosition(m_strInstrumentID, m_iExpectPosition);
		}
	}
}

void cwPandoraPositionAgent::OnRtnTrade(cwTradePtr pTrade)
{
	if (m_bAgentWorking)
	{
		cwProductTradeTime::cwTradeTimeSpace TradeTimeSpace = cwProductTradeTime::NoTrading;
		int iOpen = 0, iClose = 0;
		bool bDeal = false;
		bool bRet = GetTradeTimeSpace(m_strInstrumentID.c_str(), m_strCurrentUpdateTime.c_str(),
			TradeTimeSpace, iOpen, iClose);
		if (!bRet
			|| TradeTimeSpace == cwProductTradeTime::NoTrading
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionMatchClose
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionOrderingClose)
		{
			return;
		}
		else
		{
			if (iClose > 2)
			{
				bDeal = true;
			}
			else
			{
				return;
			}
		}

		if (bDeal)
		{
			DealExpectedPosition(m_strInstrumentID, m_iExpectPosition);
		}
	}
}

void cwPandoraPositionAgent::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
	if (m_bAgentWorking)
	{
		cwProductTradeTime::cwTradeTimeSpace TradeTimeSpace = cwProductTradeTime::NoTrading;
		int iOpen = 0, iClose = 0;
		bool bDeal = false;
		bool bRet = GetTradeTimeSpace(m_strInstrumentID.c_str(), m_strCurrentUpdateTime.c_str(),
			TradeTimeSpace, iOpen, iClose);
		if (!bRet
			|| TradeTimeSpace == cwProductTradeTime::NoTrading
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::AMCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionMatchOpen
			|| TradeTimeSpace == cwProductTradeTime::NightCallAuctionOrderingOpen
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionMatchClose
			|| TradeTimeSpace == cwProductTradeTime::CallAuctionOrderingClose)
		{
			return;
		}
		else
		{
			if (iClose > 2)
			{
				bDeal = true;
			}
			else
			{
				return;
			}
		}

		if (bDeal)
		{
			DealExpectedPosition(m_strInstrumentID, m_iExpectPosition);
		}
	}
}

void cwPandoraPositionAgent::OnOrderCanceled(cwOrderPtr pOrder)
{
}

void cwPandoraPositionAgent::OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo)
{
}

void cwPandoraPositionAgent::OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo)
{
}

void cwPandoraPositionAgent::SetExpectPosition(int iExpPos)
{
	if (iExpPos != m_iExpectPosition)
	{
		m_iExpectPosition = iExpPos;

		//if (m_bAgentWorking)
		//{
		//	DealExpectedPosition(m_strInstrumentID, m_iExpectPosition);
		//}
	}
}

void cwPandoraPositionAgent::DealExpectedPosition(std::string InstrumentID, int iExpectedMaintain/*= 0*/, const char * szCallMsg /*= NULL*/)
{
	double dTickSize = GetTickSize(InstrumentID.c_str());
	if (dTickSize < 0)
	{
		dTickSize = 0;
	}
	const double dInsEQ = dTickSize / 10;

	cwMarketDataPtr MarketData = GetLastestMarketData(InstrumentID);
	if (MarketData.get() == NULL
		|| (MarketData->AskPrice1 < dTickSize && MarketData->BidPrice1 < dTickSize))
	{
		return;
	}

	std::map<std::string, cwPositionPtr> CurrentPosMap;
	std::map<cwActiveOrderKey, cwOrderPtr> WaitOrderList;
	GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);

	int iMaintain = 0, iWaitOrder = 0;
	std::map<std::string, cwPositionPtr>::iterator PosIt;

	//Get Instrument Position
	PosIt = CurrentPosMap.find(InstrumentID);
	if (PosIt != CurrentPosMap.end())
	{
		iMaintain = PosIt->second->GetLongTotalPosition() - PosIt->second->GetShortTotalPosition();
	}
	else
	{
		iMaintain = 0;
	}

	for (auto WaitOrderIt = WaitOrderList.begin();
		WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
	{
		if (InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
		{
			if (CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
			{
				iWaitOrder += WaitOrderIt->second->VolumeTotal;
			}
			else
			{
				iWaitOrder -= WaitOrderIt->second->VolumeTotal;
			}
		}
	}

	double dPosImbalance = iExpectedMaintain - iMaintain;
	int iPosiImbalance = dPosImbalance > 0 ? (int)(dPosImbalance + 0.4) : (int)(dPosImbalance - 0.4);

	if (iPosiImbalance == 0)
	{
		for (auto WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			if (InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
			{
				CancelOrder(WaitOrderIt->second);
			}
		}
	}
	else
	{
		int iImbalance = iPosiImbalance - iWaitOrder;

		//Cancel Orders 
		if (iImbalance > 0)
		{
			for (auto WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				if (iImbalance == 0)
				{
					break;
				}
				if (InstrumentID == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
				{
					if (iImbalance - WaitOrderIt->second->VolumeTotal >= 0)
					{
						iImbalance -= WaitOrderIt->second->VolumeTotal;
						CancelOrder(WaitOrderIt->second);
					}
					else
					{
						CancelOrder(WaitOrderIt->second);
						iImbalance = 0;
					}
				}
			}
		}
		else
		{
			for (auto WaitOrderIt = WaitOrderList.begin();
				WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				if (iImbalance == 0)
				{
					break;
				}
				if (InstrumentID == (std::string)WaitOrderIt->second->InstrumentID
					&& CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
				{
					if (iImbalance + WaitOrderIt->second->VolumeTotal <= 0)
					{
						iImbalance += WaitOrderIt->second->VolumeTotal;
						CancelOrder(WaitOrderIt->second);
					}
					else
					{

						CancelOrder(WaitOrderIt->second);
						iImbalance = 0;
					}
				}
			}
		}

		//After Cancel Orders but iImbalance != 0 So Input Order
		if (iImbalance != 0)
		{
			double orderprice = 0.0;
			int ordervolume = 0;

			if (iImbalance > 0)
			{
				//Need Long
				if (MarketData->AskVolume1 > 0
					&& MarketData->AskPrice1 - MarketData->BidPrice1 > InsAskBidGap * dTickSize - dInsEQ)
				{
					if (MarketData->AskVolume1 >= InsLargeOrderVolume)
					{
						if (MarketData->BidVolume1 >= InsLittleOrderVolume)
						{
							orderprice = MarketData->BidPrice1 + dTickSize;
						}
						else
						{
							orderprice = MarketData->BidPrice1;
						}
					}
					else
					{
						double dAskBidGap = MarketData->AskPrice1 - MarketData->BidPrice1;
						if (dAskBidGap <= InsAskBidGap * dTickSize + dInsEQ
							&& MarketData->AskVolume1 < InsLittleOrderVolume)
						{
							orderprice = MarketData->AskPrice1;
						}
						else
						{
							if (dAskBidGap > 3 * InsAskBidGap * dTickSize)
							{
								orderprice = MarketData->BidPrice1 + InsAskBidGap * dTickSize;
							}
							else
							{
								orderprice = ((int)(dAskBidGap / 2 / dTickSize + 0.5)) * dTickSize;
								orderprice = MarketData->BidPrice1 + orderprice;
							}
						}
					}
				}
				else
				{
					int iLittleVol = InsLittleOrderVolume;
					//if (m_LongOrderRivalPrice[InstrumentID] < MainMarketData->AskPrice1 - dInsEQ)
					//{
					//	//多头超止损价
					//	iLittleVol = (int)(iLittleVol * 2);
					//}
					if (MarketData->UpperLimitPrice - MarketData->AskPrice1 < dInsEQ)
					{
						//快涨停
						iLittleVol = (int)(iLittleVol * 10);
					}
					if (MarketData->AskVolume1 <= iLittleVol
						|| (MarketData->BidVolume1 >= InsLargeOrderVolume
							&&  MarketData->BidVolume1 > MarketData->AskVolume1 * 1.5))
					{
						orderprice = MarketData->AskPrice1;
					}
					else
					{
						orderprice = MarketData->BidPrice1;
					}
					if (MarketData->AskVolume1 <= 0)
					{
						//已经涨停
						orderprice = MarketData->BidPrice1;
					}
				}
				if (MarketData->AskVolume1 <= 0)
				{
					//已经涨停
					//m_LongOrderRivalPrice[m_cwArbiParameter.MainInstrument] = MainMarketData->BidPrice1;
				}
				else
				{
					//m_LongOrderRivalPrice[m_cwArbiParameter.MainInstrument] = MainMarketData->AskPrice1;
				}

				if (iImbalance > InsLittleOrderVolume)
				{
					ordervolume = InsLittleOrderVolume;
				}
				else
				{
					ordervolume = iImbalance;
				}

				if (orderprice > dTickSize
					&& ordervolume > 0)
				{
					cwOrderPtr orderptr = EasyInputOrder(InstrumentID.c_str(), ordervolume, orderprice, OpenCloseMode);
					if (orderptr.get() != NULL)
					{
					}
				}
			}
			else
			{
				//Need Short
				if (MarketData->AskVolume1 > 0
					&& MarketData->AskPrice1 - MarketData->BidPrice1 > InsAskBidGap * dTickSize + dInsEQ)
				{
					if (MarketData->BidVolume1 >= InsLargeOrderVolume)
					{
						if (MarketData->AskVolume1 >= InsLittleOrderVolume)
						{
							orderprice = MarketData->AskPrice1 - dTickSize;
						}
						else
						{
							orderprice = MarketData->AskPrice1;
						}
					}
					else
					{
						double dAskBidGap = MarketData->AskPrice1 - MarketData->BidPrice1;
						if (dAskBidGap < InsAskBidGap * dTickSize + dInsEQ
							&& MarketData->AskVolume1 < InsLittleOrderVolume)
						{
							orderprice = MarketData->BidPrice1;
						}
						else
						{
							if (dAskBidGap > 3 * 3 * InsAskBidGap * dTickSize - dInsEQ)
							{
								orderprice = MarketData->AskPrice1 - InsAskBidGap * dTickSize;
							}
							else
							{
								orderprice = ((int)(dAskBidGap / 2 / dTickSize + 0.5)) * dTickSize;
								orderprice = MarketData->AskPrice1 - orderprice;
							}
						}
					}
				}
				else
				{
					int iLittleVol = InsLittleOrderVolume;
					//if (m_ShortOrderRivalPrice[m_cwArbiParameter.MainInstrument] - dInsEQ > MainMarketData->BidPrice1 )
					//{
					//	//空头超止损价
					//	iLittleVol = (int)(iLittleVol * 2);
					//}
					if (MarketData->BidPrice1 - MarketData->LowerLimitPrice < dInsEQ)
					{
						//快跌停
						iLittleVol = (int)(iLittleVol * 10);
					}
					if (MarketData->BidVolume1 <= iLittleVol
						|| (MarketData->AskVolume1 >= InsLargeOrderVolume
							&&  MarketData->AskVolume1 > MarketData->BidVolume1 * 1.5))
					{
						orderprice = MarketData->BidPrice1;
					}
					else
					{
						orderprice = MarketData->AskPrice1;
					}
					if (MarketData->BidVolume1 <= 0)
					{
						//已经跌停
						orderprice = MarketData->AskPrice1;
					}
				}
				if (MarketData->BidVolume1 <= 0)
				{
					//已经跌停
					//m_ShortOrderRivalPrice[m_cwArbiParameter.MainInstrument] = MainMarketData->AskPrice1;
				}
				else
				{
					//m_ShortOrderRivalPrice[m_cwArbiParameter.MainInstrument] = MainMarketData->BidPrice1;
				}

				if (iImbalance * -1 > InsLittleOrderVolume)
				{
					ordervolume = InsLittleOrderVolume * -1;
				}
				else
				{
					ordervolume = iImbalance;
				}

				if (orderprice > dTickSize
					&& ordervolume < 0)
				{
					cwOrderPtr orderptr = EasyInputOrder(InstrumentID.c_str(), ordervolume, orderprice, OpenCloseMode);
					if (orderptr.get() != NULL)
					{
					}
				}
			}
		}
	}

	for (auto WaitOrderIt = WaitOrderList.begin();
		WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
	{
		if (InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
		{
			if (CW_FTDC_D_Buy == WaitOrderIt->second->Direction)
			{
				int iLittleVol = InsLittleOrderVolume;
				if (MarketData->UpperLimitPrice - MarketData->AskPrice1 < dInsEQ)
				{
					//快涨停
					iLittleVol = (int)(iLittleVol * 10);
				}

				if (MarketData->AskVolume1 > 0
					&& MarketData->AskPrice1 - MarketData->BidPrice1 > dTickSize + dInsEQ)
				{
					if (MarketData->AskVolume1 <= iLittleVol
						&& MarketData->BidPrice1 - WaitOrderIt->second->LimitPrice > -dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						continue;
					}
				}
				else
				{
					if (MarketData->AskVolume1 > 0
						&& MarketData->AskVolume1 < iLittleVol
						&& MarketData->AskPrice1 - WaitOrderIt->second->LimitPrice > dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						continue;
					}
				}

				//Not At First Rank
				if (MarketData.get() == NULL
					|| WaitOrderIt->second->LimitPrice < MarketData->BidPrice1 - dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					continue;
				}
			}
			if (CW_FTDC_D_Sell == WaitOrderIt->second->Direction)
			{
				int iLittleVol = InsLittleOrderVolume;
				if (MarketData->BidPrice1 - MarketData->LowerLimitPrice < dInsEQ)
				{
					//快跌停
					iLittleVol = (int)(iLittleVol * 10);
				}

				if (MarketData->AskVolume1 > 0
					&& MarketData->AskPrice1 - MarketData->BidPrice1 > dTickSize + dInsEQ)
				{
					if (MarketData->BidVolume1 <= iLittleVol
						&& WaitOrderIt->second->LimitPrice - MarketData->AskPrice1 > -dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						continue;
					}
				}
				else
				{
					if (MarketData->BidVolume1 > 0
						&& MarketData->BidVolume1 < iLittleVol
						&& WaitOrderIt->second->LimitPrice - MarketData->BidPrice1 > dInsEQ)
					{
						CancelOrder(WaitOrderIt->second);
						continue;
					}
				}

				//Not At First Rank
				if (MarketData.get() == NULL
					|| WaitOrderIt->second->LimitPrice > MarketData->AskPrice1 + dInsEQ)
				{
					CancelOrder(WaitOrderIt->second);
					continue;
				}
			}
		}
	}
}
