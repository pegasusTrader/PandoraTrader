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

	void AddLog(int LogType, const char * pData, bool bForceWrite = false);
	void AddLog(int LogType, const char * lpParam, ...);
	void AddLog(LogDataPtr LogPtr);
};

class cwEasyStrategyLog
{
public:
	cwEasyStrategyLog(cwStrategyLog& Log, const char * szFunctionName = NULL, const char * szFunctionMsg = NULL);
	~cwEasyStrategyLog();

	void AddLog(int LogType, const char * pData, bool bForceWrite = false);
	void AddLog(int LogType, const char * lpParam, ...);

private:
	cwStrategyLog&	m_SLog;
	std::string		m_strFunctionName;
	std::string     m_strFunctionMsg;

	std::deque<LogDataPtr>		m_LogTempDeque;
};

