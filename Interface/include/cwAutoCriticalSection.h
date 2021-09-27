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
#ifdef _MSC_VER
#include "cwCriticalSection.h"

class cwAutoCriticalSection
{
public:
	cwAutoCriticalSection(CRITICAL_SECTION &cs, bool bLock = false);
	cwAutoCriticalSection(cwCriticalSection &cs, bool bLock = false);
	virtual ~cwAutoCriticalSection();

	void		lock();
	void		unlock();

	inline bool GetHasLocked() { return m_bHasLocked; }
private:
	CRITICAL_SECTION&	m_CriticalSection;
	bool				m_bHasLocked;
};
#endif // _MSC_VER