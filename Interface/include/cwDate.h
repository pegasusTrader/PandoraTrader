//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Created by Wu Chang Sheng on Dec.8th, 2016
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <stdint.h>

namespace cwPandoraTrader
{

	//date support 1900~2200
	class cwDate
	{

	public:
		enum enumWeekday :int
		{
			Sunday = 0,
			Monday = 1,
			Tuesday = 2,
			Wednesday = 3,
			Thursday = 4,
			Friday = 5,
			Saturday = 6,
			Sun = 0,
			Mon = 1,
			Tue = 2,
			Wed = 3,
			Thu = 4,
			Fri = 5,
			Sat = 6
		};

		enum enumMonth :int
		{
			January = 1,
			February = 2,
			March = 3,
			April = 4,
			May = 5,
			June = 6,
			July = 7,
			August = 8,
			September = 9,
			October = 10,
			November = 11,
			December = 12,
			Jan = 1,
			Feb = 2,
			Mar = 3,
			Apr = 4,
			Jun = 6,
			Jul = 7,
			Aug = 8,
			Sep = 9,
			Oct = 10,
			Nov = 11,
			Dec = 12

		};


	public:
		//Default Constructor returning 1900-1-1
		cwDate();

		// Constructor taking a serial number as given by Excel
		explicit cwDate(int32_t serialNum);

		//Traditional Constructor
		cwDate(int day, enumMonth month, int year);

		bool Reset(int day, enumMonth month, int year);
		bool IncreaseByMonth(int months);
		bool DecreaseByMonth(int months);

		inline	int GetDayOfMonth() const { return m_Day; }
		inline  int GetDayofYear()  { return m_iSerialNumber - GetYearOffset(m_Year); }
		inline  enumMonth GetMonth() { return m_Month; }
		inline	int GetYear() { return m_Year; }
		inline  enumWeekday GetWeekday() { return m_WeekDay; }

		inline  int GetSerialNumber() { return m_iSerialNumber; }

		inline  int operator - (const cwDate& d1) { return m_iSerialNumber - d1.m_iSerialNumber; }
		inline cwDate operator+(int days) const { return cwDate(m_iSerialNumber + days); }
		inline cwDate operator-(int days) const { return cwDate(m_iSerialNumber - days); }

		inline bool operator==(const cwDate& d1) { return m_iSerialNumber == d1.m_iSerialNumber; }
		inline bool operator>=(const cwDate& d1) { return m_iSerialNumber >= d1.m_iSerialNumber; }
		inline bool operator>(const cwDate& d1) { return m_iSerialNumber > d1.m_iSerialNumber; }
		inline bool operator<=(const cwDate& d1) { return m_iSerialNumber <= d1.m_iSerialNumber; }
		inline bool operator<(const cwDate& d1) { return m_iSerialNumber < d1.m_iSerialNumber; }


		//! increments date by the given number of days
		cwDate& operator+=(int days);
		//! decrement date by the given number of days
		cwDate& operator-=(int days);
		//! 1-day pre-increment
		cwDate& operator++();
		//! 1-day post-increment
		//cwDate operator++(int);
		//! 1-day pre-decrement
		cwDate& operator--();
		//! 1-day post-decrement
		//cwDate operator--(int);

		//tools: static methods
		static inline bool IsLeapYear(uint32_t year)
		{
			return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
		}

		static int GetMonthLength(enumMonth mon, int year);

	protected:
		int				m_Year;
		enumMonth		m_Month;
		int				m_Day;

		enumWeekday		m_WeekDay;

		int				m_iSerialNumber;

		//monthoffset per year 
		int				GetMonthOffset(enumMonth mon, bool leapYear);
		// From 1900.1.1 years offset
		int				GetYearOffset(int year);

		//update year, month, day and weekday by serialNumber;
		bool			UpdateBySerialNum();
	};	// End cwDate Class


} // End cwPandoraTrader NameSpace

