#pragma once
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector> 


// 获取当前日期YYYYMMDD
std::string GetTodayDate() {
	std::time_t now = std::time(nullptr);
	std::tm localTime;

#if defined(_WIN32) || defined(_WIN64)
	// Windows
	localtime_s(&localTime, &now);
#else
	// Linux/macOS
	localtime_r(&now, &localTime);
#endif

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y%m%d");

	return oss.str();
}

//计算简单算数平均值
double ArithmeticMean(const std::vector<double>& arr) {
	if (arr.empty()) {
		return 0.0;
	}
	double sum = 0.0;
	for (const double num : arr) {
		sum += num;
	}
	return sum / static_cast<double>(arr.size());
}
//计算简单标准差
double SampleStd(const std::vector<double>& arr) {
	double mean = ArithmeticMean(arr);
	double result = 0.0;
	for (const double num : arr) {
		result += pow(num - mean, 2);
	}
	return sqrt(result / (static_cast<double>(arr.size()) - 1));
}
