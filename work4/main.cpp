#include <iostream>
#include "include/BigInteger.h"

// 测试函数：展示两个 BigInteger 之间的各种操作
void testOperation(const char* num1Str, const char* num2Str) {
    BigInteger num1(num1Str);
    BigInteger num2(num2Str);
    
    std::cout << "\n===== 测试: " << num1 << " 和 " << num2 << " =====\n";
    
    // 测试加法
    std::cout << num1 << " + " << num2 << " = " << (num1 + num2) << std::endl;
    
    // 测试减法
    std::cout << num1 << " - " << num2 << " = " << (num1 - num2) << std::endl;
    std::cout << num2 << " - " << num1 << " = " << (num2 - num1) << std::endl;
    
    // 测试乘法
    std::cout << num1 << " * " << num2 << " = " << (num1 * num2) << std::endl;
    
    // 测试除法（避免除以零）
    if (!(num2 == BigInteger("0"))) {
        std::cout << num1 << " / " << num2 << " = " << (num1 / num2) << std::endl;
    } else {
        std::cout << num1 << " / " << num2 << " = 错误: 除数不能为零" << std::endl;
    }
    
    // 测试比较运算符
    std::cout << num1 << " == " << num2 << " ? " << (num1 == num2 ? "是" : "否") << std::endl;
    std::cout << num1 << " != " << num2 << " ? " << (num1 != num2 ? "是" : "否") << std::endl;
    std::cout << num1 << " < " << num2 << " ? " << (num1 < num2 ? "是" : "否") << std::endl;
    std::cout << num1 << " > " << num2 << " ? " << (num1 > num2 ? "是" : "否") << std::endl;
}

// 测试输入输出流操作
void testIO() {
    BigInteger num;
    std::cout << "\n===== 测试输入/输出 =====\n";
    std::cout << "请输入一个整数: ";
    std::cin >> num;
    std::cout << "您输入的数字是: " << num << std::endl;
}

// 测试一些大数计算
void testLargeNumbers() {
    std::cout << "\n===== 测试大数计算 =====\n";
    
    // 计算大数阶乘
    BigInteger factorial("1");
    int n = 20;  // 计算 20!
    
    std::cout << n << "! = ";
    for (int i = 2; i <= n; ++i) {
        factorial = factorial * BigInteger(std::to_string(i).c_str());
    }
    std::cout << factorial << std::endl;
    
    // 大数加法
    BigInteger large1("9999999999999999999999");
    BigInteger large2("1");
    std::cout << large1 << " + " << large2 << " = " << (large1 + large2) << std::endl;
}

int main() {
    std::cout << "BigInteger 类测试程序\n";
    
    // 测试基本操作
    testOperation("123", "456");         // 正数与正数
    testOperation("-123", "456");        // 负数与正数
    testOperation("123", "-456");        // 正数与负数
    testOperation("-123", "-456");       // 负数与负数
    testOperation("0", "123");           // 零与非零
    testOperation("123456789", "987654321");  // 大数测试
    
    // 测试输入输出
    testIO();
    
    // 测试大数计算
    testLargeNumbers();
    
    return 0;
}