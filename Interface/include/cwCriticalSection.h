//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Engineer: Wu Chang Sheng
//---
//---	CreateTime:	2014/12/12
//---
//---	VerifyTime:	2014/12/12
//---
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef WIN32

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
#endif // WIN32