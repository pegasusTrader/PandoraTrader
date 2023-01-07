#include "cwDualTrust.h"
#include <algorithm>


cwDualTrust::cwDualTrust(const char* szStrategyName)
	: cwBasicCTAStrategy(szStrategyName)
{
}

void cwDualTrust::OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	//Get Parameter
	double days = m_StrategyPara.CTAPara1;
	double	k1 = m_StrategyPara.CTAPara2;
	double	k2 = m_StrategyPara.CTAPara3;

	//int iKindleCount = pKindleSeries->GetKindleSize();
	
	auto pCurrentKindle = pKindleSeries->GetLastKindleStick();

	double LastOpen = pCurrentKindle->Open;
	double LastHigh = pCurrentKindle->High;
	double LastLow = pCurrentKindle->Low;

	double hh = 0.0, hc = 0.0, lc = 0.0, ll = 0.0;
	int iStart = 0, iEnd = pKindleSeries->GetKindleSize() - 1;
	iStart = (std::max)(iStart, (int)(iEnd - days));

	std::deque<cwKindleStickPtr> kindleList;
	pKindleSeries->GetKindleSerise(kindleList);

	for (int i = iStart; i < iEnd; i++)
	{
		cwKindleStickPtr KSSptr = kindleList.at(i);

		if (i == iStart)
		{
			hh = KSSptr->High;
			hc = KSSptr->Close;

			lc = KSSptr->Close;
			ll = KSSptr->Low;

			continue;
		}

		if (hh < KSSptr->High)
		{
			hh = KSSptr->High;
		}

		if (hc < KSSptr->Close)
		{
			hc = KSSptr->Close;
		}

		if (lc > KSSptr->Close)
		{
			lc = KSSptr->Close;
		}

		if (ll > KSSptr->Close)
		{
			ll = KSSptr->Close;
		}
	}

	double upper_bound = LastOpen + k1 * (std::max)(hh - lc, hc - ll);
	double lower_bound = LastOpen - k2 * (std::max)(hh - lc, hc - ll);

	int iPosition = GetStrategyPosition();

	if (iPosition == 0)
	{
		if (LastHigh >= upper_bound)
		{
			SetStrategyPosition(1);
		}

		if (LastLow <= lower_bound)
		{
			SetStrategyPosition(-1);
		}
	}
	else
	{
		if (iPosition > 0)
		{
			if (LastLow <= lower_bound)
			{
				SetStrategyPosition(0);
			}
		}
		else
		{
			if (LastHigh >= upper_bound)
			{
				SetStrategyPosition(0);
			}
		}
	}
}
