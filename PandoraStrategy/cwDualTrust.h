#pragma once
#include "cwBasicCTAStrategy.h"

//这是一个经典策略的demo，关于策略介绍，可以百度下，有很详尽说明，此处不再赘述
// 该策略实现是CTAPlatform的一个子策略实现，策略输出预期持仓，
// 由CTAPlatform综合该品种合约所有预期持仓持仓后，下单到交易所，进行实际持仓和订单管理
//
class cwDualTrust :
    public cwBasicCTAStrategy
{
public:
	cwDualTrust(const char * szStrategyName);
	//当生成一根新K线的时候，会调用该回调
	void			OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) override;
};

