#ifndef DStACK_H
#define DStACK_H
#include "/home/yohane-mashiro/cpp_homework/work2/include/Dlist.h"
//如需使用自行修改路径

class DStack:public DList{
    public:
        DStack(); // 构造函数
        using DList::DList;
        ~DStack() {}
        // 入栈
        bool push(int e);
        // 出栈
        bool pop(int &e);
        // 获取栈顶元素
        bool top(int &e) const;
        // 判断栈是否为空
        bool isEmpty() const;
        // 获取栈的大小
        int size() const;
};

DStack::DStack() : DList() {}
bool DStack::push(int e) {
    return insert(1, e); // 在头部插入元素
}
bool DStack::pop(int &e) {
    if (isEmpty()) {
        std::cout << "栈为空，无法出栈！" << std::endl;
        return false;
    }
    return remove(1, e); // 删除头部元素
}
bool DStack::top(int &e) const {
    if (isEmpty()) {
        std::cout << "栈为空，无法获取栈顶元素！" << std::endl;
        return false;
    }
    return getElem(1, e); // 获取头部元素
}
bool DStack::isEmpty() const {
    return DList::isEmpty(); // 调用基类的isEmpty方法
}
int DStack::size() const {
    return DList::size(); // 调用基类的size方法
}

#endif