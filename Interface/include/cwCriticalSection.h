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

#include <Windows.h>

class cwCriticalSection  
{
public:
	cwCriticalSection();
	~cwCriticalSection();

	void Enter(void);
	void Leave(void);

	inline void lock(void) { Enter(); }
	inline void unlock(void) { Leave(); }


	CRITICAL_SECTION m_csCriticalSection;
};
#endif // _MSC_VER