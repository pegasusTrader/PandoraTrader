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
#include <thread>

#include "cwBasicSimulator.h"
#include "cwTickTradeManager.h"
#include "cwProductTradeTime.h"
#include "cwSettlement.h"

#include "tinyxml.h"

#include "cwBasicCout.h"

class cwPegasusSimulator :
	public cwBasicSimulator
{

public:
	cwPegasusSimulator();
	~cwPegasusSimulator();

	//初始化模拟器，读取配置和合约信息
	virtual void		InitialSimulator(const char * pConfigFilePath);
	//读取配置信息
	bool				ReadXmlConfigFile();

	//启动模拟器
	bool				SimulationStart();
	//启动行情服务
	virtual bool		StartMarketDataServer();

	//请求
	//Md
	virtual int			ReqUserMdLogin();
	
	//Trade
	virtual int			ReqQryInstrument();
	virtual int			ReqQryPosition();
	virtual int			ReqQryOrders();
	virtual int			ReqQryTrades();


	virtual int			ReqOrderInsert(cwOrderPtr pOrder);
	virtual int			CancelOrder(cwOrderPtr pOrder);

	cwOrderPtr			GetOrder(cwOrderPtr pOrder);
	cwTradePtr			GetTrade(cwOrderPtr pOrder, double dTradePrice, int iTradeCnt = 1);

	cwFtdcDateType								m_CurrentTradingDay;
	cwFtdcTimeType								m_CurrentSimulationTime;

	volatile bool								m_bSimulationFinished;
	cwSettlement								m_cwSettlement;

	//Custom Data interface return Data List Size
	int					AddCustomData(cwMarketDataPtr pData, bool bSimulationPartEnd = false, bool bSimulationFinish = false);

private:
	enum SIMTYPE:int
	{
		type_CSV_file = 0,
		type_BIN_file,
		type_CSV_List_file,
		type_BIN_List_file,
		type_DB,
		type_REAL_Time_Quote,
		type_Custom_Quote
	};

	SIMTYPE				m_SimType;
	int					m_iInterval;

	std::string			m_strFrontAddr;
	std::string			m_strInstrumentFile;

	std::thread			m_SimulatorProcessorThread;
	volatile bool		m_bMarketDataUpdateThreadRun;
	void				SimulatorProcessor();

	std::thread			m_MarketDataUpdateThread;
	void				CsvMarketDataUpdate();
	void				BinMarketDataUpdate();
	void				RealTimeMarketDataUpdate();
	void				CustomMarketDataUpdate();

	std::map<std::string, std::string>			m_MarketDataFileMap;

	std::unordered_map<std::string, cwInstrumentDataPtr>	m_InstrumentMap;

	int					m_iSysOrderID;
	int					m_iSysTradeID;

	cwTickTradeManager	m_cwTickManager;


	std::map<std::string, cwMarketDataPtr>								m_LastestMarketDataMap;

	std::map<std::string, cwOrderPtr>									m_TotalOrderMap;
	std::map<std::string, std::map<int64_t, std::deque<cwOrderPtr>>>	m_TotalLongOrderMap;
	std::map<std::string, std::map<int64_t, std::deque<cwOrderPtr>>>	m_TotalShortOrderMap;

	std::map<std::string, std::map<int64_t, std::deque<cwOrderPtr>>>	m_LongWaitOrderListMap;
	std::map<std::string, std::map<int64_t, std::deque<cwOrderPtr>>>	m_ShortWaitOrderListMap;

	enum UserActionType :int
	{
		UAT_IO = 0,
		UAT_CO
	};
	struct cwSimulationUserAction
	{
		UserActionType	Actiontype;
		cwOrderPtr		pOrder;
	};

	cwProductTradeTime										m_ProductTradeTime;

	std::deque<cwSimulationUserAction>						m_UndealOrderDeque;
	
	std::deque<cwTradePtr>									m_TradeDeque;

	cwBasicCout												m_cwShow;

	cwMUTEX													m_ProcessMutex;

	std::deque<cwMarketDataPtr>								m_MDCasheDeque;
	cwMUTEX													m_MDCasheMutex;
	volatile bool											m_bMDCasheMutexReady;
	volatile bool											m_bSimulationPartEnd;

	cwAccountPtr											m_pAccount;

	double													m_dDeposit;

	//Result 
	bool													m_bSaveAccountResult;
	int														m_iAccountResultInterval;
	std::map<std::string, double>							m_dTimeBalanceMap;

	std::map<std::string, bool>								m_bSaveInsResultMap;
	std::map<std::string, int>								m_iInsResultInterval;
	std::map<std::string, std::map<std::string, double>>	m_dInsTimeBalanceMap;

	//Custom Data
	struct CustomDataStruct
	{
		cwMarketDataPtr pData;
		bool			bSimulationPartEnd;
		bool			bSimulationFinish;
	};
	typedef	std::shared_ptr<CustomDataStruct>				CustomDataPtr;
	std::deque<CustomDataPtr>								m_CustomDataDeque;
	cwMUTEX													m_CustomDataMutex;
};

