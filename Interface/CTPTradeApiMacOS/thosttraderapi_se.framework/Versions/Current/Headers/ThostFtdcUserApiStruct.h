/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ThostFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(THOST_FTDCSTRUCT_H)
#define THOST_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ThostFtdcUserApiDataType.h"

///信息分发
struct CThostFtdcDisseminationField
{
	///序列系列号
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TThostFtdcSequenceNoType	SequenceNo;
};

///用户登录请求
struct CThostFtdcReqUserLoginField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///动态密码
	TThostFtdcPasswordType	OneTimePassword;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
};

///用户登录应答
struct CThostFtdcRspUserLoginField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///登录成功时间
	TThostFtdcTimeType	LoginTime;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易系统名称
	TThostFtdcSystemNameType	SystemName;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///最大报单引用
	TThostFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TThostFtdcTimeType	SHFETime;
	///大商所时间
	TThostFtdcTimeType	DCETime;
	///郑商所时间
	TThostFtdcTimeType	CZCETime;
	///中金所时间
	TThostFtdcTimeType	FFEXTime;
	///能源中心时间
	TThostFtdcTimeType	INETime;
	///后台版本信息
	TThostFtdcSysVersionType	SysVersion;
	///广期所时间
	TThostFtdcTimeType	GFEXTime;
};

///用户登出请求
struct CThostFtdcUserLogoutField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///强制交易员退出
struct CThostFtdcForceUserLogoutField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///客户端认证请求
struct CThostFtdcReqAuthenticateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///认证码
	TThostFtdcAuthCodeType	AuthCode;
	///App代码
	TThostFtdcAppIDType	AppID;
};

///客户端认证响应
struct CThostFtdcRspAuthenticateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///App代码
	TThostFtdcAppIDType	AppID;
	///App类型
	TThostFtdcAppTypeType	AppType;
};

///客户端认证信息
struct CThostFtdcAuthenticationInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///认证信息
	TThostFtdcAuthInfoType	AuthInfo;
	///是否为认证结果
	TThostFtdcBoolType	IsResult;
	///App代码
	TThostFtdcAppIDType	AppID;
	///App类型
	TThostFtdcAppTypeType	AppType;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
};

///用户登录应答2
struct CThostFtdcRspUserLogin2Field
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///登录成功时间
	TThostFtdcTimeType	LoginTime;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易系统名称
	TThostFtdcSystemNameType	SystemName;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///最大报单引用
	TThostFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TThostFtdcTimeType	SHFETime;
	///大商所时间
	TThostFtdcTimeType	DCETime;
	///郑商所时间
	TThostFtdcTimeType	CZCETime;
	///中金所时间
	TThostFtdcTimeType	FFEXTime;
	///能源中心时间
	TThostFtdcTimeType	INETime;
	///随机串
	TThostFtdcRandomStringType	RandomString;
};

///银期转帐报文头
struct CThostFtdcTransferHeaderField
{
	///版本号，常量，1.0
	TThostFtdcVersionType	Version;
	///交易代码，必填
	TThostFtdcTradeCodeType	TradeCode;
	///交易日期，必填，格式：yyyymmdd
	TThostFtdcTradeDateType	TradeDate;
	///交易时间，必填，格式：hhmmss
	TThostFtdcTradeTimeType	TradeTime;
	///发起方流水号，N/A
	TThostFtdcTradeSerialType	TradeSerial;
	///期货公司代码，必填
	TThostFtdcFutureIDType	FutureID;
	///银行代码，根据查询银行得到，必填
	TThostFtdcBankIDType	BankID;
	///银行分中心代码，根据查询银行得到，必填
	TThostFtdcBankBrchIDType	BankBrchID;
	///操作员，N/A
	TThostFtdcOperNoType	OperNo;
	///交易设备类型，N/A
	TThostFtdcDeviceIDType	DeviceID;
	///记录数，N/A
	TThostFtdcRecordNumType	RecordNum;
	///会话编号，N/A
	TThostFtdcSessionIDType	SessionID;
	///请求编号，N/A
	TThostFtdcRequestIDType	RequestID;
};

///银行资金转期货请求，TradeCode=202001
struct CThostFtdcTransferBankToFutureReqField
{
	///期货资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///密码标志
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///转账金额
	TThostFtdcMoneyType	TradeAmt;
	///客户手续费
	TThostFtdcMoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///银行资金转期货请求响应
struct CThostFtdcTransferBankToFutureRspField
{
	///响应代码
	TThostFtdcRetCodeType	RetCode;
	///响应信息
	TThostFtdcRetInfoType	RetInfo;
	///资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///转帐金额
	TThostFtdcMoneyType	TradeAmt;
	///应收客户手续费
	TThostFtdcMoneyType	CustFee;
	///币种
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求，TradeCode=202002
struct CThostFtdcTransferFutureToBankReqField
{
	///期货资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///密码标志
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///转账金额
	TThostFtdcMoneyType	TradeAmt;
	///客户手续费
	TThostFtdcMoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求响应
struct CThostFtdcTransferFutureToBankRspField
{
	///响应代码
	TThostFtdcRetCodeType	RetCode;
	///响应信息
	TThostFtdcRetInfoType	RetInfo;
	///资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///转帐金额
	TThostFtdcMoneyType	TradeAmt;
	///应收客户手续费
	TThostFtdcMoneyType	CustFee;
	///币种
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行资金请求，TradeCode=204002
struct CThostFtdcTransferQryBankReqField
{
	///期货资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///密码标志
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行资金请求响应
struct CThostFtdcTransferQryBankRspField
{
	///响应代码
	TThostFtdcRetCodeType	RetCode;
	///响应信息
	TThostFtdcRetInfoType	RetInfo;
	///资金账户
	TThostFtdcAccountIDType	FutureAccount;
	///银行余额
	TThostFtdcMoneyType	TradeAmt;
	///银行可用余额
	TThostFtdcMoneyType	UseAmt;
	///银行可取余额
	TThostFtdcMoneyType	FetchAmt;
	///币种
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行交易明细请求，TradeCode=204999
struct CThostFtdcTransferQryDetailReqField
{
	///期货资金账户
	TThostFtdcAccountIDType	FutureAccount;
};

///查询银行交易明细请求响应
struct CThostFtdcTransferQryDetailRspField
{
	///交易日期
	TThostFtdcDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///交易代码
	TThostFtdcTradeCodeType	TradeCode;
	///期货流水号
	TThostFtdcTradeSerialNoType	FutureSerial;
	///期货公司代码
	TThostFtdcFutureIDType	FutureID;
	///资金帐号
	TThostFtdcFutureAccountType	FutureAccount;
	///银行流水号
	TThostFtdcTradeSerialNoType	BankSerial;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分中心代码
	TThostFtdcBankBrchIDType	BankBrchID;
	///银行账号
	TThostFtdcBankAccountType	BankAccount;
	///证件号码
	TThostFtdcCertCodeType	CertCode;
	///货币代码
	TThostFtdcCurrencyCodeType	CurrencyCode;
	///发生金额
	TThostFtdcMoneyType	TxAmount;
	///有效标志
	TThostFtdcTransferValidFlagType	Flag;
};

///响应信息
struct CThostFtdcRspInfoField
{
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///交易所
struct CThostFtdcExchangeField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TThostFtdcExchangeNameType	ExchangeName;
	///交易所属性
	TThostFtdcExchangePropertyType	ExchangeProperty;
};

///产品
struct CThostFtdcProductField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///产品名称
	TThostFtdcProductNameType	ProductName;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品类型
	TThostFtdcProductClassType	ProductClass;
	///合约数量乘数
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TThostFtdcPriceType	PriceTick;
	///市价单最大下单量
	TThostFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TThostFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TThostFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TThostFtdcVolumeType	MinLimitOrderVolume;
	///持仓类型
	TThostFtdcPositionTypeType	PositionType;
	///持仓日期类型
	TThostFtdcPositionDateTypeType	PositionDateType;
	///平仓处理类型
	TThostFtdcCloseDealTypeType	CloseDealType;
	///交易币种类型
	TThostFtdcCurrencyIDType	TradeCurrencyID;
	///质押资金可用范围
	TThostFtdcMortgageFundUseRangeType	MortgageFundUseRange;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///合约基础商品乘数
	TThostFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///交易所产品代码
	TThostFtdcInstrumentIDType	ExchangeProductID;
	///开仓量限制粒度
	TThostFtdcOpenLimitControlLevelType	OpenLimitControlLevel;
	///报单频率控制粒度
	TThostFtdcOrderFreqControlLevelType	OrderFreqControlLevel;
};

///合约
struct CThostFtdcInstrumentField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约名称
	TThostFtdcInstrumentNameType	InstrumentName;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve3;
	///产品类型
	TThostFtdcProductClassType	ProductClass;
	///交割年份
	TThostFtdcYearType	DeliveryYear;
	///交割月
	TThostFtdcMonthType	DeliveryMonth;
	///市价单最大下单量
	TThostFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TThostFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TThostFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TThostFtdcVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TThostFtdcPriceType	PriceTick;
	///创建日
	TThostFtdcDateType	CreateDate;
	///上市日
	TThostFtdcDateType	OpenDate;
	///到期日
	TThostFtdcDateType	ExpireDate;
	///开始交割日
	TThostFtdcDateType	StartDelivDate;
	///结束交割日
	TThostFtdcDateType	EndDelivDate;
	///合约生命周期状态
	TThostFtdcInstLifePhaseType	InstLifePhase;
	///当前是否交易
	TThostFtdcBoolType	IsTrading;
	///持仓类型
	TThostFtdcPositionTypeType	PositionType;
	///持仓日期类型
	TThostFtdcPositionDateTypeType	PositionDateType;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatio;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatio;
	///是否使用大额单边保证金算法
	TThostFtdcMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve4;
	///执行价
	TThostFtdcPriceType	StrikePrice;
	///期权类型
	TThostFtdcOptionsTypeType	OptionsType;
	///合约基础商品乘数
	TThostFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///组合类型
	TThostFtdcCombinationTypeType	CombinationType;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///基础商品代码
	TThostFtdcInstrumentIDType	UnderlyingInstrID;
};

///经纪公司
struct CThostFtdcBrokerField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///经纪公司简称
	TThostFtdcBrokerAbbrType	BrokerAbbr;
	///经纪公司名称
	TThostFtdcBrokerNameType	BrokerName;
	///是否活跃
	TThostFtdcBoolType	IsActive;
};

///交易所交易员
struct CThostFtdcTraderField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///密码
	TThostFtdcPasswordType	Password;
	///安装数量
	TThostFtdcInstallCountType	InstallCount;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///撤单时选择席位算法
	TThostFtdcOrderCancelAlgType	OrderCancelAlg;
	///交易报盘安装数量
	TThostFtdcInstallCountType	TradeInstallCount;
	///行情报盘安装数量
	TThostFtdcInstallCountType	MDInstallCount;
};

///投资者
struct CThostFtdcInvestorField
{
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TThostFtdcInvestorIDType	InvestorGroupID;
	///投资者名称
	TThostFtdcPartyNameType	InvestorName;
	///证件类型
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///联系电话
	TThostFtdcTelephoneType	Telephone;
	///通讯地址
	TThostFtdcAddressType	Address;
	///开户日期
	TThostFtdcDateType	OpenDate;
	///手机
	TThostFtdcMobileType	Mobile;
	///手续费率模板代码
	TThostFtdcInvestorIDType	CommModelID;
	///保证金率模板代码
	TThostFtdcInvestorIDType	MarginModelID;
	///是否频率控制
	TThostFtdcEnumBoolType	IsOrderFreq;
	///是否开仓限制
	TThostFtdcEnumBoolType	IsOpenVolLimit;
};

///交易编码
struct CThostFtdcTradingCodeField
{
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///交易编码类型
	TThostFtdcClientIDTypeType	ClientIDType;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///业务类型
	TThostFtdcBizTypeType	BizType;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///会员编码和经纪公司编码对照表
struct CThostFtdcPartBrokerField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///是否活跃
	TThostFtdcBoolType	IsActive;
};

///管理用户
struct CThostFtdcSuperUserField
{
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户名称
	TThostFtdcUserNameType	UserName;
	///密码
	TThostFtdcPasswordType	Password;
	///是否活跃
	TThostFtdcBoolType	IsActive;
};

///管理用户功能权限
struct CThostFtdcSuperUserFunctionField
{
	///用户代码
	TThostFtdcUserIDType	UserID;
	///功能代码
	TThostFtdcFunctionCodeType	FunctionCode;
};

///投资者组
struct CThostFtdcInvestorGroupField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TThostFtdcInvestorIDType	InvestorGroupID;
	///投资者分组名称
	TThostFtdcInvestorGroupNameType	InvestorGroupName;
};

///资金账户
struct CThostFtdcTradingAccountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///上次质押金额
	TThostFtdcMoneyType	PreMortgage;
	///上次信用额度
	TThostFtdcMoneyType	PreCredit;
	///上次存款额
	TThostFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TThostFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///利息基数
	TThostFtdcMoneyType	InterestBase;
	///利息收入
	TThostFtdcMoneyType	Interest;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///出金金额
	TThostFtdcMoneyType	Withdraw;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TThostFtdcMoneyType	CurrMargin;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///期货结算准备金
	TThostFtdcMoneyType	Balance;
	///可用资金
	TThostFtdcMoneyType	Available;
	///可取资金
	TThostFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TThostFtdcMoneyType	Reserve;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///信用额度
	TThostFtdcMoneyType	Credit;
	///质押金额
	TThostFtdcMoneyType	Mortgage;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TThostFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TThostFtdcMoneyType	ExchangeDeliveryMargin;
	///保底期货结算准备金
	TThostFtdcMoneyType	ReserveBalance;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///上次货币质入金额
	TThostFtdcMoneyType	PreFundMortgageIn;
	///上次货币质出金额
	TThostFtdcMoneyType	PreFundMortgageOut;
	///货币质入金额
	TThostFtdcMoneyType	FundMortgageIn;
	///货币质出金额
	TThostFtdcMoneyType	FundMortgageOut;
	///货币质押余额
	TThostFtdcMoneyType	FundMortgageAvailable;
	///可质押货币金额
	TThostFtdcMoneyType	MortgageableFund;
	///特殊产品占用保证金
	TThostFtdcMoneyType	SpecProductMargin;
	///特殊产品冻结保证金
	TThostFtdcMoneyType	SpecProductFrozenMargin;
	///特殊产品手续费
	TThostFtdcMoneyType	SpecProductCommission;
	///特殊产品冻结手续费
	TThostFtdcMoneyType	SpecProductFrozenCommission;
	///特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfit;
	///特殊产品平仓盈亏
	TThostFtdcMoneyType	SpecProductCloseProfit;
	///根据持仓盈亏算法计算的特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfitByAlg;
	///特殊产品交易所保证金
	TThostFtdcMoneyType	SpecProductExchangeMargin;
	///业务类型
	TThostFtdcBizTypeType	BizType;
	///延时换汇冻结金额
	TThostFtdcMoneyType	FrozenSwap;
	///剩余换汇额度
	TThostFtdcMoneyType	RemainSwap;
};

///投资者持仓
struct CThostFtdcInvestorPositionField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TThostFtdcPositionDateType	PositionDate;
	///上日持仓
	TThostFtdcVolumeType	YdPosition;
	///今日持仓
	TThostFtdcVolumeType	Position;
	///多头冻结
	TThostFtdcVolumeType	LongFrozen;
	///空头冻结
	TThostFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TThostFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TThostFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TThostFtdcVolumeType	OpenVolume;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///开仓金额
	TThostFtdcMoneyType	OpenAmount;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///持仓成本
	TThostFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///占用的保证金
	TThostFtdcMoneyType	UseMargin;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///开仓成本
	TThostFtdcMoneyType	OpenCost;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TThostFtdcVolumeType	CombPosition;
	///组合多头冻结
	TThostFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TThostFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TThostFtdcVolumeType	TodayPosition;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///执行冻结
	TThostFtdcVolumeType	StrikeFrozen;
	///执行冻结金额
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	TThostFtdcVolumeType	AbandonFrozen;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行冻结的昨仓
	TThostFtdcVolumeType	YdStrikeFrozen;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///持仓成本差值
	TThostFtdcMoneyType	PositionCostOffset;
	///tas持仓手数
	TThostFtdcVolumeType	TasPosition;
	///tas持仓成本
	TThostFtdcMoneyType	TasPositionCost;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///合约保证金率
struct CThostFtdcInstrumentMarginRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TThostFtdcBoolType	IsRelative;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///合约手续费率
struct CThostFtdcInstrumentCommissionRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///业务类型
	TThostFtdcBizTypeType	BizType;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///深度行情
struct CThostFtdcDepthMarketDataField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///最新价
	TThostFtdcPriceType	LastPrice;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TThostFtdcPriceType	PreClosePrice;
	///昨持仓量
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TThostFtdcPriceType	OpenPrice;
	///最高价
	TThostFtdcPriceType	HighestPrice;
	///最低价
	TThostFtdcPriceType	LowestPrice;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交金额
	TThostFtdcMoneyType	Turnover;
	///持仓量
	TThostFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TThostFtdcPriceType	ClosePrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///涨停板价
	TThostFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TThostFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TThostFtdcRatioType	PreDelta;
	///今虚实度
	TThostFtdcRatioType	CurrDelta;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TThostFtdcMillisecType	UpdateMillisec;
	///申买价一
	TThostFtdcPriceType	BidPrice1;
	///申买量一
	TThostFtdcVolumeType	BidVolume1;
	///申卖价一
	TThostFtdcPriceType	AskPrice1;
	///申卖量一
	TThostFtdcVolumeType	AskVolume1;
	///申买价二
	TThostFtdcPriceType	BidPrice2;
	///申买量二
	TThostFtdcVolumeType	BidVolume2;
	///申卖价二
	TThostFtdcPriceType	AskPrice2;
	///申卖量二
	TThostFtdcVolumeType	AskVolume2;
	///申买价三
	TThostFtdcPriceType	BidPrice3;
	///申买量三
	TThostFtdcVolumeType	BidVolume3;
	///申卖价三
	TThostFtdcPriceType	AskPrice3;
	///申卖量三
	TThostFtdcVolumeType	AskVolume3;
	///申买价四
	TThostFtdcPriceType	BidPrice4;
	///申买量四
	TThostFtdcVolumeType	BidVolume4;
	///申卖价四
	TThostFtdcPriceType	AskPrice4;
	///申卖量四
	TThostFtdcVolumeType	AskVolume4;
	///申买价五
	TThostFtdcPriceType	BidPrice5;
	///申买量五
	TThostFtdcVolumeType	BidVolume5;
	///申卖价五
	TThostFtdcPriceType	AskPrice5;
	///申卖量五
	TThostFtdcVolumeType	AskVolume5;
	///当日均价
	TThostFtdcPriceType	AveragePrice;
	///业务日期
	TThostFtdcDateType	ActionDay;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///上带价
	TThostFtdcPriceType	BandingUpperPrice;
	///下带价
	TThostFtdcPriceType	BandingLowerPrice;
};

///投资者合约交易权限
struct CThostFtdcInstrumentTradingRightField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易权限
	TThostFtdcTradingRightType	TradingRight;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///经纪公司用户
struct CThostFtdcBrokerUserField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户名称
	TThostFtdcUserNameType	UserName;
	///用户类型
	TThostFtdcUserTypeType	UserType;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///是否使用令牌
	TThostFtdcBoolType	IsUsingOTP;
	///是否强制终端认证
	TThostFtdcBoolType	IsAuthForce;
};

///经纪公司用户口令
struct CThostFtdcBrokerUserPasswordField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///上次修改时间
	TThostFtdcDateTimeType	LastUpdateTime;
	///上次登陆时间
	TThostFtdcDateTimeType	LastLoginTime;
	///密码过期时间
	TThostFtdcDateType	ExpireDate;
	///弱密码过期时间
	TThostFtdcDateType	WeakExpireDate;
};

///经纪公司用户功能权限
struct CThostFtdcBrokerUserFunctionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///经纪公司功能代码
	TThostFtdcBrokerFunctionCodeType	BrokerFunctionCode;
};

///交易所交易员报盘机
struct CThostFtdcTraderOfferField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TThostFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TThostFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TThostFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TThostFtdcDateType	LastReportDate;
	///上次报告时间
	TThostFtdcTimeType	LastReportTime;
	///完成连接日期
	TThostFtdcDateType	ConnectDate;
	///完成连接时间
	TThostFtdcTimeType	ConnectTime;
	///启动日期
	TThostFtdcDateType	StartDate;
	///启动时间
	TThostFtdcTimeType	StartTime;
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///本席位最大成交编号
	TThostFtdcTradeIDType	MaxTradeID;
	///本席位最大报单备拷
	TThostFtdcReturnCodeType	MaxOrderMessageReference;
	///撤单时选择席位算法
	TThostFtdcOrderCancelAlgType	OrderCancelAlg;
};

///投资者结算结果
struct CThostFtdcSettlementInfoField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///消息正文
	TThostFtdcContentType	Content;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///合约保证金率调整
struct CThostFtdcInstrumentMarginRateAdjustField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TThostFtdcBoolType	IsRelative;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所保证金率
struct CThostFtdcExchangeMarginRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所保证金率调整
struct CThostFtdcExchangeMarginRateAdjustField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///跟随交易所投资者多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///跟随交易所投资者多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///跟随交易所投资者空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///跟随交易所投资者空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///交易所多头保证金率
	TThostFtdcRatioType	ExchLongMarginRatioByMoney;
	///交易所多头保证金费
	TThostFtdcMoneyType	ExchLongMarginRatioByVolume;
	///交易所空头保证金率
	TThostFtdcRatioType	ExchShortMarginRatioByMoney;
	///交易所空头保证金费
	TThostFtdcMoneyType	ExchShortMarginRatioByVolume;
	///不跟随交易所投资者多头保证金率
	TThostFtdcRatioType	NoLongMarginRatioByMoney;
	///不跟随交易所投资者多头保证金费
	TThostFtdcMoneyType	NoLongMarginRatioByVolume;
	///不跟随交易所投资者空头保证金率
	TThostFtdcRatioType	NoShortMarginRatioByMoney;
	///不跟随交易所投资者空头保证金费
	TThostFtdcMoneyType	NoShortMarginRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///汇率
struct CThostFtdcExchangeRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///源币种
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///源币种单位数量
	TThostFtdcCurrencyUnitType	FromCurrencyUnit;
	///目标币种
	TThostFtdcCurrencyIDType	ToCurrencyID;
	///汇率
	TThostFtdcExchangeRateType	ExchangeRate;
};

///结算引用
struct CThostFtdcSettlementRefField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
};

///当前时间
struct CThostFtdcCurrentTimeField
{
	///当前交易日
	TThostFtdcDateType	CurrDate;
	///当前时间
	TThostFtdcTimeType	CurrTime;
	///当前时间（毫秒）
	TThostFtdcMillisecType	CurrMillisec;
	///自然日期
	TThostFtdcDateType	ActionDay;
};

///通讯阶段
struct CThostFtdcCommPhaseField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///通讯时段编号
	TThostFtdcCommPhaseNoType	CommPhaseNo;
	///系统编号
	TThostFtdcSystemIDType	SystemID;
};

///登录信息
struct CThostFtdcLoginInfoField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///登录日期
	TThostFtdcDateType	LoginDate;
	///登录时间
	TThostFtdcTimeType	LoginTime;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///系统名称
	TThostFtdcSystemNameType	SystemName;
	///密码,已弃用
	TThostFtdcPasswordType	PasswordDeprecated;
	///最大报单引用
	TThostFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TThostFtdcTimeType	SHFETime;
	///大商所时间
	TThostFtdcTimeType	DCETime;
	///郑商所时间
	TThostFtdcTimeType	CZCETime;
	///中金所时间
	TThostFtdcTimeType	FFEXTime;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///动态密码
	TThostFtdcPasswordType	OneTimePassword;
	///能源中心时间
	TThostFtdcTimeType	INETime;
	///查询时是否需要流控
	TThostFtdcBoolType	IsQryControl;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///密码
	TThostFtdcPasswordType	Password;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///登录信息
struct CThostFtdcLogoutAllField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///系统名称
	TThostFtdcSystemNameType	SystemName;
};

///前置状态
struct CThostFtdcFrontStatusField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///上次报告日期
	TThostFtdcDateType	LastReportDate;
	///上次报告时间
	TThostFtdcTimeType	LastReportTime;
	///是否活跃
	TThostFtdcBoolType	IsActive;
};

///用户口令变更
struct CThostFtdcUserPasswordUpdateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///原来的口令
	TThostFtdcPasswordType	OldPassword;
	///新的口令
	TThostFtdcPasswordType	NewPassword;
};

///输入报单
struct CThostFtdcInputOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///用户强平标志
	TThostFtdcBoolType	UserForceClose;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///报单
struct CThostFtdcOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TThostFtdcOrderSourceType	OrderSource;
	///报单状态
	TThostFtdcOrderStatusType	OrderStatus;
	///报单类型
	TThostFtdcOrderTypeType	OrderType;
	///今成交数量
	TThostFtdcVolumeType	VolumeTraded;
	///剩余数量
	TThostFtdcVolumeType	VolumeTotal;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///委托时间
	TThostFtdcTimeType	InsertTime;
	///激活时间
	TThostFtdcTimeType	ActiveTime;
	///挂起时间
	TThostFtdcTimeType	SuspendTime;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TThostFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///用户强平标志
	TThostFtdcBoolType	UserForceClose;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///郑商所成交数量
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///交易所报单
struct CThostFtdcExchangeOrderField
{
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TThostFtdcOrderSourceType	OrderSource;
	///报单状态
	TThostFtdcOrderStatusType	OrderStatus;
	///报单类型
	TThostFtdcOrderTypeType	OrderType;
	///今成交数量
	TThostFtdcVolumeType	VolumeTraded;
	///剩余数量
	TThostFtdcVolumeType	VolumeTotal;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///委托时间
	TThostFtdcTimeType	InsertTime;
	///激活时间
	TThostFtdcTimeType	ActiveTime;
	///挂起时间
	TThostFtdcTimeType	SuspendTime;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TThostFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所报单插入失败
struct CThostFtdcExchangeOrderInsertErrorField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///输入报单操作
struct CThostFtdcInputOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量变化
	TThostFtdcVolumeType	VolumeChange;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///报单操作
struct CThostFtdcOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量变化
	TThostFtdcVolumeType	VolumeChange;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///交易所报单操作
struct CThostFtdcExchangeOrderActionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量变化
	TThostFtdcVolumeType	VolumeChange;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所报单操作失败
struct CThostFtdcExchangeOrderActionErrorField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///交易所成交
struct CThostFtdcExchangeTradeField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///成交编号
	TThostFtdcTradeIDType	TradeID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易角色
	TThostFtdcTradingRoleType	TradingRole;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///价格
	TThostFtdcPriceType	Price;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交时期
	TThostFtdcDateType	TradeDate;
	///成交时间
	TThostFtdcTimeType	TradeTime;
	///成交类型
	TThostFtdcTradeTypeType	TradeType;
	///成交价来源
	TThostFtdcPriceSourceType	PriceSource;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///成交来源
	TThostFtdcTradeSourceType	TradeSource;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///成交
struct CThostFtdcTradeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///成交编号
	TThostFtdcTradeIDType	TradeID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易角色
	TThostFtdcTradingRoleType	TradingRole;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///价格
	TThostFtdcPriceType	Price;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交时期
	TThostFtdcDateType	TradeDate;
	///成交时间
	TThostFtdcTimeType	TradeTime;
	///成交类型
	TThostFtdcTradeTypeType	TradeType;
	///成交价来源
	TThostFtdcPriceSourceType	PriceSource;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///成交来源
	TThostFtdcTradeSourceType	TradeSource;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///用户会话
struct CThostFtdcUserSessionField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///登录日期
	TThostFtdcDateType	LoginDate;
	///登录时间
	TThostFtdcTimeType	LoginTime;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询最大报单数量
struct CThostFtdcQryMaxOrderVolumeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///最大允许报单数量
	TThostFtdcVolumeType	MaxVolume;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///投资者结算结果确认信息
struct CThostFtdcSettlementInfoConfirmField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///确认日期
	TThostFtdcDateType	ConfirmDate;
	///确认时间
	TThostFtdcTimeType	ConfirmTime;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///出入金同步
struct CThostFtdcSyncDepositField
{
	///出入金流水号
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///是否强制进行
	TThostFtdcBoolType	IsForce;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///是否是个股期权内转
	TThostFtdcBoolType	IsFromSopt;
	///资金密码
	TThostFtdcPasswordType	TradingPassword;
	///是否二级代理商的内转
	TThostFtdcBoolType	IsSecAgentTranfer;
};

///货币质押同步
struct CThostFtdcSyncFundMortgageField
{
	///货币质押流水号
	TThostFtdcDepositSeqNoType	MortgageSeqNo;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///源币种
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///质押金额
	TThostFtdcMoneyType	MortgageAmount;
	///目标币种
	TThostFtdcCurrencyIDType	ToCurrencyID;
};

///经纪公司同步
struct CThostFtdcBrokerSyncField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///正在同步中的投资者
struct CThostFtdcSyncingInvestorField
{
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TThostFtdcInvestorIDType	InvestorGroupID;
	///投资者名称
	TThostFtdcPartyNameType	InvestorName;
	///证件类型
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///联系电话
	TThostFtdcTelephoneType	Telephone;
	///通讯地址
	TThostFtdcAddressType	Address;
	///开户日期
	TThostFtdcDateType	OpenDate;
	///手机
	TThostFtdcMobileType	Mobile;
	///手续费率模板代码
	TThostFtdcInvestorIDType	CommModelID;
	///保证金率模板代码
	TThostFtdcInvestorIDType	MarginModelID;
	///是否频率控制
	TThostFtdcEnumBoolType	IsOrderFreq;
	///是否开仓限制
	TThostFtdcEnumBoolType	IsOpenVolLimit;
};

///正在同步中的交易代码
struct CThostFtdcSyncingTradingCodeField
{
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///交易编码类型
	TThostFtdcClientIDTypeType	ClientIDType;
};

///正在同步中的投资者分组
struct CThostFtdcSyncingInvestorGroupField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TThostFtdcInvestorIDType	InvestorGroupID;
	///投资者分组名称
	TThostFtdcInvestorGroupNameType	InvestorGroupName;
};

///正在同步中的交易账号
struct CThostFtdcSyncingTradingAccountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///上次质押金额
	TThostFtdcMoneyType	PreMortgage;
	///上次信用额度
	TThostFtdcMoneyType	PreCredit;
	///上次存款额
	TThostFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TThostFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///利息基数
	TThostFtdcMoneyType	InterestBase;
	///利息收入
	TThostFtdcMoneyType	Interest;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///出金金额
	TThostFtdcMoneyType	Withdraw;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TThostFtdcMoneyType	CurrMargin;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///期货结算准备金
	TThostFtdcMoneyType	Balance;
	///可用资金
	TThostFtdcMoneyType	Available;
	///可取资金
	TThostFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TThostFtdcMoneyType	Reserve;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///信用额度
	TThostFtdcMoneyType	Credit;
	///质押金额
	TThostFtdcMoneyType	Mortgage;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TThostFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TThostFtdcMoneyType	ExchangeDeliveryMargin;
	///保底期货结算准备金
	TThostFtdcMoneyType	ReserveBalance;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///上次货币质入金额
	TThostFtdcMoneyType	PreFundMortgageIn;
	///上次货币质出金额
	TThostFtdcMoneyType	PreFundMortgageOut;
	///货币质入金额
	TThostFtdcMoneyType	FundMortgageIn;
	///货币质出金额
	TThostFtdcMoneyType	FundMortgageOut;
	///货币质押余额
	TThostFtdcMoneyType	FundMortgageAvailable;
	///可质押货币金额
	TThostFtdcMoneyType	MortgageableFund;
	///特殊产品占用保证金
	TThostFtdcMoneyType	SpecProductMargin;
	///特殊产品冻结保证金
	TThostFtdcMoneyType	SpecProductFrozenMargin;
	///特殊产品手续费
	TThostFtdcMoneyType	SpecProductCommission;
	///特殊产品冻结手续费
	TThostFtdcMoneyType	SpecProductFrozenCommission;
	///特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfit;
	///特殊产品平仓盈亏
	TThostFtdcMoneyType	SpecProductCloseProfit;
	///根据持仓盈亏算法计算的特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfitByAlg;
	///特殊产品交易所保证金
	TThostFtdcMoneyType	SpecProductExchangeMargin;
	///延时换汇冻结金额
	TThostFtdcMoneyType	FrozenSwap;
	///剩余换汇额度
	TThostFtdcMoneyType	RemainSwap;
};

///正在同步中的投资者持仓
struct CThostFtdcSyncingInvestorPositionField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TThostFtdcPositionDateType	PositionDate;
	///上日持仓
	TThostFtdcVolumeType	YdPosition;
	///今日持仓
	TThostFtdcVolumeType	Position;
	///多头冻结
	TThostFtdcVolumeType	LongFrozen;
	///空头冻结
	TThostFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TThostFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TThostFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TThostFtdcVolumeType	OpenVolume;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///开仓金额
	TThostFtdcMoneyType	OpenAmount;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///持仓成本
	TThostFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///占用的保证金
	TThostFtdcMoneyType	UseMargin;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///开仓成本
	TThostFtdcMoneyType	OpenCost;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TThostFtdcVolumeType	CombPosition;
	///组合多头冻结
	TThostFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TThostFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TThostFtdcVolumeType	TodayPosition;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///执行冻结
	TThostFtdcVolumeType	StrikeFrozen;
	///执行冻结金额
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	TThostFtdcVolumeType	AbandonFrozen;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行冻结的昨仓
	TThostFtdcVolumeType	YdStrikeFrozen;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///持仓成本差值
	TThostFtdcMoneyType	PositionCostOffset;
	///tas持仓手数
	TThostFtdcVolumeType	TasPosition;
	///tas持仓成本
	TThostFtdcMoneyType	TasPositionCost;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///正在同步中的合约保证金率
struct CThostFtdcSyncingInstrumentMarginRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TThostFtdcBoolType	IsRelative;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///正在同步中的合约手续费率
struct CThostFtdcSyncingInstrumentCommissionRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///正在同步中的合约交易权限
struct CThostFtdcSyncingInstrumentTradingRightField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易权限
	TThostFtdcTradingRightType	TradingRight;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询报单
struct CThostFtdcQryOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询成交
struct CThostFtdcQryTradeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///成交编号
	TThostFtdcTradeIDType	TradeID;
	///开始时间
	TThostFtdcTimeType	TradeTimeStart;
	///结束时间
	TThostFtdcTimeType	TradeTimeEnd;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询投资者持仓
struct CThostFtdcQryInvestorPositionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询资金账户
struct CThostFtdcQryTradingAccountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///业务类型
	TThostFtdcBizTypeType	BizType;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
};

///查询投资者
struct CThostFtdcQryInvestorField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///查询交易编码
struct CThostFtdcQryTradingCodeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易编码类型
	TThostFtdcClientIDTypeType	ClientIDType;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///查询投资者组
struct CThostFtdcQryInvestorGroupField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///查询合约保证金率
struct CThostFtdcQryInstrumentMarginRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询手续费率
struct CThostFtdcQryInstrumentCommissionRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询合约交易权限
struct CThostFtdcQryInstrumentTradingRightField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询经纪公司
struct CThostFtdcQryBrokerField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///查询交易员
struct CThostFtdcQryTraderField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///查询管理用户功能权限
struct CThostFtdcQrySuperUserFunctionField
{
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///查询用户会话
struct CThostFtdcQryUserSessionField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///查询经纪公司会员代码
struct CThostFtdcQryPartBrokerField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
};

///查询前置状态
struct CThostFtdcQryFrontStatusField
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
};

///查询交易所报单
struct CThostFtdcQryExchangeOrderField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///查询报单操作
struct CThostFtdcQryOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///查询交易所报单操作
struct CThostFtdcQryExchangeOrderActionField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///查询管理用户
struct CThostFtdcQrySuperUserField
{
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///查询交易所
struct CThostFtdcQryExchangeField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///查询产品
struct CThostFtdcQryProductField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///产品类型
	TThostFtdcProductClassType	ProductClass;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///查询合约
struct CThostFtdcQryInstrumentField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve3;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///查询行情
struct CThostFtdcQryDepthMarketDataField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///产品类型
	TThostFtdcProductClassType	ProductClass;
};

///查询经纪公司用户
struct CThostFtdcQryBrokerUserField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///查询经纪公司用户权限
struct CThostFtdcQryBrokerUserFunctionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///查询交易员报盘机
struct CThostFtdcQryTraderOfferField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///查询出入金流水
struct CThostFtdcQrySyncDepositField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///出入金流水号
	TThostFtdcDepositSeqNoType	DepositSeqNo;
};

///查询投资者结算结果
struct CThostFtdcQrySettlementInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易日
	TThostFtdcDateType	TradingDay;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///查询交易所保证金率
struct CThostFtdcQryExchangeMarginRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询交易所调整保证金率
struct CThostFtdcQryExchangeMarginRateAdjustField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询汇率
struct CThostFtdcQryExchangeRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///源币种
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///目标币种
	TThostFtdcCurrencyIDType	ToCurrencyID;
};

///查询货币质押流水
struct CThostFtdcQrySyncFundMortgageField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///货币质押流水号
	TThostFtdcDepositSeqNoType	MortgageSeqNo;
};

///查询报单
struct CThostFtdcQryHisOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前期权合约最小保证金
struct CThostFtdcOptionInstrMiniMarginField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///单位（手）期权合约最小保证金
	TThostFtdcMoneyType	MinMargin;
	///取值方式
	TThostFtdcValueMethodType	ValueMethod;
	///是否跟随交易所收取
	TThostFtdcBoolType	IsRelative;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前期权合约保证金调整系数
struct CThostFtdcOptionInstrMarginAdjustField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机空头保证金调整系数
	TThostFtdcRatioType	SShortMarginRatioByMoney;
	///投机空头保证金调整系数
	TThostFtdcMoneyType	SShortMarginRatioByVolume;
	///保值空头保证金调整系数
	TThostFtdcRatioType	HShortMarginRatioByMoney;
	///保值空头保证金调整系数
	TThostFtdcMoneyType	HShortMarginRatioByVolume;
	///套利空头保证金调整系数
	TThostFtdcRatioType	AShortMarginRatioByMoney;
	///套利空头保证金调整系数
	TThostFtdcMoneyType	AShortMarginRatioByVolume;
	///是否跟随交易所收取
	TThostFtdcBoolType	IsRelative;
	///做市商空头保证金调整系数
	TThostFtdcRatioType	MShortMarginRatioByMoney;
	///做市商空头保证金调整系数
	TThostFtdcMoneyType	MShortMarginRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前期权合约手续费的详细内容
struct CThostFtdcOptionInstrCommRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///执行手续费率
	TThostFtdcRatioType	StrikeRatioByMoney;
	///执行手续费
	TThostFtdcRatioType	StrikeRatioByVolume;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///期权交易成本
struct CThostFtdcOptionInstrTradeCostField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///期权合约保证金不变部分
	TThostFtdcMoneyType	FixedMargin;
	///期权合约最小保证金
	TThostFtdcMoneyType	MiniMargin;
	///期权合约权利金
	TThostFtdcMoneyType	Royalty;
	///交易所期权合约保证金不变部分
	TThostFtdcMoneyType	ExchFixedMargin;
	///交易所期权合约最小保证金
	TThostFtdcMoneyType	ExchMiniMargin;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///期权交易成本查询
struct CThostFtdcQryOptionInstrTradeCostField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///期权合约报价
	TThostFtdcPriceType	InputPrice;
	///标的价格,填0则用昨结算价
	TThostFtdcPriceType	UnderlyingPrice;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///期权手续费率查询
struct CThostFtdcQryOptionInstrCommRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///股指现货指数
struct CThostFtdcIndexPriceField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///指数现货收盘价
	TThostFtdcPriceType	ClosePrice;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///输入的执行宣告
struct CThostFtdcInputExecOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记,该字段已废弃
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///输入执行宣告操作
struct CThostFtdcInputExecOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///执行宣告操作引用
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行宣告操作编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///执行宣告
struct CThostFtdcExecOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记,该字段已废弃
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///本地执行宣告编号
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///执行宣告提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///执行宣告编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///执行结果
	TThostFtdcExecResultType	ExecResult;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerExecOrderSeq;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///执行宣告操作
struct CThostFtdcExecOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///执行宣告操作引用
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行宣告操作编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地执行宣告编号
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///执行宣告查询
struct CThostFtdcQryExecOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行宣告编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所执行宣告信息
struct CThostFtdcExchangeExecOrderField
{
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记,该字段已废弃
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///本地执行宣告编号
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///执行宣告提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///执行宣告编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///执行结果
	TThostFtdcExecResultType	ExecResult;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所执行宣告查询
struct CThostFtdcQryExchangeExecOrderField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///执行宣告操作查询
struct CThostFtdcQryExecOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///交易所执行宣告操作
struct CThostFtdcExchangeExecOrderActionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行宣告操作编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地执行宣告编号
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///数量
	TThostFtdcVolumeType	Volume;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///交易所执行宣告操作查询
struct CThostFtdcQryExchangeExecOrderActionField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///错误执行宣告
struct CThostFtdcErrExecOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///执行类型
	TThostFtdcActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记,该字段已废弃
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询错误执行宣告
struct CThostFtdcQryErrExecOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///错误执行宣告操作
struct CThostFtdcErrExecOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///执行宣告操作引用
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	TThostFtdcOrderRefType	ExecOrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行宣告操作编号
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询错误执行宣告操作
struct CThostFtdcQryErrExecOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///投资者期权合约交易权限
struct CThostFtdcOptionInstrTradingRightField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///交易权限
	TThostFtdcTradingRightType	TradingRight;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询期权合约交易权限
struct CThostFtdcQryOptionInstrTradingRightField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///输入的询价
struct CThostFtdcInputForQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///询价引用
	TThostFtdcOrderRefType	ForQuoteRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///询价
struct CThostFtdcForQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///询价引用
	TThostFtdcOrderRefType	ForQuoteRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///本地询价编号
	TThostFtdcOrderLocalIDType	ForQuoteLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///询价状态
	TThostFtdcForQuoteStatusType	ForQuoteStatus;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司询价编号
	TThostFtdcSequenceNoType	BrokerForQutoSeq;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///询价查询
struct CThostFtdcQryForQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所询价信息
struct CThostFtdcExchangeForQuoteField
{
	///本地询价编号
	TThostFtdcOrderLocalIDType	ForQuoteLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///询价状态
	TThostFtdcForQuoteStatusType	ForQuoteStatus;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所询价查询
struct CThostFtdcQryExchangeForQuoteField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///输入的报价
struct CThostFtdcInputQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报价引用
	TThostFtdcOrderRefType	QuoteRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///卖价格
	TThostFtdcPriceType	AskPrice;
	///买价格
	TThostFtdcPriceType	BidPrice;
	///卖数量
	TThostFtdcVolumeType	AskVolume;
	///买数量
	TThostFtdcVolumeType	BidVolume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///卖开平标志
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///买开平标志
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///衍生卖报单引用
	TThostFtdcOrderRefType	AskOrderRef;
	///衍生买报单引用
	TThostFtdcOrderRefType	BidOrderRef;
	///应价编号
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///被顶单编号
	TThostFtdcOrderSysIDType	ReplaceSysID;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///输入报价操作
struct CThostFtdcInputQuoteActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报价操作引用
	TThostFtdcOrderActionRefType	QuoteActionRef;
	///报价引用
	TThostFtdcOrderRefType	QuoteRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报价操作编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///报价
struct CThostFtdcQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报价引用
	TThostFtdcOrderRefType	QuoteRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///卖价格
	TThostFtdcPriceType	AskPrice;
	///买价格
	TThostFtdcPriceType	BidPrice;
	///卖数量
	TThostFtdcVolumeType	AskVolume;
	///买数量
	TThostFtdcVolumeType	BidVolume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///卖开平标志
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///买开平标志
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///本地报价编号
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报价提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///报价提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报价编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///报价状态
	TThostFtdcOrderStatusType	QuoteStatus;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///卖方报单编号
	TThostFtdcOrderSysIDType	AskOrderSysID;
	///买方报单编号
	TThostFtdcOrderSysIDType	BidOrderSysID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报价编号
	TThostFtdcSequenceNoType	BrokerQuoteSeq;
	///衍生卖报单引用
	TThostFtdcOrderRefType	AskOrderRef;
	///衍生买报单引用
	TThostFtdcOrderRefType	BidOrderRef;
	///应价编号
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///被顶单编号
	TThostFtdcOrderSysIDType	ReplaceSysID;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///报价操作
struct CThostFtdcQuoteActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报价操作引用
	TThostFtdcOrderActionRefType	QuoteActionRef;
	///报价引用
	TThostFtdcOrderRefType	QuoteRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报价操作编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报价编号
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///报价查询
struct CThostFtdcQryQuoteField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报价编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所报价信息
struct CThostFtdcExchangeQuoteField
{
	///卖价格
	TThostFtdcPriceType	AskPrice;
	///买价格
	TThostFtdcPriceType	BidPrice;
	///卖数量
	TThostFtdcVolumeType	AskVolume;
	///买数量
	TThostFtdcVolumeType	BidVolume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///卖开平标志
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///买开平标志
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///本地报价编号
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报价提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///报价提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报价编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///报价状态
	TThostFtdcOrderStatusType	QuoteStatus;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///卖方报单编号
	TThostFtdcOrderSysIDType	AskOrderSysID;
	///买方报单编号
	TThostFtdcOrderSysIDType	BidOrderSysID;
	///应价编号
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
};

///交易所报价查询
struct CThostFtdcQryExchangeQuoteField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///报价操作查询
struct CThostFtdcQryQuoteActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///交易所报价操作
struct CThostFtdcExchangeQuoteActionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报价操作编号
	TThostFtdcOrderSysIDType	QuoteSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报价编号
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所报价操作查询
struct CThostFtdcQryExchangeQuoteActionField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///期权合约delta值
struct CThostFtdcOptionInstrDeltaField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///Delta值
	TThostFtdcRatioType	Delta;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///发给做市商的询价请求
struct CThostFtdcForQuoteRspField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///询价编号
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///询价时间
	TThostFtdcTimeType	ForQuoteTime;
	///业务日期
	TThostFtdcDateType	ActionDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前期权合约执行偏移值的详细内容
struct CThostFtdcStrikeOffsetField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///执行偏移值
	TThostFtdcMoneyType	Offset;
	///执行偏移类型
	TThostFtdcStrikeOffsetTypeType	OffsetType;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///期权执行偏移值查询
struct CThostFtdcQryStrikeOffsetField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///输入批量报单操作
struct CThostFtdcInputBatchOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///批量报单操作
struct CThostFtdcBatchOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所批量报单操作
struct CThostFtdcExchangeBatchOrderActionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询批量报单操作
struct CThostFtdcQryBatchOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///组合合约安全系数
struct CThostFtdcCombInstrumentGuardField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///
	TThostFtdcRatioType	GuarantRatio;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///组合合约安全系数查询
struct CThostFtdcQryCombInstrumentGuardField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///输入的申请组合
struct CThostFtdcInputCombActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///组合引用
	TThostFtdcOrderRefType	CombActionRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///数量
	TThostFtdcVolumeType	Volume;
	///组合指令方向
	TThostFtdcCombDirectionType	CombDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///申请组合
struct CThostFtdcCombActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///组合引用
	TThostFtdcOrderRefType	CombActionRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///数量
	TThostFtdcVolumeType	Volume;
	///组合指令方向
	TThostFtdcCombDirectionType	CombDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///本地申请组合编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///组合状态
	TThostFtdcOrderActionStatusType	ActionStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///组合编号
	TThostFtdcTradeIDType	ComTradeID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///申请组合查询
struct CThostFtdcQryCombActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所申请组合信息
struct CThostFtdcExchangeCombActionField
{
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///数量
	TThostFtdcVolumeType	Volume;
	///组合指令方向
	TThostFtdcCombDirectionType	CombDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///本地申请组合编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///组合状态
	TThostFtdcOrderActionStatusType	ActionStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///组合编号
	TThostFtdcTradeIDType	ComTradeID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///交易所申请组合查询
struct CThostFtdcQryExchangeCombActionField
{
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///产品报价汇率
struct CThostFtdcProductExchRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报价币种类型
	TThostFtdcCurrencyIDType	QuoteCurrencyID;
	///汇率
	TThostFtdcExchangeRateType	ExchangeRate;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///产品报价汇率查询
struct CThostFtdcQryProductExchRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///查询询价价差参数
struct CThostFtdcQryForQuoteParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///询价价差参数
struct CThostFtdcForQuoteParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///最新价
	TThostFtdcPriceType	LastPrice;
	///价差
	TThostFtdcPriceType	PriceInterval;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前做市商期权合约手续费的详细内容
struct CThostFtdcMMOptionInstrCommRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///执行手续费率
	TThostFtdcRatioType	StrikeRatioByMoney;
	///执行手续费
	TThostFtdcRatioType	StrikeRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///做市商期权手续费率查询
struct CThostFtdcQryMMOptionInstrCommRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///做市商合约手续费率
struct CThostFtdcMMInstrumentCommissionRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询做市商合约手续费率
struct CThostFtdcQryMMInstrumentCommissionRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///当前报单手续费的详细内容
struct CThostFtdcInstrumentOrderCommRateField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///报单手续费
	TThostFtdcRatioType	OrderCommByVolume;
	///撤单手续费
	TThostFtdcRatioType	OrderActionCommByVolume;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///报单手续费
	TThostFtdcRatioType	OrderCommByTrade;
	///撤单手续费
	TThostFtdcRatioType	OrderActionCommByTrade;
};

///报单手续费率查询
struct CThostFtdcQryInstrumentOrderCommRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易参数
struct CThostFtdcTradeParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///参数代码
	TThostFtdcTradeParamIDType	TradeParamID;
	///参数代码值
	TThostFtdcSettlementParamValueType	TradeParamValue;
	///备注
	TThostFtdcMemoType	Memo;
};

///合约保证金率调整
struct CThostFtdcInstrumentMarginRateULField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///期货持仓限制参数
struct CThostFtdcFutureLimitPosiParamField
{
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///当日投机开仓数量限制
	TThostFtdcVolumeType	SpecOpenVolume;
	///当日套利开仓数量限制
	TThostFtdcVolumeType	ArbiOpenVolume;
	///当日投机+套利开仓数量限制
	TThostFtdcVolumeType	OpenVolume;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///禁止登录IP
struct CThostFtdcLoginForbiddenIPField
{
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///IP列表
struct CThostFtdcIPListField
{
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///是否白名单
	TThostFtdcBoolType	IsWhite;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///输入的期权自对冲
struct CThostFtdcInputOptionSelfCloseField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///期权自对冲引用
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///期权行权的头寸是否自对冲
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///输入期权自对冲操作
struct CThostFtdcInputOptionSelfCloseActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///期权自对冲操作引用
	TThostFtdcOrderActionRefType	OptionSelfCloseActionRef;
	///期权自对冲引用
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///期权自对冲操作编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///期权自对冲
struct CThostFtdcOptionSelfCloseField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///期权自对冲引用
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///期权行权的头寸是否自对冲
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///本地期权自对冲编号
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期权自对冲提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///期权自对冲编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///自对冲结果
	TThostFtdcExecResultType	ExecResult;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerOptionSelfCloseSeq;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///期权自对冲操作
struct CThostFtdcOptionSelfCloseActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///期权自对冲操作引用
	TThostFtdcOrderActionRefType	OptionSelfCloseActionRef;
	///期权自对冲引用
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///期权自对冲操作编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地期权自对冲编号
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///期权自对冲查询
struct CThostFtdcQryOptionSelfCloseField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///期权自对冲编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///开始时间
	TThostFtdcTimeType	InsertTimeStart;
	///结束时间
	TThostFtdcTimeType	InsertTimeEnd;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///交易所期权自对冲信息
struct CThostFtdcExchangeOptionSelfCloseField
{
	///数量
	TThostFtdcVolumeType	Volume;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///期权行权的头寸是否自对冲
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///本地期权自对冲编号
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期权自对冲提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///期权自对冲编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///插入时间
	TThostFtdcTimeType	InsertTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///自对冲结果
	TThostFtdcExecResultType	ExecResult;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///期权自对冲操作查询
struct CThostFtdcQryOptionSelfCloseActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///交易所期权自对冲操作
struct CThostFtdcExchangeOptionSelfCloseActionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///期权自对冲操作编号
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地期权自对冲编号
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///期权行权的头寸是否自对冲
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///延时换汇同步
struct CThostFtdcSyncDelaySwapField
{
	///换汇流水号
	TThostFtdcDepositSeqNoType	DelaySwapSeqNo;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///源币种
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///源金额
	TThostFtdcMoneyType	FromAmount;
	///源换汇冻结金额(可用冻结)
	TThostFtdcMoneyType	FromFrozenSwap;
	///源剩余换汇额度(可提冻结)
	TThostFtdcMoneyType	FromRemainSwap;
	///目标币种
	TThostFtdcCurrencyIDType	ToCurrencyID;
	///目标金额
	TThostFtdcMoneyType	ToAmount;
	///是否手工换汇
	TThostFtdcBoolType	IsManualSwap;
	///是否将所有外币的剩余换汇额度设置为0
	TThostFtdcBoolType	IsAllRemainSetZero;
};

///查询延时换汇同步
struct CThostFtdcQrySyncDelaySwapField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///延时换汇流水号
	TThostFtdcDepositSeqNoType	DelaySwapSeqNo;
};

///投资单元
struct CThostFtdcInvestUnitField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///投资者单元名称
	TThostFtdcPartyNameType	InvestorUnitName;
	///投资者分组代码
	TThostFtdcInvestorIDType	InvestorGroupID;
	///手续费率模板代码
	TThostFtdcInvestorIDType	CommModelID;
	///保证金率模板代码
	TThostFtdcInvestorIDType	MarginModelID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///查询投资单元
struct CThostFtdcQryInvestUnitField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///二级代理商资金校验模式
struct CThostFtdcSecAgentCheckModeField
{
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///币种
	TThostFtdcCurrencyIDType	CurrencyID;
	///境外中介机构资金帐号
	TThostFtdcAccountIDType	BrokerSecAgentID;
	///是否需要校验自己的资金账户
	TThostFtdcBoolType	CheckSelfAccount;
};

///二级代理商信息
struct CThostFtdcSecAgentTradeInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///境外中介机构资金帐号
	TThostFtdcAccountIDType	BrokerSecAgentID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///二级代理商姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///市场行情
struct CThostFtdcMarketDataField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///最新价
	TThostFtdcPriceType	LastPrice;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TThostFtdcPriceType	PreClosePrice;
	///昨持仓量
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TThostFtdcPriceType	OpenPrice;
	///最高价
	TThostFtdcPriceType	HighestPrice;
	///最低价
	TThostFtdcPriceType	LowestPrice;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交金额
	TThostFtdcMoneyType	Turnover;
	///持仓量
	TThostFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TThostFtdcPriceType	ClosePrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///涨停板价
	TThostFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TThostFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TThostFtdcRatioType	PreDelta;
	///今虚实度
	TThostFtdcRatioType	CurrDelta;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TThostFtdcMillisecType	UpdateMillisec;
	///业务日期
	TThostFtdcDateType	ActionDay;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///行情基础属性
struct CThostFtdcMarketDataBaseField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TThostFtdcPriceType	PreClosePrice;
	///昨持仓量
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TThostFtdcRatioType	PreDelta;
};

///行情静态属性
struct CThostFtdcMarketDataStaticField
{
	///今开盘
	TThostFtdcPriceType	OpenPrice;
	///最高价
	TThostFtdcPriceType	HighestPrice;
	///最低价
	TThostFtdcPriceType	LowestPrice;
	///今收盘
	TThostFtdcPriceType	ClosePrice;
	///涨停板价
	TThostFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TThostFtdcPriceType	LowerLimitPrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///今虚实度
	TThostFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CThostFtdcMarketDataLastMatchField
{
	///最新价
	TThostFtdcPriceType	LastPrice;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交金额
	TThostFtdcMoneyType	Turnover;
	///持仓量
	TThostFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CThostFtdcMarketDataBestPriceField
{
	///申买价一
	TThostFtdcPriceType	BidPrice1;
	///申买量一
	TThostFtdcVolumeType	BidVolume1;
	///申卖价一
	TThostFtdcPriceType	AskPrice1;
	///申卖量一
	TThostFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CThostFtdcMarketDataBid23Field
{
	///申买价二
	TThostFtdcPriceType	BidPrice2;
	///申买量二
	TThostFtdcVolumeType	BidVolume2;
	///申买价三
	TThostFtdcPriceType	BidPrice3;
	///申买量三
	TThostFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CThostFtdcMarketDataAsk23Field
{
	///申卖价二
	TThostFtdcPriceType	AskPrice2;
	///申卖量二
	TThostFtdcVolumeType	AskVolume2;
	///申卖价三
	TThostFtdcPriceType	AskPrice3;
	///申卖量三
	TThostFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CThostFtdcMarketDataBid45Field
{
	///申买价四
	TThostFtdcPriceType	BidPrice4;
	///申买量四
	TThostFtdcVolumeType	BidVolume4;
	///申买价五
	TThostFtdcPriceType	BidPrice5;
	///申买量五
	TThostFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CThostFtdcMarketDataAsk45Field
{
	///申卖价四
	TThostFtdcPriceType	AskPrice4;
	///申卖量四
	TThostFtdcVolumeType	AskVolume4;
	///申卖价五
	TThostFtdcPriceType	AskPrice5;
	///申卖量五
	TThostFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CThostFtdcMarketDataUpdateTimeField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TThostFtdcMillisecType	UpdateMillisec;
	///业务日期
	TThostFtdcDateType	ActionDay;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///行情上下带价
struct CThostFtdcMarketDataBandingPriceField
{
	///上带价
	TThostFtdcPriceType	BandingUpperPrice;
	///下带价
	TThostFtdcPriceType	BandingLowerPrice;
};

///行情交易所代码属性
struct CThostFtdcMarketDataExchangeField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///指定的合约
struct CThostFtdcSpecificInstrumentField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///合约状态
struct CThostFtdcInstrumentStatusField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///结算组代码
	TThostFtdcSettlementGroupIDType	SettlementGroupID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///合约交易状态
	TThostFtdcInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TThostFtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TThostFtdcTimeType	EnterTime;
	///进入本状态原因
	TThostFtdcInstStatusEnterReasonType	EnterReason;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询合约状态
struct CThostFtdcQryInstrumentStatusField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve1;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///投资者账户
struct CThostFtdcInvestorAccountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///浮动盈亏算法
struct CThostFtdcPositionProfitAlgorithmField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///盈亏算法
	TThostFtdcAlgorithmType	Algorithm;
	///备注
	TThostFtdcMemoType	Memo;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///会员资金折扣
struct CThostFtdcDiscountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///资金折扣比例
	TThostFtdcRatioType	Discount;
};

///查询转帐银行
struct CThostFtdcQryTransferBankField
{
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分中心代码
	TThostFtdcBankBrchIDType	BankBrchID;
};

///转帐银行
struct CThostFtdcTransferBankField
{
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分中心代码
	TThostFtdcBankBrchIDType	BankBrchID;
	///银行名称
	TThostFtdcBankNameType	BankName;
	///是否活跃
	TThostFtdcBoolType	IsActive;
};

///查询投资者持仓明细
struct CThostFtdcQryInvestorPositionDetailField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///投资者持仓明细
struct CThostFtdcInvestorPositionDetailField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TThostFtdcDirectionType	Direction;
	///开仓日期
	TThostFtdcDateType	OpenDate;
	///成交编号
	TThostFtdcTradeIDType	TradeID;
	///数量
	TThostFtdcVolumeType	Volume;
	///开仓价
	TThostFtdcPriceType	OpenPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///成交类型
	TThostFtdcTradeTypeType	TradeType;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	TThostFtdcMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	TThostFtdcMoneyType	PositionProfitByTrade;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///昨结算价
	TThostFtdcPriceType	LastSettlementPrice;
	///结算价
	TThostFtdcPriceType	SettlementPrice;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///先开先平剩余数量
	TThostFtdcVolumeType	TimeFirstVolume;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///特殊持仓标志
	TThostFtdcSpecPosiTypeType	SpecPosiType;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
};

///资金账户口令域
struct CThostFtdcTradingAccountPasswordField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///密码
	TThostFtdcPasswordType	Password;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///交易所行情报盘机
struct CThostFtdcMDTraderOfferField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TThostFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TThostFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TThostFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TThostFtdcDateType	LastReportDate;
	///上次报告时间
	TThostFtdcTimeType	LastReportTime;
	///完成连接日期
	TThostFtdcDateType	ConnectDate;
	///完成连接时间
	TThostFtdcTimeType	ConnectTime;
	///启动日期
	TThostFtdcDateType	StartDate;
	///启动时间
	TThostFtdcTimeType	StartTime;
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///本席位最大成交编号
	TThostFtdcTradeIDType	MaxTradeID;
	///本席位最大报单备拷
	TThostFtdcReturnCodeType	MaxOrderMessageReference;
	///撤单时选择席位算法
	TThostFtdcOrderCancelAlgType	OrderCancelAlg;
};

///查询行情报盘机
struct CThostFtdcQryMDTraderOfferField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///查询客户通知
struct CThostFtdcQryNoticeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///客户通知
struct CThostFtdcNoticeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///消息正文
	TThostFtdcContentType	Content;
	///经纪公司通知内容序列号
	TThostFtdcSequenceLabelType	SequenceLabel;
};

///用户权限
struct CThostFtdcUserRightField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///客户权限类型
	TThostFtdcUserRightTypeType	UserRightType;
	///是否禁止
	TThostFtdcBoolType	IsForbidden;
};

///查询结算信息确认域
struct CThostFtdcQrySettlementInfoConfirmField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///装载结算信息
struct CThostFtdcLoadSettlementInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///经纪公司可提资金算法表
struct CThostFtdcBrokerWithdrawAlgorithmField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///可提资金算法
	TThostFtdcAlgorithmType	WithdrawAlgorithm;
	///资金使用率
	TThostFtdcRatioType	UsingRatio;
	///可提是否包含平仓盈利
	TThostFtdcIncludeCloseProfitType	IncludeCloseProfit;
	///本日无仓且无成交客户是否受可提比例限制
	TThostFtdcAllWithoutTradeType	AllWithoutTrade;
	///可用是否包含平仓盈利
	TThostFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
	///是否启用用户事件
	TThostFtdcBoolType	IsBrokerUserEvent;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///货币质押比率
	TThostFtdcRatioType	FundMortgageRatio;
	///权益算法
	TThostFtdcBalanceAlgorithmType	BalanceAlgorithm;
};

///资金账户口令变更域
struct CThostFtdcTradingAccountPasswordUpdateV1Field
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///原来的口令
	TThostFtdcPasswordType	OldPassword;
	///新的口令
	TThostFtdcPasswordType	NewPassword;
};

///资金账户口令变更域
struct CThostFtdcTradingAccountPasswordUpdateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///原来的口令
	TThostFtdcPasswordType	OldPassword;
	///新的口令
	TThostFtdcPasswordType	NewPassword;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///查询组合合约分腿
struct CThostFtdcQryCombinationLegField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///单腿合约代码
	TThostFtdcInstrumentIDType	LegInstrumentID;
};

///查询组合合约分腿
struct CThostFtdcQrySyncStatusField
{
	///交易日
	TThostFtdcDateType	TradingDay;
};

///组合交易合约的单腿
struct CThostFtdcCombinationLegField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///单腿乘数
	TThostFtdcLegMultipleType	LegMultiple;
	///派生层数
	TThostFtdcImplyLevelType	ImplyLevel;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///单腿合约代码
	TThostFtdcInstrumentIDType	LegInstrumentID;
};

///数据同步状态
struct CThostFtdcSyncStatusField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///数据同步状态
	TThostFtdcDataSyncStatusType	DataSyncStatus;
};

///查询联系人
struct CThostFtdcQryLinkManField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///联系人
struct CThostFtdcLinkManField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///联系人类型
	TThostFtdcPersonTypeType	PersonType;
	///证件类型
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///名称
	TThostFtdcPartyNameType	PersonName;
	///联系电话
	TThostFtdcTelephoneType	Telephone;
	///通讯地址
	TThostFtdcAddressType	Address;
	///邮政编码
	TThostFtdcZipCodeType	ZipCode;
	///优先级
	TThostFtdcPriorityType	Priority;
	///开户邮政编码
	TThostFtdcUOAZipCodeType	UOAZipCode;
	///全称
	TThostFtdcInvestorFullNameType	PersonFullName;
};

///查询经纪公司用户事件
struct CThostFtdcQryBrokerUserEventField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户事件类型
	TThostFtdcUserEventTypeType	UserEventType;
};

///查询经纪公司用户事件
struct CThostFtdcBrokerUserEventField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户事件类型
	TThostFtdcUserEventTypeType	UserEventType;
	///用户事件序号
	TThostFtdcSequenceNoType	EventSequenceNo;
	///事件发生日期
	TThostFtdcDateType	EventDate;
	///事件发生时间
	TThostFtdcTimeType	EventTime;
	///用户事件信息
	TThostFtdcUserEventInfoType	UserEventInfo;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
	///交易日
	TThostFtdcDateType	TradingDay;
};

///查询签约银行请求
struct CThostFtdcQryContractBankField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分中心代码
	TThostFtdcBankBrchIDType	BankBrchID;
};

///查询签约银行响应
struct CThostFtdcContractBankField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分中心代码
	TThostFtdcBankBrchIDType	BankBrchID;
	///银行名称
	TThostFtdcBankNameType	BankName;
};

///投资者组合持仓明细
struct CThostFtdcInvestorPositionCombineDetailField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///开仓日期
	TThostFtdcDateType	OpenDate;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///组合编号
	TThostFtdcTradeIDType	ComTradeID;
	///撮合编号
	TThostFtdcTradeIDType	TradeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TThostFtdcDirectionType	Direction;
	///持仓量
	TThostFtdcVolumeType	TotalAmt;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///单腿乘数
	TThostFtdcLegMultipleType	LegMultiple;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///成交组号
	TThostFtdcTradeGroupIDType	TradeGroupID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///组合持仓合约编码
	TThostFtdcInstrumentIDType	CombInstrumentID;
};

///预埋单
struct CThostFtdcParkedOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///用户强平标志
	TThostFtdcBoolType	UserForceClose;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///预埋报单编号
	TThostFtdcParkedOrderIDType	ParkedOrderID;
	///用户类型
	TThostFtdcUserTypeType	UserType;
	///预埋单状态
	TThostFtdcParkedOrderStatusType	Status;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///输入预埋单操作
struct CThostFtdcParkedOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量变化
	TThostFtdcVolumeType	VolumeChange;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///预埋撤单单编号
	TThostFtdcParkedOrderActionIDType	ParkedOrderActionID;
	///用户类型
	TThostFtdcUserTypeType	UserType;
	///预埋撤单状态
	TThostFtdcParkedOrderStatusType	Status;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询预埋单
struct CThostFtdcQryParkedOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询预埋撤单
struct CThostFtdcQryParkedOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///删除预埋单
struct CThostFtdcRemoveParkedOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///预埋报单编号
	TThostFtdcParkedOrderIDType	ParkedOrderID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///删除预埋撤单
struct CThostFtdcRemoveParkedOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///预埋撤单编号
	TThostFtdcParkedOrderActionIDType	ParkedOrderActionID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///经纪公司可提资金算法表
struct CThostFtdcInvestorWithdrawAlgorithmField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///可提资金比例
	TThostFtdcRatioType	UsingRatio;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///货币质押比率
	TThostFtdcRatioType	FundMortgageRatio;
};

///查询组合持仓明细
struct CThostFtdcQryInvestorPositionCombineDetailField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///组合持仓合约编码
	TThostFtdcInstrumentIDType	CombInstrumentID;
};

///成交均价
struct CThostFtdcMarketDataAveragePriceField
{
	///当日均价
	TThostFtdcPriceType	AveragePrice;
};

///校验投资者密码
struct CThostFtdcVerifyInvestorPasswordField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///密码
	TThostFtdcPasswordType	Password;
};

///用户IP
struct CThostFtdcUserIPField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///IP地址掩码
	TThostFtdcIPAddressType	IPMask;
};

///用户事件通知信息
struct CThostFtdcTradingNoticeInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///发送时间
	TThostFtdcTimeType	SendTime;
	///消息正文
	TThostFtdcContentType	FieldContent;
	///序列系列号
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TThostFtdcSequenceNoType	SequenceNo;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///用户事件通知
struct CThostFtdcTradingNoticeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///序列系列号
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///发送时间
	TThostFtdcTimeType	SendTime;
	///序列号
	TThostFtdcSequenceNoType	SequenceNo;
	///消息正文
	TThostFtdcContentType	FieldContent;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///查询交易事件通知
struct CThostFtdcQryTradingNoticeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///查询错误报单
struct CThostFtdcQryErrOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///错误报单
struct CThostFtdcErrOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///用户强平标志
	TThostFtdcBoolType	UserForceClose;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易编码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///查询错误报单操作
struct CThostFtdcErrorConditionalOrderField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///保留的无效字段
	TThostFtdcOldExchangeInstIDType	reserve2;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TThostFtdcOrderSourceType	OrderSource;
	///报单状态
	TThostFtdcOrderStatusType	OrderStatus;
	///报单类型
	TThostFtdcOrderTypeType	OrderType;
	///今成交数量
	TThostFtdcVolumeType	VolumeTraded;
	///剩余数量
	TThostFtdcVolumeType	VolumeTotal;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///委托时间
	TThostFtdcTimeType	InsertTime;
	///激活时间
	TThostFtdcTimeType	ActiveTime;
	///挂起时间
	TThostFtdcTimeType	SuspendTime;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TThostFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///用户强平标志
	TThostFtdcBoolType	UserForceClose;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///郑商所成交数量
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve3;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询错误报单操作
struct CThostFtdcQryErrOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///错误报单操作
struct CThostFtdcErrOrderActionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TThostFtdcActionFlagType	ActionFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量变化
	TThostFtdcVolumeType	VolumeChange;
	///操作日期
	TThostFtdcDateType	ActionDate;
	///操作时间
	TThostFtdcTimeType	ActionTime;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve2;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///报单回显字段
	TThostFtdcOrderMemoType	OrderMemo;
	///session上请求计数 api自动维护
	TThostFtdcSequenceNo12Type	SessionReqSeq;
};

///查询交易所状态
struct CThostFtdcQryExchangeSequenceField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///交易所状态
struct CThostFtdcExchangeSequenceField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///合约交易状态
	TThostFtdcInstrumentStatusType	MarketStatus;
};

///根据价格查询最大报单数量
struct CThostFtdcQryMaxOrderVolumeWithPriceField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///开平标志
	TThostFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///最大允许报单数量
	TThostFtdcVolumeType	MaxVolume;
	///报单价格
	TThostFtdcPriceType	Price;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询经纪公司交易参数
struct CThostFtdcQryBrokerTradingParamsField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
};

///经纪公司交易参数
struct CThostFtdcBrokerTradingParamsField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保证金价格类型
	TThostFtdcMarginPriceTypeType	MarginPriceType;
	///盈亏算法
	TThostFtdcAlgorithmType	Algorithm;
	///可用是否包含平仓盈利
	TThostFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///期权权利金价格类型
	TThostFtdcOptionRoyaltyPriceTypeType	OptionRoyaltyPriceType;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
};

///查询经纪公司交易算法
struct CThostFtdcQryBrokerTradingAlgosField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///经纪公司交易算法
struct CThostFtdcBrokerTradingAlgosField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///持仓处理算法编号
	TThostFtdcHandlePositionAlgoIDType	HandlePositionAlgoID;
	///寻找保证金率算法编号
	TThostFtdcFindMarginRateAlgoIDType	FindMarginRateAlgoID;
	///资金处理算法编号
	TThostFtdcHandleTradingAccountAlgoIDType	HandleTradingAccountAlgoID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询经纪公司资金
struct CThostFtdcQueryBrokerDepositField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
};

///经纪公司资金
struct CThostFtdcBrokerDepositField
{
	///交易日期
	TThostFtdcTradeDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///上次结算准备金
	TThostFtdcMoneyType	PreBalance;
	///当前保证金总额
	TThostFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///期货结算准备金
	TThostFtdcMoneyType	Balance;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///出金金额
	TThostFtdcMoneyType	Withdraw;
	///可提资金
	TThostFtdcMoneyType	Available;
	///基本准备金
	TThostFtdcMoneyType	Reserve;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
};

///查询保证金监管系统经纪公司密钥
struct CThostFtdcQryCFMMCBrokerKeyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///保证金监管系统经纪公司密钥
struct CThostFtdcCFMMCBrokerKeyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///经纪公司统一编码
	TThostFtdcParticipantIDType	ParticipantID;
	///密钥生成日期
	TThostFtdcDateType	CreateDate;
	///密钥生成时间
	TThostFtdcTimeType	CreateTime;
	///密钥编号
	TThostFtdcSequenceNoType	KeyID;
	///动态密钥
	TThostFtdcCFMMCKeyType	CurrentKey;
	///动态密钥类型
	TThostFtdcCFMMCKeyKindType	KeyKind;
};

///保证金监管系统经纪公司资金账户密钥
struct CThostFtdcCFMMCTradingAccountKeyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///经纪公司统一编码
	TThostFtdcParticipantIDType	ParticipantID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///密钥编号
	TThostFtdcSequenceNoType	KeyID;
	///动态密钥
	TThostFtdcCFMMCKeyType	CurrentKey;
};

///请求查询保证金监管系统经纪公司资金账户密钥
struct CThostFtdcQryCFMMCTradingAccountKeyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///用户动态令牌参数
struct CThostFtdcBrokerUserOTPParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///动态令牌提供商
	TThostFtdcOTPVendorsIDType	OTPVendorsID;
	///动态令牌序列号
	TThostFtdcSerialNumberType	SerialNumber;
	///令牌密钥
	TThostFtdcAuthKeyType	AuthKey;
	///漂移值
	TThostFtdcLastDriftType	LastDrift;
	///成功值
	TThostFtdcLastSuccessType	LastSuccess;
	///动态令牌类型
	TThostFtdcOTPTypeType	OTPType;
};

///手工同步用户动态令牌
struct CThostFtdcManualSyncBrokerUserOTPField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///动态令牌类型
	TThostFtdcOTPTypeType	OTPType;
	///第一个动态密码
	TThostFtdcPasswordType	FirstOTP;
	///第二个动态密码
	TThostFtdcPasswordType	SecondOTP;
};

///投资者手续费率模板
struct CThostFtdcCommRateModelField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///手续费率模板代码
	TThostFtdcInvestorIDType	CommModelID;
	///模板名称
	TThostFtdcCommModelNameType	CommModelName;
};

///请求查询投资者手续费率模板
struct CThostFtdcQryCommRateModelField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///手续费率模板代码
	TThostFtdcInvestorIDType	CommModelID;
};

///投资者保证金率模板
struct CThostFtdcMarginModelField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保证金率模板代码
	TThostFtdcInvestorIDType	MarginModelID;
	///模板名称
	TThostFtdcCommModelNameType	MarginModelName;
};

///请求查询投资者保证金率模板
struct CThostFtdcQryMarginModelField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///保证金率模板代码
	TThostFtdcInvestorIDType	MarginModelID;
};

///仓单折抵信息
struct CThostFtdcEWarrantOffsetField
{
	///交易日期
	TThostFtdcTradeDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///数量
	TThostFtdcVolumeType	Volume;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询仓单折抵信息
struct CThostFtdcQryEWarrantOffsetField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///查询投资者品种/跨品种保证金
struct CThostFtdcQryInvestorProductGroupMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///品种/跨品种标示
	TThostFtdcInstrumentIDType	ProductGroupID;
};

///投资者品种/跨品种保证金
struct CThostFtdcInvestorProductGroupMarginField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TThostFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TThostFtdcMoneyType	ShortFrozenMargin;
	///占用的保证金
	TThostFtdcMoneyType	UseMargin;
	///多头保证金
	TThostFtdcMoneyType	LongUseMargin;
	///空头保证金
	TThostFtdcMoneyType	ShortUseMargin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///交易所多头保证金
	TThostFtdcMoneyType	LongExchMargin;
	///交易所空头保证金
	TThostFtdcMoneyType	ShortExchMargin;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///手续费
	TThostFtdcMoneyType	Commission;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///折抵总金额
	TThostFtdcMoneyType	OffsetAmount;
	///多头折抵总金额
	TThostFtdcMoneyType	LongOffsetAmount;
	///空头折抵总金额
	TThostFtdcMoneyType	ShortOffsetAmount;
	///交易所折抵总金额
	TThostFtdcMoneyType	ExchOffsetAmount;
	///交易所多头折抵总金额
	TThostFtdcMoneyType	LongExchOffsetAmount;
	///交易所空头折抵总金额
	TThostFtdcMoneyType	ShortExchOffsetAmount;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///品种/跨品种标示
	TThostFtdcInstrumentIDType	ProductGroupID;
};

///查询监控中心用户令牌
struct CThostFtdcQueryCFMMCTradingAccountTokenField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///监控中心用户令牌
struct CThostFtdcCFMMCTradingAccountTokenField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///经纪公司统一编码
	TThostFtdcParticipantIDType	ParticipantID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///密钥编号
	TThostFtdcSequenceNoType	KeyID;
	///动态令牌
	TThostFtdcCFMMCTokenType	Token;
};

///查询产品组
struct CThostFtdcQryProductGroupField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///投资者品种/跨品种保证金产品组
struct CThostFtdcProductGroupField
{
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve2;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///产品组代码
	TThostFtdcInstrumentIDType	ProductGroupID;
};

///交易所公告
struct CThostFtdcBulletinField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易日
	TThostFtdcDateType	TradingDay;
	///公告编号
	TThostFtdcBulletinIDType	BulletinID;
	///序列号
	TThostFtdcSequenceNoType	SequenceNo;
	///公告类型
	TThostFtdcNewsTypeType	NewsType;
	///紧急程度
	TThostFtdcNewsUrgencyType	NewsUrgency;
	///发送时间
	TThostFtdcTimeType	SendTime;
	///消息摘要
	TThostFtdcAbstractType	Abstract;
	///消息来源
	TThostFtdcComeFromType	ComeFrom;
	///消息正文
	TThostFtdcContentType	Content;
	///WEB地址
	TThostFtdcURLLinkType	URLLink;
	///市场代码
	TThostFtdcMarketIDType	MarketID;
};

///查询交易所公告
struct CThostFtdcQryBulletinField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///公告编号
	TThostFtdcBulletinIDType	BulletinID;
	///序列号
	TThostFtdcSequenceNoType	SequenceNo;
	///公告类型
	TThostFtdcNewsTypeType	NewsType;
	///紧急程度
	TThostFtdcNewsUrgencyType	NewsUrgency;
};

///MulticastInstrument
struct CThostFtdcMulticastInstrumentField
{
	///主题号
	TThostFtdcInstallIDType	TopicID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约编号
	TThostFtdcInstallIDType	InstrumentNo;
	///基准价
	TThostFtdcPriceType	CodePrice;
	///合约数量乘数
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TThostFtdcPriceType	PriceTick;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///QryMulticastInstrument
struct CThostFtdcQryMulticastInstrumentField
{
	///主题号
	TThostFtdcInstallIDType	TopicID;
	///保留的无效字段
	TThostFtdcOldInstrumentIDType	reserve1;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///App客户端权限分配
struct CThostFtdcAppIDAuthAssignField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///App代码
	TThostFtdcAppIDType	AppID;
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///转帐开户请求
struct CThostFtdcReqOpenAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///交易ID
	TThostFtdcTIDType	TID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///转帐销户请求
struct CThostFtdcReqCancelAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///交易ID
	TThostFtdcTIDType	TID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///变更银行账户请求
struct CThostFtdcReqChangeAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///新银行帐号
	TThostFtdcBankAccountType	NewBankAccount;
	///新银行密码
	TThostFtdcPasswordType	NewBankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易ID
	TThostFtdcTIDType	TID;
	///摘要
	TThostFtdcDigestType	Digest;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///转账请求
struct CThostFtdcReqTransferField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TThostFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TThostFtdcAddInfoType	Message;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///转账交易状态
	TThostFtdcTransferStatusType	TransferStatus;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///银行发起银行资金转期货响应
struct CThostFtdcRspTransferField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TThostFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TThostFtdcAddInfoType	Message;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///转账交易状态
	TThostFtdcTransferStatusType	TransferStatus;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///冲正请求
struct CThostFtdcReqRepealField
{
	///冲正时间间隔
	TThostFtdcRepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	TThostFtdcRepealedTimesType	RepealedTimes;
	///银行冲正标志
	TThostFtdcBankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	TThostFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	TThostFtdcPlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	TThostFtdcBankSerialType	BankRepealSerial;
	///被冲正期货流水号
	TThostFtdcFutureSerialType	FutureRepealSerial;
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TThostFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TThostFtdcAddInfoType	Message;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///转账交易状态
	TThostFtdcTransferStatusType	TransferStatus;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///冲正响应
struct CThostFtdcRspRepealField
{
	///冲正时间间隔
	TThostFtdcRepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	TThostFtdcRepealedTimesType	RepealedTimes;
	///银行冲正标志
	TThostFtdcBankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	TThostFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	TThostFtdcPlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	TThostFtdcBankSerialType	BankRepealSerial;
	///被冲正期货流水号
	TThostFtdcFutureSerialType	FutureRepealSerial;
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TThostFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TThostFtdcAddInfoType	Message;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///转账交易状态
	TThostFtdcTransferStatusType	TransferStatus;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///查询账户信息请求
struct CThostFtdcReqQueryAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///查询账户信息响应
struct CThostFtdcRspQueryAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///银行可用金额
	TThostFtdcTradeAmountType	BankUseAmount;
	///银行可取金额
	TThostFtdcTradeAmountType	BankFetchAmount;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///期商签到签退
struct CThostFtdcFutureSignIOField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
};

///期商签到响应
struct CThostFtdcRspFutureSignInField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///PIN密钥
	TThostFtdcPasswordKeyType	PinKey;
	///MAC密钥
	TThostFtdcPasswordKeyType	MacKey;
};

///期商签退请求
struct CThostFtdcReqFutureSignOutField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
};

///期商签退响应
struct CThostFtdcRspFutureSignOutField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///查询指定流水号的交易结果请求
struct CThostFtdcReqQueryTradeResultBySerialField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///流水号
	TThostFtdcSerialType	Reference;
	///本流水号发布者的机构类型
	TThostFtdcInstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	TThostFtdcOrganCodeType	RefrenceIssure;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///摘要
	TThostFtdcDigestType	Digest;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///查询指定流水号的交易结果响应
struct CThostFtdcRspQueryTradeResultBySerialField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///流水号
	TThostFtdcSerialType	Reference;
	///本流水号发布者的机构类型
	TThostFtdcInstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	TThostFtdcOrganCodeType	RefrenceIssure;
	///原始返回代码
	TThostFtdcReturnCodeType	OriginReturnCode;
	///原始返回码描述
	TThostFtdcDescrInfoForReturnCodeType	OriginDescrInfoForReturnCode;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///摘要
	TThostFtdcDigestType	Digest;
};

///日终文件就绪请求
struct CThostFtdcReqDayEndFileReadyField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///文件业务功能
	TThostFtdcFileBusinessCodeType	FileBusinessCode;
	///摘要
	TThostFtdcDigestType	Digest;
};

///返回结果
struct CThostFtdcReturnResultField
{
	///返回代码
	TThostFtdcReturnCodeType	ReturnCode;
	///返回码描述
	TThostFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///验证期货资金密码
struct CThostFtdcVerifyFuturePasswordField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///交易ID
	TThostFtdcTIDType	TID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///验证客户信息
struct CThostFtdcVerifyCustInfoField
{
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///验证期货资金密码和客户信息
struct CThostFtdcVerifyFuturePasswordAndCustInfoField
{
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///验证期货资金密码和客户信息
struct CThostFtdcDepositResultInformField
{
	///出入金流水号，该流水号为银期报盘返回的流水号
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///返回代码
	TThostFtdcReturnCodeType	ReturnCode;
	///返回码描述
	TThostFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///交易核心向银期报盘发出密钥同步请求
struct CThostFtdcReqSyncKeyField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TThostFtdcAddInfoType	Message;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
};

///交易核心向银期报盘发出密钥同步响应
struct CThostFtdcRspSyncKeyField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TThostFtdcAddInfoType	Message;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///查询账户信息通知
struct CThostFtdcNotifyQueryAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///银行可用金额
	TThostFtdcTradeAmountType	BankUseAmount;
	///银行可取金额
	TThostFtdcTradeAmountType	BankFetchAmount;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///银期转账交易流水表
struct CThostFtdcTransferSerialField
{
	///平台流水号
	TThostFtdcPlateSerialType	PlateSerial;
	///交易发起方日期
	TThostFtdcTradeDateType	TradeDate;
	///交易日期
	TThostFtdcDateType	TradingDay;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///交易代码
	TThostFtdcTradeCodeType	TradeCode;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///银行编码
	TThostFtdcBankIDType	BankID;
	///银行分支机构编码
	TThostFtdcBankBrchIDType	BankBranchID;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///期货公司编码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///期货公司帐号类型
	TThostFtdcFutureAccTypeType	FutureAccType;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///交易金额
	TThostFtdcTradeAmountType	TradeAmount;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///有效标志
	TThostFtdcAvailabilityFlagType	AvailabilityFlag;
	///操作员
	TThostFtdcOperatorCodeType	OperatorCode;
	///新银行帐号
	TThostFtdcBankAccountType	BankNewAccount;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///请求查询转帐流水
struct CThostFtdcQryTransferSerialField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///银行编码
	TThostFtdcBankIDType	BankID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///期商签到通知
struct CThostFtdcNotifyFutureSignInField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///PIN密钥
	TThostFtdcPasswordKeyType	PinKey;
	///MAC密钥
	TThostFtdcPasswordKeyType	MacKey;
};

///期商签退通知
struct CThostFtdcNotifyFutureSignOutField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///摘要
	TThostFtdcDigestType	Digest;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///交易核心向银期报盘发出密钥同步处理结果的通知
struct CThostFtdcNotifySyncKeyField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TThostFtdcAddInfoType	Message;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///请求查询银期签约关系
struct CThostFtdcQryAccountregisterField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///银行编码
	TThostFtdcBankIDType	BankID;
	///银行分支机构编码
	TThostFtdcBankBrchIDType	BankBranchID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///客户开销户信息表
struct CThostFtdcAccountregisterField
{
	///交易日期
	TThostFtdcTradeDateType	TradeDay;
	///银行编码
	TThostFtdcBankIDType	BankID;
	///银行分支机构编码
	TThostFtdcBankBrchIDType	BankBranchID;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///期货公司编码
	TThostFtdcBrokerIDType	BrokerID;
	///期货公司分支机构编码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///开销户类别
	TThostFtdcOpenOrDestroyType	OpenOrDestroy;
	///签约日期
	TThostFtdcTradeDateType	RegDate;
	///解约日期
	TThostFtdcTradeDateType	OutDate;
	///交易ID
	TThostFtdcTIDType	TID;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///银期开户信息
struct CThostFtdcOpenAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///交易ID
	TThostFtdcTIDType	TID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///银期销户信息
struct CThostFtdcCancelAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///交易ID
	TThostFtdcTIDType	TID;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///银期变更银行账号信息
struct CThostFtdcChangeAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///新银行帐号
	TThostFtdcBankAccountType	NewBankAccount;
	///新银行密码
	TThostFtdcPasswordType	NewBankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易ID
	TThostFtdcTIDType	TID;
	///摘要
	TThostFtdcDigestType	Digest;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
};

///二级代理操作员银期权限
struct CThostFtdcSecAgentACIDMapField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///资金账户
	TThostFtdcAccountIDType	AccountID;
	///币种
	TThostFtdcCurrencyIDType	CurrencyID;
	///境外中介机构资金帐号
	TThostFtdcAccountIDType	BrokerSecAgentID;
};

///二级代理操作员银期权限查询
struct CThostFtdcQrySecAgentACIDMapField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///资金账户
	TThostFtdcAccountIDType	AccountID;
	///币种
	TThostFtdcCurrencyIDType	CurrencyID;
};

///灾备中心交易权限
struct CThostFtdcUserRightsAssignField
{
	///应用单元代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///经济公司是否有在本标示的交易权限
struct CThostFtdcBrokerUserRightAssignField
{
	///应用单元代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
	///能否交易
	TThostFtdcBoolType	Tradeable;
};

///灾备交易转换报文
struct CThostFtdcDRTransferField
{
	///原交易中心代码
	TThostFtdcDRIdentityIDType	OrigDRIdentityID;
	///目标交易中心代码
	TThostFtdcDRIdentityIDType	DestDRIdentityID;
	///原应用单元代码
	TThostFtdcBrokerIDType	OrigBrokerID;
	///目标易用单元代码
	TThostFtdcBrokerIDType	DestBrokerID;
};

///Fens用户信息
struct CThostFtdcFensUserInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///登录模式
	TThostFtdcLoginModeType	LoginMode;
};

///当前银期所属交易中心
struct CThostFtdcCurrTransferIdentityField
{
	///交易中心代码
	TThostFtdcDRIdentityIDType	IdentityID;
};

///禁止登录用户
struct CThostFtdcLoginForbiddenUserField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询禁止登录用户
struct CThostFtdcQryLoginForbiddenUserField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///资金账户基本准备金
struct CThostFtdcTradingAccountReserveField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///基本准备金
	TThostFtdcMoneyType	Reserve;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///查询禁止登录IP
struct CThostFtdcQryLoginForbiddenIPField
{
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询IP列表
struct CThostFtdcQryIPListField
{
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询用户下单权限分配表
struct CThostFtdcQryUserRightsAssignField
{
	///应用单元代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///银期预约开户确认请求
struct CThostFtdcReserveOpenAccountConfirmField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcLongIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易ID
	TThostFtdcTIDType	TID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///预约开户银行流水号
	TThostFtdcBankSerialType	BankReserveOpenSeq;
	///预约开户日期
	TThostFtdcTradeDateType	BookDate;
	///预约开户验证密码
	TThostFtdcPasswordType	BookPsw;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///银期预约开户
struct CThostFtdcReserveOpenAccountField
{
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcLongIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TThostFtdcGenderType	Gender;
	///国家代码
	TThostFtdcCountryCodeType	CountryCode;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///地址
	TThostFtdcAddressType	Address;
	///邮编
	TThostFtdcZipCodeType	ZipCode;
	///电话号码
	TThostFtdcTelephoneType	Telephone;
	///手机
	TThostFtdcMobilePhoneType	MobilePhone;
	///传真
	TThostFtdcFaxType	Fax;
	///电子邮件
	TThostFtdcEMailType	EMail;
	///资金账户状态
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易ID
	TThostFtdcTIDType	TID;
	///预约开户状态
	TThostFtdcReserveOpenAccStasType	ReserveOpenAccStas;
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};

///银行账户属性
struct CThostFtdcAccountPropertyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///银行统一标识类型
	TThostFtdcBankIDType	BankID;
	///银行账户
	TThostFtdcBankAccountType	BankAccount;
	///银行账户的开户人名称
	TThostFtdcInvestorFullNameType	OpenName;
	///银行账户的开户行
	TThostFtdcOpenBankType	OpenBank;
	///是否活跃
	TThostFtdcBoolType	IsActive;
	///账户来源
	TThostFtdcAccountSourceTypeType	AccountSourceType;
	///开户日期
	TThostFtdcDateType	OpenDate;
	///注销日期
	TThostFtdcDateType	CancelDate;
	///录入员代码
	TThostFtdcOperatorIDType	OperatorID;
	///录入日期
	TThostFtdcDateType	OperateDate;
	///录入时间
	TThostFtdcTimeType	OperateTime;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
};

///查询当前交易中心
struct CThostFtdcQryCurrDRIdentityField
{
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///当前交易中心
struct CThostFtdcCurrDRIdentityField
{
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///查询二级代理商资金校验模式
struct CThostFtdcQrySecAgentCheckModeField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///查询二级代理商信息
struct CThostFtdcQrySecAgentTradeInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///境外中介机构资金帐号
	TThostFtdcAccountIDType	BrokerSecAgentID;
};

///用户发出获取安全安全登陆方法请求
struct CThostFtdcReqUserAuthMethodField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///用户发出获取安全安全登陆方法回复
struct CThostFtdcRspUserAuthMethodField
{
	///当前可以用的认证模式
	TThostFtdcCurrentAuthMethodType	UsableAuthMethod;
};

///用户发出获取安全安全登陆方法请求
struct CThostFtdcReqGenUserCaptchaField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///生成的图片验证码信息
struct CThostFtdcRspGenUserCaptchaField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///图片信息长度
	TThostFtdcCaptchaInfoLenType	CaptchaInfoLen;
	///图片信息
	TThostFtdcCaptchaInfoType	CaptchaInfo;
};

///用户发出获取安全安全登陆方法请求
struct CThostFtdcReqGenUserTextField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///短信验证码生成的回复
struct CThostFtdcRspGenUserTextField
{
	///短信验证码序号
	TThostFtdcUserTextSeqType	UserTextSeq;
};

///用户发出带图形验证码的登录请求请求
struct CThostFtdcReqUserLoginWithCaptchaField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///图形验证码的文字内容
	TThostFtdcPasswordType	Captcha;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
};

///用户发出带短信验证码的登录请求请求
struct CThostFtdcReqUserLoginWithTextField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///短信验证码文字内容
	TThostFtdcPasswordType	Text;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
};

///用户发出带动态验证码的登录请求请求
struct CThostFtdcReqUserLoginWithOTPField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///OTP密码
	TThostFtdcPasswordType	OTPPassword;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
};

///api握手请求
struct CThostFtdcReqApiHandshakeField
{
	///api与front通信密钥版本号
	TThostFtdcCryptoKeyVersionType	CryptoKeyVersion;
};

///front发给api的握手回复
struct CThostFtdcRspApiHandshakeField
{
	///握手回复数据长度
	TThostFtdcHandshakeDataLenType	FrontHandshakeDataLen;
	///握手回复数据
	TThostFtdcHandshakeDataType	FrontHandshakeData;
	///API认证是否开启
	TThostFtdcBoolType	IsApiAuthEnabled;
};

///api给front的验证key的请求
struct CThostFtdcReqVerifyApiKeyField
{
	///握手回复数据长度
	TThostFtdcHandshakeDataLenType	ApiHandshakeDataLen;
	///握手回复数据
	TThostFtdcHandshakeDataType	ApiHandshakeData;
};

///操作员组织架构关系
struct CThostFtdcDepartmentUserField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///投资者范围
	TThostFtdcDepartmentRangeType	InvestorRange;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///查询频率，每秒查询比数
struct CThostFtdcQueryFreqField
{
	///查询频率
	TThostFtdcQueryFreqType	QueryFreq;
	///FTD频率
	TThostFtdcQueryFreqType	FTDPkgFreq;
};

///禁止认证IP
struct CThostFtdcAuthForbiddenIPField
{
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///查询禁止认证IP
struct CThostFtdcQryAuthForbiddenIPField
{
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
};

///换汇可提冻结
struct CThostFtdcSyncDelaySwapFrozenField
{
	///换汇流水号
	TThostFtdcDepositSeqNoType	DelaySwapSeqNo;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///源币种
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///源剩余换汇额度(可提冻结)
	TThostFtdcMoneyType	FromRemainSwap;
	///是否手工换汇
	TThostFtdcBoolType	IsManualSwap;
};

///用户系统信息
struct CThostFtdcUserSystemInfoField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///用户端系统内部信息长度
	TThostFtdcSystemInfoLenType	ClientSystemInfoLen;
	///用户端系统内部信息
	TThostFtdcClientSystemInfoType	ClientSystemInfo;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///登录成功时间
	TThostFtdcTimeType	ClientLoginTime;
	///App代码
	TThostFtdcAppIDType	ClientAppID;
	///用户公网IP
	TThostFtdcIPAddressType	ClientPublicIP;
	///客户登录备注2
	TThostFtdcClientLoginRemarkType	ClientLoginRemark;
};

///终端用户绑定信息
struct CThostFtdcAuthUserIDField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///App代码
	TThostFtdcAppIDType	AppID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///校验类型
	TThostFtdcAuthTypeType	AuthType;
};

///用户IP绑定信息
struct CThostFtdcAuthIPField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///App代码
	TThostFtdcAppIDType	AppID;
	///用户代码
	TThostFtdcIPAddressType	IPAddress;
};

///查询分类合约
struct CThostFtdcQryClassifiedInstrumentField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///合约交易状态
	TThostFtdcTradingTypeType	TradingType;
	///合约分类类型
	TThostFtdcClassTypeType	ClassType;
};

///查询组合优惠比例
struct CThostFtdcQryCombPromotionParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///组合优惠比例
struct CThostFtdcCombPromotionParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///期权组合保证金比例
	TThostFtdcDiscountRatioType	Xparameter;
};

///国密用户登录请求
struct CThostFtdcReqUserLoginSMField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///密码
	TThostFtdcPasswordType	Password;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
	///动态密码
	TThostFtdcPasswordType	OneTimePassword;
	///保留的无效字段
	TThostFtdcOldIPAddressType	reserve1;
	///登录备注
	TThostFtdcLoginRemarkType	LoginRemark;
	///终端IP端口
	TThostFtdcIPPortType	ClientIPPort;
	///终端IP地址
	TThostFtdcIPAddressType	ClientIPAddress;
	///经纪公司名称
	TThostFtdcBrokerNameType	BrokerName;
	///认证码
	TThostFtdcAuthCodeType	AuthCode;
	///App代码
	TThostFtdcAppIDType	AppID;
	///PIN码
	TThostFtdcPasswordType	PIN;
};

///投资者风险结算持仓查询
struct CThostFtdcQryRiskSettleInvstPositionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///风险结算产品查询
struct CThostFtdcQryRiskSettleProductStatusField
{
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
};

///投资者风险结算持仓
struct CThostFtdcRiskSettleInvstPositionField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TThostFtdcPositionDateType	PositionDate;
	///上日持仓
	TThostFtdcVolumeType	YdPosition;
	///今日持仓
	TThostFtdcVolumeType	Position;
	///多头冻结
	TThostFtdcVolumeType	LongFrozen;
	///空头冻结
	TThostFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TThostFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TThostFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TThostFtdcVolumeType	OpenVolume;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///开仓金额
	TThostFtdcMoneyType	OpenAmount;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///持仓成本
	TThostFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///占用的保证金
	TThostFtdcMoneyType	UseMargin;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///开仓成本
	TThostFtdcMoneyType	OpenCost;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TThostFtdcVolumeType	CombPosition;
	///组合多头冻结
	TThostFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TThostFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TThostFtdcVolumeType	TodayPosition;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///执行冻结
	TThostFtdcVolumeType	StrikeFrozen;
	///执行冻结金额
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	TThostFtdcVolumeType	AbandonFrozen;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行冻结的昨仓
	TThostFtdcVolumeType	YdStrikeFrozen;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///持仓成本差值
	TThostFtdcMoneyType	PositionCostOffset;
	///tas持仓手数
	TThostFtdcVolumeType	TasPosition;
	///tas持仓成本
	TThostFtdcMoneyType	TasPositionCost;
};

///风险品种
struct CThostFtdcRiskSettleProductStatusField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品编号
	TThostFtdcInstrumentIDType	ProductID;
	///产品结算状态
	TThostFtdcProductStatusType	ProductStatus;
};

///风险结算追平信息
struct CThostFtdcSyncDeltaInfoField
{
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
	///追平状态
	TThostFtdcSyncDeltaStatusType	SyncDeltaStatus;
	///追平描述
	TThostFtdcSyncDescriptionType	SyncDescription;
	///是否只有资金追平
	TThostFtdcBoolType	IsOnlyTrdDelta;
};

///风险结算追平产品信息
struct CThostFtdcSyncDeltaProductStatusField
{
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///是否允许交易
	TThostFtdcProductStatusType	ProductStatus;
};

///风险结算追平持仓明细
struct CThostFtdcSyncDeltaInvstPosDtlField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TThostFtdcDirectionType	Direction;
	///开仓日期
	TThostFtdcDateType	OpenDate;
	///成交编号
	TThostFtdcTradeIDType	TradeID;
	///数量
	TThostFtdcVolumeType	Volume;
	///开仓价
	TThostFtdcPriceType	OpenPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///成交类型
	TThostFtdcTradeTypeType	TradeType;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	TThostFtdcMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	TThostFtdcMoneyType	PositionProfitByTrade;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///昨结算价
	TThostFtdcPriceType	LastSettlementPrice;
	///结算价
	TThostFtdcPriceType	SettlementPrice;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///先开先平剩余数量
	TThostFtdcVolumeType	TimeFirstVolume;
	///特殊持仓标志
	TThostFtdcSpecPosiTypeType	SpecPosiType;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平组合持仓明细
struct CThostFtdcSyncDeltaInvstPosCombDtlField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///开仓日期
	TThostFtdcDateType	OpenDate;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///组合编号
	TThostFtdcTradeIDType	ComTradeID;
	///撮合编号
	TThostFtdcTradeIDType	TradeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TThostFtdcDirectionType	Direction;
	///持仓量
	TThostFtdcVolumeType	TotalAmt;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///单腿乘数
	TThostFtdcLegMultipleType	LegMultiple;
	///成交组号
	TThostFtdcTradeGroupIDType	TradeGroupID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平资金
struct CThostFtdcSyncDeltaTradingAccountField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///上次质押金额
	TThostFtdcMoneyType	PreMortgage;
	///上次信用额度
	TThostFtdcMoneyType	PreCredit;
	///上次存款额
	TThostFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TThostFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///利息基数
	TThostFtdcMoneyType	InterestBase;
	///利息收入
	TThostFtdcMoneyType	Interest;
	///入金金额
	TThostFtdcMoneyType	Deposit;
	///出金金额
	TThostFtdcMoneyType	Withdraw;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TThostFtdcMoneyType	CurrMargin;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///期货结算准备金
	TThostFtdcMoneyType	Balance;
	///可用资金
	TThostFtdcMoneyType	Available;
	///可取资金
	TThostFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TThostFtdcMoneyType	Reserve;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///信用额度
	TThostFtdcMoneyType	Credit;
	///质押金额
	TThostFtdcMoneyType	Mortgage;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TThostFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TThostFtdcMoneyType	ExchangeDeliveryMargin;
	///保底期货结算准备金
	TThostFtdcMoneyType	ReserveBalance;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///上次货币质入金额
	TThostFtdcMoneyType	PreFundMortgageIn;
	///上次货币质出金额
	TThostFtdcMoneyType	PreFundMortgageOut;
	///货币质入金额
	TThostFtdcMoneyType	FundMortgageIn;
	///货币质出金额
	TThostFtdcMoneyType	FundMortgageOut;
	///货币质押余额
	TThostFtdcMoneyType	FundMortgageAvailable;
	///可质押货币金额
	TThostFtdcMoneyType	MortgageableFund;
	///特殊产品占用保证金
	TThostFtdcMoneyType	SpecProductMargin;
	///特殊产品冻结保证金
	TThostFtdcMoneyType	SpecProductFrozenMargin;
	///特殊产品手续费
	TThostFtdcMoneyType	SpecProductCommission;
	///特殊产品冻结手续费
	TThostFtdcMoneyType	SpecProductFrozenCommission;
	///特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfit;
	///特殊产品平仓盈亏
	TThostFtdcMoneyType	SpecProductCloseProfit;
	///根据持仓盈亏算法计算的特殊产品持仓盈亏
	TThostFtdcMoneyType	SpecProductPositionProfitByAlg;
	///特殊产品交易所保证金
	TThostFtdcMoneyType	SpecProductExchangeMargin;
	///延时换汇冻结金额
	TThostFtdcMoneyType	FrozenSwap;
	///剩余换汇额度
	TThostFtdcMoneyType	RemainSwap;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///投资者风险结算总保证金
struct CThostFtdcSyncDeltaInitInvstMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///追平前总风险保证金
	TThostFtdcMoneyType	LastRiskTotalInvstMargin;
	///追平前交易所总风险保证金
	TThostFtdcMoneyType	LastRiskTotalExchMargin;
	///本次追平品种总保证金
	TThostFtdcMoneyType	ThisSyncInvstMargin;
	///本次追平品种交易所总保证金
	TThostFtdcMoneyType	ThisSyncExchMargin;
	///本次未追平品种总保证金
	TThostFtdcMoneyType	RemainRiskInvstMargin;
	///本次未追平品种交易所总保证金
	TThostFtdcMoneyType	RemainRiskExchMargin;
	///追平前总特殊产品风险保证金
	TThostFtdcMoneyType	LastRiskSpecTotalInvstMargin;
	///追平前总特殊产品交易所风险保证金
	TThostFtdcMoneyType	LastRiskSpecTotalExchMargin;
	///本次追平品种特殊产品总保证金
	TThostFtdcMoneyType	ThisSyncSpecInvstMargin;
	///本次追平品种特殊产品交易所总保证金
	TThostFtdcMoneyType	ThisSyncSpecExchMargin;
	///本次未追平品种特殊产品总保证金
	TThostFtdcMoneyType	RemainRiskSpecInvstMargin;
	///本次未追平品种特殊产品交易所总保证金
	TThostFtdcMoneyType	RemainRiskSpecExchMargin;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平组合优先级
struct CThostFtdcSyncDeltaDceCombInstrumentField
{
	///合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///成交组号
	TThostFtdcTradeGroupIDType	TradeGroupID;
	///投机套保标志
	TThostFtdcHedgeFlagType	CombHedgeFlag;
	///组合类型
	TThostFtdcDceCombinationTypeType	CombinationType;
	///买卖
	TThostFtdcDirectionType	Direction;
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///期权组合保证金比例
	TThostFtdcDiscountRatioType	Xparameter;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平投资者期货保证金率
struct CThostFtdcSyncDeltaInvstMarginRateField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TThostFtdcBoolType	IsRelative;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平交易所期货保证金率
struct CThostFtdcSyncDeltaExchMarginRateField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平中金现货期权交易所保证金率
struct CThostFtdcSyncDeltaOptExchMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投机空头保证金调整系数
	TThostFtdcRatioType	SShortMarginRatioByMoney;
	///投机空头保证金调整系数
	TThostFtdcMoneyType	SShortMarginRatioByVolume;
	///保值空头保证金调整系数
	TThostFtdcRatioType	HShortMarginRatioByMoney;
	///保值空头保证金调整系数
	TThostFtdcMoneyType	HShortMarginRatioByVolume;
	///套利空头保证金调整系数
	TThostFtdcRatioType	AShortMarginRatioByMoney;
	///套利空头保证金调整系数
	TThostFtdcMoneyType	AShortMarginRatioByVolume;
	///做市商空头保证金调整系数
	TThostFtdcRatioType	MShortMarginRatioByMoney;
	///做市商空头保证金调整系数
	TThostFtdcMoneyType	MShortMarginRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平中金现货期权投资者保证金率
struct CThostFtdcSyncDeltaOptInvstMarginField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机空头保证金调整系数
	TThostFtdcRatioType	SShortMarginRatioByMoney;
	///投机空头保证金调整系数
	TThostFtdcMoneyType	SShortMarginRatioByVolume;
	///保值空头保证金调整系数
	TThostFtdcRatioType	HShortMarginRatioByMoney;
	///保值空头保证金调整系数
	TThostFtdcMoneyType	HShortMarginRatioByVolume;
	///套利空头保证金调整系数
	TThostFtdcRatioType	AShortMarginRatioByMoney;
	///套利空头保证金调整系数
	TThostFtdcMoneyType	AShortMarginRatioByVolume;
	///是否跟随交易所收取
	TThostFtdcBoolType	IsRelative;
	///做市商空头保证金调整系数
	TThostFtdcRatioType	MShortMarginRatioByMoney;
	///做市商空头保证金调整系数
	TThostFtdcMoneyType	MShortMarginRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平期权标的调整保证金率
struct CThostFtdcSyncDeltaInvstMarginRateULField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平期权手续费率
struct CThostFtdcSyncDeltaOptInvstCommRateField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///执行手续费率
	TThostFtdcRatioType	StrikeRatioByMoney;
	///执行手续费
	TThostFtdcRatioType	StrikeRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平期货手续费率
struct CThostFtdcSyncDeltaInvstCommRateField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TThostFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TThostFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平交叉汇率
struct CThostFtdcSyncDeltaProductExchRateField
{
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///报价币种类型
	TThostFtdcCurrencyIDType	QuoteCurrencyID;
	///汇率
	TThostFtdcExchangeRateType	ExchangeRate;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平行情
struct CThostFtdcSyncDeltaDepthMarketDataField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///最新价
	TThostFtdcPriceType	LastPrice;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TThostFtdcPriceType	PreClosePrice;
	///昨持仓量
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TThostFtdcPriceType	OpenPrice;
	///最高价
	TThostFtdcPriceType	HighestPrice;
	///最低价
	TThostFtdcPriceType	LowestPrice;
	///数量
	TThostFtdcVolumeType	Volume;
	///成交金额
	TThostFtdcMoneyType	Turnover;
	///持仓量
	TThostFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TThostFtdcPriceType	ClosePrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///涨停板价
	TThostFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TThostFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TThostFtdcRatioType	PreDelta;
	///今虚实度
	TThostFtdcRatioType	CurrDelta;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TThostFtdcMillisecType	UpdateMillisec;
	///申买价一
	TThostFtdcPriceType	BidPrice1;
	///申买量一
	TThostFtdcVolumeType	BidVolume1;
	///申卖价一
	TThostFtdcPriceType	AskPrice1;
	///申卖量一
	TThostFtdcVolumeType	AskVolume1;
	///申买价二
	TThostFtdcPriceType	BidPrice2;
	///申买量二
	TThostFtdcVolumeType	BidVolume2;
	///申卖价二
	TThostFtdcPriceType	AskPrice2;
	///申卖量二
	TThostFtdcVolumeType	AskVolume2;
	///申买价三
	TThostFtdcPriceType	BidPrice3;
	///申买量三
	TThostFtdcVolumeType	BidVolume3;
	///申卖价三
	TThostFtdcPriceType	AskPrice3;
	///申卖量三
	TThostFtdcVolumeType	AskVolume3;
	///申买价四
	TThostFtdcPriceType	BidPrice4;
	///申买量四
	TThostFtdcVolumeType	BidVolume4;
	///申卖价四
	TThostFtdcPriceType	AskPrice4;
	///申卖量四
	TThostFtdcVolumeType	AskVolume4;
	///申买价五
	TThostFtdcPriceType	BidPrice5;
	///申买量五
	TThostFtdcVolumeType	BidVolume5;
	///申卖价五
	TThostFtdcPriceType	AskPrice5;
	///申卖量五
	TThostFtdcVolumeType	AskVolume5;
	///当日均价
	TThostFtdcPriceType	AveragePrice;
	///业务日期
	TThostFtdcDateType	ActionDay;
	///上带价
	TThostFtdcPriceType	BandingUpperPrice;
	///下带价
	TThostFtdcPriceType	BandingLowerPrice;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平现货指数
struct CThostFtdcSyncDeltaIndexPriceField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///指数现货收盘价
	TThostFtdcPriceType	ClosePrice;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平仓单折抵
struct CThostFtdcSyncDeltaEWarrantOffsetField
{
	///交易日期
	TThostFtdcTradeDateType	TradingDay;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///数量
	TThostFtdcVolumeType	Volume;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///SPBM期货合约保证金参数
struct CThostFtdcSPBMFutureParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///期货合约因子
	TThostFtdcVolumeMultipleType	Cvf;
	///阶段标识
	TThostFtdcTimeRangeType	TimeRange;
	///品种保证金标准
	TThostFtdcRatioType	MarginRate;
	///期货合约内部对锁仓费率折扣比例
	TThostFtdcRatioType	LockRateX;
	///提高保证金标准
	TThostFtdcRatioType	AddOnRate;
	///昨结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///期货合约内部对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnLockRateX2;
};

///SPBM期权合约保证金参数
struct CThostFtdcSPBMOptionParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///期权合约因子
	TThostFtdcVolumeMultipleType	Cvf;
	///期权冲抵价格
	TThostFtdcPriceType	DownPrice;
	///Delta值
	TThostFtdcDeltaType	Delta;
	///卖方期权风险转换最低值
	TThostFtdcDeltaType	SlimiDelta;
	///昨结算价
	TThostFtdcPriceType	PreSettlementPrice;
};

///SPBM品种内对锁仓折扣参数
struct CThostFtdcSPBMIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///品种内合约间对锁仓费率折扣比例
	TThostFtdcRatioType	IntraRateY;
	///品种内合约间对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnIntraRateY2;
};

///SPBM跨品种抵扣参数
struct CThostFtdcSPBMInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓费率折扣比例
	TThostFtdcRatioType	InterRateZ;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
};

///同步SPBM参数结束
struct CThostFtdcSyncSPBMParameterEndField
{
	///交易日
	TThostFtdcDateType	TradingDay;
};

///SPBM期货合约保证金参数查询
struct CThostFtdcQrySPBMFutureParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///SPBM期权合约保证金参数查询
struct CThostFtdcQrySPBMOptionParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///SPBM品种内对锁仓折扣参数查询
struct CThostFtdcQrySPBMIntraParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///SPBM跨品种抵扣参数查询
struct CThostFtdcQrySPBMInterParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
};

///组合保证金套餐
struct CThostFtdcSPBMPortfDefinitionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///组合保证金套餐代码
	TThostFtdcPortfolioDefIDType	PortfolioDefID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///是否启用SPBM
	TThostFtdcBoolType	IsSPBM;
};

///投资者套餐选择
struct CThostFtdcSPBMInvestorPortfDefField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///组合保证金套餐代码
	TThostFtdcPortfolioDefIDType	PortfolioDefID;
};

///投资者新型组合保证金系数
struct CThostFtdcInvestorPortfMarginRatioField
{
	///投资者范围
	TThostFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员对投资者收取的保证金和交易所对投资者收取的保证金的比例
	TThostFtdcRatioType	MarginRatio;
	///产品群代码
	TThostFtdcProductIDType	ProductGroupID;
};

///组合保证金套餐查询
struct CThostFtdcQrySPBMPortfDefinitionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///组合保证金套餐代码
	TThostFtdcPortfolioDefIDType	PortfolioDefID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///投资者套餐选择查询
struct CThostFtdcQrySPBMInvestorPortfDefField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

///投资者新型组合保证金系数查询
struct CThostFtdcQryInvestorPortfMarginRatioField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品群代码
	TThostFtdcProductIDType	ProductGroupID;
};

///投资者产品SPBM明细
struct CThostFtdcInvestorProdSPBMDetailField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///合约内对锁保证金
	TThostFtdcMoneyType	IntraInstrMargin;
	///买归集保证金
	TThostFtdcMoneyType	BCollectingMargin;
	///卖归集保证金
	TThostFtdcMoneyType	SCollectingMargin;
	///品种内合约间对锁保证金
	TThostFtdcMoneyType	IntraProdMargin;
	///净保证金
	TThostFtdcMoneyType	NetMargin;
	///产品间对锁保证金
	TThostFtdcMoneyType	InterProdMargin;
	///裸保证金
	TThostFtdcMoneyType	SingleMargin;
	///附加保证金
	TThostFtdcMoneyType	AddOnMargin;
	///交割月保证金
	TThostFtdcMoneyType	DeliveryMargin;
	///看涨期权最低风险
	TThostFtdcMoneyType	CallOptionMinRisk;
	///看跌期权最低风险
	TThostFtdcMoneyType	PutOptionMinRisk;
	///卖方期权最低风险
	TThostFtdcMoneyType	OptionMinRisk;
	///买方期权冲抵价值
	TThostFtdcMoneyType	OptionValueOffset;
	///卖方期权权利金
	TThostFtdcMoneyType	OptionRoyalty;
	///价值冲抵
	TThostFtdcMoneyType	RealOptionValueOffset;
	///保证金
	TThostFtdcMoneyType	Margin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
};

///投资者产品SPBM明细查询
struct CThostFtdcQryInvestorProdSPBMDetailField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///组保交易参数设置
struct CThostFtdcPortfTradeParamSettingField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///新型组保算法
	TThostFtdcPortfolioType	Portfolio;
	///撤单是否验资
	TThostFtdcBoolType	IsActionVerify;
	///平仓是否验资
	TThostFtdcBoolType	IsCloseVerify;
};

///投资者交易权限设置
struct CThostFtdcInvestorTradingRightField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///交易权限
	TThostFtdcInvstTradingRightType	InvstTradingRight;
};

///质押配比参数
struct CThostFtdcMortgageParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///质押配比系数
	TThostFtdcRatioType	MortgageBalance;
	///开仓是否验证质押配比
	TThostFtdcBoolType	CheckMortgageRatio;
};

///可提控制参数
struct CThostFtdcWithDrawParamField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///参数代码
	TThostFtdcWithDrawParamIDType	WithDrawParamID;
	///参数代码值
	TThostFtdcWithDrawParamValueType	WithDrawParamValue;
};

///Thost终端用户功能权限
struct CThostFtdcThostUserFunctionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///Thost终端功能代码
	TThostFtdcThostFunctionCodeType	ThostFunctionCode;
};

///Thost终端用户功能权限查询
struct CThostFtdcQryThostUserFunctionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///用户代码
	TThostFtdcUserIDType	UserID;
};

///SPBM附加跨品种抵扣参数
struct CThostFtdcSPBMAddOnInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnInterRateZ2;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
};

///SPBM附加跨品种抵扣参数查询
struct CThostFtdcQrySPBMAddOnInterParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
};

///投资者商品组SPMM记录查询
struct CThostFtdcQryInvestorCommoditySPMMMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
};

///投资者商品群SPMM记录查询
struct CThostFtdcQryInvestorCommodityGroupSPMMMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
};

///SPMM合约参数查询
struct CThostFtdcQrySPMMInstParamField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///SPMM产品参数查询
struct CThostFtdcQrySPMMProductParamField
{
	///产品代码
	TThostFtdcSPMMProductIDType	ProductID;
};

///投资者商品组SPMM记录
struct CThostFtdcInvestorCommoditySPMMMarginField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
	///优惠仓位应收保证金
	TThostFtdcMoneyType	MarginBeforeDiscount;
	///不优惠仓位应收保证金
	TThostFtdcMoneyType	MarginNoDiscount;
	///多头实仓风险
	TThostFtdcMoneyType	LongPosRisk;
	///多头开仓冻结风险
	TThostFtdcMoneyType	LongOpenFrozenRisk;
	///多头被平冻结风险
	TThostFtdcMoneyType	LongCloseFrozenRisk;
	///空头实仓风险
	TThostFtdcMoneyType	ShortPosRisk;
	///空头开仓冻结风险
	TThostFtdcMoneyType	ShortOpenFrozenRisk;
	///空头被平冻结风险
	TThostFtdcMoneyType	ShortCloseFrozenRisk;
	///SPMM品种内跨期优惠系数
	TThostFtdcSPMMDiscountRatioType	IntraCommodityRate;
	///SPMM期权优惠系数
	TThostFtdcSPMMDiscountRatioType	OptionDiscountRate;
	///实仓对冲优惠金额
	TThostFtdcMoneyType	PosDiscount;
	///开仓报单对冲优惠金额
	TThostFtdcMoneyType	OpenFrozenDiscount;
	///品种风险净头
	TThostFtdcMoneyType	NetRisk;
	///平仓冻结保证金
	TThostFtdcMoneyType	CloseFrozenMargin;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///手续费
	TThostFtdcMoneyType	Commission;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///行权冻结资金
	TThostFtdcMoneyType	StrikeFrozenMargin;
};

///投资者商品群SPMM记录
struct CThostFtdcInvestorCommodityGroupSPMMMarginField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
	///优惠仓位应收保证金
	TThostFtdcMoneyType	MarginBeforeDiscount;
	///不优惠仓位应收保证金
	TThostFtdcMoneyType	MarginNoDiscount;
	///多头风险
	TThostFtdcMoneyType	LongRisk;
	///空头风险
	TThostFtdcMoneyType	ShortRisk;
	///商品群平仓冻结保证金
	TThostFtdcMoneyType	CloseFrozenMargin;
	///SPMM跨品种优惠系数
	TThostFtdcSPMMDiscountRatioType	InterCommodityRate;
	///商品群最小保证金比例
	TThostFtdcSPMMDiscountRatioType	MiniMarginRatio;
	///投资者保证金和交易所保证金的比例
	TThostFtdcRatioType	AdjustRatio;
	///SPMM品种内优惠汇总
	TThostFtdcMoneyType	IntraCommodityDiscount;
	///SPMM跨品种优惠
	TThostFtdcMoneyType	InterCommodityDiscount;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///投资者保证金
	TThostFtdcMoneyType	InvestorMargin;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///手续费
	TThostFtdcMoneyType	Commission;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///行权冻结资金
	TThostFtdcMoneyType	StrikeFrozenMargin;
};

///SPMM合约参数
struct CThostFtdcSPMMInstParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///SPMM合约保证金算法
	TThostFtdcInstMarginCalIDType	InstMarginCalID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
};

///SPMM产品参数
struct CThostFtdcSPMMProductParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcSPMMProductIDType	ProductID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
};

///席位与交易中心对应关系维护查询
struct CThostFtdcQryTraderAssignField
{
	///交易员代码
	TThostFtdcTraderIDType	TraderID;
};

///席位与交易中心对应关系
struct CThostFtdcTraderAssignField
{
	///应用单元代码
	TThostFtdcBrokerIDType	BrokerID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///交易中心代码
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///投资者申报费阶梯收取设置
struct CThostFtdcInvestorInfoCntSettingField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///商品代码
	TThostFtdcProductIDType	ProductID;
	///是否收取申报费
	TThostFtdcBoolType	IsCalInfoComm;
	///是否限制信息量
	TThostFtdcBoolType	IsLimitInfoMax;
	///信息量限制笔数
	TThostFtdcVolumeType	InfoMaxLimit;
};

///RCAMS产品组合信息
struct CThostFtdcRCAMSCombProductInfoField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcProductIDType	ProductID;
	///商品组代码
	TThostFtdcProductIDType	CombProductID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
};

///RCAMS同合约风险对冲参数
struct CThostFtdcRCAMSInstrParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcProductIDType	ProductID;
	///同合约风险对冲比率
	TThostFtdcHedgeRateType	HedgeRate;
};

///RCAMS品种内风险对冲参数
struct CThostFtdcRCAMSIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///品种内对冲比率
	TThostFtdcHedgeRateType	HedgeRate;
};

///RCAMS跨品种风险折抵参数
struct CThostFtdcRCAMSInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
	///优先级
	TThostFtdcRCAMSPriorityType	Priority;
	///折抵率
	TThostFtdcHedgeRateType	CreditRate;
	///产品组合代码1
	TThostFtdcProductIDType	CombProduct1;
	///产品组合代码2
	TThostFtdcProductIDType	CombProduct2;
};

///RCAMS空头期权风险调整参数
struct CThostFtdcRCAMSShortOptAdjustParamField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///空头期权风险调整标准
	TThostFtdcAdjustValueType	AdjustValue;
};

///RCAMS策略组合持仓
struct CThostFtdcRCAMSInvestorCombPositionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///交易所组合合约代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///持仓量
	TThostFtdcVolumeType	TotalAmt;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
};

///投资者品种RCAMS保证金
struct CThostFtdcInvestorProdRCAMSMarginField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
	///品种组合前风险
	TThostFtdcMoneyType	RiskBeforeDiscount;
	///同合约对冲风险
	TThostFtdcMoneyType	IntraInstrRisk;
	///品种买持仓风险
	TThostFtdcMoneyType	BPosRisk;
	///品种卖持仓风险
	TThostFtdcMoneyType	SPosRisk;
	///品种内对冲风险
	TThostFtdcMoneyType	IntraProdRisk;
	///品种净持仓风险
	TThostFtdcMoneyType	NetRisk;
	///品种间对冲风险
	TThostFtdcMoneyType	InterProdRisk;
	///空头期权风险调整
	TThostFtdcMoneyType	ShortOptRiskAdj;
	///空头期权权利金
	TThostFtdcMoneyType	OptionRoyalty;
	///大边组合平仓冻结保证金
	TThostFtdcMoneyType	MMSACloseFrozenMargin;
	///策略组合平仓/行权冻结保证金
	TThostFtdcMoneyType	CloseCombFrozenMargin;
	///平仓/行权冻结保证金
	TThostFtdcMoneyType	CloseFrozenMargin;
	///大边组合开仓冻结保证金
	TThostFtdcMoneyType	MMSAOpenFrozenMargin;
	///交割月期货开仓冻结保证金
	TThostFtdcMoneyType	DeliveryOpenFrozenMargin;
	///开仓冻结保证金
	TThostFtdcMoneyType	OpenFrozenMargin;
	///投资者冻结保证金
	TThostFtdcMoneyType	UseFrozenMargin;
	///大边组合交易所持仓保证金
	TThostFtdcMoneyType	MMSAExchMargin;
	///交割月期货交易所持仓保证金
	TThostFtdcMoneyType	DeliveryExchMargin;
	///策略组合交易所保证金
	TThostFtdcMoneyType	CombExchMargin;
	///交易所持仓保证金
	TThostFtdcMoneyType	ExchMargin;
	///投资者持仓保证金
	TThostFtdcMoneyType	UseMargin;
};

///RCAMS产品组合信息查询
struct CThostFtdcQryRCAMSCombProductInfoField
{
	///产品代码
	TThostFtdcProductIDType	ProductID;
	///商品组代码
	TThostFtdcProductIDType	CombProductID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
};

///RCAMS同合约风险对冲参数查询
struct CThostFtdcQryRCAMSInstrParameterField
{
	///产品代码
	TThostFtdcProductIDType	ProductID;
};

///RCAMS品种内风险对冲参数查询
struct CThostFtdcQryRCAMSIntraParameterField
{
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
};

///RCAMS跨品种风险折抵参数查询
struct CThostFtdcQryRCAMSInterParameterField
{
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
	///产品组合代码1
	TThostFtdcProductIDType	CombProduct1;
	///产品组合代码2
	TThostFtdcProductIDType	CombProduct2;
};

///RCAMS空头期权风险调整参数查询
struct CThostFtdcQryRCAMSShortOptAdjustParamField
{
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
};

///RCAMS策略组合持仓查询
struct CThostFtdcQryRCAMSInvestorCombPositionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
};

///投资者品种RCAMS保证金查询
struct CThostFtdcQryInvestorProdRCAMSMarginField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
};

///RULE合约保证金参数
struct CThostFtdcRULEInstrParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约类型
	TThostFtdcInstrumentClassType	InstrumentClass;
	///标准合约
	TThostFtdcInstrumentIDType	StdInstrumentID;
	///投机买折算系数
	TThostFtdcRatioType	BSpecRatio;
	///投机卖折算系数
	TThostFtdcRatioType	SSpecRatio;
	///套保买折算系数
	TThostFtdcRatioType	BHedgeRatio;
	///套保卖折算系数
	TThostFtdcRatioType	SHedgeRatio;
	///买附加风险保证金
	TThostFtdcMoneyType	BAddOnMargin;
	///卖附加风险保证金
	TThostFtdcMoneyType	SAddOnMargin;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
};

///RULE品种内对锁仓折扣参数
struct CThostFtdcRULEIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///标准合约
	TThostFtdcInstrumentIDType	StdInstrumentID;
	///标准合约保证金
	TThostFtdcMoneyType	StdInstrMargin;
	///一般月份合约组合保证金系数
	TThostFtdcRatioType	UsualIntraRate;
	///临近交割合约组合保证金系数
	TThostFtdcRatioType	DeliveryIntraRate;
};

///RULE跨品种抵扣参数
struct CThostFtdcRULEInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓费率折扣比例
	TThostFtdcRatioType	InterRate;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
	///腿1比例系数
	TThostFtdcCommonIntType	Leg1PropFactor;
	///腿2比例系数
	TThostFtdcCommonIntType	Leg2PropFactor;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
	///商品群名称
	TThostFtdcInstrumentNameType	CommodityGroupName;
};

///RULE合约保证金参数查询
struct CThostFtdcQryRULEInstrParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};

///RULE品种内对锁仓折扣参数查询
struct CThostFtdcQryRULEIntraParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
};

///RULE跨品种抵扣参数查询
struct CThostFtdcQryRULEInterParameterField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
};

///投资者产品RULE保证金
struct CThostFtdcInvestorProdRULEMarginField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///合约类型
	TThostFtdcInstrumentClassType	InstrumentClass;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
	///买标准持仓
	TThostFtdcStdPositionType	BStdPosition;
	///卖标准持仓
	TThostFtdcStdPositionType	SStdPosition;
	///买标准开仓冻结
	TThostFtdcStdPositionType	BStdOpenFrozen;
	///卖标准开仓冻结
	TThostFtdcStdPositionType	SStdOpenFrozen;
	///买标准平仓冻结
	TThostFtdcStdPositionType	BStdCloseFrozen;
	///卖标准平仓冻结
	TThostFtdcStdPositionType	SStdCloseFrozen;
	///品种内对冲标准持仓
	TThostFtdcStdPositionType	IntraProdStdPosition;
	///品种内单腿标准持仓
	TThostFtdcStdPositionType	NetStdPosition;
	///品种间对冲标准持仓
	TThostFtdcStdPositionType	InterProdStdPosition;
	///单腿标准持仓
	TThostFtdcStdPositionType	SingleStdPosition;
	///品种内对锁保证金
	TThostFtdcMoneyType	IntraProdMargin;
	///品种间对锁保证金
	TThostFtdcMoneyType	InterProdMargin;
	///跨品种单腿保证金
	TThostFtdcMoneyType	SingleMargin;
	///非组合合约保证金
	TThostFtdcMoneyType	NonCombMargin;
	///附加保证金
	TThostFtdcMoneyType	AddOnMargin;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///附加冻结保证金
	TThostFtdcMoneyType	AddOnFrozenMargin;
	///开仓冻结保证金
	TThostFtdcMoneyType	OpenFrozenMargin;
	///平仓冻结保证金
	TThostFtdcMoneyType	CloseFrozenMargin;
	///品种保证金
	TThostFtdcMoneyType	Margin;
	///冻结保证金
	TThostFtdcMoneyType	FrozenMargin;
};

///投资者产品RULE保证金查询
struct CThostFtdcQryInvestorProdRULEMarginField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
};

///风险结算追平SPBM组合保证金套餐
struct CThostFtdcSyncDeltaSPBMPortfDefinitionField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///组合保证金套餐代码
	TThostFtdcPortfolioDefIDType	PortfolioDefID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///是否启用SPBM
	TThostFtdcBoolType	IsSPBM;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平投资者SPBM套餐选择
struct CThostFtdcSyncDeltaSPBMInvstPortfDefField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///组合保证金套餐代码
	TThostFtdcPortfolioDefIDType	PortfolioDefID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPBM期货合约保证金参数
struct CThostFtdcSyncDeltaSPBMFutureParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///期货合约因子
	TThostFtdcVolumeMultipleType	Cvf;
	///阶段标识
	TThostFtdcTimeRangeType	TimeRange;
	///品种保证金标准
	TThostFtdcRatioType	MarginRate;
	///期货合约内部对锁仓费率折扣比例
	TThostFtdcRatioType	LockRateX;
	///提高保证金标准
	TThostFtdcRatioType	AddOnRate;
	///昨结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///期货合约内部对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnLockRateX2;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPBM期权合约保证金参数
struct CThostFtdcSyncDeltaSPBMOptionParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///期权合约因子
	TThostFtdcVolumeMultipleType	Cvf;
	///期权冲抵价格
	TThostFtdcPriceType	DownPrice;
	///Delta值
	TThostFtdcDeltaType	Delta;
	///卖方期权风险转换最低值
	TThostFtdcDeltaType	SlimiDelta;
	///昨结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPBM品种内对锁仓折扣参数
struct CThostFtdcSyncDeltaSPBMIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///品种内合约间对锁仓费率折扣比例
	TThostFtdcRatioType	IntraRateY;
	///品种内合约间对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnIntraRateY2;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPBM跨品种抵扣参数
struct CThostFtdcSyncDeltaSPBMInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓费率折扣比例
	TThostFtdcRatioType	InterRateZ;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPBM附加跨品种抵扣参数
struct CThostFtdcSyncDeltaSPBMAddOnInterParamField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓附加费率折扣比例
	TThostFtdcRatioType	AddOnInterRateZ2;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPMM合约参数
struct CThostFtdcSyncDeltaSPMMInstParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///SPMM合约保证金算法
	TThostFtdcInstMarginCalIDType	InstMarginCalID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPMM产品相关参数
struct CThostFtdcSyncDeltaSPMMProductParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcSPMMProductIDType	ProductID;
	///商品组代码
	TThostFtdcSPMMProductIDType	CommodityID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平投资者SPMM模板选择
struct CThostFtdcSyncDeltaInvestorSPMMModelField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///SPMM模板ID
	TThostFtdcSPMMModelIDType	SPMMModelID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平SPMM模板参数设置
struct CThostFtdcSyncDeltaSPMMModelParamField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///SPMM模板ID
	TThostFtdcSPMMModelIDType	SPMMModelID;
	///商品群代码
	TThostFtdcSPMMProductIDType	CommodityGroupID;
	///SPMM品种内跨期优惠系数
	TThostFtdcSPMMDiscountRatioType	IntraCommodityRate;
	///SPMM品种间优惠系数
	TThostFtdcSPMMDiscountRatioType	InterCommodityRate;
	///SPMM期权优惠系数
	TThostFtdcSPMMDiscountRatioType	OptionDiscountRate;
	///商品群最小保证金比例
	TThostFtdcSPMMDiscountRatioType	MiniMarginRatio;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS产品组合信息
struct CThostFtdcSyncDeltaRCAMSCombProdInfoField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcProductIDType	ProductID;
	///商品组代码
	TThostFtdcProductIDType	CombProductID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS同合约风险对冲参数
struct CThostFtdcSyncDeltaRCAMSInstrParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品代码
	TThostFtdcProductIDType	ProductID;
	///同合约风险对冲比率
	TThostFtdcHedgeRateType	HedgeRate;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS品种内风险对冲参数
struct CThostFtdcSyncDeltaRCAMSIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///品种内对冲比率
	TThostFtdcHedgeRateType	HedgeRate;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS跨品种风险折抵参数
struct CThostFtdcSyncDeltaRCAMSInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///商品群代码
	TThostFtdcProductIDType	ProductGroupID;
	///优先级
	TThostFtdcRCAMSPriorityType	Priority;
	///折抵率
	TThostFtdcHedgeRateType	CreditRate;
	///产品组合代码1
	TThostFtdcProductIDType	CombProduct1;
	///产品组合代码2
	TThostFtdcProductIDType	CombProduct2;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS空头期权风险调整参数
struct CThostFtdcSyncDeltaRCAMSSOptAdjParamField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///产品组合代码
	TThostFtdcProductIDType	CombProductID;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///空头期权风险调整标准
	TThostFtdcAdjustValueType	AdjustValue;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS策略组合规则明细
struct CThostFtdcSyncDeltaRCAMSCombRuleDtlField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///策略产品
	TThostFtdcProductIDType	ProdGroup;
	///策略id
	TThostFtdcRuleIdType	RuleId;
	///优先级
	TThostFtdcRCAMSPriorityType	Priority;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///组合保证金标准
	TThostFtdcMoneyType	CombMargin;
	///交易所组合合约代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///单腿合约代码
	TThostFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///单腿乘数
	TThostFtdcLegMultipleType	LegMultiple;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RCAMS策略组合持仓
struct CThostFtdcSyncDeltaRCAMSInvstCombPosField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///投套标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///组合合约代码
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TThostFtdcLegIDType	LegID;
	///交易所组合合约代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///持仓量
	TThostFtdcVolumeType	TotalAmt;
	///交易所保证金
	TThostFtdcMoneyType	ExchMargin;
	///投资者保证金
	TThostFtdcMoneyType	Margin;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RULE合约保证金参数
struct CThostFtdcSyncDeltaRULEInstrParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约类型
	TThostFtdcInstrumentClassType	InstrumentClass;
	///标准合约
	TThostFtdcInstrumentIDType	StdInstrumentID;
	///投机买折算系数
	TThostFtdcRatioType	BSpecRatio;
	///投机卖折算系数
	TThostFtdcRatioType	SSpecRatio;
	///套保买折算系数
	TThostFtdcRatioType	BHedgeRatio;
	///套保卖折算系数
	TThostFtdcRatioType	SHedgeRatio;
	///买附加风险保证金
	TThostFtdcMoneyType	BAddOnMargin;
	///卖附加风险保证金
	TThostFtdcMoneyType	SAddOnMargin;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RULE品种内对锁仓折扣参数
struct CThostFtdcSyncDeltaRULEIntraParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///品种代码
	TThostFtdcInstrumentIDType	ProdFamilyCode;
	///标准合约
	TThostFtdcInstrumentIDType	StdInstrumentID;
	///标准合约保证金
	TThostFtdcMoneyType	StdInstrMargin;
	///一般月份合约组合保证金系数
	TThostFtdcRatioType	UsualIntraRate;
	///临近交割合约组合保证金系数
	TThostFtdcRatioType	DeliveryIntraRate;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///风险结算追平RULE跨品种抵扣参数
struct CThostFtdcSyncDeltaRULEInterParameterField
{
	///交易日
	TThostFtdcDateType	TradingDay;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///优先级
	TThostFtdcSpreadIdType	SpreadId;
	///品种间对锁仓费率折扣比例
	TThostFtdcRatioType	InterRate;
	///第一腿构成品种
	TThostFtdcInstrumentIDType	Leg1ProdFamilyCode;
	///第二腿构成品种
	TThostFtdcInstrumentIDType	Leg2ProdFamilyCode;
	///腿1比例系数
	TThostFtdcCommonIntType	Leg1PropFactor;
	///腿2比例系数
	TThostFtdcCommonIntType	Leg2PropFactor;
	///商品群号
	TThostFtdcCommodityGroupIDType	CommodityGroupID;
	///商品群名称
	TThostFtdcInstrumentNameType	CommodityGroupName;
	///操作标志
	TThostFtdcActionDirectionType	ActionDirection;
	///追平序号
	TThostFtdcSequenceNoType	SyncDeltaSequenceNo;
};

///退出紧急状态参数
struct CThostFtdcExitEmergencyField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
};

///新组保保证金系数投资者模板对应关系
struct CThostFtdcInvestorPortfMarginModelField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///保证金系数模板
	TThostFtdcInvestorIDType	MarginModelID;
};

///投资者新组保设置
struct CThostFtdcInvestorPortfSettingField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者编号
	TThostFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///是否开启新组保
	TThostFtdcBoolType	UsePortf;
};

///投资者新组保设置查询
struct CThostFtdcQryInvestorPortfSettingField
{
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者编号
	TThostFtdcInvestorIDType	InvestorID;
};


///前置信息
struct CThostFtdcFrontInfoField
{
	///前置地址
	TThostFtdcAddressType  FrontAddr;
	///查询频率
	TThostFtdcQueryFreqType QryFreq;
	///FTD频率
	TThostFtdcQueryFreqType FTDPkgFreq;
};

#endif
