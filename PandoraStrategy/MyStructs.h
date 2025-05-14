#pragma once
#include <string>
#include <deque>

// �ڻ���Լ��Ϣ�ṹ��
struct futInfMng {
	std::string contract; //��Լ
	int multiple; //��Լ����
	std::string Fac;
	int Rs; //����
	int Rl; //��֤����
	std::string code; //��Լ����
	double accfactor; //�ۼƸ�Ȩ����	 
};

struct orderInfo
{
	std::string szInstrumentID;
	int volume;
	double price;
};


struct StrategyContext {
	std::vector<futInfMng> tarContracInfo;               // Ŀ���Լ�ṹ��
	std::map<std::string, std::deque<double>> retBar;   // ����������
	std::map<std::string, std::deque<double>> barFlow;  // ���̼�����(δ��Ȩ)
	std::map<std::string, std::deque<double>> queueBar;  // ���̼�����(�Ѹ�Ȩ)
	std::map<std::string, int> countLimitCur;            // ��Լ��Ӧ��������
};