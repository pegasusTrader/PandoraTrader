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
        // sqlite链接
        static sqlite3* cnn;
        static sqlite3* cnnSys;

        //全局变量
        static std::map<mainCtrKeys, mainCtrValues>* MainInf;//交易的主力合约对应信息
        static std::map<std::string, std::vector<barFuture>>* barFlow;// 历史行情数据，键为string类型，值为barFuture结构体的vector（相当于C#中的List）

        static std::map<std::string, std::vector<barFuture>>* barFlowCur; // 新增行情数据
        static std::map<cwFtdcInstrumentIDType, double>* factorDictCur;// 因子数据
        static std::map<std::string, std::string>* codeTractCur;// 目标交易合约
        static std::map<std::string, futInfMng>* futInfDict;// 期货合约信息，键为string类型，值为futInfMng结构体

        static std::map<std::string, std::vector<double>>* queueBar;// 行情数据，键为string类型，值为double类型的vector
        static std::map<std::string, std::vector<double>>* retBar;// 收益率数据

        static std::map<std::string, catePortInf>* spePos;// 当前持仓情况，键为string类型，值为catePortInf结构体
        static std::map<std::string, paraMng>* verDictCur;// 策略参数对应信息
        static std::map<std::string, int>* countLimitCur;// 合约对应交易数量

        static std::vector<std::string>* tarCateList;

        static std::string cursor_str; // 交易当天日期

        static double ArithmeticMean(const std::vector<double>& arr); //计算简单算数平均值

        static double SampleStd(const std::vector<double>& arr); //计算样本标准差

        static void UpdateBarData();// 加载历史信息

        static void UpdateFlow(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data, std::unordered_map<std::string, PositionFieldPtr> curPos);// 记录最新持仓状况（方向，数量，成本价格，开仓成本，数量）

        static std::vector<cwOrderPtr> StrategyTick(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data/*数据*/);

        static std::vector<cwOrderPtr> StrategyPosOpen(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

        static std::vector<cwOrderPtr> StrategyPosClose(std::string contract, cwMarketDataPtr barBook, double stdLong, double stdShort);

        static std::vector<cwOrderPtr> StrategyPosSpeC(std::string contract, cwMarketDataPtr barBook, long posO);

        static std::vector<cwOrderPtr> HandBar(std::unordered_map<cwFtdcInstrumentIDType, cwMarketDataPtr> code2data/*昨仓数据*/, std::unordered_map<std::string, PositionFieldPtr> curPos);

    };


}