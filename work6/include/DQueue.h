#ifndef DQeueue_H
#define DQeueue_H
#include "/home/yohane-mashiro/cpp_homework/work2/include/Dlist.h"
//如需使用自行修改路径
class DQueue:public DList{
    public:
        DQueue(); // 构造函数
        using DList::DList;
        ~DQueue() {}
        // 入队
        bool enqueue(int e);
        // 出队
        bool dequeue(int &e);
        // 获取队头元素
        bool front(int &e) const;
        // 判断队列是否为空
        bool isEmpty() const;
        // 获取队列的大小
        int size() const;
};

DQueue::DQueue() : DList() {}
bool DQueue::enqueue(int e) {
    return insert(size() + 1, e); // 在尾部插入元素
}
bool DQueue::dequeue(int &e) {
    if (isEmpty()) {
        std::cout << "队列为空，无法出队！" << std::endl;
        return false;
    }
    return remove(1, e); // 删除头部元素
}
bool DQueue::front(int &e) const {
    if (isEmpty()) {
        std::cout << "队列为空，无法获取队头元素！" << std::endl;
        return false;
    }
    return getElem(1, e); // 获取头部元素
}
bool DQueue::isEmpty() const {
    return DList::isEmpty(); // 调用基类的isEmpty方法
}
int DQueue::size() const {
    return DList::size(); // 调用基类的size方法
}
#endif