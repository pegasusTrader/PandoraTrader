#pragma once
#include <string>
#include "sqlite3.h"
#include <map>
#include <vector>
#include <unordered_map>
#include "cwBasicKindleStrategy.h"
#include "My_structs.h"




namespace MyTrade {

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