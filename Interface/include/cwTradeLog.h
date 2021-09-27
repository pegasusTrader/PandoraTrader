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
#include "cwLog.h"

class cwTradeLog
	: public cwLog
{
public:
	enum enTradeLogType :int
	{
		enMsg = 0
		, enIO
		, enCO
		, enUO
		, enUT
		, enRP
		, enRO
		, enRT
		, enErr
		, enCount
	};
	static char s_szTradeLogType[cwTradeLog::enCount][4];
public:
	cwTradeLog();
	cwTradeLog(const char * pFileName);
	cwTradeLog(const char * pFileName, const char * pFolder);

	~cwTradeLog();

	void AddLog(int LogType, const char * pData, bool bForceWrite = false);
};

