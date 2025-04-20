#pragma once
#include <string>
#include "sqlite3.h"
#include <map>
#include <vector>
#include <unordered_map>
#include "cwBasicKindleStrategy.h"




namespace MyTrade {

    // 持仓状况结构体
    struct catePortInf {
        std::string direction;
        int volume;
        double costPrice;
        double openCost;
        int amount;
    };

    // 合约乘数与一跳价位结构体
    struct marginovk {
        int multiple;
        double ticksize;
    };

    // 主力合约键结构体
    struct mainCtrKeys {
        std::string date;
        std::string contract;
    };

    // 主力合约值结构体
    struct mainCtrValues {
        cwFtdcInstrumentIDType code;
        double factor;
        double accfactor;
    };

    // 分钟数据信息结构体
    struct barFuture {
        std::string code;
        std::string tradingday;
        std::string timestamp;
        int64_t volume;
        double price;
    };

    // 以下结构体如果有需要可以取消注释并使用
    // 仓位管理结构体（原posMng，这里先注释掉，你可按需启用）
    // struct posMng {
    //     string code;
    //     string direction;
    //     int volume;
    //     double costPrice;
    //     double openCost;
    //     int amount;
    // };

    // 开仓管理结构体
    struct orcMng {
        std::string cdate;
        std::string ctime;
        std::string dire;
        int htime;
        double profit;
        std::string method;
    };

    // 策略参数信息结构体
    struct paraMng {
        std::string Fac;
        std::string ver;
        std::string typ;
        int Rs;
        int Rl;
    };

    // 期货合约信息结构体
    struct futInfMng {
        std::string exchange;
        int multiple;
        double ticksize;
        double marginrate;
    };

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