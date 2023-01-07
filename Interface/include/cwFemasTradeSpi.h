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
#include <string>
#include <map>
#include <thread>

#include "cwCommonUtility.h"
#include "cwBasicStrategy.h"
#include "cwBasicTradeSpi.h"
#include "cwBasicCout.h"

#ifdef _WIN64
//define something for Windows (64-bit)
#include "FemasTradeApi64\USTPFtdcTraderApi.h"
#elif _WIN32
//define something for Windows (32-bit)
#include "FemasTradeApi32\USTPFtdcTraderApi.h"
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
// define something for simulator   
#elif TARGET_OS_IPHONE
// define something for iphone  
#else
#define TARGET_OS_OSX 1
// define something for OSX
#endif
#elif __linux__ or _linux
// linux
#include "FemasTradeApiLinux/USTPFtdcTraderApi.h"
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#define CW_USING_AUTHCODE

#ifdef _MSC_VER
#ifdef CW_USING_AUTHCODE
#pragma comment(lib, "USTPtraderapiAF.lib")
#else
#pragma comment(lib, "USTPtraderapiAF.lib")
#endif // CW_USING_AUTHCODE

#endif // _MSC_VER



class cwFemasTradeSpi 
	: public CUstpFtdcTraderSpi
	, public cwBasicTradeSpi
{
public:
	friend class cwBasicStrategy;

	enum cwReqType
	{
		cwReqAuthenticate = 0
		, cwReqUserLogin
		, cwReqQryInvestor
		, cwReqQryInstrument
		, cwReqQryTradingAccount
		, cwRspQryInvestorPosition
		, cwReqQryOrder
		, cwReqQryTrade
	};

public:
	cwFemasTradeSpi();
	~cwFemasTradeSpi();

public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();
	virtual void OnQryFrontConnected() {};
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnQryFrontDisconnected(int nReason) {};

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) {};

	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo) {};

	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo) {};


	///错误应答
	virtual void OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///风控前置系统用户登录应答
	virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户退出应答
	virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入应答
	virtual void OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作应答
	virtual void OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报价录入应答
	virtual void OnRspQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作应答
	virtual void OnRspQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价请求应答
	virtual void OnRspForQuote(CUstpFtdcReqForQuoteField *pReqForQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///客户申请组合应答
	virtual void OnRspMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户请求出入金应答
	virtual void OnRspUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户主次席出入金应答
	virtual void OnRspTransferMoney(CUstpFtdcstpTransferMoneyField *pstpTransferMoney, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo);

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo);

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus);

	///账户出入金回报
	virtual void OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes) {};

	///报价回报
	virtual void OnRtnQuote(CUstpFtdcRtnQuoteField *pRtnQuote) {};

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo) {};

	///报价撤单错误回报
	virtual void OnErrRtnQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo) {};

	///询价回报
	virtual void OnRtnForQuote(CUstpFtdcReqForQuoteField *pReqForQuote) {};

	///增加组合规则通知
	virtual void OnRtnMarginCombinationLeg(CUstpFtdcMarginCombinationLegField *pMarginCombinationLeg) {};

	///客户申请组合确认
	virtual void OnRtnMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction) {};

	///用户请求出入金
	virtual void OnRtnUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit) {};

	///查询前置系统用户登录应答
	virtual void OnRspQueryUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单查询应答
	virtual void OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///成交单查询应答
	virtual void OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///可用投资者账户查询应答
	virtual void OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pRspUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///交易编码查询应答
	virtual void OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pRspTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者资金账户查询应答
	virtual void OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///合约查询应答
	virtual void OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///交易所查询应答
	virtual void OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者持仓查询应答
	virtual void OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///合规参数查询应答
	virtual void OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者手续费率查询应答
	virtual void OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者保证金率查询应答
	virtual void OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易编码组合持仓查询应答
	virtual void OnRspQryInvestorCombPosition(CUstpFtdcRspInvestorCombPositionField *pRspInvestorCombPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易编码单腿持仓查询应答
	virtual void OnRspQryInvestorLegPosition(CUstpFtdcRspInvestorLegPositionField *pRspInvestorLegPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约组信息查询应答
	virtual void OnRspQryInstrumentGroup(CUstpFtdcRspInstrumentGroupField *pRspInstrumentGroup, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///组合保证金类型查询应答
	virtual void OnRspQryClientMarginCombType(CUstpFtdcRspClientMarginCombTypeField *pRspClientMarginCombType, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///行权录入应答
	virtual void OnRspExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///行权操作应答
	virtual void OnRspExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///行权通知
	virtual void OnRtnExecOrder(CUstpFtdcExecOrderField *pExecOrder) {};

	///行权录入错误回报
	virtual void OnErrRtnExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo) {};

	///行权操作错误回报
	virtual void OnErrRtnExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo) {};

	///主次席资金同步通知
	virtual void OnRtnTransferMoney(CUstpFtdcSyncMoneyTransferField *pSyncMoneyTransfer) {};

	///系统时间查询应答
	virtual void OnRspQrySystemTime(CUstpFtdcRspQrySystemTimeField *pRspQrySystemTime, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
#ifdef CW_USING_AUTHCODE
	///穿透监管客户认证应答
	virtual void OnRspDSUserCertification(CUstpFtdcDSUserCertRspDataField *pDSUserCertRspData, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
#endif

public:
	//User Setting Method
	inline CUstpFtdcTraderApi * GetUserThostFtdcMdApi()
	{
		return m_pTraderUserApi;
	}

	virtual void RegisterBasicStrategy(cwBasicStrategy * pBasicStrategy, void * pSpi = NULL);

	void Connect(const char * pszFrontAddress, const char * pszLocalAddr = NULL);
	void DisConnect();

	void WaitForFinish();

	void SetUserLoginField(const char * szBrokerID, const char * szUserID, const char * szPassword, const char * szUserProductInfo = INTERFACENAME);
	void SetUserLoginField(CUstpFtdcReqUserLoginField& reqUserLoginField);
	void SetAuthenticateInfo(const char * szAppID, const char * szAuthCode);

	//User Trader Method
	//行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);


	///报单回报
	virtual void OnRtnOrder(CUstpFtdcOrderField *pOrder);

	///成交回报
	virtual void OnRtnTrade(CUstpFtdcTradeField *pTrade);

	//virtual void Input Order
	virtual	cwOrderPtr InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
	virtual cwOrderPtr InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
	virtual cwOrderPtr InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction,
		cwOpenClose openclose, int volume, double price);
#if 0
	virtual void InputOrder(cwOrderPtr pOrder);
#endif

	virtual void CancelOrder(const char * szLocalOrderID);
	virtual void CancelOrder(cwOrderPtr pOrder);

	//查询保证金率
	virtual double		GetMarginRate(std::string InstrumentID);

protected:
	bool		MyReqFunction(cwReqType nType, void * pData);

	bool		AddMyReqToList(cwReqType nType);

#ifdef _MSC_VER
#pragma region CTPDefine2CWDefine
#endif // _MSC_VER
	cwFtdcDirectionType			GetFemas2CwDirectionType(TUstpFtdcDirectionType direction);
	cwFtdcHedgeFlagType			GetFemas2CwHedgeFlagType(TUstpFtdcHedgeFlagType hedge);
	cwFtdcOffsetFlagType		GetFemas2CwOffsetFlagType(TUstpFtdcOffsetFlagType Offset);
	cwFtdcOrderPriceType		GetFemas2CwOrderPriceType(TUstpFtdcOrderPriceTypeType orderpricetype);
	cwFtdcTimeConditionType		GetFemas2CwTimeConditionType(TUstpFtdcTimeConditionType timeconditiontype);
	cwFtdcVolumeConditionType	GetFemas2CwVolumeConditionType(TUstpFtdcVolumeConditionType volumeconditiontype);
	cwFtdcForceCloseReasonType	GetFemas2CwForceCloseReasonType(TUstpFtdcForceCloseReasonType forceclosereasontype);
	cwFtdcOrderSourceType		GetFemas2CwOrderSourceType(TUstpFtdcOrderSourceType ordersource);
	cwFtdcOrderStatusType		GetFemas2CwOrderStatusType(TUstpFtdcOrderStatusType orderstatustype);
	cwFtdcOrderTypeType			GetFemas2CwOrderTypetype(TUstpFtdcOrderTypeType ordertype);
	cwFtdcInstrumentStatusType	GetFemas2CwInstrumentStatusType(TUstpFtdcInstrumentStatusType intrumentstatustype);

	TUstpFtdcDirectionType		GetCw2FemasDirectionType(cwFtdcDirectionType direction);

	cwOrderPtr					GetcwOrderPtr(CUstpFtdcOrderField * pOrder);
	cwOrderPtr					GetcwOrderPtr(CUstpFtdcInputOrderField * pInputOrder);
	cwTradePtr					GetcwTradePtr(CUstpFtdcTradeField * pTrade);
#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

private:
	CUstpFtdcTraderApi *		m_pTraderUserApi;

	int							m_iRequestId;

	void						LoopReqQryThread();
protected:
	std::thread					m_MyReqQryThread;
	volatile bool				m_bReqQryThreadRun;
	std::deque<cwReqType>		m_PrioritizedReqList;
	cwMUTEX						m_PrioritizedReqListMutex;

	//Investor Data
	CUstpFtdcReqUserLoginField  m_ReqUserLoginField;
	std::string					m_strInvestorID;

	//TThostFtdcSessionIDType		m_SessionID;
	//TThostFtdcFrontIDType		m_FrontID;
#ifdef CW_USING_AUTHCODE
		///用户AppID
	TUstpFtdcDSAppIDType				m_AppID;
	///用户授权码
	TUstpFtdcDSAuthorizationCodeType	m_AuthCode;
#endif

	char						m_szTradeFrount[1024];

#ifdef NoCancelTooMuchPerTick
	uint32_t					m_iLatestUpdateTime;
#endif // NoCancelTooMuchPerTick

	int m_iTradeAPIIndex;

#ifdef CWCOUTINFO
	cwBasicCout					m_cwShow;
#endif

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwFemasTradeSpi);
};

