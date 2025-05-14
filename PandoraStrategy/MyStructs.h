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

// �ֲ�״���ṹ��
//�������������־��ۡ����ֳɱ�������
struct catePortInf {
	std::string direction;
	int volume;
	double costPrice;
	double openCost;
	int amount;
};

// ��Լ������һ����λ�ṹ��
struct marginovk {
	int multiple;
	double ticksize;
};

// ������Լ���ṹ��
struct mainCtrKeys {
	std::string date; // ����
	std::string contract; // ��Լ
	bool operator==(const mainCtrKeys& other) const {
		return date == other.date && contract == other.contract;
	};
};

namespace std {
	template <>
	struct hash<mainCtrKeys> {
		std::size_t operator()(const mainCtrKeys& p) const {
			auto hash1 = std::hash<std::string>{}(p.date);
			auto hash2 = std::hash<std::string>{}(p.contract);
			return hash1 ^ (hash2 << 1);
		}
	};
}

// ������Լֵ�ṹ��
struct mainCtrValues {
	std::string code; // ��Լ����
	double factor; // ��Ȩ����
	double accfactor; // �ۼƸ�Ȩ����
};

// ����������Ϣ�ṹ��
struct barFuture {
	std::string code; // ��Լ����
	std::string tradingday; // ������
	std::string timestamp; //ʱ���
	int64_t volume; // �ɽ���
	double price; // ���¼۸�
};

//���½ṹ���������Ҫ����ȡ��ע�Ͳ�ʹ��
//��λ����ṹ�壨ԭposMng��������ע�͵�����ɰ������ã�
struct posMng {
	std::string code; //��Լ����
	std::string direction; //�ֲַ���
	int volume; //�ֲ�����
	double costPrice; //
	double openCost; //
	int amount;
};

// ���ֹ���ṹ��
struct orcMng {
	std::string cdate;
	std::string ctime;
	std::string dire;
	int htime;
	double profit;
	std::string method;
};

// ���Բ�����Ϣ�ṹ��
struct paraMng {
	std::string Fac;//���Ա��
	std::string ver;//���԰汾
	std::string typ;//��������
	int Rs;//���ڴ���
	int Rl;//���ڴ���
};



struct StrategyContext {
	std::vector<futInfMng> tarContracInfo;               // Ŀ���Լ�ṹ��
	std::map<std::string, std::deque<double>> retBar;   // ����������
	std::map<std::string, std::deque<double>> barFlow;  // ���̼�����(δ��Ȩ)
	std::map<std::string, std::deque<double>> queueBar;  // ���̼�����(�Ѹ�Ȩ)
	std::map<std::string, int> countLimitCur;            // ��Լ��Ӧ��������
};