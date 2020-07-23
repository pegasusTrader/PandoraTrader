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
#include <stdint.h>
#include <memory>
#include <string>
#include <deque>

#include "cwInterfaceDefine.h"

#define INTERFACENAME	" "
//#define INTERFACENAME	"Pegasus"
#ifndef INTERFACENAME
#define INTERFACENAME ""
#endif

#ifndef CW_SLEEP
#define CW_SLEEP
#ifdef _WIN64
//define something for Windows (64-bit)
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#define cwSleep(milliseconds) Sleep(milliseconds)
#elif _WIN32
//define something for Windows (32-bit)
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#define cwSleep(milliseconds) Sleep(milliseconds)
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
#include "unistd.h"
#define cwSleep(milliseconds) usleep(milliseconds * 1000)
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif
#endif

#ifndef MAX_PATH
#define MAX_PATH          260
#endif // !MAX_PATH

#define		CWCOUTINFO

#define		InstrumentIDLength	32
#define		MARKET_PRICE_DEPTH	5

enum CW_TE_RESUME_TYPE
{
	CW_TERT_RESTART = 0,
	CW_TERT_RESUME,
	CW_TERT_QUICK
};

///--------------------Market Data---------------------------------------------

#ifdef _MSC_VER
#pragma region CW_Data_Type_Define
#endif // _MSC_VER
///cwFtdcDateType是一个日期类型
typedef char		cwFtdcDateType[9];
///cwFtdcInstrumentIDType是一个合约代码类型
typedef char		cwFtdcInstrumentIDType[InstrumentIDLength];
///cwFtdcProductIDType是一个合约代码类型
typedef char		cwFtdcProductIDType[31];
///cwFtdcExchangeIDType是一个交易所代码类型
typedef char		cwFtdcExchangeIDType[11];
///cwFtdcTimeType是一个时间类型
typedef char		cwFtdcTimeType[9];
///cwFtdcMillisecType是一个时间（毫秒）类型
typedef uint32_t	cwFtdcMillisecType;
///cwFtdcPriceType是一个价格类型
typedef double		cwFtdcPriceType;
///cwFtdcVolumeType是一个数量类型
typedef int32_t		cwFtdcVolumeType;
///cwFtdcLargeVolumeType是一个大额数量类型
typedef int64_t		cwFtdcLargeVolumeType;
///cwFtdcAccountIDType是一个投资者帐号类型
typedef char		cwFtdcAccountIDType[16];
///cwFtdcMoneyType是一个资金类型
typedef double		cwFtdcMoneyType;
///cwFtdcInstrumentNameType是一个合约名称类型
typedef char		cwFtdcInstrumentNameType[21];
///cwFtdcYearType是一个年份类型
typedef uint32_t	cwFtdcYearType;
///cwFtdcMonthType是一个月份类型
typedef uint32_t	cwFtdcMonthType;
///cwFtdcVolumeMultipleType是一个合约数量乘数类型
typedef uint32_t	cwFtdcVolumeMultipleType;
///cwFtdcBoolType是一个布尔型类型
typedef uint32_t	cwFtdcBoolType;
///cwFtdcUnderlyingMultipleType是一个基础商品乘数类型
typedef double		cwFtdcUnderlyingMultipleType;
///cwFtdcRatioType是一个比率类型
typedef double		cwFtdcRatioType;
///cwFtdcBrokerIDType是一个经纪公司代码类型
typedef char		cwFtdcBrokerIDType[11];
///cwFtdcInvestorIDType是一个投资者代码类型
typedef char		cwFtdcInvestorIDType[19];
///cwFtdcOrderRefType是一个报单引用类型
typedef char		cwFtdcOrderRefType[23];
///cwFtdcUserIDType是一个用户代码类型
typedef char		cwFtdcUserIDType[16];
///cwFtdcPasswordType是一个密码类型
typedef char		cwFtdcPasswordType[41];
///cwFtdcCombOffsetFlagType是一个组合开平标志类型
typedef char		cwFtdcCombOffsetFlagType[5];
///cwFtdcCombHedgeFlagType是一个组合投机套保标志类型
typedef char		cwFtdcCombHedgeFlagType[5];
///cwFtdcOrderLocalIDType是一个本地报单编号类型
typedef char		cwFtdcOrderLocalIDType[33];
///cwFtdcClientIDType是一个交易编码类型
typedef char		cwFtdcClientIDType[19];
///cwFtdcSettlementIDType是一个结算编号类型
typedef uint32_t	cwFtdcSettlementIDType;
///cwFtdcOrderSysIDType是一个报单编号类型
typedef char		cwFtdcOrderSysIDType[31];
///cwFtdcFrontIDType是一个前置编号类型
typedef uint32_t	cwFtdcFrontIDType;
///cwFtdcSessionIDType是一个会话编号类型
typedef uint32_t	cwFtdcSessionIDType;
///cwFtdcProductInfoType是一个产品信息类型
typedef char		cwFtdcProductInfoType[11];
///cwFtdcAppIDType是一个登录前认证appid类型
typedef char		cwFtdcAppIDType[33];
///cwFtdcErrorMsgType是一个错误信息类型
typedef char		cwFtdcErrorMsgType[87];
///cwFtdcCurrencyIDType是一个币种代码类型
typedef char		cwFtdcCurrencyIDType[4];
///cwFtdcIPAddressType是一个IP地址类型
typedef char		cwFtdcIPAddressType[16];
///cwFtdcMacAddressType是一个Mac地址类型
typedef char		cwFtdcMacAddressType[21];
///cwFtdcTradeIDType是一个成交编号类型
typedef char		cwFtdcTradeIDType[21];
///cwFtdcTraderIDType是一个交易所交易员代码类型
typedef char		cwFtdcTraderIDType[21];
///cwFtdcErrorIDType是一个错误代码类型
typedef int			cwFtdcErrorIDType;


#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

#ifdef _MSC_VER
#pragma region CW_Data_Type_Enum_Define
#endif // _MSC_VER
/////////////////////////////////////////////////////////////////////////
///cwFtdcProductClassType是一个产品类型类型
/////////////////////////////////////////////////////////////////////////
///期货
#define CW_FTDC_PC_Futures '1'
///期货期权
#define CW_FTDC_PC_Options '2'
///组合
#define CW_FTDC_PC_Combination '3'
///即期
#define CW_FTDC_PC_Spot '4'
///期转现
#define CWT_FTDC_PC_EFP '5'
///现货期权
#define CW_FTDC_PC_SpotOption '6'
///证券
#define CW_FTDC_PC_Stocks '7'
///股票期权
#define CW_FTDC_PC_StockOptions '8'
///金交所现货
#define CW_FTDC_PC_SGE_SPOT '9'
///金交所递延
#define CW_FTDC_PC_SGE_DEFER 'a'
///金交所远期
#define CW_FTDC_PC_SGE_FOWARD 'b'

typedef char		cwFtdcProductClassType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPositionTypeType是一个持仓类型类型
/////////////////////////////////////////////////////////////////////////
///净持仓
#define CW_FTDC_PT_Net '1'
///综合持仓
#define CW_FTDC_PT_Gross '2'

typedef char cwFtdcPositionTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcMaxMarginSideAlgorithmType是一个大额单边保证金算法类型
/////////////////////////////////////////////////////////////////////////
///不使用大额单边保证金算法
#define CW_FTDC_MMSA_NO '0'
///使用大额单边保证金算法
#define CW_FTDC_MMSA_YES '1'

typedef char cwFtdcMaxMarginSideAlgorithmType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOptionsTypeType是一个期权类型类型
/////////////////////////////////////////////////////////////////////////
///看涨
#define CW_FTDC_CP_CallOptions '1'
///看跌
#define CW_FTDC_CP_PutOptions '2'

typedef char cwFtdcOptionsTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcCurrencyType是一个币种类型
/////////////////////////////////////////////////////////////////////////
///人民币
#define CW_FTDC_C_RMB '1'
///美元
#define CW_FTDC_C_UDOLLAR '2'

typedef char cwFtdcCurrencyType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcDirectionType是一个买卖方向类型
/////////////////////////////////////////////////////////////////////////
//买
#define CW_FTDC_D_Buy '0'
//卖
#define CW_FTDC_D_Sell '1'

typedef char cwFtdcDirectionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcHedgeFlagType是一个投机套保标志类型
/////////////////////////////////////////////////////////////////////////
//投机
#define CW_FTDC_HF_Speculation '1'
//套利
#define CW_FTDC_HF_Arbitrage '2'
//套保
#define CW_FTDC_HF_Hedge '3'
//做市商
#define CW_FTDC_HF_MarketMaker '5'

typedef char cwFtdcHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPositionDateType是一个持仓日期类型
/////////////////////////////////////////////////////////////////////////
///更新时不区分今日和昨日持仓, QDP持仓
#define CW_FTDC_PSD_UNKNOW '0'
///今日持仓
#define CW_FTDC_PSD_Today '1'
///历史持仓
#define CW_FTDC_PSD_History '2'

typedef char cwFtdcPositionDateType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderPriceTypeType是一个报单价格条件类型
/////////////////////////////////////////////////////////////////////////
///任意价
#define CW_FTDC_OPT_AnyPrice '1'
///限价
#define CW_FTDC_OPT_LimitPrice '2'
///最优价
#define CW_FTDC_OPT_BestPrice '3'
///最新价
#define CW_FTDC_OPT_LastPrice '4'
///最新价浮动上浮1个ticks
#define CW_FTDC_OPT_LastPricePlusOneTicks '5'
///最新价浮动上浮2个ticks
#define CW_FTDC_OPT_LastPricePlusTwoTicks '6'
///最新价浮动上浮3个ticks
#define CW_FTDC_OPT_LastPricePlusThreeTicks '7'
///卖一价
#define CW_FTDC_OPT_AskPrice1 '8'
///卖一价浮动上浮1个ticks
#define CW_FTDC_OPT_AskPrice1PlusOneTicks '9'
///卖一价浮动上浮2个ticks
#define CW_FTDC_OPT_AskPrice1PlusTwoTicks 'A'
///卖一价浮动上浮3个ticks
#define CW_FTDC_OPT_AskPrice1PlusThreeTicks 'B'
///买一价
#define CW_FTDC_OPT_BidPrice1 'C'
///买一价浮动上浮1个ticks
#define CW_FTDC_OPT_BidPrice1PlusOneTicks 'D'
///买一价浮动上浮2个ticks
#define CW_FTDC_OPT_BidPrice1PlusTwoTicks 'E'
///买一价浮动上浮3个ticks
#define CW_FTDC_OPT_BidPrice1PlusThreeTicks 'F'
///五档价
#define CW_FTDC_OPT_FiveLevelPrice 'G'

typedef char cwFtdcOrderPriceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTimeConditionType是一个有效期类型类型
/////////////////////////////////////////////////////////////////////////
//立即完成，否则撤销
#define CW_FTDC_TC_IOC '1'
//本节有效
#define CW_FTDC_TC_GFS '2'
//当日有效
#define CW_FTDC_TC_GFD '3'
//指定日期前有效
#define CW_FTDC_TC_GTD '4'
//撤销前有效
#define CW_FTDC_TC_GTC '5'
//集合竞价有效
#define CW_FTDC_TC_GFA '6'

typedef char cwFtdcTimeConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcVolumeConditionType是一个成交量类型类型
/////////////////////////////////////////////////////////////////////////
///任何数量
#define CW_FTDC_VC_AV '1'
///最小数量
#define CW_FTDC_VC_MV '2'
///全部数量
#define CW_FTDC_VC_CV '3'

typedef char cwFtdcVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcContingentConditionType是一个触发条件类型
/////////////////////////////////////////////////////////////////////////
///立即
#define CW_FTDC_CC_Immediately '1'
///止损
#define CW_FTDC_CC_Touch '2'
///止赢
#define CW_FTDC_CC_TouchProfit '3'
///预埋单
#define CW_FTDC_CC_ParkedOrder '4'
///最新价大于条件价
#define CW_FTDC_CC_LastPriceGreaterThanStopPrice '5'
///最新价大于等于条件价
#define CW_FTDC_CC_LastPriceGreaterEqualStopPrice '6'
///最新价小于条件价
#define CW_FTDC_CC_LastPriceLesserThanStopPrice '7'
///最新价小于等于条件价
#define CW_FTDC_CC_LastPriceLesserEqualStopPrice '8'
///卖一价大于条件价
#define CW_FTDC_CC_AskPriceGreaterThanStopPrice '9'
///卖一价大于等于条件价
#define CW_FTDC_CC_AskPriceGreaterEqualStopPrice 'A'
///卖一价小于条件价
#define CW_FTDC_CC_AskPriceLesserThanStopPrice 'B'
///卖一价小于等于条件价
#define CW_FTDC_CC_AskPriceLesserEqualStopPrice 'C'
///买一价大于条件价
#define CW_FTDC_CC_BidPriceGreaterThanStopPrice 'D'
///买一价大于等于条件价
#define CW_FTDC_CC_BidPriceGreaterEqualStopPrice 'E'
///买一价小于条件价
#define CW_FTDC_CC_BidPriceLesserThanStopPrice 'F'
///买一价小于等于条件价
#define CW_FTDC_CC_BidPriceLesserEqualStopPrice 'H'

typedef char cwFtdcContingentConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcForceCloseReasonType是一个强平原因类型
/////////////////////////////////////////////////////////////////////////
///非强平
#define CW_FTDC_FCC_NotForceClose '0'
///资金不足
#define CW_FTDC_FCC_LackDeposit '1'
///客户超仓
#define CW_FTDC_FCC_ClientOverPositionLimit '2'
///会员超仓
#define CW_FTDC_FCC_MemberOverPositionLimit '3'
///持仓非整数倍
#define CW_FTDC_FCC_NotMultiple '4'
///违规
#define CW_FTDC_FCC_Violation '5'
///其它
#define CW_FTDC_FCC_Other '6'
///自然人临近交割
#define CW_FTDC_FCC_PersonDeliv '7'

typedef char cwFtdcForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderSubmitStatusType是一个报单提交状态类型
/////////////////////////////////////////////////////////////////////////
///已经提交
#define CW_FTDC_OSS_InsertSubmitted '0'
///撤单已经提交
#define CW_FTDC_OSS_CancelSubmitted '1'
///修改已经提交
#define CW_FTDC_OSS_ModifySubmitted '2'
///已经接受
#define CW_FTDC_OSS_Accepted '3'
///报单已经被拒绝
#define CW_FTDC_OSS_InsertRejected '4'
///撤单已经被拒绝
#define CW_FTDC_OSS_CancelRejected '5'
///改单已经被拒绝
#define CW_FTDC_OSS_ModifyRejected '6'

typedef char cwFtdcOrderSubmitStatusType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderSourceType是一个报单来源类型
/////////////////////////////////////////////////////////////////////////
///来自参与者
#define CW_FTDC_OSRC_Participant '0'
///来自管理员
#define CW_FTDC_OSRC_Administrator '1'

typedef char cwFtdcOrderSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderStatusType是一个报单状态类型
/////////////////////////////////////////////////////////////////////////
//全部成交
#define CW_FTDC_OST_AllTraded '0'
//部分成交还在队列中
#define CW_FTDC_OST_PartTradedQueueing '1'
//部分成交不在队列中
#define CW_FTDC_OST_PartTradedNotQueueing '2'
//未成交还在队列中
#define CW_FTDC_OST_NoTradeQueueing '3'
//未成交不在队列中
#define CW_FTDC_OST_NoTradeNotQueueing '4'
//撤单
#define CW_FTDC_OST_Canceled '5'
//订单已报入交易所未应答
#define CW_FTDC_OST_AcceptedNoReply '6'
//未知
#define CW_FTDC_OST_Unknown 'a'
//尚未触发
#define CW_FTDC_OST_NotTouched 'b'
//已触发
#define CW_FTDC_OST_Touched 'c'
//Default
#define CW_FTDC_OST_cwDefault ' '

typedef char cwFtdcOrderStatusType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderTypeType是一个报单类型类型
/////////////////////////////////////////////////////////////////////////
///正常
#define CW_FTDC_ORDT_Normal '0'
///报价衍生
#define CW_FTDC_ORDT_DeriveFromQuote '1'
///组合衍生
#define CW_FTDC_ORDT_DeriveFromCombination '2'
///组合报单
#define CW_FTDC_ORDT_Combination '3'
///条件单
#define CW_FTDC_ORDT_ConditionalOrder '4'
///互换单
#define CW_FTDC_ORDT_Swap '5'

typedef char cwFtdcOrderTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOffsetFlagType是一个开平标志类型
/////////////////////////////////////////////////////////////////////////
///开仓
#define CW_FTDC_OF_Open '0'
///平仓
#define CW_FTDC_OF_Close '1'
///强平
#define CW_FTDC_OF_ForceClose '2'
///平今
#define CW_FTDC_OF_CloseToday '3'
///平昨
#define CW_FTDC_OF_CloseYesterday '4'
///强减
#define CW_FTDC_OF_ForceOff '5'
///本地强平
#define CW_FTDC_OF_LocalForceClose '6'

typedef char cwFtdcOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTradeTypeType是一个成交类型类型
/////////////////////////////////////////////////////////////////////////
///组合持仓拆分为单一持仓,初始化不应包含该类型的持仓
#define CW_FTDC_TRDT_SplitCombination '#'
///普通成交
#define CW_FTDC_TRDT_Common '0'
///期权执行
#define CW_FTDC_TRDT_OptionsExecution '1'
///OTC成交
#define CW_FTDC_TRDT_OTC '2'
///期转现衍生成交
#define CW_FTDC_TRDT_EFPDerived '3'
///组合衍生成交
#define CW_FTDC_TRDT_CombinationDerived '4'

typedef char cwFtdcTradeTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPriceSourceType是一个成交价来源类型
/////////////////////////////////////////////////////////////////////////
///前成交价
#define CW_FTDC_PSRC_LastPrice '0'
///买委托价
#define CW_FTDC_PSRC_Buy '1'
///卖委托价
#define CW_FTDC_PSRC_Sell '2'

typedef char cwFtdcPriceSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTradeSourceType是一个成交来源类型
/////////////////////////////////////////////////////////////////////////
///来自交易所普通回报
#define CW_FTDC_TSRC_NORMAL '0'
///来自查询
#define CW_FTDC_TSRC_QUERY '1'

typedef char cwFtdcTradeSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcInstrumentStatusType是一个合约交易状态类型
/////////////////////////////////////////////////////////////////////////
///开盘前
#define CW_FTDC_IS_BeforeTrading '0'
///非交易
#define CW_FTDC_IS_NoTrading '1'
///连续交易
#define CW_FTDC_IS_Continous '2'
///集合竞价报单
#define CW_FTDC_IS_AuctionOrdering '3'
///集合竞价价格平衡
#define CW_FTDC_IS_AuctionBalance '4'
///集合竞价撮合
#define CW_FTDC_IS_AuctionMatch '5'
///收盘
#define CW_FTDC_IS_Closed '6'
///金交所交割申报
#define CW_FTDC_IS_SGE_Dery_App '7'
///金交所交割申报结束
#define CW_FTDC_IS_SGE_Dery_Match '8'
///金交所中立仓申报
#define CW_FTDC_IS_SGE_Mid_App '9'
///金交所交割申报撮合
#define CW_FTDC_IS_SGE_Mid_Match 'a'
///大商所自动转换报警
#define CW_FTDC_IS_DCE_MarketStatusAlarm 'b'

typedef char cwFtdcInstrumentStatusType;
const char * g_cwGetInstrumentStatus(cwFtdcInstrumentStatusType insstatustype);

enum cwInsertOrderType :int
{
	cwInsertLimitOrder = 0,			//限价单
	cwInsertFAKOrder = 1,			//FAK Filled And Kill 立即成交剩余自动撤销指令
	cwInsertFOKOrder = 2,			//FOK Filled Or Kill 立即全部成交否则自动撤销指令
	cwInsertMarketOrder = 3,		//市价单（暂不支持）
	cwInsertOtherTypeOrder
};

const char * GetInsertOrderTypeString(cwInsertOrderType ordertype);

#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

/// 一档行情结构体
struct OneLevelQuote
{
	cwFtdcPriceType		Price;							// 价格
	cwFtdcVolumeType	Volume;							// 数量
};

//是否使用内存池
#define USING_CW_MEMORY_POOL

///深度行情
struct cwFtdcDepthMarketDataField
{
	///交易所代码
	cwFtdcExchangeIDType	ExchangeID;
	///交易日
	cwFtdcDateType			TradingDay;
	///业务日期
	cwFtdcDateType			ActionDay;
	///最后修改时间
	cwFtdcTimeType			UpdateTime;
	///最后修改毫秒
	cwFtdcMillisecType		UpdateMillisec;
	///合约代码
	cwFtdcInstrumentIDType	InstrumentID;
	union
	{
		OneLevelQuote			BuyLevel[MARKET_PRICE_DEPTH];
		struct
		{
			///申买价一
			cwFtdcPriceType BidPrice1;
			cwFtdcVolumeType BidVolume1;

			cwFtdcPriceType BidPrice2;
			cwFtdcVolumeType BidVolume2;

			cwFtdcPriceType BidPrice3;
			cwFtdcVolumeType BidVolume3;

			cwFtdcPriceType BidPrice4;
			cwFtdcVolumeType BidVolume4;

			cwFtdcPriceType BidPrice5;
			cwFtdcVolumeType BidVolume5;
		};
	};
	union
	{
		OneLevelQuote			SellLevel[MARKET_PRICE_DEPTH];
		struct
		{
			cwFtdcPriceType AskPrice1; //卖一价
			cwFtdcVolumeType AskVolume1;

			cwFtdcPriceType AskPrice2;
			cwFtdcVolumeType AskVolume2;

			cwFtdcPriceType AskPrice3;
			cwFtdcVolumeType AskVolume3;

			cwFtdcPriceType AskPrice4;
			cwFtdcVolumeType AskVolume4;

			cwFtdcPriceType AskPrice5;
			cwFtdcVolumeType AskVolume5;
		};
	};

	///最新价
	cwFtdcPriceType		LastPrice;
	///上次结算价
	cwFtdcPriceType		PreSettlementPrice;
	///昨收盘
	cwFtdcPriceType		PreClosePrice;
	///昨持仓量
	cwFtdcPriceType		PreOpenInterest;
	///昨虚实度
	cwFtdcPriceType		PreDelta;

	///数量
	cwFtdcLargeVolumeType	Volume;
	///成交金额
	cwFtdcPriceType		Turnover;
	///持仓量
	cwFtdcPriceType		OpenInterest;

	///今开盘
	cwFtdcPriceType		OpenPrice;
	///最高价
	cwFtdcPriceType		HighestPrice;
	///最低价
	cwFtdcPriceType		LowestPrice;
	///今收盘
	cwFtdcPriceType		ClosePrice;
	///本次结算价
	cwFtdcPriceType		SettlementPrice;
	///涨停板价
	cwFtdcPriceType		UpperLimitPrice;
	///跌停板价
	cwFtdcPriceType		LowerLimitPrice;

	///今虚实度
	cwFtdcPriceType		CurrDelta;
	///当日均价
	//cwFtdcPriceType		AveragePrice;

#ifdef USING_CW_MEMORY_POOL


#endif // USING_CW_MEMORY_POOL

};
typedef std::shared_ptr<cwFtdcDepthMarketDataField> cwMarketDataPtr;


//Instrument
struct cwFtdcInstrumentField
{
	///交易所代码
	cwFtdcExchangeIDType				ExchangeID;
	///合约代码
	cwFtdcInstrumentIDType				InstrumentID;
	///合约名称
	cwFtdcInstrumentNameType			InstrumentName;
	///产品代码
	cwFtdcProductIDType					ProductID;
	///产品类型
	cwFtdcProductClassType				ProductClass;
	///创建日
	cwFtdcDateType						CreateDate;
	///上市日
	cwFtdcDateType						OpenDate;
	///到期日
	cwFtdcDateType						ExpireDate;
	///币种
	cwFtdcCurrencyType					Currency;
	///期权类型
	cwFtdcOptionsTypeType				OptionsType;
	///开始交割日
	cwFtdcDateType						StartDelivDate;
	///结束交割日
	cwFtdcDateType						EndDelivDate;
	///持仓类型
	cwFtdcPositionTypeType				PositionType;
	///是否使用大额单边保证金算法
	cwFtdcMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///基础商品代码
	cwFtdcInstrumentIDType				UnderlyingInstrID;
	///合约基础商品乘数
	cwFtdcUnderlyingMultipleType		UnderlyingMultiple;
	///交割年份
	cwFtdcYearType						DeliveryYear;
	///交割月
	cwFtdcMonthType						DeliveryMonth;
	///市价单最大下单量
	cwFtdcVolumeType					MaxMarketOrderVolume;
	///市价单最小下单量
	cwFtdcVolumeType					MinMarketOrderVolume;
	///限价单最大下单量
	cwFtdcVolumeType					MaxLimitOrderVolume;
	///限价单最小下单量
	cwFtdcVolumeType					MinLimitOrderVolume;
	///当前是否交易
	cwFtdcBoolType						IsTrading;
	///合约数量乘数
	cwFtdcVolumeMultipleType			VolumeMultiple;
	///最小变动价位
	cwFtdcPriceType						PriceTick;
	///执行价
	cwFtdcPriceType						StrikePrice;

};
typedef std::shared_ptr<cwFtdcInstrumentField> cwInstrumentDataPtr;


///--------------------Trade---------------------------------------------
///Account
typedef struct cwFtdcACCOUNTFIELD
{
	///投资者帐号
	cwFtdcAccountIDType				AccountID;
	///上次结算准备金
	cwFtdcMoneyType					PreBalance;
	///入金金额
	cwFtdcMoneyType					Deposit;
	///出金金额
	cwFtdcMoneyType					Withdraw;
	///当前保证金总额
	cwFtdcMoneyType					CurrMargin;
	///手续费
	cwFtdcMoneyType					Commission;
	///冻结的保证金
	cwFtdcMoneyType					FrozenMargin;
	///冻结的手续费
	cwFtdcMoneyType					FrozenCommission;
	///平仓盈亏
	cwFtdcMoneyType					CloseProfit;
	///持仓盈亏
	cwFtdcMoneyType					PositionProfit;
	///期货结算准备金
	cwFtdcMoneyType					Balance;
	///可用资金
	cwFtdcMoneyType					Available;

	cwFtdcACCOUNTFIELD();

	void Reset();
}cwAccountField;
typedef std::shared_ptr<cwFtdcACCOUNTFIELD>	cwAccountPtr;

///Order
enum  cwOpenClose
{
	//开仓
	cwOpen = 0
	//平仓（平昨）
	, cwClose
	//平今
	, cwCloseToday
};

enum cwUserCanceleStatus : uint32_t
{
	cwUserCancel_NoCancel = 0
	, cwUserCancel_ReqCancel
	, cwUserCancel_Canceled
};

struct ActiveOrderKey
{
	std::string OrderSysID;
	std::string OrderRef;
	std::string InstrumentID;

	double Price;
	cwFtdcVolumeType Volume;

	ActiveOrderKey(const char * sysId, const char * ref, const char * ins, double price, int vol);

	bool operator < (const ActiveOrderKey& orderkey) const;
	bool operator == (const ActiveOrderKey& orderkey) const;
};

struct ORDERFIELD
{
	///经纪公司代码
	cwFtdcBrokerIDType					BrokerID;
	///投资者代码
	cwFtdcInvestorIDType				InvestorID;
	///合约代码
	cwFtdcInstrumentIDType				InstrumentID;
	///报单引用
	cwFtdcOrderRefType					OrderRef;
	///用户代码
	cwFtdcUserIDType					UserID;
	///买卖方向
	cwFtdcDirectionType					Direction;
	///组合开平标志
	cwFtdcCombOffsetFlagType			CombOffsetFlag;
	///组合投机套保标志
	cwFtdcCombHedgeFlagType				CombHedgeFlag;
	///价格
	cwFtdcPriceType						LimitPrice;
	///数量
	cwFtdcVolumeType					VolumeTotalOriginal;
	///最小成交量
	cwFtdcVolumeType					MinVolume;
	///报单价格条件
	cwFtdcOrderPriceType				OrderPriceType;
	///有效期类型
	cwFtdcTimeConditionType				TimeCondition;
	///GTD日期
	cwFtdcDateType						GTDDate;
	///成交量类型
	cwFtdcVolumeConditionType			VolumeCondition;
	///触发条件
	cwFtdcContingentConditionType		ContingentCondition;
	///强平原因
	cwFtdcForceCloseReasonType			ForceCloseReason;
	///本地报单编号
	cwFtdcOrderLocalIDType				OrderLocalID;
	///交易所代码
	cwFtdcExchangeIDType				ExchangeID;
	///客户代码
	cwFtdcClientIDType					ClientID;
	///报单提交状态
	cwFtdcOrderSubmitStatusType			OrderSubmitStatus;
	///报单来源
	cwFtdcOrderSourceType				OrderSource;
	///报单状态
	cwFtdcOrderStatusType				OrderStatus;
	///止损价
	cwFtdcPriceType						StopPrice;
	///交易日
	cwFtdcDateType						TradingDay;
	///报单编号
	cwFtdcOrderSysIDType				OrderSysID;
	///今成交数量
	cwFtdcVolumeType					VolumeTraded;
	///剩余数量
	cwFtdcVolumeType					VolumeTotal;
	///报单日期
	cwFtdcDateType						InsertDate;
	///委托时间
	cwFtdcTimeType						InsertTime;
	///激活时间
	cwFtdcTimeType						ActiveTime;
	///挂起时间
	cwFtdcTimeType						SuspendTime;
	///最后修改时间
	cwFtdcTimeType						UpdateTime;
	///撤销时间
	cwFtdcTimeType						CancelTime;
	///用户端产品信息
	cwFtdcProductInfoType				UserProductInfo;
	///状态信息
	cwFtdcErrorMsgType					StatusMsg;
	///相关报单
	cwFtdcOrderSysIDType				RelativeOrderSysID;
	///报单类型
	cwFtdcOrderTypeType					OrderType;
	///结算编号
	cwFtdcSettlementIDType				SettlementID;
	///前置编号
	cwFtdcFrontIDType					FrontID;
	///会话编号
	cwFtdcSessionIDType					SessionID;
	///用户强评标志
	cwFtdcBoolType						UserForceClose;
	///Mac地址
	//cwFtdcMacAddressType				MacAddress;
	///IP地址
	cwFtdcIPAddressType					IPAddress;
	///币种代码
	cwFtdcCurrencyIDType				CurrencyID;

	cwUserCanceleStatus					UserCancelStatus;
	uint32_t							UserCancelTime;
	// Add From PlatForm
	int32_t								iRanked;

	//ORDERFIELD(CThostFtdcOrderField * pOrder);
	//ORDERFIELD(CThostFtdcInputOrderField* pOrder);
	ORDERFIELD();

	//void Reset(CThostFtdcOrderField * pOrder);
	void Reset();
};
typedef std::shared_ptr<ORDERFIELD> cwOrderPtr;

///Trade
struct TRADEFIELD
{
	///经纪公司代码
	cwFtdcBrokerIDType					BrokerID;
	///投资者代码
	cwFtdcInvestorIDType				InvestorID;
	///合约代码
	cwFtdcInstrumentIDType				InstrumentID;
	///报单引用
	cwFtdcOrderRefType					OrderRef;
	///用户代码
	cwFtdcUserIDType					UserID;
	///交易所代码
	cwFtdcExchangeIDType				ExchangeID;
	///成交编号
	cwFtdcTradeIDType					TradeID;
	///买卖方向
	cwFtdcDirectionType					Direction;
	///报单编号
	cwFtdcOrderSysIDType				OrderSysID;
	///客户代码
	cwFtdcClientIDType					ClientID;
	///价格
	cwFtdcPriceType						Price;
	///数量
	cwFtdcVolumeType					Volume;
	///开平标志
	cwFtdcOffsetFlagType				OffsetFlag;
	///投机套保标志
	cwFtdcHedgeFlagType					HedgeFlag;
	///成交时期
	cwFtdcDateType						TradeDate;
	///成交时间
	cwFtdcTimeType						TradeTime;
	///成交类型
	cwFtdcTradeTypeType					TradeType;
	///成交来源
	cwFtdcTradeSourceType				TradeSource;
	///交易所交易员代码
	cwFtdcTraderIDType					TraderID;
	///本地报单编号
	cwFtdcOrderLocalIDType				OrderLocalID;
	///交易日
	//cwFtdcDateType					TradingDay;
	///成交价来源
	//cwFtdcPriceSourceType				PriceSource;

	//TRADEFIELD(CThostFtdcTradeField * pTrade);
	TRADEFIELD();

	//void Reset(CThostFtdcTradeField * pTrade);
	void Reset();
};
typedef std::shared_ptr<TRADEFIELD> cwTradePtr;

//#define CW_POSITION_UPDATE_BY_TRADE
#define CW_POSITION_UPDATE_BY_ORDER

///Position
struct POSITIONFIELD
{
	///合约代码
	cwFtdcInstrumentIDType				InstrumentID;
	///上日持仓
	cwFtdcVolumeType					YdPosition;
	///今日持仓
	cwFtdcVolumeType					TodayPosition;
	///总持仓
	cwFtdcVolumeType					TotalPosition;
	///持仓冻结
	cwFtdcVolumeType					PositionFrozen;
	///持仓成本
	cwFtdcMoneyType						PositionCost;
	///开仓成本
	cwFtdcMoneyType						OpenCost;
	///交易所保证金
	cwFtdcMoneyType						ExchangeMargin;
	///持仓均价
	cwFtdcMoneyType						AveragePosPrice;
	///持仓盈亏
	cwFtdcMoneyType						PositionProfit;
	///逐日盯市平仓盈亏
	cwFtdcMoneyType						CloseProfitByDate;
	///逐笔对冲平仓盈亏
	cwFtdcMoneyType						CloseProfitByTrade;
	///保证金率
	cwFtdcRatioType						MarginRateByMoney;
	///保证金率(按手数)
	cwFtdcRatioType						MarginRateByVolume;
	///持仓多空方向
	cwFtdcDirectionType					PosiDirection;
	///投机套保标志
	cwFtdcHedgeFlagType					HedgeFlag;

	POSITIONFIELD();

	void Reset();

	void UpdatePosition(const char * szInstrumentID, cwFtdcDirectionType cPosiDirection, cwFtdcHedgeFlagType cHedgeFlag,
		cwFtdcVolumeType iYdPosition, cwFtdcVolumeType iTdPosition, cwFtdcVolumeType iPosition,
		cwFtdcVolumeType iLongFrozen, cwFtdcVolumeType iShortFrozen, cwFtdcMoneyType dPositionCost,
		cwFtdcMoneyType dOpenCost, cwFtdcMoneyType dExchangeMargin,
		cwFtdcMoneyType dPositionProfit, cwFtdcMoneyType dCloseProfitByDate, cwFtdcMoneyType dCloseProfitByTrade,
		cwFtdcRatioType dMarginRateByMoney, cwFtdcRatioType dMarginRateByVolume, cwFtdcPositionDateType cPositionDate = CW_FTDC_PSD_UNKNOW);
};
typedef std::shared_ptr<POSITIONFIELD>  PositionFieldPtr;

typedef struct CWPOSITIONFIELD
{
	bool IsUpdating;
	PositionFieldPtr LongPosition;
	PositionFieldPtr ShortPosition;

	std::deque<double> LongPositionPrice;
	double LongPositionPriceSum;

	std::deque<double> ShortPositionPrice;
	double ShortPositionPriceSum;

	CWPOSITIONFIELD();

	void Reset();

#ifdef CW_POSITION_UPDATE_BY_TRADE
	void UpdatePosition(cwOrderPtr pOrigionOrder, cwOrderPtr pOrder, bool bNetPositionModel = false);
	void UpdatePosition(cwTradePtr pTrade, cwInstrumentDataPtr InsPtr, bool bNetPositionModel = false);
#endif // CW_POSITION_UPDATE_BY_TRADE
#ifdef CW_POSITION_UPDATE_BY_ORDER
	void UpdatePosition(cwOrderPtr pOrigionOrder, cwOrderPtr pOrder, bool bNetPositionModel = false);
	void UpdatePosition(cwTradePtr pTrade, cwInstrumentDataPtr InsPtr, bool bNetPositionModel = false);
#endif // CW_POSITION_UPDATE_BY_ORDER



	cwFtdcVolumeType GetLongYdPosition();
	cwFtdcVolumeType GetLongTotalPosition();
	cwFtdcVolumeType GetLongTodayPosition();

	cwFtdcMoneyType  GetLongAveragePosPrice();
	cwFtdcMoneyType  GetLongCurrentPosPrice();

	cwFtdcVolumeType GetShortYdPosition();
	cwFtdcVolumeType GetShortTotalPosition();
	cwFtdcVolumeType GetShortTodayPosition();

	cwFtdcMoneyType  GetShortAveragePosPrice();
	cwFtdcMoneyType  GetShortCurrentPosPrice();
}cwPositionField;
typedef std::shared_ptr<cwPositionField> cwPositionPtr;

///响应信息
struct cwFtdcRspInfoField
{
	///错误代码
	cwFtdcErrorIDType	ErrorID;
	///错误信息
	cwFtdcErrorMsgType	ErrorMsg;
};
typedef std::shared_ptr<cwFtdcRspInfoField> cwRspInfoPtr;
