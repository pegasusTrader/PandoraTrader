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
namespace cwCommonUtility
{

	//Math
	double cwCeil(double dValue, double dTickSize = 1);

	double cwfloor(double dValue, double dTickSize = 1);

	// TOOLs
	#define CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(TypeName) \
	private:\
		TypeName(const TypeName&); \
		TypeName& operator=(const TypeName&);
}
