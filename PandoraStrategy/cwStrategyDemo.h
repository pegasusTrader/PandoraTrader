#pragma once
#include "cwBasicKindleStrategy.h"
#include "sqlite3.h"
#include "My_structs.h"

class cwStrategyDemo :
	public cwBasicKindleStrategy
{
public:
	cwStrategyDemo();
	~cwStrategyDemo();

	//MarketData SPI
	///�������
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//Trade SPI
	///�ɽ��ر�
	virtual void OnRtnTrade(cwTradePtr pTrade);
	//�����ر�
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	//�����ɹ�
	virtual void OnOrderCanceled(cwOrderPtr pOrder);
	//�����Խ��׳�ʼ�����ʱ�����OnReady, �����ڴ˺��������Եĳ�ʼ������
	virtual void			OnReady();

	std::string m_strCurrentUpdateTime;

	static double ArithmeticMean(const std::vector<double>& arr); //���������ƽ��ֵ

	static double SampleStd(const std::vector<double>& arr); //����������׼��

	static std::string getTodayDate();

	static void UpdateBarData();// ������ʷ��Ϣ

	static void UpdateFlow(std::unordered_map<std::string, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos);// ��¼���³ֲ�״���������������ɱ��۸񣬿��ֳɱ���������

	static std::vector<cwOrderPtr> StrategyTick(std::unordered_map<std::string, cwMarketDataPtr> code2data/*����*/);

	static std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

	static std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

	static std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO);

	static std::vector<cwOrderPtr> HandBar(std::unordered_map<std::string, cwMarketDataPtr> code2data/*�������*/, std::unordered_map<std::string, PositionFieldPtr> curPos);
	
};