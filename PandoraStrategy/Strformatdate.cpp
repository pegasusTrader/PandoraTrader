#pragma once
//#include <iostream>
//#include <ctime>
//#include <sstream>
//#include <string>
#include "Strformatdate.h"
//#pragma warning(disable:4996)

using namespace std;


string Strformatdate::getCurrentDateString() {
    time_t currentTime = time(nullptr);
    tm* timeInfo = localtime(&currentTime);

    char buffer[9];  // yyyyMMdd��ʽ��Ҫ8���ַ������ټ�һ���ַ���������'\0'
    strftime(buffer, sizeof(buffer), "%Y%m%d", timeInfo);

    return string(buffer);

};