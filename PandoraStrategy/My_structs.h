#pragma once
#include <string>
#include "cwBasicKindleStrategy.h"



// �ֲ�״���ṹ��
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
    std::string date;
    std::string contract;
};

// ������Լֵ�ṹ��
struct mainCtrValues {
    cwFtdcInstrumentIDType code;
    double factor;
    double accfactor;
};

// ����������Ϣ�ṹ��
struct barFuture {
    std::string code;
    std::string tradingday;
    std::string timestamp;
    int64_t volume;
    double price;
};

 //���½ṹ���������Ҫ����ȡ��ע�Ͳ�ʹ��
 //��λ����ṹ�壨ԭposMng��������ע�͵�����ɰ������ã�
 struct posMng {
     std::string code;
     std::string direction;
     int volume;
     double costPrice;
     double openCost;
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
    std::string Fac;
    std::string ver;
    std::string typ;
    int Rs;
    int Rl;
};

// �ڻ���Լ��Ϣ�ṹ��
struct futInfMng {
    std::string exchange;
    int multiple;
    double ticksize;
    double marginrate;
};