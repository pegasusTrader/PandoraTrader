#pragma once
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector> 
#include <chrono>
#include <algorithm>  // std::find_if
#include <iterator>   // std::distance
#include <functional> // std::function

struct timePara {
	int hour;
	int minute;
	int second;

};

// ��ȡ��ǰ����YYYYMMDD
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

//���������ƽ��ֵ
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
//����򵥱�׼��
double SampleStd(const std::vector<double>& arr) {
	double mean = ArithmeticMean(arr);
	double result = 0.0;
	for (const double num : arr) {
		result += pow(num - mean, 2);
	}
	return sqrt(result / (static_cast<double>(arr.size()) - 1));
}

timePara IsTradingTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm local_time;
#ifdef _WIN32
	localtime_s(&local_time, &now_time); // Windows ƽ̨
#else
	localtime_r(&now_time, &local_time); // POSIX (Linux/macOS)
#endif

	int hour = local_time.tm_hour;
	int minute = local_time.tm_min;
	int second = local_time.tm_sec;

	timePara timePara_ = { hour ,minute ,second };
	return timePara_;
}

// ���ͺ����������Զ����������ҽṹ���� vector �е�����
template <typename T>
int findIndex(const std::vector<T>& vec, std::function<bool(const T&)> condition) {
	auto it = std::find_if(vec.begin(), vec.end(), condition);
	if (it != vec.end()) {
		return static_cast<int>(std::distance(vec.begin(), it));
	}
	else {
		return -1; // û�ҵ����� -1
	}
}

inline bool IsNormalTradingTime(int hour, int minute) {
	int time = hour * 100 + minute;
	return
		(time >= 901 && time < 1015) ||  // ����ǰ��
		(time >= 1030 && time < 1130) ||  // ������
		(time >= 1330 && time < 1445);    // ����
}

inline bool IsClosingTime(int hour, int minute) { return (hour == 14 && minute >= 45) || (hour == 15 && minute == 0); }

inline bool IsAfterMarket(int hour, int minute) { return hour == 15 && minute >= 0 && minute < 10; }

inline int GetCurrentTimeInSeconds() { time_t now = std::time(nullptr);return static_cast<int>(now); }


