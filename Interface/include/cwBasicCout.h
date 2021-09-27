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

#include <iostream>
#include <thread>
#include <memory>
#include <string.h>
#include <stdarg.h>
#include <atomic>

#ifdef CW_USING_TBB_LIB
#include "oneapi/tbb/concurrent_queue.h"
#else
#include "cwMutex.h"
#include <deque>
#endif

#define cw_COUT_DATAMSG_LENGTH 4096

class cwBasicCout
{
public:
	cwBasicCout();
	~cwBasicCout();

	struct CoutData
	{
		char szDataMsg[cw_COUT_DATAMSG_LENGTH];

		CoutData()
		{
			memset(this, 0, sizeof(CoutData));
		}
	};
	typedef std::shared_ptr<CoutData> CoutDataPtr;


	static void AddLog(CoutDataPtr dataPtr);
	//static void AddLog(bool bNoPara, const char * pData);
	static void AddLog(const char * lpParam, ...);

	static void SetNoWorkRequired(bool NoWork = false);
private:
	static std::thread							m_CoutWorkingThread;
	static volatile std::atomic<bool>			m_bCoutWorkingThreadRun;
	static void									CoutWorkingThread();

	static volatile std::atomic<int>			m_iInitialCount;

#ifdef CW_USING_TBB_LIB
	static tbb::concurrent_queue<CoutDataPtr>	m_LogDataDeque;
#else
	static cwMUTEX								m_DequeMutex;
	static std::deque<CoutDataPtr>				m_LogDataDeque;
#endif

	//不需要工作
	static volatile bool						m_bNoWorkRequired;
};

