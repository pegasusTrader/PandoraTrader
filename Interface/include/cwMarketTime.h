#pragma once
#include <string>
#include <memory>

class cwMarketTime
{
public:
	//UpdateTime Format: hh:mm:ss 09:10:11
	cwMarketTime();
	cwMarketTime(int hour, int minute, int second, int MilliSecond = 0);
	cwMarketTime(std::string updatetime, int MilliSecond = 0);
	~cwMarketTime();

	inline bool Reset(int hour, int minute, int second, int MilliSecond = 0);
	bool Reset(std::string updatetime, int MilliSecond = 0);
	
	inline int64_t GetTotalSecond() { return m_iTotalMilliSecond / 1000; }
	inline int64_t GetTotalMilliSecond() { return m_iTotalMilliSecond; }

	bool operator > (cwMarketTime const& right) const;
	bool operator < (cwMarketTime const& right) const;
	bool operator >= (cwMarketTime const& right) const;
	bool operator <= (cwMarketTime const& right) const;
	bool operator == (cwMarketTime const& right) const;
	bool operator != (cwMarketTime const& right) const { return !operator ==(right); }

private:
	int64_t m_iTotalMilliSecond;
};
typedef std::shared_ptr<cwMarketTime> cwMarketTimePtr;
