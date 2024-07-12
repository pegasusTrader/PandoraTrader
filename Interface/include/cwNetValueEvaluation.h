//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Liao Peng, Wu Chang Sheng
//---
//--	2023/8/27 吴长盛在廖鹏博士的cwEvaluator基础上，进行调整更新
// 
//--	感谢廖鹏博士为PandoraTrader贡献代码。
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <deque>
#include <memory>
#include <string>

class cwNetValueEvaluation
{
public:
	cwNetValueEvaluation();
	~cwNetValueEvaluation();

#if 0
	//Common Define
	struct TimeBalanceData
	{
		std::string		strDateTime;
		std::uint64_t	iTimeStamp;
		double			dBalance;
		double			dMaxFundOccupied;
	};
	typedef std::shared_ptr<TimeBalanceData> TimeBalancePtr;

	std::deque<TimeBalancePtr> m_cwTimeBalanceSeries;
	//Statistics
	TimeBalancePtr				m_MaxBalanceStamp;			//最大权益时刻
	TimeBalancePtr				m_MaxDrupDowmStamp;			//最大回撤时刻
#endif

	//variable
	std::uint64_t											m_iTimeStamp;                   //最新时间戳
	std::uint64_t											m_iStartTimeStamp;              //开始时间戳
	std::string												m_strStartTimeStamp;			//开始时间字符串（如20120312_092312）
	std::string												m_strTimeStamp;					//最新时间字符串(未赋值）
	std::uint64_t											m_iThisDayEndTimeStamp;			//当日结束时间戳（默认为周一到周五，16时）

	double													m_dPreTotalPNL;					//上次总盈亏
	double                                                  m_dLastEquity;                  //最新修正后的权益（考虑出入金）
	double                                                  m_dUnits;                       //基金份额
	double                                                  m_dPreNetAsset;                 //前一日净值
	double                                                  m_dCurNetAsset;                 //当前净值

	double													m_dTotalDeposit;				//总入金金额

	double                                                  m_HighestNetAsset;              //最高净值
	double													m_dDrawDownRatio;				//当前回撤比率
	double													m_dMaxDrawDownRatio;			//最大回撤率

	int                                                     m_iKindleCount;                 //K线数量
	double                                                  m_dAvgDailyRet;                 //日均收益率（增量计算法）


	/// <summary>
	/// Running Parameter
	/// </summary>
	double													m_dExpectedRet;					//预期收益每日（252），默认值为0.05
	const double											m_dDoubleEQ; 
	std::deque<double>                                      m_dailyRetDQ;                   //日收益率序列

	//Interface
	//出入金
	void Deposit(double deposit);
	/// <summary>
	/// 更新净值
	/// </summary>
	void UpdateNetValueByTotalPNL(std::uint64_t timestamp, double totalPNL, double fundUsed);

	//设置预期收益
	void SetExpectedReturn(double expectedret);
	
	void Calculate();
	///Calculate Result
	double													m_dAverageDDR;					//简单平均回撤率(待修复）

	double                                                  m_dTradingYears;	            //交易时间跨度（如0.3年）
	double                                                  m_dIRR;							//年化复利
	double													m_dAR;							//年化单利

	double													m_dVolatility;					//日收益率的波动率
	double													m_dVolatilityDownward;			//下行波动率

	double													m_dSharpeRatio;					//夏普比率
	double													m_dSortinoRatio;				//索提诺比率
	double													m_dCalmarRatio;					//卡玛比率
	double													m_dSterlingRatio;				//斯特林比率(待修复）

};

