#pragma once
#include "cwBasicKindleStrategy.h"
#include "sqlite3.h"
#include "myStructs.h"

class cwStrategyDemo :
	public cwBasicKindleStrategy
{
public:
	cwStrategyDemo();
	~cwStrategyDemo();

	//MarketData SPI
	///�������
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);
	//������һ����K�ߵ�ʱ�򣬻���øûص�
	virtual void OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);
	//Trade SPI
	///�ɽ��ر�
	virtual void OnRtnTrade(cwTradePtr pTrade);
	//�����ر�
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	//�����ɹ�
	virtual void OnOrderCanceled(cwOrderPtr pOrder);
	//�����Խ��׳�ʼ�����ʱ�����OnReady, �����ڴ˺��������Եĳ�ʼ������
	virtual void OnReady();
	//��ʼ������������
	void UpdateBarData();
	// �Զ�ƽ��ֺ���
	void AutoCloseAllPositionsLoop();
	//��ǰʱ��
	std::string m_strCurrentUpdateTime;
	// bar����
	void UpdateCtx(cwMarketDataPtr pPriceData);
	// ���ֽ��� ����
	orderInfo StrategyPosOpen(cwMarketDataPtr, orderInfo& order);
	// ƽ�ֽ��� ����
	orderInfo StrategyPosClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos, orderInfo& order);
};