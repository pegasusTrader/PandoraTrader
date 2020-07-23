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
#include <cstdint>

#ifndef _MSC_VER
typedef unsigned short	WORD;
typedef unsigned int	DWORD;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#else
#include<Windows.h>
#endif // !_MSC_VER

class cwTimeStamp
{
public:
	cwTimeStamp(uint64_t totalMicrosecond = 0L);
	~cwTimeStamp();


	inline void Set100Nanosecond(std::uint64_t NanosecondX100) { m_100nanosecond = NanosecondX100; }

	inline void SetTotalMicrosecond(std::uint64_t totalMicrosecond) { m_100nanosecond = totalMicrosecond * 10; }
	std::uint64_t GetTotalMicrosecond() const { return m_100nanosecond / 10; }

	void SetYear(std::uint32_t year);
	std::uint32_t GetYear() const;	//1970 - 2100

	void SetMonth(std::uint32_t month);
	std::uint32_t GetMonth() const; //01- 12

	void SetDay(std::uint32_t day);
	std::uint32_t GetDay() const;
	std::uint32_t GetDayofWeek();	//0-6 SUN MUN TUE WED THU FRI SAT
	
	static std::uint32_t GetDayofWeek(std::uint32_t year, std::uint32_t month, std::uint32_t day);

	void SetHour(std::uint32_t hour);
	std::uint32_t GetHour() const;  //0-24

	void SetMinute(std::uint32_t minute);
	std::uint32_t GetMinute() const; //0-60

	void SetSecond(std::uint32_t second);
	std::uint32_t GetSecond() const; //0-60

	void SetMicrosecond(std::uint32_t microsecond);
	std::uint32_t GetMicrosecond() const; //0-999

	void GoForward(std::int32_t nDay);

	bool operator > (cwTimeStamp const& right) const;
	bool operator < (cwTimeStamp const& right) const;
	bool operator >= (cwTimeStamp const& right) const;
	bool operator <= (cwTimeStamp const& right) const;
	bool operator == (cwTimeStamp const& right) const;
	bool operator != (cwTimeStamp const& right) const { return !operator ==(right); }
	
	std::int64_t operator - (cwTimeStamp const& right) const;
	cwTimeStamp operator +(std::uint64_t offset) const;
	cwTimeStamp operator -(std::uint64_t offset) const;
	cwTimeStamp operator +=(std::uint64_t offset);
	cwTimeStamp operator -=(std::uint64_t offset);

	void SetSystemTime(SYSTEMTIME const* pSysTime);
	void GetSystemTime(SYSTEMTIME * pSysTime) const;

	static inline bool IsLeapYear(std::uint32_t year)
	{
		return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
	}

	static const std::uint32_t s_MonthLengths[2][12];
private:
	//may the same with Windows' FileTime
	//Contains a 64 - bit value representing the number of 100 - nanosecond intervals since January 1, 1601 (UTC).
	std::uint64_t	m_100nanosecond;
};

