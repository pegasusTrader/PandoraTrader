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
#include <stdint.h>

#include "cwMutex.h"

//#define OrderRef_SimpleMode

class cwOrderReference
{
public:
	cwOrderReference();
	~cwOrderReference();

	void			UpdateOrderRef(const char * pOrderRef);
	void			UpdateOrderRef(uint64_t iOrderRef);

	uint64_t		GetOrderRef();
private:
	cwMUTEX			m_OderRefMutex;
	uint64_t		m_OrderReferenceIndex;

#ifndef OrderRef_SimpleMode
#ifdef _MSC_VER
	DWORD			m_dwCurrentProcessID;
#else
	int				m_iCurrentProcessID;
#endif
#endif // !OrderRef_SimpleMode

};

