#pragma once
#include <string>
#include <deque>

// 期货合约信息结构体
struct futInfMng {
	std::string contract; //合约
	int multiple; //合约乘数
	std::string Fac;
	int Rs; //跳价
	int Rl; //保证金率
	std::string code; //合约代码
	double accfactor; //累计复权因子	 
};

struct orderInfo
{
	std::string szInstrumentID;
	int volume;
	double price;
};


struct StrategyContext {
	std::vector<futInfMng> tarContracInfo;               // 目标合约结构体
	std::map<std::string, std::deque<double>> retBar;   // 收益率数据
	std::map<std::string, std::deque<double>> barFlow;  // 收盘价数据(未复权)
	std::map<std::string, std::deque<double>> queueBar;  // 收盘价数据(已复权)
	std::map<std::string, int> countLimitCur;            // 合约对应交易数量
};