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

//PairTrading may use for arbitrage

#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwStrategyLog.h"
#include "cwBasicCout.h"
#include "cwPandoraAgentManager.h"

class cwPandoraPairTrading :
	public cwBasicKindleStrategy
{
public:
	cwPandoraPairTrading();
	~cwPandoraPairTrading();


	///MarketData SPI
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	///Trade SPI
	//成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade) {};
	//报单回报, pOrder为最新报单，pOriginOrder为上一次更新报单结构体，有可能为NULL
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	//撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) {};
	//报单录入请求响应
	virtual void OnRspOrderInsert(cwOrderPtr pOrder, cwFtdcRspInfoField * pRspInfo) {};
	//报单操作请求响应
	virtual void OnRspOrderCancel(cwOrderPtr pOrder, cwFtdcRspInfoField * pRspInfo) {};
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void OnReady();
	
	//策略交易次主力合约
	void		 DoManualSpread();

	std::string					m_strCurrentUpdateTime;			//最新行情时间

protected:
	std::string					m_MainInstrumentID;				//主力合约
	std::string					m_SubMainInstrumentID;			//次主力合约

	//价差定义为主力-次主力
	double						m_dBuyThreadHold;				//价差买阈值
	double						m_dSellThreadHold;				//价差卖阈值
	
	double						m_dVolumeCoefficient;			//对冲比率

	cwMarketDataPtr				m_cwMainMarketData;				//主力合约行情
	cwMarketDataPtr				m_cwSubMainMarketData;			//次主力合约行情

	cwOpenCloseMode				m_cwMainOpenCloseMode;			//主力开平模式
	cwOpenCloseMode				m_cwSubMainOpenCloseMode;		//次主力开平模式

	int							m_iPositionLimit;				//持仓限制
	int							m_iOrderVolume;					//报单手数

	cwStrategyLog				m_StrategyLog;					//策略日志
	cwBasicCout					m_cwShow;						//cout


	cwPandoraAgentManager					m_PandoraAgentManager;		//代理人管理者，可通过他创建代理人

	cwPandoraAgentManager::cwAgentDataPtr	m_pPositionAgent;			//仓位管理代理人，要指定合约
};

