//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on May. 20th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "cwBasicAgent.h"
#include "cwBasicStrategy.h"

class cwPandoraPositionAgent :
	public cwBasicAgent
{
public:
	cwPandoraPositionAgent();
	~cwPandoraPositionAgent();

	virtual void			PriceUpdate(cwMarketDataPtr pPriceData);
	virtual void			OnRtnTrade(cwTradePtr pTrade);
	virtual void			OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	virtual void			OnOrderCanceled(cwOrderPtr pOrder);
	virtual void			OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);

	void					DealExpectedPosition(std::string InstrumentID, int iExpectedMaintain= 0, const char * szCallMsg = NULL);


	void					SetExpectPosition(int iExpPos = 0);

	int						m_iExpectPosition;
	std::string				m_strInstrumentID;

	cwBasicStrategy::cwOpenCloseMode OpenCloseMode;			//开平模式
	int			InsLargeOrderVolume;		//大单量，大于其认为大单
	int			InsLittleOrderVolume;		//小单量，小于其认为小单
	int			InsAskBidGap;				//盘口价差
};

