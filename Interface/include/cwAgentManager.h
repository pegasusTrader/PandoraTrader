//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on May. 16th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "cwCommonUtility.h"
#include "cwBasicAgent.h"
#include "cwTradeCommonDefine.h"
#include "cwBasicKindleStrategy.h"

class cwAgentManager
{
public:
	friend class cwBasicKindleStrategy;
public:
	cwAgentManager();
	~cwAgentManager();

	virtual void			_PriceUpdate(cwMarketDataPtr pPriceData);
	virtual void			_OnRtnTrade(cwTradePtr pTrade);
	virtual void			_OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	virtual void			_OnOrderCanceled(cwOrderPtr pOrder);
	virtual void			_OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);


	//报单函数--限价单
	cwOrderPtr				InputLimitOrder(int agentid, const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//报单函数--FAK单（Filled And Kill 立即成交剩余自动撤销指令）
	cwOrderPtr				InputFAKOrder(int agentid, const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//报单函数--FOK单(FOK Filled Or Kill 立即全部成交否则自动撤销指令)
	cwOrderPtr				InputFOKOrder(int agentid, const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);

	//简化报单函数， volume正表示买，负表示卖，自动开平，有持仓就平仓，没有就开仓
	cwOrderPtr				EasyInputOrder(int agentid, const char * szInstrumentID, int volume, double price,
		cwBasicStrategy::cwOpenCloseMode openclosemode = cwBasicStrategy::cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);

	//撤单
	bool					CancelOrder(int agentid, cwOrderPtr pOrder);

	//获取最新的行情
	cwMarketDataPtr	GetLastestMarketData(std::string InstrumentID);

	//获取持仓和挂单列表
	bool GetPositionsAndActiveOrders(std::map<std::string, cwPositionPtr>& PositionMap,
		std::map<std::string, cwOrderPtr>& ActiveOrders);
	//获取指定合约持仓和挂单列表
	bool GetPositionsAndActiveOrders(std::string InstrumentID, cwPositionPtr& pPosition, std::map<std::string, cwOrderPtr>& ActiveOrders);
	//获取指定合约净持仓和挂单列表
	bool GetNetPositionAndActiveOrders(std::string InstrumentID, int & iPosition, std::map<std::string, cwOrderPtr> & ActiveOrders);

	//获取交易时间段，距开盘多少秒和距收盘多少秒
	//参数：合约名，行情时间（102835->10:28:35),交易阶段， 距该交易时段开盘多少秒，距收盘多少秒
	bool	  GetTradeTimeSpace(const char * szInstrumentID, const char * updatetime,
		cwProductTradeTime::cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);
	//获取合约最小变动，如果获取失败返回-1
	double    GetTickSize(const char * szInstrumentID);


	inline virtual bool		HasAgent(std::string instrumentid);

	//将Agent 指针注册过来，如果不用了调用UnRegisterAgent；
	//需要保证pAgent在运行期间有效，并自行管理Agent内存空间申请和释放。
	int						RegisterAgent(std::string instrumentid, cwBasicAgent * pAgent, bool bMonopoly = false);
	int						UnRegisterAgent(std::string instrumentid, int iAgentId);
	int						UnRegisterAgent(int iAgentId);

	struct cwAgentContainer
	{
		int					MonopolyAgentID;
		cwBasicAgent *		pMonopolyAgent;

		std::unordered_map<int, cwBasicAgent *>	pAgentMap;
	};
	typedef std::shared_ptr<cwAgentContainer> cwAgentContainerPtr;

	//
protected:
	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwAgentManager);

	cwBasicKindleStrategy *											m_pBasicStrategy;
	void					_SetBasicStrategy(cwBasicKindleStrategy * pBasicStrategy);

	std::unordered_map<int, cwBasicAgent *>							m_TotalAgentMap;			//key AgentID,
	std::unordered_map<std::string, cwAgentContainerPtr>			m_AgentContainerMap;		//key Instrument
	std::unordered_map<std::string, int>							m_OrderRefToAgentIDMap;		//key: Order Ref, value: AgentId

	volatile	int													m_iAgentID;
};

