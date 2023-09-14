#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwStrategyLog.h"
#include "cwSettlement.h"
#include "cwNetValueEvaluation.h"

//#define CW_NEED_STRATEGY_LOG

class cwBasicCTAStrategy
{
	//
public:
	struct cwCTAParaField
	{
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

	};

	struct TimeBalanceData
	{
		std::string		strDateTime;
		std::uint64_t	iTimeStamp;
		double			dBalance;
		double			dMaxFundOccupied;
	};
	typedef std::shared_ptr<TimeBalanceData> TimeBalanceDataPtr;


	struct EvaluatorTimeSeriesData
	{
		std::uint64_t	iTimeStamp;
		double			dNetAsset;					//净值曲线
		double			dTradingYears;				//累计交易年限（自然日计算）
		double          dIRR;						//年化复利
		double          dVolatility;				//日收益率的波动率
		double          dVolatilityDownward;		//下行波动率
		double          dAR;						//年化单利

		double          dDrawDownRatio;				//当前回撤比率
		double          dMaxDrawDownRatio;			//最大回撤率
		double          dAverageDDR;				//简单平均回撤率

		double          dSharpeRatio;				//夏普比率
		double          dSortinoRatio;				//索提诺比率
		double          dCalmarRatio;				//卡玛比率
		double          dSterlingRatio;				//斯特林比率
	};

public:
	cwBasicCTAStrategy(const char* szStrategyName);
	~cwBasicCTAStrategy();

	//初始化策略
	virtual void			InitialStrategy() {};
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) = 0;

	inline const char*		GetStrategyName() { return m_strStrategyName.c_str(); }

	void		 SetStrategyPosition(int iPosition, char * szInstrumentID = nullptr);
	int			 GetStrategyPosition(char* szInstrumentID = nullptr);

	double		 GetEntryPrice(std::string InstrumentID);
	size_t		 GetEntryIndex(std::string InstrumentID);
	const char * GetEntryTime(std::string InstrumentID);

	std::unordered_map<std::string,int>			m_iStrategyPositionMap;

	cwCTAParaField			m_StrategyPara;
	std::string				m_strDealInstrument;

	cwInstrumentDataPtr		m_pInstrument;
	//
	void					_PreOnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);
	void                    UpdateEvaluator(double dCurrentMoneyUsed, double dPreMoneyUsed, double dCurrentTotalProfit,
											std::string str_time, std::uint64_t timeStamp, double dExpectedRet);

protected:
	std::string				m_strStrategyName;

#ifdef CW_NEED_STRATEGY_LOG
public:
	cwStrategyLog			m_StrategyLog;
#endif // CW_NEED_STRATEGY_LOG

private:
	cwStrategyLog			m_StrategyTradeListLog;

	//
	std::unordered_map<std::string, double>			m_dEntryPrice;
	std::unordered_map<std::string, size_t>			m_iEntryIndex;
	std::unordered_map<std::string, std::string>	m_strEntryTime;
public:
	double					m_dLastPrice;			//当前价格
	size_t					m_iLastIndex;			//当前k线数
	std::string				m_strLastUpdateTime;	//当前行情时间

	//用于记录策略净值变化
	cwSettlement									m_cwSettlement;
	std::deque<TimeBalanceDataPtr>					m_dTimeBalanceDQ;//采用push back方法增加元素
	

	//策略评价器
	cwNetValueEvaluation                            m_cwEvaluator;
	std::deque< EvaluatorTimeSeriesData>            m_dEvaluatorDQ;//策略评价数据记录
};

