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

//提示，下划线开头的函数如_PriceUpdate为系统调用，请勿调用。

#pragma once
#include "cwCommonUtility.h"
#include "cwBasicStrategy.h"
#include "cwKindleStickSeries.h"
#include <condition_variable>
#include <atomic>

#define		CW_CORRECT_TRADINGDAY
//#define		CW_USING_MYSQL_LIB


class cwBasicKindleStrategy :
	public cwBasicStrategy
{
public:
	typedef std::shared_ptr<cwKindleStickSeries>				cwKindleSeriesPtr;

public:
	cwBasicKindleStrategy();
	virtual ~cwBasicKindleStrategy();

	///MarketData SPI
	//行情更新（OnBar会先于PriceUpdate回调， 在PriceUpdate已经可以获取更新好的K线）
	virtual void			PriceUpdate(cwMarketDataPtr pPriceData) {};
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {};

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
	//定时器ID, 在SetTimer的时候传给系统，如果InstrumentID传NULL,在回调的时候szInstrumentID为空字符串（“”），
	//否则传什么合约和TimerId，OnStrategyTimer的szInstrumentID就是那个合约信息
	virtual void			OnStrategyTimer(int iTimerId, const char * szInstrumentID) {};
	//当策略交易初始化完成时会调用OnReady, 可以在此函数做策略的初始化操作
	virtual void			OnReady() {};


	//订阅k线， iTimeScale是k线周期，秒数（如5分钟为300）
	cwKindleSeriesPtr		SubcribeKindle(const char * szInstrumentID, int iTimeScale, int HisKindleCount = 0);
	cwKindleSeriesPtr		SubcribeDailyKindle(const char * szInstrumentID);
	//需要合约信息支持
	cwKindleSeriesPtr		SubcribeIndexKindle(const char* szProductId, int iTimeScale, int HisKindleCount = 0);

	std::string				GetIndexName(const char* szProductId);

	//从tick数据构建历史数据
	bool					InitialHisKindleFromKinldeFile(const char * szFilePath);
	bool					InitialHisKindleFromIndexFile(const char * szTickFile);

	bool					InitialHisKindleFromHisKindleFolder(const char* szHisFolder);
	//
	void					GetKindleFromPublicBus();

	bool					InitialHisKindleFromDB();

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

	//简化报单函数， volume正表示买，负表示卖，自动开平，有持仓就平仓，没有就开仓
	//该函数会对订单，根据下单模式和交易所合约信息配置，进行拆单操作。
	std::deque<cwOrderPtr>	EasyInputMultiOrder(const char * szInstrumentID, int volume, double price,
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

	//设置合约所在资产组合ID, 对于没有设置的合约，默认在资产组合（portfolio)ID为0的资产组合中。
	//对于同个portfolio下的合约，会用同个线程来处理，对于每个资产组合都有自己的处理线程
	void					SetPortfolioId(const char * szInstrumentID, unsigned int iPortfolioId);

	//设置同步模式
	//true:同步, false:异步
	//如果仓位和挂单相关的信息，需要根据回调接口来更新统计的话，请使用同步模式
	//如果仓位和挂单相关的信息，只用平台回调接口来获取即可，做多资产组合的化，可以用异步模式提速
	//建议在回测的时候，使用同步模式
	void					SetSynchronizeMode(bool bSynchronous);

	//设置是否将用于指数计算的最新行情写入缓存文件，
	//如果有单独指数计算进程，则设置为不需要（false）,如果只有自身进程，则设置为需要（true）
	void					SetWriteIndexInfoCacheToFile(bool bNeedWriteToFile) { m_bNeedWriteCacheToFile = bNeedWriteToFile; };

	//研究模式(暂不支持）
	void					SetResearchMode(bool bResearch, int iReserveTime = 5);


	///系统自用接口信息，勿动
	virtual void			_SetReady();
	virtual void			_OnDisConnect();
	virtual void			_OnSimulationBegin(int64_t timeStamp);
	virtual void			_PriceUpdate(cwMarketDataPtr pPriceData);
	virtual void			_OnRtnTrade(cwTradePtr pTrade);
	virtual void			_OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	virtual void			_OnOrderCanceled(cwOrderPtr pOrder);
	virtual void			_OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnTimer(int iTimerId, const char * szInstrumentID);

	enum cwKINDLE_TIMESCALE:int
	{
		cwKINDLE_TIMESCALE_1MIN = 60,
		cwKINDLE_TIMESCALE_3MIN = cwKINDLE_TIMESCALE_1MIN * 3,
		cwKINDLE_TIMESCALE_5MIN = cwKINDLE_TIMESCALE_1MIN * 5,
		cwKINDLE_TIMESCALE_15MIN = cwKINDLE_TIMESCALE_1MIN * 15,
		cwKINDLE_TIMESCALE_30MIN = cwKINDLE_TIMESCALE_1MIN * 30,
		cwKINDLE_TIMESCALE_1HOUR = cwKINDLE_TIMESCALE_1MIN * 60,
		cwKINDLE_TIMESCALE_DAILY
	};
private:
	///系统自用接口信息，勿动
	//更新K线
	void					_UpdateKindleSeries(cwMarketDataPtr pPriceData, std::map<int, cwKindleSeriesPtr> & OnBarMap);
	bool					_GetAgentWorking(std::string instrumentid);

protected:
	bool					m_bNightMode;						//是否为夜盘
	std::string				m_strAppStartDay;					//当前日期
	std::string				m_strAppStartNextDay;				//第二天日期
	std::string				m_strNextTradingDay;				//下一个交易日（以当前日期计算，下一个交易日）
	std::string				m_strAppStartTime;					//程序开启时间

	const unsigned int		m_iDefaultWorkBenchId;				//默认工作区ID, 为0，自定义工作区ID,请大于0.

	bool					m_bResearchMode = false;			//研究模式

private:
	bool					m_bSynchronizeMode;					//是否同步	true:同步， false:异步

	cwMUTEX																			m_cwDealKindleMutex;			//K线处理同步
	///K线容器 key:instrument key: TimeScale value :Kindle Series
	std::unordered_map<std::string, std::unordered_map<int, cwKindleSeriesPtr>>		m_KindleSeriesMap;
	///历史k线容器 Key:Instrument key: TimeScale value:HisKindle Count
	std::unordered_map<std::string, std::unordered_map<int, int>>					m_HisKindleCountMap;

	///Updating Thread 
	///策略事件类型
	enum StrategyEventType
	{
		EventType_OnReady = 0							//系统Ready回调
		, EventType_SimulationBegin						//回测开始
		, EventType_OnTimer								//定时器回调
		, EventType_PriceUpdate							//Tick行情更新
		, EventType_OnBar								//K线更新
		, EventType_RtnTrade							//成交回报
		, EventType_RtnOrder							//报单回报
		, EventType_OnCanceled							//撤单回报
		, EventType_OnRspInsert							//报单录入回报响应
		, EventType_OnRspCancel							//撤单操作请求响应
		, AgentType_PriceUpdate							//代理人行情更新
		, AgentType_RtnTrade							//代理人 成交回报
		, AgentType_RtnOrder							//代理人 报单回报
		, AgentType_OnCanceled							//代理人 撤单回报
		, AgentType_OnRspInsert							//代理人 报单录入回报响应
		, AgentType_OnRspCancel							//代理人 撤单操作请求响应
	};

	///策略事件信息内容， 不同事件类型下不同的数据字段有数据
	struct EventTypeStruct
	{
		StrategyEventType		EventType;				//事件信息类型
		cwMarketDataPtr			pPriceData;				//行情数据
		cwTradePtr				pTrade;					//成交信息
		cwOrderPtr				pOrder;					//当前报单信息
		cwOrderPtr				pOriginOrder;			//更新前报单信息内容
		cwRspInfoPtr			pRspInfo;				//回报信息

		std::string				strInstrumentID;		//合约
		int64_t					iBarId;					//k线号
		cwKindleSeriesPtr		pKindle;				//K线内容
	};
	typedef std::shared_ptr<EventTypeStruct>					EventTypeStructPtr;

	//资产组合工作区
	struct PortfolioWorkBench
	{
		unsigned int											iWorkBenchId;					//工作区ID，必须项
		std::string												strWorkBenchName;				//工作区名称，可不赋值

		std::atomic<int>										iTradeInfoCnt;					//当前需要处理的交易信息数量
		std::condition_variable									TradeInfoDoneCv;				//

		std::deque<EventTypeStructPtr>							EventTypeStructDeque;			//工作区事件信息队列
		cwMUTEX													EventTypeDequeMutex;			//事件信息队列同步
		std::condition_variable									EventWorkingMutexCv;			//添加条件变量通知工作区工作线程
		std::atomic<bool>										bEventFinished;

		std::thread												EventTypeWorkingThread;			//工作区工作线程
		volatile std::atomic<bool>								bEventTypeWorkingThreadRun;		//工作区线程运行状态
	};
	typedef std::shared_ptr<PortfolioWorkBench>					PortfolioWorkBenchPtr;

	//支持根据资产组合（portfolio)数量，来设定工作线程数量。
	std::unordered_map<std::string, unsigned int>				m_InstrumentToPortfolioMap;		//Key:InstrumentID， value:WorkBenchID
	std::unordered_map<unsigned int, PortfolioWorkBenchPtr>		m_PortfolioMgrIntMap;			//key:WorkBenchID, value:WorkBench
	std::unordered_map<std::string, PortfolioWorkBenchPtr>		m_PortfolioMgrStrMap;			//Key:InstrumentID, value:WorkBench

	PortfolioWorkBenchPtr										m_pDefaultWorkBench;			//默认工作区

	//创建工作区
	PortfolioWorkBenchPtr						CreateWorkBench(unsigned int iBenchId, const char * pBenchName = NULL);
	//获取工作区
	PortfolioWorkBenchPtr						GetWorkBench(std::string instrumentid);

	//工作区工作线程
	void										_EventTypeWorkingThread(PortfolioWorkBenchPtr pWorkBench);
	void										_AddEventType(PortfolioWorkBenchPtr pWorkBench, EventTypeStructPtr EventPtr);


	//std::deque<EventTypeStructPtr>				m_EventTypeStructDeque;
	//cwMUTEX										m_EventTypeDequeMutex;
	//std::condition_variable						m_EventWorkingMutexCv;

	//std::thread									m_EventTypeWorkingThread;
	//volatile bool								m_bEventTypeWorkingThreadRun;

	//void										_EventTypeWorkingThread();
	//void										_AddEventType(EventTypeStructPtr EventPtr);

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwBasicKindleStrategy);

	void *										m_pAgentManager;


	///Index Price and Kindle Update;
	std::string									m_strHisDataPath;
	bool										m_bNeedIndexKindle = false;

	std::unordered_map<std::string, cwMarketDataPtr>									m_FileLastMDCacheMap;
	//key Product, key InstrumentID
	std::unordered_map <std::string, std::unordered_map<std::string, cwMarketDataPtr>>	m_IndexCalcuteDataCache;

	//指数计算工作线程
	cwMUTEX										m_UpdateIndexPriceDequeMutex;
	bool										m_bUpdateIndexPriceThreadRun = false;
	bool										m_bNeedWriteCacheToFile = false;		//默认不需要将数据写入Cache文件，只有行情存储程序才需要。
	void										_UpdateIndexPriceWorkingThread();
	std::thread									m_UpdateIndexPriceWorkingThread;
};

