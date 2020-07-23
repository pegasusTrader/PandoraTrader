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
#include <deque>
#include <fstream>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif // _MSC_VER


#include "cwMutex.h"

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
	void WriteLog(bool bForceWrite = false);

	void		 SetBufferLength(size_t nLength);
	inline size_t SetBufferLength() { return m_iBufferLength; }
private:
	size_t						m_iBufferLength;
	cwMUTEX						m_LogMutex;
	std::deque<LogDataPtr>		m_LogDataDeque;

	std::fstream				m_Log;
};

