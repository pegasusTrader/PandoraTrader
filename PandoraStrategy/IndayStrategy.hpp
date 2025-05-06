#pragma once

class IndayStrategy {
private:
    double length;
    double width;

public:
    // ���캯��
    IndayStrategy(double l, double w) : length(l), width(w) {}

    // ��ȡ���ε����
    double getArea() const {
        return length * width;
    }

    // ��ȡ���ε��ܳ�
    double getPerimeter() const {
        return 2 * (length + width);
    }
};