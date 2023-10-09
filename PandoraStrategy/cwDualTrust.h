#pragma once
#include "cwBasicCTAStrategy.h"

class cwDualTrust :
    public cwBasicCTAStrategy
{
public:
	cwDualTrust(const char * szStrategyName);
	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);


};

