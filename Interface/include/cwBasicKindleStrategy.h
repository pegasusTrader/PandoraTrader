//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on May. 10th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////


#pragma once
#include "cwCommonUtility.h"
#include "cwBasicStrategy.h"
#include "cwKindleStickSeries.h"
#include <condition_variable>

class cwBasicKindleStrategy :
	public cwBasicStrategy
{
public:
	typedef std::shared_ptr<cwKindleStickSeries>				cwKindleSeriesPtr;

public:
	cwBasicKindleStrategy();
	virtual ~cwBasicKindleStrategy();

	///MarketData SPI
	//行情更新（PriceUpdate回调会先于OnBar， 在PriceUpdate已经可以获取更新好的K线）
	virtual void			PriceUpdate(cwMarketDataPtr pPriceData) {};
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(std::string InstrumentID, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindle) {};

	///Trade SPI
	//成交回报
	virtual void			OnRtnTrade(cwTradePtr pTrade) {};
	//报单回报, pOrder为最新报单，pOriginOrder为上一次更新报单结构体，有可能为NULL
	virtual void			OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	//撤单成功
	virtual void			OnOrderCanceled(cwOrderPtr pOrder) {};
	//报单录入请求响应
	virtual void			OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};
	//报单操作请求响应
	virtual void			OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};

	///System Call Back
	//定时器响应
	virtual void			OnStrategyTimer(int iTimerId) {};
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void			OnReady() {};


	//订阅k线
	cwKindleSeriesPtr		SubcribeKindle(const char * szInstrumentID, int iTimeScale);
	//获取已经订阅的k线
	cwKindleSeriesPtr		GetKindleSeries(const char * szInstrumentID, int iTimeScale);

	//报单函数--限价单
	cwOrderPtr				InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//报单函数--FAK单（Filled And Kill 立即成交剩余自动撤销指令）
	cwOrderPtr				InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//报单函数--FOK单(FOK Filled Or Kill 立即全部成交否则自动撤销指令)
	cwOrderPtr				InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);

	//简化报单函数， volume正表示买，负表示卖，自动开平，有持仓就平仓，没有就开仓
	cwOrderPtr				EasyInputOrder(const char * szInstrumentID, int volume, double price,
		cwOpenCloseMode openclosemode = cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);

	//撤单
	bool					CancelOrder(cwOrderPtr pOrder);
	//全部撤单
	int						CancelAll();
	//按指定合约全部撤单
	int						CancelAll(const char * szInstrumentID);
	//按指定合约和方向全部撤单
	int						CancelAll(const char * szInstrumentID, cwFtdcDirectionType direction);

	//委托交易，PositionAgency代理机构将会按需求管理好持仓
	//注意，当启用PositionAgency功能之后，请勿做下单或者撤单操作，以免产生冲突。

	virtual void			SetAgentManager(void * pAgentMgr);


	///系统自用接口信息，勿动
	virtual void			_SetReady();
	virtual void			_PriceUpdate(cwMarketDataPtr pPriceData);
	virtual void			_OnRtnTrade(cwTradePtr pTrade);
	virtual void			_OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	virtual void			_OnOrderCanceled(cwOrderPtr pOrder);
	virtual void			_OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnTimer(int iTimerId);
private:
	///系统自用接口信息，勿动
	//更新K线
	void					_UpdateKindleSeries(cwMarketDataPtr pPriceData, std::map<int, cwKindleSeriesPtr> & OnBarMap);
	bool					_GetAgentWorking(std::string instrumentid);
	
private:
	///K线容器 key:instrument key: TimeScale value :Kindle Series
	std::map<std::string, std::map<int, cwKindleSeriesPtr>>		m_KindleSeriesMap;

	bool					m_bAgentWork;


	bool					m_bNightMode;
	std::string				m_strAppStartDay;
	std::string				m_strAppStartNextDay;
	std::string				m_strAppStartTime;

	///Updating Thread 
	///策略事件类型
	enum StrategyEventType
	{
		EventType_OnReady = 0
		, EventType_OnTimer
		, EventType_PriceUpdate
		, EventType_OnBar
		, EventType_RtnTrade
		, EventType_RtnOrder
		, EventType_OnCanceled
		, EventType_OnRspInsert
		, EventType_OnRspCancel
		, AgentType_PriceUpdate
		, AgentType_RtnTrade
		, AgentType_RtnOrder
		, AgentType_OnCanceled
		, AgentType_OnRspInsert
		, AgentType_OnRspCancel
	};

	///策略事件信息内容
	struct EventTypeStruct
	{
		StrategyEventType		EventType;
		cwMarketDataPtr			pPriceData;
		cwTradePtr				pTrade;
		cwOrderPtr				pOrder;
		cwOrderPtr				pOriginOrder;
		cwRspInfoPtr			pRspInfo;

		std::string				strInstrumentID;
		int						iBarId;
		cwKindleSeriesPtr		pKindle;
	};
	typedef std::shared_ptr<EventTypeStruct>	EventTypeStructPtr;


	std::deque<EventTypeStructPtr>				m_EventTypeStructDeque;
	cwMUTEX										m_EventTypeDequeMutex;
	std::condition_variable						m_EventWorkingMutexCv;

	std::thread									m_EventTypeWorkingThread;
	volatile bool								m_bEventTypeWorkingThreadRun;

	void										_EventTypeWorkingThread();
	void										_AddEventType(EventTypeStructPtr EventPtr);

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwBasicKindleStrategy);

	void *										m_pAgentManager;

};

