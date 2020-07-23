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
#include "cwKindleStick.h"

typedef std::shared_ptr<cwKindleStick> cwKindleStickPtr;

class cwKindleStickSeries
{
public:

public:
	cwKindleStickSeries();
	~cwKindleStickSeries();

	bool InitialKindleStickSeries(uint32_t iTimeScale = 60);
	void PriceUpdate(cwMarketDataPtr pPriceData);

	inline uint32_t GetTimeScale() { return m_iTimeScale; }

public:
	cwMarketDataPtr					m_PrePriceData;
	cwKindleStickPtr				m_pCurrentKindleStick;
	uint32_t						m_iCurrentKindleLeftTime;
	std::deque<cwKindleStickPtr>	m_KindleStickDeque;

	bool		m_bIsNewKindle;

public:
	cwKindleStickPtr GetKindleStick(unsigned int nCount = 0);
	
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
	
	/*函数功能：获取指定范围K线的波峰位置
	* 参数描述：
	*     [in] nBegin	- K线范围开始编号；
	*     [in] nEnd		- K线范围结束编号；
	*	  [in] nUnilateralCompareNum - 单边比较数量，如2，则表示比左起2根K线都高，且比右起两根K线都高为波峰，如果为零，将输出所有K线
	*     [in, out] nIndexVector - 符合要求的K线编号
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
	*     [in, out] nIndexVector - 符合要求的K线编号
	*	  [in, out] nIndexLowestTrough - 最低波谷的位置
	* 返回值：
	*     true 找到符合要求的K线，false 未找到符合要求的K线
	*/
	bool GetKindleStickTrough(unsigned int nBegin, unsigned int nEnd,
		unsigned int nUnilateralCompareNum, std::vector<unsigned int>& nIndexVector, unsigned int& nIndexLowestTrough);
	
private:
	//K线周期，秒为单位
	uint32_t	m_iTimeScale;
	bool		m_bIsInitialed;
};

