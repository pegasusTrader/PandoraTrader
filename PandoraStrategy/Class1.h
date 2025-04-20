#pragma once
#include <string>
#include "sqlite3.h"
#include <map>
#include <vector>
#include <unordered_map>
#include "cwBasicKindleStrategy.h"




namespace MyTrade {

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

    // ���½ṹ���������Ҫ����ȡ��ע�Ͳ�ʹ��
    // ��λ����ṹ�壨ԭposMng��������ע�͵�����ɰ������ã�
    // struct posMng {
    //     string code;
    //     string direction;
    //     int volume;
    //     double costPrice;
    //     double openCost;
    //     int amount;
    // };

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

    class Class1 {
    public:
        // sqlite����
        static sqlite3* cnn;
        static sqlite3* cnnSys;

        //ȫ�ֱ���
        static std::map<mainCtrKeys, mainCtrValues>* MainInf;//���׵�������Լ��Ӧ��Ϣ
        static std::map<std::string, std::vector<barFuture>>* barFlow;// ��ʷ�������ݣ���Ϊstring���ͣ�ֵΪbarFuture�ṹ���vector���൱��C#�е�List��

        static std::map<std::string, std::vector<barFuture>>* barFlowCur; // ������������
        static std::map<cwFtdcInstrumentIDType, double>* factorDictCur;// ��������
        static std::map<std::string, std::string>* codeTractCur;// Ŀ�꽻�׺�Լ
        static std::map<std::string, futInfMng>* futInfDict;// �ڻ���Լ��Ϣ����Ϊstring���ͣ�ֵΪfutInfMng�ṹ��

        static std::map<std::string, std::vector<double>>* queueBar;// �������ݣ���Ϊstring���ͣ�ֵΪdouble���͵�vector
        static std::map<std::string, std::vector<double>>* retBar;// ����������

        static std::map<std::string, catePortInf>* spePos;// ��ǰ�ֲ��������Ϊstring���ͣ�ֵΪcatePortInf�ṹ��
        static std::map<std::string, paraMng>* verDictCur;// ���Բ�����Ӧ��Ϣ
        static std::map<std::string, int>* countLimitCur;// ��Լ��Ӧ��������

        static std::vector<std::string>* tarCateList;

        static std::string cursor_str; // ���׵�������

        static double ArithmeticMean(const std::vector<double>& arr); //���������ƽ��ֵ

        static double SampleStd(const std::vector<double>& arr); //����������׼��

        static void UpdateBarData();// ������ʷ��Ϣ

        static void UpdateFlow(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos);// ��¼���³ֲ�״���������������ɱ��۸񣬿��ֳɱ���������

        static std::vector<cwOrderPtr> StrategyTick(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data/*����*/);

        static std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

        static std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

        static std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO);

        static std::vector<cwOrderPtr> HandBar(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data/*�������*/, std::unordered_map<std::string, PositionFieldPtr> curPos);

    };


}