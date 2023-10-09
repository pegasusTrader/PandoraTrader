//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on May. 10th 2022
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

//Note:
//曾经在坊间售卖该策略源码，整工程作为盲盒出售，定价约3万
//策略主要逻辑为追涨杀跌，现将策略要义抽出，作为一个示例策略，仅供参考，
//如用于交易，请务必了解策略逻辑，设置合适品种及参数，并自负盈亏。

#pragma once
#include "cwBasicKindleStrategy.h"

class cwChasingRisingStrategy :
    public cwBasicKindleStrategy
{
public:
	//获取策略版本号
	virtual std::string  GetStrategyVersion();
	//表示策略名称
	virtual std::string  GetStrategyName();

	//MarketData SPI
	///行情更新
	virtual void			PriceUpdate(cwMarketDataPtr pPriceData);
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) {};


	//Trade SPI
	///成交回报
	virtual void OnRtnTrade(cwTradePtr pTrade);
	///报单回报
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	///撤单成功
	virtual void OnOrderCanceled(cwOrderPtr pOrder) {};

	virtual void OnStrategyTimer(int iTimerId, const char* szInstrumentID) {};
	virtual void OnReady();

	virtual  void InitialStrategy(const char* pConfigFilePath);
	bool		IsNearDeliverDateWarning(const char* szInstrumentID);
	int			GetTradingDayRemainWarning(const char* szInstrumentID);



	///strategy parameter
	//策略运行代号
	std::string m_strStrategyName;
	//策略是否运行, can be modified by config file
	bool		m_bStrategyRun;
	//显示持仓，can be modified by config file
	bool		m_bShowPosition;

	std::string	m_strCurrentUpdateTime;
	std::string	m_strExeFolderPath;

	struct StrategyParameter
	{
		//general
		bool        Manual;							//是否手动干预
		int			Portfolio;						//资产组合id

		int			TotalPositionLimit;				//总持仓限制
		int			OrderVolume;					//报单量

		double		dStep;							//步长

		//Instrument
		std::string Instrument;				//次主力合约
		cwOpenCloseMode OpenCloseMode;		//开平模式
		int			OpenCancelLimit;			//开仓撤单次数限制
		int			CloseCancelLimit;		//平仓撤单次数限制

		StrategyParameter()
			: Manual(false)
			, Portfolio(0)

			, TotalPositionLimit(0)
			, OrderVolume(1)

			, dStep(0.005)

			, OpenCloseMode(cwOpenCloseMode::CloseTodayThenYd)
			, OpenCancelLimit(350)
			, CloseCancelLimit(380)
		{

		}
	};
	typedef std::shared_ptr<StrategyParameter>			StrategyParaPtr;

	//Strategy Info Update By Strategy
	struct RunningParameter
	{
		cwMarketDataPtr LastMarketData;

		int64_t			baseTime;
		int64_t			oldTime;
		double			basePrice;
		double			dHighPx;
		double			dLowPx;
		std::string		strBaseTime;
		bool			bFirst;

		int				iTradeCnt;

		RunningParameter()
			: baseTime(0)
			, oldTime(0)
			, basePrice(0.0)
			, dHighPx(0.0)
			, dLowPx(0.0)
			, bFirst(true)
			, iTradeCnt(0)
		{
		}

	};
	typedef std::shared_ptr<RunningParameter>			cwRunningParaPtr;


	StrategyParameter									m_cwStrategyParameter;
	cwRunningParaPtr									m_cwRunningParaPtr;

	std::map<std::string, StrategyParaPtr>				m_StrategyParameterMap;		//key Instrument value:StrategyParameter
	std::map<std::string, cwRunningParaPtr>				m_cwRunningParameterMap;	//key Instrument value Running Parameter


	//Get Strategy Config
	bool ReadXmlConfigFile(const char* pConfigFilePath, bool bNeedDisPlay = true);
	bool				m_bFirstGetConfig;
	time_t				m_tLastestGetConfigTime;


	bool GetParameter(const char* szInstrumentID);

	void ChasingRising();

	int64_t TimeToint64(cwMarketDataPtr pData);

private:

	cwStrategyLog			m_StrategyLog;
	cwBasicCout				m_cwShow;

	int						m_iDoChasingRisingCount;


};

