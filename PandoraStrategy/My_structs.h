#pragma once
#include <string>
#include "cwBasicKindleStrategy.h"



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

 //以下结构体如果有需要可以取消注释并使用
 //仓位管理结构体（原posMng，这里先注释掉，你可按需启用）
 struct posMng {
     std::string code;
     std::string direction;
     int volume;
     double costPrice;
     double openCost;
     int amount;
 };

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