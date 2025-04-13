#include<iostream>
#include "include/DStack.h"
using namespace std;
int main() {
    DStack stack;
    int e;

    std::cout << "测试栈基本操作：" << std::endl;

    // 测试入栈操作
    std::cout << "\n===== 测试入栈操作 =====" << std::endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();

    // 测试获取栈顶元素
    std::cout << "\n===== 测试获取栈顶元素 =====" << std::endl;
    if (stack.top(e)) {
        std::cout << "栈顶元素是：" << e << std::endl;
    }

    // 测试出栈操作
    std::cout << "\n===== 测试出栈操作 =====" << std::endl;
    if (stack.pop(e)) {
        std::cout << "出栈元素是：" << e << std::endl;
    }
    stack.display();

    // 测试其他操作
    std::cout << "\n===== 测试其他操作 =====" << std::endl;
    std::cout << "栈的大小：" << stack.size() << std::endl;
    std::cout << "栈是否为空：" << (stack.isEmpty() ? "是" : "否") << std::endl;

    // 测试清空操作
    std::cout << "\n===== 测试清空操作 =====" << std::endl;
    stack.clear();
    std::cout << "清空后，栈的大小：" << stack.size() << std::endl;
    std::cout << "清空后，栈是否为空：" << (stack.isEmpty() ? "是" : "否") << std::endl;
    
    return 0;
}