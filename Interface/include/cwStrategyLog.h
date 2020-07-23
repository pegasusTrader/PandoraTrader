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
#include <stdarg.h>

class cwStrategyLog
	: public cwLog
{
public:
	enum enStrategyLogType :int
	{
		enMsg = 0
		, enIO
		, enCO
		, enReIO
		, enIMMS
		, enErr
		, enCount
	};
	static char s_szStrategyLogType[cwStrategyLog::enCount][8];
public:
	cwStrategyLog();
	cwStrategyLog(const char * pFileName);
	cwStrategyLog(const char * pFileName, const char * pFolder);
	~cwStrategyLog();

	void AddLog(const char * pData, int LogType,  bool bForceWrite = false);
	void AddLog(int LogType, const char * lpParam, ...);
	void AddLog(int LogType, int bForceWrite, const char * lpParam, ...);

	void AddLog(LogDataPtr LogPtr);
};

class cwEasyStrategyLog
{
public:
	cwEasyStrategyLog(cwStrategyLog& Log, const char * szFunctionName = NULL, const char * szFunctionMsg = NULL);
	~cwEasyStrategyLog();

	void AddLog(int LogType, const char * lpParam, ...);
	void AddLog(const char * pData, int LogType, bool bForceWrite = false);

	inline void SetForceWrite(bool bForceWrite) { m_bHasForceWrite = bForceWrite; }

private:
	cwStrategyLog&	m_SLog;
	std::string		m_strFunctionName;
	std::string     m_strFunctionMsg;

	std::deque<LogDataPtr>		m_LogTempDeque;

	bool			m_bHasForceWrite;
};

