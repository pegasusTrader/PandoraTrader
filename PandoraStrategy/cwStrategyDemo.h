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

	void TryAggressiveClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos);
	//��ǰʱ��
	std::string m_strCurrentUpdateTime;
	// bar����
	void UpdateCtx(cwMarketDataPtr pPriceData);
	// ���ֽ��� ����
	void StrategyPosOpen(cwMarketDataPtr, std::unordered_map<std::string, orderInfo>& cwOrderInfo);
	// ƽ�ֽ��� ����
	void StrategyPosClose(cwMarketDataPtr pPriceData, cwPositionPtr pPos, std::unordered_map<std::string, orderInfo>& cwOrderInfo);

	bool IsPendingOrder(std::string instrumentID);
};