#pragma once

#if !(defined cwMUTEX && defined cwAUTOMUTEX)
#ifdef WIN32
#include "cwAutoCriticalSection.h"
#define cwMUTEX cwCriticalSection
#define cwAUTOMUTEX cwAutoCriticalSection
#else
#include "cwAutoMutex.h"
#define cwMUTEX std::mutex
#define cwAUTOMUTEX cwAutoMutex
#endif // WIN32
#endif // !(defined cwMUTEX && defined cwAUTOMUTEX)