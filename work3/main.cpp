#include <iostream>
#include "include/DlistPlus.h"
using namespace std;
int main(){
    DList_plus list;
    int e;
    
    std::cout << "测试线性表基本操作：" << std::endl;
    
    // 测试插入操作
    std::cout << "\n===== 测试插入操作 =====" << std::endl;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);
    list.insert(2, 15); // 在中间插入
    list.display();
    
    // 赋值运算符重载
    std::cout << "\n===== 赋值运算符重载 =====" << std::endl;
    DList_plus list2;
    list2 = list;
    list2.display();
    
    return 0;
}
