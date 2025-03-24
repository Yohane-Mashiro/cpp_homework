#ifndef DLIST_PLUS_H
#define DLIST_PLUS_H

#include "/home/yohane-mashiro/cpp_homework/work2/include/Dlist.h"
//如需使用自行修改路径

class DList_plus:public DList{
    public:
        using DList::DList;
        ~DList_plus() {}
        // 拷贝构造函数
        DList_plus(const DList_plus& other);
        // 赋值运算符重载
        DList_plus& operator=(const DList_plus& other);
};

// 拷贝构造函数实现
DList_plus::DList_plus(const DList_plus& other) : DList() {
    // 首先确保当前链表为空
    clear();
    
    // 遍历other链表，复制每个节点
    Node* current = other.head->next;
    while (current != other.tail) {
        insert(length + 1, current->data); // 在末尾添加元素，位置是当前长度+1
        current = current->next;
    }
}

// 赋值运算符重载实现
DList_plus& DList_plus::operator=(const DList_plus& other) {
    // 自我赋值检查
    if (this == &other) {
        return *this;
    }
    
    // 清空当前链表
    clear();
    
    // 复制other链表的所有节点
    Node* current = other.head->next;
    while (current != other.tail) {
        insert(length + 1, current->data); // 在末尾添加元素，位置是当前长度+1
        current = current->next;
    }
    
    return *this;
}

#endif