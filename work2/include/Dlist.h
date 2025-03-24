#ifndef DLIST_H
#define DLIST_H
#include <iostream>

class DList {
public:
    // 构造函数
    DList();
    
    // 析构函数
    ~DList();
    
    // 清空线性表
    void clear();
    
    // 判断线性表是否为空
    bool isEmpty() const;
    
    // 获取线性表长度
    int size() const;
    
    // 获取指定位置的元素
    bool getElem(int i, int &e) const;
    
    // 查找元素位置（返回第一次出现的位置，未找到返回0）
    int locate(int e) const;
    
    // 在指定位置插入元素
    bool insert(int i, int e);
    
    // 删除指定位置的元素
    bool remove(int i, int &e);
    
    // 打印线性表
    void display() const;
protected:
    struct Node {
        int data;
        Node *prev;
        Node *next;
    };
    Node *head;
    Node *tail;
    int length;
};

DList::DList() : length(0) {
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

DList::~DList() {
    clear();
    delete head;
    delete tail;
}

void DList::clear() {
    Node *p = head->next;
    while (p != tail) {
        Node *q = p;
        p = p->next;
        delete q;
    }
    head->next = tail;
    tail->prev = head;
    length = 0;
}

bool DList::isEmpty() const {
    return length == 0;
}

int DList::size() const {
    return length;
}

bool DList::getElem(int i, int &e) const {
    if (i < 1 || i > length) {
        std::cout << "位置无效！" << std::endl;
        return false;
    }
    Node *p = head->next;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }
    e = p->data;
    return true;
}

int DList::locate(int e) const {
    Node *p = head->next;
    for (int i = 1; p != tail; i++) {
        if (p->data == e) {
            return i;
        }
        p = p->next;
    }
    return 0;
}

bool DList::insert(int i, int e) {
    if (length >= 100) {
        std::cout << "线性表已满，无法插入！" << std::endl;
        return false;
    }
    if (i < 1 || i > length + 1) {
        std::cout << "插入位置无效！" << std::endl;
        return false;
    }
    Node *p = head;
    for (int j = 0; j < i; j++) {
        p = p->next;
    }
    Node *q = new Node;
    q->data = e;
    q->prev = p->prev;
    q->next = p;
    p->prev->next = q;
    p->prev = q;
    length++;
    return true;
}

bool DList::remove(int i, int &e) {
    if (i < 1 || i > length) {
        std::cout << "位置无效！" << std::endl;
        return false;
    }
    Node *p = head->next;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }
    e = p->data;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    length--;
    return true;
}

void DList::display() const {
    Node *p = head->next;
    while (p != tail) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}



#endif