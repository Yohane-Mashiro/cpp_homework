#include <iostream>
#include "head/Dlist.h"
using namespace std;
int main(){
    DList list;
    int e;
    
    std::cout << "测试线性表基本操作：" << std::endl;
    
    // 测试插入操作
    std::cout << "\n===== 测试插入操作 =====" << std::endl;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);
    list.insert(2, 15); // 在中间插入
    list.display();
    
    // 测试获取元素
    std::cout << "\n===== 测试获取元素 =====" << std::endl;
    if (list.getElem(2, e)) {
        std::cout << "第2个元素是：" << e << std::endl;
    }
    
    // 测试查找元素
    std::cout << "\n===== 测试查找元素 =====" << std::endl;
    int pos = list.locate(20);
    if (pos) {
        std::cout << "元素20的位置是：" << pos << std::endl;
    } else {
        std::cout << "未找到元素20" << std::endl;
    }
    
    // 测试删除操作
    std::cout << "\n===== 测试删除操作 =====" << std::endl;
    if (list.remove(2, e)) {
        std::cout << "删除的元素是：" << e << std::endl;
    }
    list.display();
    
    // 测试其他操作
    std::cout << "\n===== 测试其他操作 =====" << std::endl;
    std::cout << "线性表长度：" << list.size() << std::endl;
    std::cout << "线性表是否为空：" << (list.isEmpty() ? "是" : "否") << std::endl;
    
    // 测试清空操作
    std::cout << "\n===== 测试清空操作 =====" << std::endl;
    list.clear();
    std::cout << "清空后，线性表长度：" << list.size() << std::endl;
    std::cout << "清空后，线性表是否为空：" << (list.isEmpty() ? "是" : "否") << std::endl;
    list.display();
    
    return 0;
}
