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
#include <memory>
#include <vector>
#include <deque>
#include "cwTradeCommonDefine.h"
#include "cwProductTradeTime.h"
#include "cwKindleStick.h"

#define KINDLE_MULTI_THREAD

#ifdef KINDLE_MULTI_THREAD
#include "cwMutex.h"
#endif // KINDLE_MULTI_THREAD


typedef std::shared_ptr<cwKindleStick> cwKindleStickPtr;

class cwKindleStickSeries
{
public:
	enum cwKindleSeriesType
	{
		cwKindleTypeMinute = 0,							//分钟k线（允许秒k），k线周期级别按秒数来记
		cwKindleTypeDaily,								//日线，				按交易日来记k线
	};

public:
	cwKindleStickSeries();
	~cwKindleStickSeries();

	//初始化K线  不需根据品种交易时间进行
	bool InitialKindleStickSeries(const char * szInstrumentID, cwKindleSeriesType type = cwKindleTypeMinute, uint32_t m_iTimeScale = 60);
	//初始化K线  需根据品种交易时间进行
	bool InitialKindleStickSeries(const char * szInstrumentID, const char * szProductID, cwKindleSeriesType type = cwKindleTypeMinute, uint32_t iTimeScale = 60);

	//行情更新，调用后会自动形成k线
	void PriceUpdate(cwMarketDataPtr pPriceData);

	//利用k线来更新K线序列。主要利用利用k线来合并数据,要求k线序列需要按顺序进行更新
	void UpdateKindle(cwKindleStickPtr pKindle);
	//替换现有k线序列
	void ReplaceKindle(cwKindleStickPtr pKindle);
	//移除时间点之前的K线
	void RemoveKinldeBeforeTime(uint64_t time);
	//移除时间点以后的K线
	void RemoveKinldeAfterTime(uint64_t time);
	//获取k线周期
	inline uint32_t GetTimeScale() { return m_iTimeScale; }
	//设置K线行情处理的数据精度，默认值为0.00001
	void SetPrecision(double precision);
public:
	cwMarketDataPtr					m_PrePriceData;
	cwKindleStickPtr				m_pCurrentKindleStick;
	cwRangeOpenClose				m_cwRangeOCMode;
	uint32_t						m_iCurrentKindleLeftTime;

	bool							m_bIsNewKindle;
	bool							m_bThisFinished;

public:
	//获取K线序列
	bool			 GetKindleSerise(std::deque<cwKindleStickPtr> &	KindleStickDeque);

	//按时间顺序获取k线，nCount为k线序列，最早的k线nCount为0
	cwKindleStickPtr GetKindleStick(unsigned int nCount = 0);
	//按时间逆序获取k线，nCount为k线序列，最近的k线nCount为0
	cwKindleStickPtr GetLastKindleStick(unsigned int nCount = 0);

	/*函数功能：获取K线序列长度
	* 参数描述：
	*     NULL
	* 返回值：
	*     k线序列长度
	*
	*/
	inline size_t			GetKindleSize() { return m_KindleStickDeque.size(); }

	/*函数功能：获取K线最高的k线，如果有多个一样高的，返回最近的一根
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	* 返回值：
	*     最高K线的编号，如果-1.则失败，参数有误
	*/
	int GetKindleStickHighest();
	int GetKindleStickHighest(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickHighest(unsigned int nCount);

	/*函数功能：获取K线最高的k线，如果有多个一样高的，返回最先（早）的一根
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	* 返回值：
	*     最高K线的编号，如果-1.则失败，参数有误
	*/
	int GetKindleStickHighestFirstOne();
	int GetKindleStickHighestFirstOne(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickHighestFirstOne(unsigned int nCount);

	/*函数功能：获取K线最高的k线的最大值
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	*	  [in,out] High - K线最大值
	* 返回值：
	*     true，High值有效，否则High值无效。
	*/
	bool GetHighest(double &High);
	bool GetHighest(unsigned int nBegin, unsigned int nEnd, double &High);
	bool GetHighest(unsigned int nCount, double &High);

	/*函数功能：获取下一个（最近一个,包括nBegin）比指定值更高的K线
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	* 返回值：
	*     满足要求的K线编号，如果-1，则查无此k线。
	*/
	int GetKindleStickNextHigher(double High, unsigned int nBegin);
	int GetKindleStickNextHigher(double High, unsigned int nBegin, unsigned int nEnd);

	/*函数功能：获取K线最低的k线，如果有多个一样低的，返回最近的一根
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	* 返回值：
	*     最低K线的编号，如果-1.则失败，参数有误
	*/
	int GetKindleStickLowest();
	int GetKindleStickLowest(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickLowest(unsigned int nCount);

	/*函数功能：获取K线最低的k线，如果有多个一样低的，返回最先（早）的一根
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	* 返回值：
	*     最低K线的编号，如果-1.则失败，参数有误
	*/
	int GetKindleStickLowestFirstOne();
	int GetKindleStickLowestFirstOne(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickLowestFirstOne(unsigned int nCount);

	/*函数功能：获取K线最低的k线的最小值
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	*	  [in,out] Low  - K线最小值
	* 返回值：
	*     true，Low值有效，否则Low值无效。
	*/
	bool GetLowest(double &Low);
	bool GetLowest(unsigned int nBegin, unsigned int nEnd, double &Low);
	bool GetLowest(unsigned int nCount, double &Low);

	/*函数功能：获取下一个（最近一个,包括nBegin）比指定值更低的K线
* 参数描述：
*     [in] nBegin	- K线范围开始编号；
*     [in] nEnd		- K线范围结束编号；
* 返回值：
*     满足要求的K线编号，如果-1，则查无此k线。
*/
	int GetKindleStickNextLower(double Low, unsigned int nBegin);
	int GetKindleStickNextLower(double Low, unsigned int nBegin, unsigned int nEnd);

	/*函数功能：获取指定范围K线的波峰位置
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	*	  [in] nUnilateralCompareNum - 单边比较数量，如2，则表示比左起2根K线都高，且比右起两根K线都高为波峰，如果为零，将输出所有K线
	*     [in, out] nIndexVector - 符合要求的K线编号(按时间顺序列出）
	*	  [in, out] nIndexHighestPeak - 最高波峰的位置
	* 返回值：
	*     true 找到符合要求的K线，false 未找到符合要求的K线
	*/
	bool GetKindleStickPeak(unsigned int nBegin, unsigned int nEnd,
		unsigned int nUnilateralCompareNum, std::vector<unsigned int>& nIndexVector, unsigned int& nIndexHighestPeak);
	
	/*函数功能：获取指定范围K线的波谷位置
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	*	  [in] nUnilateralCompareNum - 单边比较数量，如2，则表示比左起2根K线都低，且比右起两根K线都低为波谷，如果为零，将输出所有K线
	*     [in, out] nIndexVector - 符合要求的K线编号(按时间顺序列出）
	*	  [in, out] nIndexLowestTrough - 最低波谷的位置
	* 返回值：
	*     true 找到符合要求的K线，false 未找到符合要求的K线
	*/
	bool GetKindleStickTrough(unsigned int nBegin, unsigned int nEnd,
		unsigned int nUnilateralCompareNum, std::vector<unsigned int>& nIndexVector, unsigned int& nIndexLowestTrough);

	/*函数功能：获取当日K线数，
	* 参数描述：
	*  
	* 返回值：
	*     返回当日K线数，如果不用产品初始时间，则返回-1，表示错误，当前处于开盘第一根K线则，返回1.
	*/
	int  GetBarCountSinceToday();

	const char* GetInstrumentID() { return m_strInstrumentID.c_str(); }
private:
	std::string								m_strInstrumentID;
	std::string								m_strProductID;							//产品信息，在m_bUsingProductTradeTime为true的时候有效

	cwKindleSeriesType						m_cwKindleSeriesType;
	//K线周期，秒为单位
	uint32_t								m_iTimeScale;
	bool									m_bIsInitialed;
	std::uint64_t							m_LastestUpdateTime;

	//是否根据品种交易时间来合成
	bool									m_bUsingProductTradeTime;
	cwProductTradeTime						m_ProductTradeTime;

	std::uint64_t							m_iTodayBeginTime;						//该交易日的开始时间，在m_bUsingProductTradeTime为true的时候有效
	std::uint64_t							m_iTodayEndTime;						//该交易日的结束时间，在m_bUsingProductTradeTime为true的时候有效

#ifdef KINDLE_MULTI_THREAD
	cwMUTEX									m_KindleQueueMutex;
#endif // KINDLE_MULTI_THREAD
	std::deque<cwKindleStickPtr>			m_KindleStickDeque;

	double									m_dInsEQ;
};

