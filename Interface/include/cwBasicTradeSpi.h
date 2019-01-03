#pragma once
#include "cwTradeCommonDefine.h"
#include "cwMutex.h"
#include "cwBasicStrategy.h"
#include "cwOrderReference.h"

#define CWRISK
#define TRADELOG
#define TRADELOG
#define UPDATE_ORDERRANKED

#ifdef UPDATE_ORDERRANKED
#define NO_TRADEINFO_LOG
#include "cwTickTradeManager.h"
#endif // UPDATE_ORDERRANKED

#ifdef TRADELOG
#include "cwTradeLog.h"
#endif

class cwBasicTradeSpi
{
public:
	friend class cwBasicStrategy;

	enum TradeServerStatus
	{
		Status_UnConnected = 0
		, Status_Connected
		, Status_Logined
		, Status_Initial
		, Status_Normal
	};

public:
	cwBasicTradeSpi(cwTradeAPIType apiType);
	~cwBasicTradeSpi();

	inline TradeServerStatus GetCurrentStatus()
	{
		return m_CurrentStatus;
	}

	virtual void RegisterBasicStrategy(cwBasicStrategy * pBasicStrategy, void * pSpi = NULL) = 0;

	inline cwAccountPtr GetAccount()
	{
		return m_pAccount;
	}

	inline std::map<std::string, cwPositionPtr> GetPosition(bool ClearChangedFlag = true)
	{
		if (ClearChangedFlag)
		{
			m_bHasPositionChanged = false;
		}
		cwAUTOMUTEX mt(m_TradeSpiMutex, true);
		return m_PositionMap;
	}
	inline std::map<std::string, cwOrderPtr> GetOrders(bool ClearChangedFlag = true)
	{
		if (ClearChangedFlag)
		{
			m_bHasOrdersChanged = false;
		}
		cwAUTOMUTEX mt(m_TradeSpiMutex, true);
		return m_OrdersMap;
	}
	inline std::map<std::string, cwOrderPtr> GetActiveOrders(bool ClearChangedFlag = true)
	{
		if (ClearChangedFlag)
		{
			m_bHasActiveOrdersChanged = false;
		}
		cwAUTOMUTEX mt(m_TradeSpiMutex, true);
		return m_ActiveOrdersMap;
	}
	inline std::map<std::string, cwTradePtr> GetTrades(bool ClearChangedFlag = true)
	{
		if (ClearChangedFlag)
		{
			m_bHasTradesChanged = false;
		}
		return m_TradeMap;
	}
	bool		IsWaitOrder(cwOrderPtr pOrder);
	bool		GetPosition(std::string InstrumentID, cwFtdcDirectionType direction,
		int& TotalPositon, int& TodayPosition);
	bool		GetPositionAndActiveOrders(std::string InstrumentID, cwFtdcDirectionType direction,
		int& TotalPositon, int& TodayPosition, int& FrozenTdPosition, int& FrozenYdPosition);

	//CWRISK
#ifdef CWRISK
	int			GetOrderCancelCount(std::string InstrumentID);
#endif

	//User Trader Method
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData) = 0;
	virtual	cwOrderPtr InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price) = 0;
	virtual cwOrderPtr InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price) = 0;
	virtual cwOrderPtr InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price) = 0;
	virtual void CancelOrder(char * szLocalOrderID) = 0;
	virtual void CancelOrder(cwOrderPtr pOrder) = 0;

	void	SetDisConnectExit(bool bDisConnectExit = true) { m_bDisConnectExit = bDisConnectExit; }

	std::map<std::string, cwInstrumentDataPtr> m_InstrumentMap;

	const cwTradeAPIType		m_cwTradeAPIType;
protected:
	TradeServerStatus			m_CurrentStatus;

	cwBasicStrategy	*			m_pBasicStrategy;

	//Trade info
	cwOrderReference			m_cwOrderRef;
	cwAccountPtr				m_pAccount;

	cwMUTEX						m_TradeSpiMutex;

	bool						m_bIsQryingPosition;
	std::map<std::string, cwPositionPtr> m_PositionMap;
	std::map<std::string, cwPositionPtr> m_PositionTempMap;

	//
	bool						m_bHasGetPosition;
	bool						m_bHasGetOrders;
	bool						m_bHasGetTrades;
	bool						m_bOrderRankedUpdate;

	std::map<std::string, cwOrderPtr>	m_OrdersMap;		//Key OrderSysID
	std::map<std::string, cwOrderPtr>	m_ActiveOrdersMap;	//Key OrderRef

	std::map<std::string, cwTradePtr>	m_TradeMap;			//key TradeID

	std::map<std::string, cwFtdcInstrumentStatusType>		m_ExchangeStatus;

	bool						m_bHasPositionChanged;

	bool						m_bHasOrdersChanged;
	bool						m_bHasActiveOrdersChanged;

	bool						m_bHasTradesChanged;


	//UPDATE_ORDERRANKED
#ifdef  UPDATE_ORDERRANKED
	cwTickTradeManager			m_TickTradeManger;
#endif //  UPDATE_ORDERRANKED

#ifdef TRADELOG
	cwTradeLog					m_TradeLog;
#endif // TRADELOG

	//CWRISK
#ifdef CWRISK
	const int					m_iMaxCancelLimitNum;
	std::map<std::string, int>	m_iCancelLimitMap;
#endif // CWRISK

	bool						m_bDisConnectExit;
};

