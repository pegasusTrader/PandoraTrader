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
namespace cwCommonUtility
{

	//Math 数值不能超过int，否则会出现溢出
	//向上取值，调整到最小单位
	double cwCeil(double dValue, double dTickSize = 1);
	//向下取值，调整到最小单位
	double cwFloor(double dValue, double dTickSize = 1);
	//四舍五入，调整到最小单位
	inline double cwRound(double dValue, double dTickSize = 1) 
	{
		return cwFloor(dValue + 0.5 * dTickSize, dTickSize);
	};

	int    cwDouble2Int(double dValue, double dTickSize = 1);

	// TOOLs

	#define CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(TypeName) \
	private:\
		TypeName(const TypeName&); \
		TypeName& operator=(const TypeName&);
}
