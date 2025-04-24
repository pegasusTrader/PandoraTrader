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
#include <functional>
#include <unordered_map>

#include "cwInterfaceDefine.h"

//#define		CW_TURBO_MODE
//#define		CW_USING_TBB_LIB

//#define INTERFACENAME	" "
#define INTERFACENAME	"PandoraT"
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

//#define		CW_ACTIVEORDERKEY_AS_STRING

#ifdef CW_ACTIVEORDERKEY_AS_STRING
#define		cwActiveOrderKey	std::string
#else
#define		cwActiveOrderKey	ActiveEasyKey
#endif // CW_ACTIVEORDERKEY_AS_STRING


#define		cwSysOrderKey		std::string

#define		InstrumentIDLength	82
#define		MARKET_PRICE_DEPTH	5

enum CW_TE_RESUME_TYPE
{
	CW_TERT_RESTART = 0,
	CW_TERT_RESUME,
	CW_TERT_QUICK,
	CW_TERT_NONE
};

enum cwRangeOpenClose
{
	cwLeftOpenRightOpen = 0,							//(a,b)
	cwLeftOpenRightClose,								//(a,b]
	cwLeftCloseRightOpen,								//[a,b)
	cwLeftCloseRightClose								//[a,b]
};

///--------------------Market Data---------------------------------------------

#ifdef _MSC_VER
#pragma region CW_Data_Type_Define
#endif // _MSC_VER
///cwFtdcDateType��һ����������
typedef char		cwFtdcDateType[9];
///cwFtdcInstrumentIDType��һ����Լ��������
typedef char		cwFtdcInstrumentIDType[InstrumentIDLength];
///cwFtdcProductIDType��һ����Լ��������
typedef char		cwFtdcProductIDType[InstrumentIDLength];
///cwFtdcExchangeIDType��һ����������������
typedef char		cwFtdcExchangeIDType[11];
///cwFtdcTimeType��һ��ʱ������
typedef char		cwFtdcTimeType[9];
///cwFtdcMillisecType��һ��ʱ�䣨���룩����
typedef uint32_t	cwFtdcMillisecType;
///cwFtdcPriceType��һ���۸�����
typedef double		cwFtdcPriceType;
///cwFtdcVolumeType��һ����������
typedef int32_t		cwFtdcVolumeType;
///cwFtdcLargeVolumeType��һ�������������
typedef int64_t		cwFtdcLargeVolumeType;
///cwFtdcAccountIDType��һ��Ͷ�����ʺ�����
typedef char		cwFtdcAccountIDType[16];
///cwFtdcMoneyType��һ���ʽ�����
typedef double		cwFtdcMoneyType;
///cwFtdcInstrumentNameType��һ����Լ��������
typedef char		cwFtdcInstrumentNameType[21];
///cwFtdcYearType��һ���������
typedef uint32_t	cwFtdcYearType;
///cwFtdcMonthType��һ���·�����
typedef uint32_t	cwFtdcMonthType;
///cwFtdcVolumeMultipleType��һ����Լ������������
typedef uint32_t	cwFtdcVolumeMultipleType;
///cwFtdcBoolType��һ������������
typedef uint32_t	cwFtdcBoolType;
///cwFtdcUnderlyingMultipleType��һ��������Ʒ��������
typedef double		cwFtdcUnderlyingMultipleType;
///cwFtdcRatioType��һ����������
typedef double		cwFtdcRatioType;
///cwFtdcBrokerIDType��һ�����͹�˾��������
typedef char		cwFtdcBrokerIDType[64];
///cwFtdcInvestorIDType��һ��Ͷ���ߴ�������
typedef char		cwFtdcInvestorIDType[19];
///cwFtdcOrderRefType��һ��������������
typedef char		cwFtdcOrderRefType[23];
///cwFtdcUserIDType��һ���û���������
typedef char		cwFtdcUserIDType[16];
///cwFtdcPasswordType��һ����������
typedef char		cwFtdcPasswordType[100];
///cwFtdcCombOffsetFlagType��һ����Ͽ�ƽ��־����
typedef char		cwFtdcCombOffsetFlagType[5];
///cwFtdcCombHedgeFlagType��һ�����Ͷ���ױ���־����
typedef char		cwFtdcCombHedgeFlagType[5];
///cwFtdcOrderLocalIDType��һ�����ر����������
typedef char		cwFtdcOrderLocalIDType[33];
///cwFtdcClientIDType��һ�����ױ�������
typedef char		cwFtdcClientIDType[19];
///cwFtdcSettlementIDType��һ������������
typedef uint32_t	cwFtdcSettlementIDType;
///cwFtdcOrderSysIDType��һ�������������
typedef char		cwFtdcOrderSysIDType[31];
///cwFtdcFrontIDType��һ��ǰ�ñ������
typedef uint32_t	cwFtdcFrontIDType;
///cwFtdcSessionIDType��һ���Ự�������
typedef uint32_t	cwFtdcSessionIDType;
///cwFtdcProductInfoType��һ����Ʒ��Ϣ����
typedef char		cwFtdcProductInfoType[11];
///cwFtdcAppIDType��һ����¼ǰ��֤appid����
typedef char		cwFtdcAppIDType[33];
///cwFtdcErrorMsgType��һ��������Ϣ����
typedef char		cwFtdcErrorMsgType[87];
///cwFtdcCurrencyIDType��һ�����ִ�������
typedef char		cwFtdcCurrencyIDType[4];
///cwFtdcIPAddressType��һ��IP��ַ����
typedef char		cwFtdcIPAddressType[33];
///cwFtdcMacAddressType��һ��Mac��ַ����
typedef char		cwFtdcMacAddressType[21];
///cwFtdcTradeIDType��һ���ɽ��������
typedef char		cwFtdcTradeIDType[21];
///cwFtdcTraderIDType��һ������������Ա��������
typedef char		cwFtdcTraderIDType[21];
///cwFtdcErrorIDType��һ�������������
typedef int			cwFtdcErrorIDType;


#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

#ifdef _MSC_VER
#pragma region CW_Data_Type_Enum_Define
#endif // _MSC_VER
/////////////////////////////////////////////////////////////////////////
///cwFtdcProductClassType��һ����Ʒ��������
/////////////////////////////////////////////////////////////////////////
///δ֪
#define CW_FTDC_PC_UnKnow 'u'
///�ڻ�
#define CW_FTDC_PC_Futures '1'
///�ڻ���Ȩ
#define CW_FTDC_PC_Options '2'
///���
#define CW_FTDC_PC_Combination '3'
///����
#define CW_FTDC_PC_Spot '4'
///��ת��
#define CW_FTDC_PC_EFP '5'
///�ֻ���Ȩ
#define CW_FTDC_PC_SpotOption '6'
///TAS��Լ
#define CW_FTDC_PC_TAS '7'
///����ָ��
#define CW_FTDC_PC_MI 'I'
///��Ʊ��Ȩ
#define CW_FTDC_PC_StockOptions '8'
///�����ֻ�
#define CW_FTDC_PC_SGE_SPOT '9'
///֤ȯ
#define CW_FTDC_PC_Stocks '0'
///��������
#define CW_FTDC_PC_SGE_DEFER 'a'
///����Զ��
#define CW_FTDC_PC_SGE_FOWARD 'b'

typedef char		cwFtdcProductClassType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPositionTypeType��һ���ֲ���������
/////////////////////////////////////////////////////////////////////////
///���ֲ�
#define CW_FTDC_PT_Net '1'
///�ۺϳֲ�
#define CW_FTDC_PT_Gross '2'

typedef char cwFtdcPositionTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcMaxMarginSideAlgorithmType��һ�����߱�֤���㷨����
/////////////////////////////////////////////////////////////////////////
///��ʹ�ô��߱�֤���㷨
#define CW_FTDC_MMSA_NO '0'
///ʹ�ô��߱�֤���㷨
#define CW_FTDC_MMSA_YES '1'

typedef char cwFtdcMaxMarginSideAlgorithmType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOptionsTypeType��һ����Ȩ��������
/////////////////////////////////////////////////////////////////////////
///����
#define CW_FTDC_CP_CallOptions '1'
///����
#define CW_FTDC_CP_PutOptions '2'

typedef char cwFtdcOptionsTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcCurrencyType��һ����������
/////////////////////////////////////////////////////////////////////////
///�����
#define CW_FTDC_C_RMB '1'
///��Ԫ
#define CW_FTDC_C_UDOLLAR '2'

typedef char cwFtdcCurrencyType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcDirectionType��һ��������������
/////////////////////////////////////////////////////////////////////////
//��
#define CW_FTDC_D_Buy '0'
//��
#define CW_FTDC_D_Sell '1'

typedef char cwFtdcDirectionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcHedgeFlagType��һ��Ͷ���ױ���־����
/////////////////////////////////////////////////////////////////////////
//Ͷ��
#define CW_FTDC_HF_Speculation '1'
//����
#define CW_FTDC_HF_Arbitrage '2'
//�ױ�
#define CW_FTDC_HF_Hedge '3'
//������
#define CW_FTDC_HF_MarketMaker '5'

typedef char cwFtdcHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPositionDateType��һ���ֲ���������
/////////////////////////////////////////////////////////////////////////
///����ʱ�����ֽ��պ����ճֲ�, QDP�ֲ�
#define CW_FTDC_PSD_UNKNOW '0'
///���ճֲ�
#define CW_FTDC_PSD_Today '1'
///��ʷ�ֲ�
#define CW_FTDC_PSD_History '2'

typedef char cwFtdcPositionDateType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderPriceTypeType��һ�������۸���������
/////////////////////////////////////////////////////////////////////////
///�����
#define CW_FTDC_OPT_AnyPrice '1'
///�޼�
#define CW_FTDC_OPT_LimitPrice '2'
///���ż�
#define CW_FTDC_OPT_BestPrice '3'
///���¼�
#define CW_FTDC_OPT_LastPrice '4'
///���¼۸����ϸ�1��ticks
#define CW_FTDC_OPT_LastPricePlusOneTicks '5'
///���¼۸����ϸ�2��ticks
#define CW_FTDC_OPT_LastPricePlusTwoTicks '6'
///���¼۸����ϸ�3��ticks
#define CW_FTDC_OPT_LastPricePlusThreeTicks '7'
///��һ��
#define CW_FTDC_OPT_AskPrice1 '8'
///��һ�۸����ϸ�1��ticks
#define CW_FTDC_OPT_AskPrice1PlusOneTicks '9'
///��һ�۸����ϸ�2��ticks
#define CW_FTDC_OPT_AskPrice1PlusTwoTicks 'A'
///��һ�۸����ϸ�3��ticks
#define CW_FTDC_OPT_AskPrice1PlusThreeTicks 'B'
///��һ��
#define CW_FTDC_OPT_BidPrice1 'C'
///��һ�۸����ϸ�1��ticks
#define CW_FTDC_OPT_BidPrice1PlusOneTicks 'D'
///��һ�۸����ϸ�2��ticks
#define CW_FTDC_OPT_BidPrice1PlusTwoTicks 'E'
///��һ�۸����ϸ�3��ticks
#define CW_FTDC_OPT_BidPrice1PlusThreeTicks 'F'
///�嵵��
#define CW_FTDC_OPT_FiveLevelPrice 'G'

typedef char cwFtdcOrderPriceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTimeConditionType��һ����Ч����������
/////////////////////////////////////////////////////////////////////////
//������ɣ�������
#define CW_FTDC_TC_IOC '1'
//������Ч
#define CW_FTDC_TC_GFS '2'
//������Ч
#define CW_FTDC_TC_GFD '3'
//ָ������ǰ��Ч
#define CW_FTDC_TC_GTD '4'
//����ǰ��Ч
#define CW_FTDC_TC_GTC '5'
//���Ͼ�����Ч
#define CW_FTDC_TC_GFA '6'

typedef char cwFtdcTimeConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcVolumeConditionType��һ���ɽ�����������
/////////////////////////////////////////////////////////////////////////
///�κ�����
#define CW_FTDC_VC_AV '1'
///��С����
#define CW_FTDC_VC_MV '2'
///ȫ������
#define CW_FTDC_VC_CV '3'

typedef char cwFtdcVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcContingentConditionType��һ��������������
/////////////////////////////////////////////////////////////////////////
///����
#define CW_FTDC_CC_Immediately '1'
///ֹ��
#define CW_FTDC_CC_Touch '2'
///ֹӮ
#define CW_FTDC_CC_TouchProfit '3'
///Ԥ��
#define CW_FTDC_CC_ParkedOrder '4'
///���¼۴���������
#define CW_FTDC_CC_LastPriceGreaterThanStopPrice '5'
///���¼۴��ڵ���������
#define CW_FTDC_CC_LastPriceGreaterEqualStopPrice '6'
///���¼�С��������
#define CW_FTDC_CC_LastPriceLesserThanStopPrice '7'
///���¼�С�ڵ���������
#define CW_FTDC_CC_LastPriceLesserEqualStopPrice '8'
///��һ�۴���������
#define CW_FTDC_CC_AskPriceGreaterThanStopPrice '9'
///��һ�۴��ڵ���������
#define CW_FTDC_CC_AskPriceGreaterEqualStopPrice 'A'
///��һ��С��������
#define CW_FTDC_CC_AskPriceLesserThanStopPrice 'B'
///��һ��С�ڵ���������
#define CW_FTDC_CC_AskPriceLesserEqualStopPrice 'C'
///��һ�۴���������
#define CW_FTDC_CC_BidPriceGreaterThanStopPrice 'D'
///��һ�۴��ڵ���������
#define CW_FTDC_CC_BidPriceGreaterEqualStopPrice 'E'
///��һ��С��������
#define CW_FTDC_CC_BidPriceLesserThanStopPrice 'F'
///��һ��С�ڵ���������
#define CW_FTDC_CC_BidPriceLesserEqualStopPrice 'H'

typedef char cwFtdcContingentConditionType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcForceCloseReasonType��һ��ǿƽԭ������
/////////////////////////////////////////////////////////////////////////
///��ǿƽ
#define CW_FTDC_FCC_NotForceClose '0'
///�ʽ���
#define CW_FTDC_FCC_LackDeposit '1'
///�ͻ�����
#define CW_FTDC_FCC_ClientOverPositionLimit '2'
///��Ա����
#define CW_FTDC_FCC_MemberOverPositionLimit '3'
///�ֲַ�������
#define CW_FTDC_FCC_NotMultiple '4'
///Υ��
#define CW_FTDC_FCC_Violation '5'
///����
#define CW_FTDC_FCC_Other '6'
///��Ȼ���ٽ�����
#define CW_FTDC_FCC_PersonDeliv '7'

typedef char cwFtdcForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderSubmitStatusType��һ�������ύ״̬����
/////////////////////////////////////////////////////////////////////////
///�Ѿ��ύ
#define CW_FTDC_OSS_InsertSubmitted '0'
///�����Ѿ��ύ
#define CW_FTDC_OSS_CancelSubmitted '1'
///�޸��Ѿ��ύ
#define CW_FTDC_OSS_ModifySubmitted '2'
///�Ѿ�����
#define CW_FTDC_OSS_Accepted '3'
///�����Ѿ����ܾ�
#define CW_FTDC_OSS_InsertRejected '4'
///�����Ѿ����ܾ�
#define CW_FTDC_OSS_CancelRejected '5'
///�ĵ��Ѿ����ܾ�
#define CW_FTDC_OSS_ModifyRejected '6'

typedef char cwFtdcOrderSubmitStatusType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderSourceType��һ��������Դ����
/////////////////////////////////////////////////////////////////////////
///���Բ�����
#define CW_FTDC_OSRC_Participant '0'
///���Թ���Ա
#define CW_FTDC_OSRC_Administrator '1'

typedef char cwFtdcOrderSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderStatusType��һ������״̬����
/////////////////////////////////////////////////////////////////////////
//ȫ���ɽ�
#define CW_FTDC_OST_AllTraded '0'
//���ֳɽ����ڶ�����
#define CW_FTDC_OST_PartTradedQueueing '1'
//���ֳɽ����ڶ�����
#define CW_FTDC_OST_PartTradedNotQueueing '2'
//δ�ɽ����ڶ�����
#define CW_FTDC_OST_NoTradeQueueing '3'
//δ�ɽ����ڶ�����
#define CW_FTDC_OST_NoTradeNotQueueing '4'
//����
#define CW_FTDC_OST_Canceled '5'
//�����ѱ��뽻����δӦ��
#define CW_FTDC_OST_AcceptedNoReply '6'
//δ֪
#define CW_FTDC_OST_Unknown 'a'
//��δ����
#define CW_FTDC_OST_NotTouched 'b'
//�Ѵ���
#define CW_FTDC_OST_Touched 'c'
//Default
#define CW_FTDC_OST_cwDefault ' '

typedef char cwFtdcOrderStatusType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOrderTypeType��һ��������������
/////////////////////////////////////////////////////////////////////////
///����
#define CW_FTDC_ORDT_Normal '0'
///��������
#define CW_FTDC_ORDT_DeriveFromQuote '1'
///�������
#define CW_FTDC_ORDT_DeriveFromCombination '2'
///��ϱ���
#define CW_FTDC_ORDT_Combination '3'
///������
#define CW_FTDC_ORDT_ConditionalOrder '4'
///������
#define CW_FTDC_ORDT_Swap '5'

typedef char cwFtdcOrderTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcOffsetFlagType��һ����ƽ��־����
/////////////////////////////////////////////////////////////////////////
///����
#define CW_FTDC_OF_Open '0'
///ƽ��
#define CW_FTDC_OF_Close '1'
///ǿƽ
#define CW_FTDC_OF_ForceClose '2'
///ƽ��
#define CW_FTDC_OF_CloseToday '3'
///ƽ��
#define CW_FTDC_OF_CloseYesterday '4'
///ǿ��
#define CW_FTDC_OF_ForceOff '5'
///����ǿƽ
#define CW_FTDC_OF_LocalForceClose '6'

typedef char cwFtdcOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTradeTypeType��һ���ɽ���������
/////////////////////////////////////////////////////////////////////////
///��ϳֲֲ��Ϊ��һ�ֲ�,��ʼ����Ӧ���������͵ĳֲ�
#define CW_FTDC_TRDT_SplitCombination '#'
///��ͨ�ɽ�
#define CW_FTDC_TRDT_Common '0'
///��Ȩִ��
#define CW_FTDC_TRDT_OptionsExecution '1'
///OTC�ɽ�
#define CW_FTDC_TRDT_OTC '2'
///��ת�������ɽ�
#define CW_FTDC_TRDT_EFPDerived '3'
///��������ɽ�
#define CW_FTDC_TRDT_CombinationDerived '4'

typedef char cwFtdcTradeTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcSpecPosiTypeType��һ������ֲ���ϸ��ʶ����
/////////////////////////////////////////////////////////////////////////
///��ͨ�ֲ���ϸ
#define CW_FTDC_SPOST_Common '#'
///TAS��Լ�ɽ������ı�ĺ�Լ�ֲ���ϸ
#define CW_FTDC_SPOST_Tas '0'

typedef char cwFtdcSpecPosiTypeType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcPriceSourceType��һ���ɽ�����Դ����
/////////////////////////////////////////////////////////////////////////
///ǰ�ɽ���
#define CW_FTDC_PSRC_LastPrice '0'
///��ί�м�
#define CW_FTDC_PSRC_Buy '1'
///��ί�м�
#define CW_FTDC_PSRC_Sell '2'

typedef char cwFtdcPriceSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcTradeSourceType��һ���ɽ���Դ����
/////////////////////////////////////////////////////////////////////////
///���Խ�������ͨ�ر�
#define CW_FTDC_TSRC_NORMAL '0'
///���Բ�ѯ
#define CW_FTDC_TSRC_QUERY '1'

typedef char cwFtdcTradeSourceType;

/////////////////////////////////////////////////////////////////////////
///cwFtdcInstrumentStatusType��һ����Լ����״̬����
/////////////////////////////////////////////////////////////////////////
///����ǰ
#define CW_FTDC_IS_BeforeTrading '0'
///�ǽ���
#define CW_FTDC_IS_NoTrading '1'
///��������
#define CW_FTDC_IS_Continous '2'
///���Ͼ��۱���
#define CW_FTDC_IS_AuctionOrdering '3'
///���Ͼ��ۼ۸�ƽ��
#define CW_FTDC_IS_AuctionBalance '4'
///���Ͼ��۴��
#define CW_FTDC_IS_AuctionMatch '5'
///����
#define CW_FTDC_IS_Closed '6'
///���������걨
#define CW_FTDC_IS_SGE_Dery_App '7'
///���������걨����
#define CW_FTDC_IS_SGE_Dery_Match '8'
///�����������걨
#define CW_FTDC_IS_SGE_Mid_App '9'
///���������걨���
#define CW_FTDC_IS_SGE_Mid_Match 'a'
///�������Զ�ת������
#define CW_FTDC_IS_DCE_MarketStatusAlarm 'b'

typedef char cwFtdcInstrumentStatusType;
const char * g_cwGetInstrumentStatus(cwFtdcInstrumentStatusType insstatustype);

enum cwInsertOrderType :int
{
	cwInsertLimitOrder = 0,			//�޼۵�
	cwInsertFAKOrder = 1,			//FAK Filled And Kill �����ɽ�ʣ���Զ�����ָ��
	cwInsertFOKOrder = 2,			//FOK Filled Or Kill ����ȫ���ɽ������Զ�����ָ��
	cwInsertMarketOrder = 3,		//�м۵����ݲ�֧�֣�
	cwInsertOtherTypeOrder
};

const char * GetInsertOrderTypeString(cwInsertOrderType ordertype);

#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

/// һ������ṹ��
struct OneLevelQuote
{
	cwFtdcPriceType		Price;							// �۸�
	cwFtdcVolumeType	Volume;							// ����
};

//�Ƿ�ʹ���ڴ��
//#define USING_CW_MEMORY_POOL

///�������
struct cwFtdcDepthMarketDataField
{
	///����������
	cwFtdcExchangeIDType	ExchangeID;
	///������
	cwFtdcDateType			TradingDay;
	///ҵ������
	cwFtdcDateType			ActionDay;
	///����޸�ʱ��
	cwFtdcTimeType			UpdateTime;
	///����޸ĺ���
	cwFtdcMillisecType		UpdateMillisec;
	///��Լ����
	cwFtdcInstrumentIDType	InstrumentID;
	union
	{
		OneLevelQuote			BuyLevel[MARKET_PRICE_DEPTH];
		struct
		{
			///�����һ
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
			cwFtdcPriceType AskPrice1; //��һ��
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

	///���¼�
	cwFtdcPriceType		LastPrice;
	///�ϴν����
	cwFtdcPriceType		PreSettlementPrice;
	///������
	cwFtdcPriceType		PreClosePrice;
	///��ֲ���
	cwFtdcPriceType		PreOpenInterest;
	///����ʵ��
	cwFtdcPriceType		PreDelta;

	///����
	cwFtdcLargeVolumeType	Volume;
	///�ɽ����
	cwFtdcPriceType		Turnover;
	///�ֲ���
	cwFtdcPriceType		OpenInterest;

	///����
	cwFtdcPriceType		OpenPrice;
	///��߼�
	cwFtdcPriceType		HighestPrice;
	///��ͼ�
	cwFtdcPriceType		LowestPrice;
	///������
	cwFtdcPriceType		ClosePrice;
	///���ν����
	cwFtdcPriceType		SettlementPrice;
	///��ͣ���
	cwFtdcPriceType		UpperLimitPrice;
	///��ͣ���
	cwFtdcPriceType		LowerLimitPrice;

	///����ʵ��
	cwFtdcPriceType		CurrDelta;
	///���վ���
	cwFtdcPriceType		AveragePrice;
};
typedef std::shared_ptr<cwFtdcDepthMarketDataField> cwMarketDataPtr;


//Instrument
struct cwFtdcInstrumentField
{
	///����������
	cwFtdcExchangeIDType				ExchangeID;
	///��Լ����
	cwFtdcInstrumentIDType				InstrumentID;
	///��Լ����
	cwFtdcInstrumentNameType			InstrumentName;
	///��Ʒ����
	cwFtdcProductIDType					ProductID;
	///��Ʒ����
	cwFtdcProductClassType				ProductClass;
	///������
	cwFtdcDateType						CreateDate;
	///������
	cwFtdcDateType						OpenDate;
	///������
	cwFtdcDateType						ExpireDate;
	///����
	cwFtdcCurrencyType					Currency;
	///��Ȩ����
	cwFtdcOptionsTypeType				OptionsType;
	///��ʼ������
	cwFtdcDateType						StartDelivDate;
	///����������
	cwFtdcDateType						EndDelivDate;
	///�ֲ�����
	cwFtdcPositionTypeType				PositionType;
	///�Ƿ�ʹ�ô��߱�֤���㷨
	cwFtdcMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///������Ʒ����
	cwFtdcInstrumentIDType				UnderlyingInstrID;
	///��Լ������Ʒ����
	cwFtdcUnderlyingMultipleType		UnderlyingMultiple;
	///�������
	cwFtdcYearType						DeliveryYear;
	///������
	cwFtdcMonthType						DeliveryMonth;
	///�м۵�����µ���
	cwFtdcVolumeType					MaxMarketOrderVolume;
	///�м۵���С�µ���
	cwFtdcVolumeType					MinMarketOrderVolume;
	///�޼۵�����µ���
	cwFtdcVolumeType					MaxLimitOrderVolume;
	///�޼۵���С�µ���
	cwFtdcVolumeType					MinLimitOrderVolume;
	///��ǰ�Ƿ���
	cwFtdcBoolType						IsTrading;
	///��Լ��������
	cwFtdcVolumeMultipleType			VolumeMultiple;
	///��С�䶯��λ
	cwFtdcPriceType						PriceTick;
	///ִ�м�
	cwFtdcPriceType						StrikePrice;

};
typedef std::shared_ptr<cwFtdcInstrumentField> cwInstrumentDataPtr;

///��Լ��֤����
struct cwFtdcInstrumentMarginRateField
{
	///�Ƿ�Ϊ��ѯֵ��0ΪĬ��ֵ��1Ϊ��ѯֵ
	cwFtdcBoolType		QryValue;
	///���͹�˾����
	cwFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	cwFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	cwFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	cwFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	cwFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	cwFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	cwFtdcMoneyType	ShortMarginRatioByVolume;
	///�Ƿ���Խ�������ȡ
	cwFtdcBoolType	IsRelative;
	///����������
	cwFtdcExchangeIDType	ExchangeID;
	///��Լ����
	cwFtdcInstrumentIDType	InstrumentID;
};
typedef std::shared_ptr<cwFtdcInstrumentMarginRateField> cwMarginRateDataPtr;

///��Լ��������
struct cwFtdcInstrumentCommissionRateField
{
	///�Ƿ�Ϊ��ѯֵ��0ΪĬ��ֵ��1Ϊ��ѯֵ
	cwFtdcBoolType		QryValue;
	///���͹�˾����
	cwFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	cwFtdcInvestorIDType	InvestorID;
	///������������
	cwFtdcRatioType	OpenRatioByMoney;
	///����������
	cwFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	cwFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	cwFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	cwFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	cwFtdcRatioType	CloseTodayRatioByVolume;
	///����������
	cwFtdcExchangeIDType	ExchangeID;
	///��Լ����
	cwFtdcInstrumentIDType	InstrumentID;
};
typedef std::shared_ptr<cwFtdcInstrumentCommissionRateField> cwCommissionRateDataPtr;

///--------------------Trade---------------------------------------------
///Account
typedef struct cwFtdcACCOUNTFIELD
{
	///Ͷ�����ʺ�
	cwFtdcAccountIDType				AccountID;
	///�ϴν���׼����
	cwFtdcMoneyType					PreBalance;
	///�����
	cwFtdcMoneyType					Deposit;
	///������
	cwFtdcMoneyType					Withdraw;
	///��ǰ��֤���ܶ�
	cwFtdcMoneyType					CurrMargin;
	///������
	cwFtdcMoneyType					Commission;
	///����ı�֤��
	cwFtdcMoneyType					FrozenMargin;
	///�����������
	cwFtdcMoneyType					FrozenCommission;
	///ƽ��ӯ��
	cwFtdcMoneyType					CloseProfit;
	///�ֲ�ӯ��
	cwFtdcMoneyType					PositionProfit;
	///�ڻ�����׼����
	cwFtdcMoneyType					Balance;
	///�����ʽ�
	cwFtdcMoneyType					Available;

	cwFtdcACCOUNTFIELD();

	void Reset();
}cwAccountField;
typedef std::shared_ptr<cwFtdcACCOUNTFIELD>	cwAccountPtr;

///Order
enum  cwOpenClose
{
	//����
	cwOpen = 0
	//ƽ�֣�ƽ��
	, cwClose
	//ƽ��
	, cwCloseToday
};

const char * GetcwOpenCloseString(cwOpenClose openclose);


enum cwUserCanceleStatus : uint32_t
{
	cwUserCancel_NoCancel = 0
	, cwUserCancel_ReqCancel
	, cwUserCancel_Canceled
};

struct ActiveOrderKey
{
	///ǰ�ñ��
	cwFtdcFrontIDType					FrontID;
	///�Ự���
	cwFtdcSessionIDType					SessionID;

	uint64_t							OrderRef;

	ActiveOrderKey(const char * ref, cwFtdcFrontIDType front, cwFtdcSessionIDType session);
	ActiveOrderKey(uint64_t ref, cwFtdcFrontIDType front, cwFtdcSessionIDType session);


	bool operator < (const ActiveOrderKey& orderkey) const;
	bool operator == (const ActiveOrderKey& orderkey) const;
};

struct ActiveOrderKey_HashFun
{
	std::size_t operator() (const ActiveOrderKey &key) const
	{
		return (std::hash<uint32_t>()(static_cast<uint32_t>(key.FrontID))
			^ std::hash<uint32_t>()(static_cast<uint32_t>(key.SessionID))
			^ std::hash<uint64_t>()(static_cast<uint64_t>(key.OrderRef)));
	}
};
size_t ActiveOrderKeyHash(ActiveOrderKey & key);

struct ActiveEasyKey
{
	///��Լ
	std::string						InstrumentID;

	//���ر������
	uint64_t						OrderRef;

	ActiveEasyKey(const char* ref, const char * szInstrumentID);
	ActiveEasyKey(uint64_t ref, const char * szInstrumentID);


	bool operator < (const ActiveEasyKey& orderkey) const;
	bool operator == (const ActiveEasyKey& orderkey) const;
};

struct ActiveEasyKey_HashFun
{
	std::size_t operator() (const ActiveEasyKey& key) const
	{
		return (std::hash<std::string>()(key.InstrumentID)
			^ std::hash<uint64_t>()(static_cast<uint64_t>(key.OrderRef)));
	}
};
size_t ActiveEasyKeyHash(ActiveEasyKey& key);


struct SysOrderKey
{
	///����������
	cwFtdcExchangeIDType				ExchangeID;
	///�������
	cwFtdcOrderSysIDType				OrderSysID;

	SysOrderKey(const char * exchange, const char * sysid);

	bool operator < (const SysOrderKey& orderkey) const;
	bool operator == (const SysOrderKey& orderkey) const;
};

struct SysOrderKey_HashFun
{
	std::size_t operator() (const SysOrderKey &key) const
	{
		return (std::hash<std::string>()(key.ExchangeID)
			^ std::hash<std::string>()(key.OrderSysID));
	}
};

struct ORDERFIELD
{
	///���͹�˾����
	cwFtdcBrokerIDType					BrokerID;
	///Ͷ���ߴ���
	cwFtdcInvestorIDType				InvestorID;
	///��Լ����
	cwFtdcInstrumentIDType				InstrumentID;
	///��������
	cwFtdcOrderRefType					OrderRef;
	///�û�����
	cwFtdcUserIDType					UserID;
	///��������
	cwFtdcDirectionType					Direction;
	///��Ͽ�ƽ��־
	cwFtdcCombOffsetFlagType			CombOffsetFlag;
	///���Ͷ���ױ���־
	cwFtdcCombHedgeFlagType				CombHedgeFlag;
	///�۸�
	cwFtdcPriceType						LimitPrice;
	///����
	cwFtdcVolumeType					VolumeTotalOriginal;
	///��С�ɽ���
	cwFtdcVolumeType					MinVolume;
	///�����۸�����
	cwFtdcOrderPriceType				OrderPriceType;
	///��Ч������
	cwFtdcTimeConditionType				TimeCondition;
	///GTD����
	cwFtdcDateType						GTDDate;
	///�ɽ�������
	cwFtdcVolumeConditionType			VolumeCondition;
	///��������
	cwFtdcContingentConditionType		ContingentCondition;
	///ǿƽԭ��
	cwFtdcForceCloseReasonType			ForceCloseReason;
	///���ر������
	cwFtdcOrderLocalIDType				OrderLocalID;
	///����������
	cwFtdcExchangeIDType				ExchangeID;
	///�ͻ�����
	cwFtdcClientIDType					ClientID;
	///�����ύ״̬
	cwFtdcOrderSubmitStatusType			OrderSubmitStatus;
	///������Դ
	cwFtdcOrderSourceType				OrderSource;
	///����״̬
	cwFtdcOrderStatusType				OrderStatus;
	///ֹ���
	cwFtdcPriceType						StopPrice;
	///������
	cwFtdcDateType						TradingDay;
	///�������
	cwFtdcOrderSysIDType				OrderSysID;
	///��ɽ�����
	cwFtdcVolumeType					VolumeTraded;
	///ʣ������
	cwFtdcVolumeType					VolumeTotal;
	///��������
	cwFtdcDateType						InsertDate;
	///ί��ʱ��
	cwFtdcTimeType						InsertTime;
	///����ʱ��
	cwFtdcTimeType						ActiveTime;
	///����ʱ��
	cwFtdcTimeType						SuspendTime;
	///����޸�ʱ��
	cwFtdcTimeType						UpdateTime;
	///����ʱ��
	cwFtdcTimeType						CancelTime;
	///�û��˲�Ʒ��Ϣ
	cwFtdcProductInfoType				UserProductInfo;
	///״̬��Ϣ
	cwFtdcErrorMsgType					StatusMsg;
	///��ر���
	cwFtdcOrderSysIDType				RelativeOrderSysID;
	///��������
	cwFtdcOrderTypeType					OrderType;
	///������
	cwFtdcSettlementIDType				SettlementID;
	///ǰ�ñ��
	cwFtdcFrontIDType					FrontID;
	///�Ự���
	cwFtdcSessionIDType					SessionID;
	///�û�ǿ����־
	cwFtdcBoolType						UserForceClose;
	///Mac��ַ
	//cwFtdcMacAddressType				MacAddress;
	///IP��ַ
	cwFtdcIPAddressType					IPAddress;
	///���ִ���
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
	///���͹�˾����
	cwFtdcBrokerIDType					BrokerID;
	///Ͷ���ߴ���
	cwFtdcInvestorIDType				InvestorID;
	///��Լ����
	cwFtdcInstrumentIDType				InstrumentID;
	///��������
	cwFtdcOrderRefType					OrderRef;
	///�û�����
	cwFtdcUserIDType					UserID;
	///����������
	cwFtdcExchangeIDType				ExchangeID;
	///�ɽ����
	cwFtdcTradeIDType					TradeID;
	///��������
	cwFtdcDirectionType					Direction;
	///�������
	cwFtdcOrderSysIDType				OrderSysID;
	///�ͻ�����
	cwFtdcClientIDType					ClientID;
	///�۸�
	cwFtdcPriceType						Price;
	///����
	cwFtdcVolumeType					Volume;
	///��ƽ��־
	cwFtdcOffsetFlagType				OffsetFlag;
	///Ͷ���ױ���־
	cwFtdcHedgeFlagType					HedgeFlag;
	///�ɽ�ʱ��
	cwFtdcDateType						TradeDate;
	///�ɽ�ʱ��
	cwFtdcTimeType						TradeTime;
	///�ɽ�����
	cwFtdcTradeTypeType					TradeType;
	///�ɽ���Դ
	cwFtdcTradeSourceType				TradeSource;
	///����������Ա����
	cwFtdcTraderIDType					TraderID;
	///���ر������
	cwFtdcOrderLocalIDType				OrderLocalID;
	///������
	//cwFtdcDateType					TradingDay;
	///�ɽ�����Դ
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
	///��Լ����
	cwFtdcInstrumentIDType				InstrumentID;
	///���ճֲ�
	cwFtdcVolumeType					YdPosition;
	///���ճֲ�
	cwFtdcVolumeType					TodayPosition;
	///�ֲܳ�
	cwFtdcVolumeType					TotalPosition;
	///�ֲֶ���
	cwFtdcVolumeType					PositionFrozen;
	///�ֲֳɱ�
	cwFtdcMoneyType						PositionCost;
	///���ֳɱ�
	cwFtdcMoneyType						OpenCost;
	///��������֤��
	cwFtdcMoneyType						ExchangeMargin;
	///�ֲ־���
	cwFtdcMoneyType						AveragePosPrice;
	///�ֲ�ӯ��
	cwFtdcMoneyType						PositionProfit;
	///���ն���ƽ��ӯ��
	cwFtdcMoneyType						CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	cwFtdcMoneyType						CloseProfitByTrade;
	///��֤����
	cwFtdcRatioType						MarginRateByMoney;
	///��֤����(������)
	cwFtdcRatioType						MarginRateByVolume;
	///�ֲֶ�շ���
	cwFtdcDirectionType					PosiDirection;
	///Ͷ���ױ���־
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

///��Ӧ��Ϣ
struct cwFtdcRspInfoField
{
	///�������
	cwFtdcErrorIDType	ErrorID;
	///������Ϣ
	cwFtdcErrorMsgType	ErrorMsg;
};
typedef std::shared_ptr<cwFtdcRspInfoField> cwRspInfoPtr;


cwActiveOrderKey GenerateActiveKey(cwOrderPtr pOrder);

namespace cwPandoraFs{
// ��ȡ��ǰִ���ļ��ľ���·��,��.exe��β
// @return �ļ�·���ָ�����0 ��ǰ��windowsϵͳ'\\'��1 ��ǰ��linuxϵͳ'/'
int GetExePath(std::string &exePath);

// ��ȡ��ǰִ���ļ������ļ��еľ���·��,�Էָ�����β
// @return �ļ�·���ָ�����0 ��ǰ��windowsϵͳ'\\'��1 ��ǰ��linuxϵͳ'/'
int GetExeFolder(std::string& exeFolder);

// ����Ŀ¼��·���ָ����ο�GetExePath�ķ���ֵ��
// @return 0:Ŀ¼�Ѵ���.  1:Ŀ¼�����ڣ��򴴽�.
int MkDir(std::string &dirPath);
}
