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
#include "cwCalendar.h"

namespace cwPandoraTrader
{

class cwChinaTradingCalendar :
	public cwCalendar
{
public:
	cwChinaTradingCalendar();
	~cwChinaTradingCalendar();

private:
	class cwSHFEImpl
		:public cwCalendar::cwCanlendarImpl
	{
	public:

		std::string GetName() const override;
		bool IsBusinessDay( cwDate date) const override;
		bool IsWeekend(const cwDate::enumWeekday weekday) const override;
	private:

	};
	
};

} // End NameSpace


