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

#if !(defined cwMUTEX && defined cwAUTOMUTEX)
#ifdef _MSC_VER
#include "cwAutoCriticalSection.h"
#define cwMUTEX cwCriticalSection
#define cwAUTOMUTEX cwAutoCriticalSection
#else
#include "cwAutoMutex.h"
#define cwMUTEX std::mutex
#define cwAUTOMUTEX cwAutoMutex
#endif // _MSC_VER
#endif // !(defined cwMUTEX && defined cwAUTOMUTEX)