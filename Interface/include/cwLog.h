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
#include <time.h>
#include <memory>
#include <string.h>
#include <functional>
#include <thread>
#include <atomic>
#include <fstream>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif // _MSC_VER
#include "cwMutex.h"

#ifdef CW_USING_TBB_LIB
#include "oneapi/tbb/concurrent_queue.h"
#else
#include <deque>
#endif



#define cw_LOG_DATATYPE_LENGTH 16
#define cw_LOG_TIME_LENGH 18
#define cw_LOG_DATAMSG_LENGTH 4058


struct LogData
{
	int	 DataType;
	char szDataType[cw_LOG_DATATYPE_LENGTH];
	char szTime[cw_LOG_TIME_LENGH];	//20170309_00:00:00
	char szDataMsg[cw_LOG_DATAMSG_LENGTH];

	LogData()
	{
		memset(this, 0, sizeof(LogData));
	}
};
typedef std::shared_ptr<LogData> LogDataPtr;

class cwLog
{
public:
	cwLog(const char * pFileName, const char * pFolder = NULL);
	~cwLog();
	


	void AddTitle(const char * pData);
	void AddLog(LogDataPtr LogPtr, bool bForceWrite = false);
	void AddLog(int LogType, const char * pData, const char * szLogType = NULL, bool bForceWrite = false);

#ifndef CW_USING_TBB_LIB
	void WriteLog(bool bForceWrite = false);
#endif

	const char* GetLogFileName() { return m_LogFileName.c_str(); }

	void			SetBufferLength(size_t nLength);
	inline size_t	SetBufferLength() { return m_iBufferLength; }

	void			SetNoWorkRequired(bool NoWork = false);
	void			SetKeepFileOpen(bool FileOpen = false);
private:
	std::thread							m_LogWorkingThread;
	volatile std::atomic<bool>			m_bLogWorkingThreadRun;
	void								LogWorkingThread();


	size_t								m_iBufferLength;

#ifdef CW_USING_TBB_LIB
	tbb::concurrent_queue<LogDataPtr>	m_LogDataDeque;
#else
	std::deque<LogDataPtr>				m_LogDataDeque;
#endif // CW_USING_TBB_LIB

	cwMUTEX								m_LogMutex;
	std::fstream						m_Log;

	std::string							m_LogFileName;

private:
	//不需要工作
	volatile bool						m_bNoWorkRequired;
	volatile bool						m_bKeepFileOpen;
};

