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

// 持仓状况结构体
//方向、数量、开仓均价、开仓成本、数量
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
	std::string date; // 日期
	std::string contract; // 合约
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

// 主力合约值结构体
struct mainCtrValues {
	std::string code; // 合约代码
	double factor; // 复权因子
	double accfactor; // 累计复权因子
};

// 分钟数据信息结构体
struct barFuture {
	std::string code; // 合约代码
	std::string tradingday; // 交易日
	std::string timestamp; //时间戳
	int64_t volume; // 成交量
	double price; // 最新价格
};

//以下结构体如果有需要可以取消注释并使用
//仓位管理结构体（原posMng，这里先注释掉，你可按需启用）
struct posMng {
	std::string code; //合约代码
	std::string direction; //持仓方向
	int volume; //持仓数量
	double costPrice; //
	double openCost; //
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
	std::string Fac;//策略编号
	std::string ver;//策略版本
	std::string typ;//策略类型
	int Rs;//短期窗口
	int Rl;//长期窗口
};



struct StrategyContext {
	std::vector<futInfMng> tarContracInfo;               // 目标合约结构体
	std::map<std::string, std::deque<double>> retBar;   // 收益率数据
	std::map<std::string, std::deque<double>> barFlow;  // 收盘价数据(未复权)
	std::map<std::string, std::deque<double>> queueBar;  // 收盘价数据(已复权)
	std::map<std::string, int> countLimitCur;            // 合约对应交易数量
};