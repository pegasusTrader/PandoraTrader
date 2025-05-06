#pragma once

class IndayStrategy {
private:
    double length;
    double width;

public:
    // 构造函数
    IndayStrategy(double l, double w) : length(l), width(w) {}

    // 获取矩形的面积
    double getArea() const {
        return length * width;
    }

    // 获取矩形的周长
    double getPerimeter() const {
        return 2 * (length + width);
    }
};