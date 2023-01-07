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
#include <string>
#include <memory>

#include "cwDate.h"

namespace cwPandoraTrader
{

class cwCalendar
{
public:
	cwCalendar();
	~cwCalendar();

	//! abstract base class for calendar implementation
	class cwCanlendarImpl
	{
	public:
		virtual ~cwCanlendarImpl() = default;
		virtual std::string GetName() const = 0;
		virtual bool IsBusinessDay(cwDate date) const = 0;
		virtual bool IsWeekend(const cwDate::enumWeekday weekday) const = 0;
	private:

	};

	std::shared_ptr<cwCanlendarImpl>	m_Impl;

public:
	//! returns whether or not the calendar is initialized
	bool empty() const;

	std::string name() const;

	bool IsBusinessDay(const cwDate& d) const;

	bool IsHoliday(const cwDate& d) const;

	bool IsWeekend(cwDate& d) const;
	bool IsWeekend(cwDate::enumWeekday w) const;
};

} // End cwPandoraTrader NameSpace
