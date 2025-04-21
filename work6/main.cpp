#include<iostream>
#include"include/DQueue.h"
using namespace std;
int main() {
    DQueue queue;
    int e;

    std::cout << "测试队列基本操作：" << std::endl;

    // 测试入队操作
    std::cout << "\n===== 测试入队操作 =====" << std::endl;
    queue.Insert(10);
    queue.Insert(20);
    queue.Insert(30);
    queue.display();

    // 测试获取队头元素
    std::cout << "\n===== 测试获取队头元素 =====" << std::endl;
    if (queue.front(e)) {
        std::cout << "队头元素是：" << e << std::endl;
    }

    // 测试出队操作
    std::cout << "\n===== 测试出队操作 =====" << std::endl;
    if (queue.Delete(e)) {
        std::cout << "出队元素是：" << e << std::endl;
    }
    queue.display();

    // 测试其他操作
    std::cout << "\n===== 测试其他操作 =====" << std::endl;
    std::cout << "队列的大小：" << queue.size() << std::endl;
    std::cout << "队列是否为空：" << (queue.isEmpty() ? "是" : "否") << std::endl;

    // 测试清空操作
    std::cout << "\n===== 测试清空操作 =====" << std::endl;
    queue.clear();
    std::cout << "清空后，队列的大小：" << queue.size() << std::endl;
    std::cout << "清空后，队列是否为空：" << (queue.isEmpty() ? "是" : "否") << std::endl;

    return 0;
}