#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwBasicCTAStrategy.h"
#include "cwPandoraAgentManager.h"

#include "cwDualTrust.h"

class cwCTAPlatform :
    public cwBasicKindleStrategy
{
public:
	enum cwStrategyEnum:int
	{
		cw_DualTrust_Strategy = 0
		, cwJackC_Strategy
		, cwJackA_Strategy
		, cwStrategyCount
	};


	struct StrategyContext
	{
		cwKindleSeriesPtr pKindleSeries;
	};

#ifdef _MSC_VER
#pragma region CommenDefine
#endif // _MSC_VER
	struct StrategyParameter
	{
		std::string	StrategyID;

		std::string StrategyName;

		bool		bIndex;
		int			iTimeScale;
		std::string InstrumentID;

		double		dMultiple;

		union
		{
			double			ParaList[50];
			struct
			{
				double		CTAPara1;
				double		CTAPara2;
				double		CTAPara3;
				double		CTAPara4;
				double		CTAPara5;
				double		CTAPara6;
				double		CTAPara7;
				double		CTAPara8;
				double		CTAPara9;
				double		CTAPara10;
				double		CTAPara11;
				double		CTAPara12;
				double		CTAPara13;
				double		CTAPara14;
				double		CTAPara15;
				double		CTAPara16;
				double		CTAPara17;
				double		CTAPara18;
				double		CTAPara19;
				double		CTAPara20;
				double		CTAPara21;
				double		CTAPara22;
				double		CTAPara23;
				double		CTAPara24;
				double		CTAPara25;
				double		CTAPara26;
				double		CTAPara27;
				double		CTAPara28;
				double		CTAPara29;
				double		CTAPara30;
				double		CTAPara31;
				double		CTAPara32;
				double		CTAPara33;
				double		CTAPara34;
				double		CTAPara35;
				double		CTAPara36;
				double		CTAPara37;
				double		CTAPara38;
				double		CTAPara39;
				double		CTAPara40;
				double		CTAPara41;
				double		CTAPara42;
				double		CTAPara43;
				double		CTAPara44;
				double		CTAPara45;
				double		CTAPara46;
				double		CTAPara47;
				double		CTAPara48;
				double		CTAPara49;
				double		CTAPara50;

			};
		};

		StrategyParameter()
			: bIndex(true)
			, iTimeScale(60)
			, dMultiple(1.0)
		{
			memset(ParaList, 0, sizeof(ParaList));
		}
	};
	typedef std::shared_ptr<StrategyParameter>			StrategyParaPtr;

	struct TradeParameter
	{
		// Instrument
		bool		Pause;						//暂停程序对该合约的交易

		std::string InstrumentID;				//交易合约
		std::string	SignalInstrumentID;			//信号里对应的合约名
		double		Ratio;						//合约下单比例，
		bool		Mod;						//下单合约mod，1则向下取整，0则向上去整。

		cwOpenCloseMode InsOpenCloseMode;		//开平模式
		int			InsLargeOrderVolume;		//大单量，大于其认为大单
		int			InsLittleOrderVolume;		//小单量，小于其认为小单
		int			InsAskBidGap;				//盘口价差
		int			InsAddTick;					//报单超价
		int			InsWaitInterval;			//挂单离盘口价差 撤单门限值

		TradeParameter()
			: Pause(false)
			, Ratio(0)
			, Mod(true)
			, InsOpenCloseMode(cwOpenCloseMode::CloseTodayThenYd)
			, InsLargeOrderVolume(100000)
			, InsLittleOrderVolume(100000)
			, InsAskBidGap(1)
			, InsAddTick(0)
			, InsWaitInterval(1)
		{

		}
		TradeParameter(TradeParameter& copy)
		{
			Pause = copy.Pause;

			InstrumentID = copy.InstrumentID;
			SignalInstrumentID = copy.SignalInstrumentID;
			Ratio = copy.Ratio;
			Mod = copy.Mod;

			InsOpenCloseMode = copy.InsOpenCloseMode;
			InsLargeOrderVolume = copy.InsLargeOrderVolume;
			InsLittleOrderVolume = copy.InsLittleOrderVolume;
			InsAskBidGap = copy.InsAskBidGap;
			InsAddTick = copy.InsAddTick;
			InsWaitInterval = copy.InsWaitInterval;
		}
	};
	typedef std::shared_ptr<TradeParameter>				TradeParaPtr;

	struct ManualIntervention
	{
		bool Manual;

		std::string InstrumentID;
		std::string StrategyName;
		int			ExpectedPosition;

		ManualIntervention()
			: Manual(false)
			, ExpectedPosition(0)
		{

		}
	};
	typedef std::shared_ptr<ManualIntervention>			ManualInterventionPtr;

	struct StrategyInstrumentUnion
	{
		std::string InstrumentID;		//InstrumentID
		std::string StrategyName;

		bool operator == (const StrategyInstrumentUnion& p) const
		{
			if (InstrumentID == p.InstrumentID
				&& StrategyName == p.StrategyName)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool operator < (const StrategyInstrumentUnion& p) const
		{
			if (StrategyName < p.StrategyName)
			{
				return true;
			}
			else
			{
				if (StrategyName == p.StrategyName
					&& InstrumentID < p.InstrumentID)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	};

#ifdef _MSC_VER
#pragma endregion
#endif

	struct CTAStrategyInfo
	{
		cwBasicCTAStrategy	*	_pStrategy;
		std::string				_StrategyID;
		StrategyParaPtr			_pParameter;
	};
	typedef std::shared_ptr<CTAStrategyInfo>					CTAStrategyInfoPtr;

	//struct 
public:
	//获取策略版本号
	virtual std::string  GetStrategyVersion();
	//表示策略名称
	virtual std::string  GetStrategyName();

	//MarketData SPI
	///行情更新
	virtual void			PriceUpdate(cwMarketDataPtr pPriceData);
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);

	virtual void			OnReady();

	virtual  void	InitialStrategy(const char* pConfigFilePath);
	bool			IsNearDeliverDateWarning(const char* szInstrumentID);
	int				GetTradingDayRemainWarning(const char* szInstrumentID);

	bool			ReadXmlConfigFile(const char * pConfigFilePath, bool bNeedDisPlay = true);



	bool		 AddStrategyToPools(std::string strStrategyID, cwBasicCTAStrategy * pCTAStrategy, StrategyParaPtr pPara);
	void		 SetKindle(std::string strStrategyID, bool bIndex, const char* szInstrumentID, int iTimeScale, int HisKindleCount);

	int			MergeStrategyPosition(std::string InstrumentID);
	
	cwInstrumentDataPtr GetFirstInstrumentData(std::string ProductID);

	///strategy parameter
	//策略运行代号
	std::string			m_strStrategyName;
	std::string			m_strCurrentUpdateTime;

	//策略是否运行
	bool		m_bStrategyRun;
	bool		m_bShowPosition;

protected:
	//配置参数
	//Key:StrategyID
	std::unordered_map<std::string, StrategyParaPtr>					m_StrategyParameterMap;
	//Key:TradeInstrumentID
	std::unordered_map<std::string, TradeParaPtr>						m_TradeParameterMap;

	//Strategy pool策略池
	//key:Intrument, key:TimeScale
	std::unordered_map<std::string, std::unordered_map<int, std::deque<CTAStrategyInfoPtr>>>		m_InsCTAStrategyList;
	//Key:StrategyID
	std::unordered_map<std::string, CTAStrategyInfoPtr>					m_NameCTAStrategy;

	//策略组合 Portfolio
	//key:
	std::unordered_map<std::string, std::deque<CTAStrategyInfoPtr>>		m_PortfolioStrategyList;


	//key:SignalInstrument, key:StrategyID
	std::unordered_map<std::string, std::unordered_map<std::string, int>> m_cwStrategyPositionMap;


	//Deal Trade Signal
	TradeParameter									m_cwTradeParameter;
	cwPandoraAgentManager::cwAgentDataPtr			m_pAgentData;

	bool		GetParameter(const char * szInstrumentID);
	int			GetExpectedPosition(std::string InstrumentID);


	//Agent
	cwPandoraAgentManager											m_PandoraAgentManager;		//代理人管理者，可通过他创建代理人
	cwPandoraAgentManager::cwAgentDataPtr							m_pPositionAgent;			//仓位管理代理人，要指定合约
	std::map<std::string, cwPandoraAgentManager::cwAgentDataPtr>	m_cwAgentDataMap;	//key Instrument value AgentData



	cwStrategyLog			m_StrategyLog;

	std::string				m_strConfigFileFullPath;
	bool					m_bFirstGetConfig;
	time_t					m_tLastestGetConfigTime;

	cwMUTEX					m_ParameterMutex;

};

