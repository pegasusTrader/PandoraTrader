#include "cwStrategyDemo.h"


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
	m_strCurrentUpdateTime = pPriceData->UpdateTime;

	//定义map，用于保存持仓信息 
	std::map<std::string, cwPositionPtr> CurrentPosMap;

	std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
	//定义map，用于保存挂单信息 
	std::map<std::string, cwOrderPtr> WaitOrderList;
	//获取挂单信  当前持仓信息
	GetPositionsAndActiveOrders(CurrentPosMap, WaitOrderList);

	//找出当前合约的持仓
	std::map<std::string, cwPositionPtr>::iterator PosIt;
	PosIt = CurrentPosMap.find(pPriceData->InstrumentID);
	if (PosIt != CurrentPosMap.end())
	{
		int iPos = PosIt->second->GetLongTotalPosition();
		if (iPos > 0)
		{
			//有多仓
			bool bHasWaitOrder = false;
			//检查所有挂单
			for (WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				//确定这个挂单是这个合约的
				if ((std::string)pPriceData->InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
				{
					//多单撤去
					if (WaitOrderIt->second->Direction == CW_FTDC_D_Buy)
					{
						CancelOrder(WaitOrderIt->second);
					}
					else
					{
						//标识有挂单
						bHasWaitOrder = true;

						//挂单价格大于最新价+2，撤单
						if (WaitOrderIt->second->LimitPrice > pPriceData->LastPrice + 2)
						{
							CancelOrder(WaitOrderIt->second);
						}
					}
				}
			}
			//没有挂单，就挂单平仓
			if (!bHasWaitOrder)
			{
				//挂委托限价单，
				EasyInputOrder(pPriceData->InstrumentID, -1 * iPos, pPriceData->BidPrice1);
			}
		}
		iPos = PosIt->second->GetShortTotalPosition();
		if (iPos > 0)
		{
			//有空仓
			std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
			//定义map，用于保存挂单信息 
			std::map<std::string, cwOrderPtr> WaitOrderList;
			//获取挂单信息
			GetActiveOrders(WaitOrderList);

			bool bHasWaitOrder = false;
			for (WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				if ((std::string)pPriceData->InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
				{
					if (WaitOrderIt->second->Direction == CW_FTDC_D_Sell)
					{
						CancelOrder(WaitOrderIt->second);
					}
					else
					{
						//有挂单
						bHasWaitOrder = true;

						//挂单价格小于最新价-2，撤单
						if (WaitOrderIt->second->LimitPrice < pPriceData->LastPrice - 2)
						{
							CancelOrder(WaitOrderIt->second);
						}
					}
				}
			}

			//没有挂单，就挂单平仓
			if (!bHasWaitOrder)
			{
				EasyInputOrder(pPriceData->InstrumentID, iPos, pPriceData->AskPrice1);
			}
		}
		if (PosIt->second->GetLongTotalPosition() + PosIt->second->GetShortTotalPosition() == 0)
		{
			
			std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
			//定义map，用于保存挂单信息 
			std::map<std::string, cwOrderPtr> WaitOrderList;
			//获取挂单信息
			GetActiveOrders(WaitOrderList);

			//看看有没有挂单
			bool bHasWaitOrder = false;
			for (WaitOrderIt = WaitOrderList.begin();
			WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
			{
				if ((std::string)pPriceData->InstrumentID == (std::string)WaitOrderIt->second->InstrumentID)
				{
					//有挂单
					bHasWaitOrder = true;

					//挂单价格小于最新价-2，撤单
					if (WaitOrderIt->second->LimitPrice < pPriceData->LastPrice - 2)
					{
						CancelOrder(WaitOrderIt->second);
					}
				}
			}

			//没有挂单就报委托单，方向多，价格买一价
			if (!bHasWaitOrder)
			{
				EasyInputOrder(pPriceData->InstrumentID, 1, pPriceData->BidPrice1);
			}
		}
	}
	else
	{
		//没找到持仓信息

		std::map<std::string, cwOrderPtr>::iterator WaitOrderIt;
		//定义map，用于保存挂单信息 
		std::map<std::string, cwOrderPtr> WaitOrderList;
		//获取挂单信息
		GetActiveOrders(WaitOrderList);

		//看看有没有挂单
		bool bHasWaitOrder = false;
		for (WaitOrderIt = WaitOrderList.begin();
		WaitOrderIt != WaitOrderList.end(); WaitOrderIt++)
		{
			if ((std::string)pPriceData->InstrumentID == (std::string)WaitOrderIt->second->InstrumentID
				&& (WaitOrderIt->second->Direction == CW_FTDC_D_Buy))
			{
				bHasWaitOrder = true;

				//挂单价格小于最新价-2，撤单
				if (WaitOrderIt->second->LimitPrice < pPriceData->LastPrice - 2)
				{
					CancelOrder(WaitOrderIt->second);
				}
			}
		}

		//没有挂单就报委托单，方向多，价格买一价
		if (!bHasWaitOrder)
		{
			EasyInputOrder(pPriceData->InstrumentID, 1, pPriceData->BidPrice1);
		}
	}

	
}

void cwStrategyDemo::OnRtnTrade(cwTradePtr pTrade)
{
}

void cwStrategyDemo::OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder)
{
}

void cwStrategyDemo::OnOrderCanceled(cwOrderPtr pOrder)
{
}

