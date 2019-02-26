//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//---	CreateTime:	2019/01/24
//---
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////
#pragma once

enum cwMDAPIType :int
{
	cwMD_SIM = 0,
	cwMD_CTP,
	cwMD_CNT
};
const char * g_cwGetMdApiName(cwMDAPIType apitype);

enum cwTradeAPIType :int
{
	cwTrade_SIM = 0,
	cwTrade_CTP,
	cwTrade_CNT
};
const char * g_cwGetTradeApiName(cwTradeAPIType apitype);