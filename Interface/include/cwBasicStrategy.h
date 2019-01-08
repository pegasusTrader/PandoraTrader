#pragma once
#include <vector>
#include <set>
#include "cwProductTradeTime.h"
#include "cwTradeCommonDefine.h"
#include "cwStrategyLog.h"

enum cwOpenCloseMode:int
{
	CloseTodayThenYd = 0,//先平今，再平昨,可开，用于平今免的品种
	OpenOnly = 1,//只开
	CloseOnly = 2,//只平
	CloseYdThenOpen = 3,//先平昨，后开仓，不平今，用于平今很贵的品种，弊病是要等全部平完再开仓
	CloseYdOrOpen = 4,//优先平昨，可开仓，开仓后不再平仓，用于平今很贵的品种，又不耽误开仓，弊病是有一点昨仓可能没平
	CloseYdThenToday = 5//先平昨，再平今,可开，用于平昨便宜，平今和开仓差不多的品种
};

enum cwInsertOrderType:int
{
	cwInsertLimitOrder = 0,			//限价单
	cwInsertFAKOrder = 1,			//FAK 
	cwInsertFOKOrder = 2,			//FOK
	cwInsertMarketOrder				//市价单（暂不支持）
};

class cwBasicStrategy
{
public:
	cwBasicStrategy();
	~cwBasicStrategy();

	//表示系统是否初始化完成，可以正常进行报撤单操作
	bool	m_bStrategyReady;

	//表示策略名称
	virtual std::string  GetStrategyName() { return "BasicStrategy"; }

	///MarketData SPI
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData) = 0;
	
	///Trade SPI
	//成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade) = 0;
	//报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder) = 0;
	//撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) = 0;


	virtual void InitialStrategy(const char * pConfigFilePath);
	std::string			m_strConfigFileFullPath;

	///Action  Function
	//获取最新的行情
	cwMarketDataPtr	GetLastestMarketData(std::string InstrumentID);
	//获取账户信息
	cwAccountPtr GetAccount();
	//获取挂单列表，传入map用于返回信息，本地报单编号为Key
	bool GetActiveOrders(std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//获取挂单列表，传入map用于返回信息，本地报单编号为Key
	bool GetActiveOrders(std::string InstrumentID, std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//获取挂单列表，传入map用于返回信息，本地报单编号为Key
	int GetActiveOrdersLong(std::string InstrumentID);		///key OrderRef
	//获取挂单列表，传入map用于返回信息，本地报单编号为Key
	int GetActiveOrdersShort(std::string InstrumentID);		///key OrderRef
	//获取所有报单列表，传入map用于返回信息，交易所报单编号为Key
	bool GetAllOrders(std::map<std::string, cwOrderPtr>& Orders);				///Key OrderSysID
	//获取持仓列表，传入map用于返回信息，合约ID为Key
	bool GetPositions(std::map<std::string, cwPositionPtr>& PositionMap);		///Key InstrumentID
	//获取持仓和挂单列表
	bool GetPositionsAndActiveOrders(std::map<std::string, cwPositionPtr>& PositionMap,
		std::map<std::string, cwOrderPtr>& ActiveOrders);
	bool GetPositionsAndActiveOrders(std::string InstrumentID, cwPositionPtr& pPosition, std::map<std::string, cwOrderPtr>& ActiveOrders);
	//获取合约信息
	cwInstrumentDataPtr GetInstrumentData(std::string InstrumentID);
	//报单函数
	cwOrderPtr InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//简化报单函数， volume正表示买，负表示卖，自动开平，有持仓就平仓，没有就开仓
	cwOrderPtr EasyInputOrder(const char * szInstrumentID, int volume, double price,
		cwOpenCloseMode openclosemode = cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);
	//撤单函数
	bool CancelOrder(cwOrderPtr pOrder);

	//订阅合约
	void	   SubScribePrice(std::vector<std::string>& SubscribeInstrument);
	//取消订阅合约
	void	   UnSubScribePrice(std::vector<std::string>& UnSubscribeInstrument);

	//合约信息列表，需要最小变动，合约乘数等信息可以通过这个map获取，合约ID为Key
	std::map<std::string, cwInstrumentDataPtr> m_InstrumentMap;
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
	
	int		  GetInstrumentCancelCount(std::string InstrumentID);
	///如果重载该函数，请确保最后基类的函数能够被调用到！
	virtual void	   SetStrategyReady();
	///系统自用接口信息，勿动
	void			   SetMdSpi(cwMDAPIType apiType, void * pSpi);
	void			   SetTradeSpi(cwTradeAPIType apiType, void *pSpi);
private:
	///系统自用接口信息，勿动
	friend class		cwFtdTradeSpi;
	void *				m_pTradeSpi;
	cwTradeAPIType		m_TradeApiType;

	void *				m_pMdSpi;
	cwMDAPIType			m_MdApiType;


	std::set<std::string>	m_SubscribeInstrumentSet;
	cwProductTradeTime		m_ProductTradeTime;

	cwStrategyLog			m_BasicStrategyLog;
};
