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
#include <mutex>

class cwAutoMutex
{
public:
	cwAutoMutex(std::mutex& mtx, bool bLock = false);
	~cwAutoMutex();

	void		lock();
	void		unlock();

	inline bool GetHasLocked() { return m_bHasLocked; }
private:
	std::mutex&	m_Mutex;
	bool		m_bHasLocked;
};

