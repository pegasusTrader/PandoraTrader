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

//交易行情时间，精确到毫秒数，0:0:0.000到当前的毫秒数。
//默认设置起始时间为6点，可以通过SetStartTime函数进行修改，但请勿超过24
//如果时间小于6点，则加24表示，即实际时间取值为是[6:0:0.000-30:0:0.000)
//也就是说0点对应24点，1点25点，5点为29点，其他取值不变，

#pragma once
#include <string>
#include <memory>

class cwMarketTime
{
public:
	//UpdateTime Format: hh:mm:ss 09:10:11
	cwMarketTime(int StartTime = 6);
	cwMarketTime(int hour, int minute, int second, int MilliSecond = 0, int StartTime = 6);
	cwMarketTime(std::string updatetime, int MilliSecond = 0, int StartTime = 6);
	~cwMarketTime();

	void		SetStartTime(int iStartTime = 6) 
	{ 
		if (iStartTime < 24)
		{
			m_iStartTime = iStartTime;
		}
	}

	bool Reset(int hour, int minute, int second, int MilliSecond = 0);
	bool Reset(std::string updatetime, int MilliSecond = 0);
	bool Reset(int64_t iTotalMilliSecond);
	
	inline int64_t	GetTotalSecond() { return m_iTotalMilliSecond / 1000; }
	inline int64_t	GetTotalMilliSecond() { return m_iTotalMilliSecond; }

	inline int		GetHour() { return (m_iHour >= 24) ? m_iHour - 24 : m_iHour; }
	inline int		GetMinute() { return m_iMinute; }
	inline int		GetSecond() { return m_iSecond; }
	inline int		GetMilliSecond() { return m_iMilliSecond; }

	bool operator > (cwMarketTime const& right) const;
	bool operator < (cwMarketTime const& right) const;
	bool operator >= (cwMarketTime const& right) const;
	bool operator <= (cwMarketTime const& right) const;
	bool operator == (cwMarketTime const& right) const;
	bool operator != (cwMarketTime const& right) const { return !operator ==(right); }

private:
	int64_t m_iTotalMilliSecond;
	int		m_iHour, m_iMinute, m_iSecond, m_iMilliSecond;

	int		m_iStartTime;
};
typedef std::shared_ptr<cwMarketTime> cwMarketTimePtr;
