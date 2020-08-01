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
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <thread>
#include "cwProductTradeTime.h"
#include "cwTradeCommonDefine.h"
#include "cwStrategyLog.h"

class cwBasicStrategy
{
public:
	enum cwOpenCloseMode :int
	{
		CloseTodayThenYd = 0,//先平今，再平昨,可开，用于平今免的品种
		OpenOnly = 1,//只开
		CloseOnly = 2,//只平
		CloseYdThenOpen = 3,//先平昨，后开仓，不平今，用于平今很贵的品种，弊病是要等全部平完再开仓
		CloseYdOrOpen = 4,//优先平昨，可开仓，开仓后不再平仓，用于平今很贵的品种，又不耽误开仓，弊病是有一点昨仓可能没平
		CloseYdThenToday = 5//先平昨，再平今,可开，用于平昨便宜，平今和开仓差不多的品种
	};
	const char * GetOpenCloseModeString(cwOpenCloseMode openclose);

public:
	cwBasicStrategy();
	~cwBasicStrategy();

	//表示系统是否初始化完成，可以正常进行报撤单操作
	bool	m_bStrategyReady;

	//表示策略名称
	virtual std::string  GetStrategyName() { return "BasicStrategy"; }

	/*
	PriceUpdate，OnRtnTrade，OnOrderCanceled，OnRspOrderInsert，OnRspOrderCancel这几个函数是系统回调函数，即策略的同名虚函数
	会在相应的情况下被系统调用，并执行用以实现策略功能。
	*/
	///MarketData SPI
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData) = 0;
	
	///Trade SPI
	//成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade) = 0;
	//报单回报, pOrder为最新报单，pOriginOrder为上一次更新报单结构体，有可能为NULL
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) = 0;
	//撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) = 0;
	//报单录入请求响应
	virtual void OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};
	//报单操作请求响应
	virtual void OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};

	///Strategy Timer
	virtual void OnStrategyTimer(int iTimerId) {};
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void OnReady() {};

	///Special For Simulation 
	///These functions will NOT be called in normal mode
	//回测部分结束（夜盘结束和日盘结束将被调用）
	virtual void OnSimulationPartEnd() {};
	//整个回测结束将被调用
	virtual void OnSimulationFinished() {};

	virtual void InitialStrategy(const char * pConfigFilePath);
	std::string			m_strConfigFileFullPath;

	//在Trade SPI准备就绪前，策略需要用到合约信息，可以利用该函数先从文件中获取合约信息，参数为NULL时，默认和程序在同一路径
	virtual void InitalInstrumentData(const char * pInstrumentDataFilePath = NULL);

	///Action  Function
	//获取最新的行情
	cwMarketDataPtr	GetLastestMarketData(std::string InstrumentID);
	//获取账户信息
	cwAccountPtr GetAccount();
	//获取挂单列表，传入map用于返回信息，本地报单编号(OrderRef)为Key
	bool GetActiveOrders(std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//获取挂单列表，传入合约，map用于返回信息，本地报单编号(OrderRef)为Key
	bool GetActiveOrders(std::string InstrumentID, std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//获取多头挂单数量，传入合约
	int GetActiveOrdersLong(std::string InstrumentID);		///key OrderRef
	//获取空头挂单数量，传入合约
	int GetActiveOrdersShort(std::string InstrumentID);		///key OrderRef
	//获取所有报单列表，传入map用于返回信息，交易所报单编号(sysOrderID)为Key
	bool GetAllOrders(std::map<std::string, cwOrderPtr>& Orders);				///Key OrderSysID
	//获取持仓列表，传入map用于返回信息，合约ID为Key
	bool GetPositions(std::map<std::string, cwPositionPtr>& PositionMap);		///Key InstrumentID
	//获取合约的净持仓，
	int	 GetNetPosition(std::string InstrumentID);
	//获取持仓和挂单列表
	bool GetPositionsAndActiveOrders(std::map<std::string, cwPositionPtr>& PositionMap,
		std::map<std::string, cwOrderPtr>& ActiveOrders);
	//获取指定合约持仓和挂单列表
	bool GetPositionsAndActiveOrders(std::string InstrumentID, cwPositionPtr& pPosition, std::map<std::string, cwOrderPtr>& ActiveOrders);
	//获取指定合约净持仓和挂单列表
	bool GetNetPositionAndActiveOrders(std::string InstrumentID, int & iPosition, std::map<std::string, cwOrderPtr> & ActiveOrders);
	//获取合约信息
	cwInstrumentDataPtr GetInstrumentData(std::string InstrumentID);


	//订阅合约
	void	   SubScribePrice(std::vector<std::string>& SubscribeInstrument);
	//取消订阅合约
	void	   UnSubScribePrice(std::vector<std::string>& UnSubscribeInstrument);

	//合约信息列表，需要最小变动，合约乘数等信息可以通过这个map获取，合约ID为Key
	std::unordered_map<std::string, cwInstrumentDataPtr> m_InstrumentMap;
	//获取合约最小变动，如果获取失败返回-1
	double    GetTickSize(const char * szInstrumentID);
	//获取合约乘数，如果获取失败返回-1
	double	  GetMultiplier(const char * szInstrumentID);
	//获取产品ID 
	char *    GetProductID(const char * szInstrumentID);
	//获取交易时间段，距开盘多少秒和距收盘多少秒
	//参数：合约名，行情时间（102835->10:28:35),交易阶段， 距该交易时段开盘多少秒，距收盘多少秒
	bool	  GetTradeTimeSpace(const char * szInstrumentID, const char * updatetime,
		cwProductTradeTime::cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);
	//获取前一个交易时段到当前交易时段开盘时间间隔
	int		  GetPreTimeSpaceInterval(const char * szInstrumentID, cwProductTradeTime::cwTradeTimeSpace iTradeIndex);

	//获取合约当前撤单次数
	int		  GetInstrumentCancelCount(std::string InstrumentID);
	//获取合约是否是订阅
	bool	  IsThisStrategySubScribed(std::string InstrumentID);
	//获取当前状态是否为回测模拟情况
	inline bool GetIsSimulation() { return m_bIsSimulation; }

	//设置定时器 iTimerId定时器id，在OnTimer回调依据此id判定是哪个定时器触发, iElapse 触发间隔（毫秒）
	//目前仅支持100个定时器，定时器内回调函数请勿处理复杂逻辑，所有定时器回调共用一个线程。
	//同个id下，触发间隔将会被覆盖
	bool	  SetTimer(int iTimerId, int iElapse);
	void	  RemoveTimer(int iTimerId);

	///系统自用接口信息，勿动
	void					_SetMdSpi(cwMDAPIType apiType, void * pSpi);
	void					_SetTradeSpi(cwTradeAPIType apiType, void *pSpi);
	void					_SetIsSimulation(bool IsSimulation = false) { m_bIsSimulation = IsSimulation; };

	virtual void			_SetReady() = 0;
	virtual void			_PriceUpdate(cwMarketDataPtr pPriceData) = 0;
	virtual void			_OnRtnTrade(cwTradePtr pTrade) = 0;
	virtual void			_OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) = 0;
	virtual void			_OnOrderCanceled(cwOrderPtr pOrder) = 0;
	virtual void			_OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) = 0;
	virtual void			_OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) = 0;
	virtual void			_OnTimer(int iTimerId) = 0;
protected:
	///系统自用接口信息，勿动
	std::set<std::string>	m_SubscribeInstrumentSet;

	cwOrderPtr				_InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);		///报单函数--限价单
	cwOrderPtr				_InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);		///报单函数--FAK单（Filled And Kill 立即成交剩余自动撤销指令）
	cwOrderPtr				_InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);		///报单函数--FOK单(FOK Filled Or Kill 立即全部成交否则自动撤销指令)

	cwOrderPtr				_EasyInputOrder(const char * szInstrumentID, int volume, double price,
		cwOpenCloseMode openclosemode = cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);																				///简化报单函数， volume正表示买，负表示卖，自动开平，有持仓就平仓，没有就开仓

	bool					_CancelOrder(cwOrderPtr pOrder);

private:	
	///系统自用接口信息，勿动
	bool					m_bIsSimulation;

	void *					m_pTradeSpi;
	cwTradeAPIType			m_TradeApiType;

	void *					m_pMdSpi;
	cwMDAPIType				m_MdApiType;

	cwProductTradeTime		m_ProductTradeTime;
	cwStrategyLog			m_BasicStrategyLog;

	//Timer	key:TimerID, value:Elapse in ms
	std::map<int, int>		m_cwTimerElapseMap;

	std::thread				m_StrategyTimerWorkingThread;
	volatile bool			m_bStrategyTimerWorkingThreadRun;
	void					StrategyTimerWorkingThread();
};
