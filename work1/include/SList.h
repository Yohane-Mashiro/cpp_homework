#ifndef SLIST_H
#define SLIST_H
#include <iostream>
// 定义最大容量
const int MAX_SIZE = 100;

// 线性表类定义
class SList {
public:
    // 构造函数
    SList();
    
    // 析构函数
    ~SList();
    
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
    
private:
    int data[MAX_SIZE]; // 数据数组
    int length;         // 当前长度
};

// 构造函数
SList::SList() : length(0) {}

// 析构函数
SList::~SList() {}

// 清空线性表
void SList::clear() {
    length = 0;
}

// 判断线性表是否为空
bool SList::isEmpty() const {
    return length == 0;
}

// 获取线性表长度
int SList::size() const {
    return length;
}

// 获取指定位置的元素
bool SList::getElem(int i, int &e) const {
    // 检查位置是否有效（i从1开始计数）
    if (i < 1 || i > length) {
        return false;
    }
    e = data[i-1]; // 数组从0开始，因此要减1
    return true;
}

// 查找元素位置（返回第一次出现的位置，未找到返回0）
int SList::locate(int e) const {
    for (int i = 0; i < length; i++) {
        if (data[i] == e) {
            return i + 1; // 返回逻辑位置（从1开始）
        }
    }
    return 0; // 未找到
}

// 在指定位置插入元素
bool SList::insert(int i, int e) {
    // 检查线性表是否已满
    if (length >= MAX_SIZE) {
        std::cout << "线性表已满，无法插入！" << std::endl;
        return false;
    }
    
    // 检查插入位置是否有效（i可以从1到length+1）
    if (i < 1 || i > length + 1) {
        std::cout << "插入位置无效！" << std::endl;
        return false;
    }
    
    // 将第i个位置及之后的元素后移
    for (int j = length; j >= i; j--) {
        data[j] = data[j-1];
    }
    
    // 插入元素
    data[i-1] = e;
    length++;
    return true;
}

// 删除指定位置的元素
bool SList::remove(int i, int &e) {
    // 检查位置是否有效
    if (i < 1 || i > length) {
        std::cout << "删除位置无效！" << std::endl;
        return false;
    }
    
    // 保存被删除的元素
    e = data[i-1];
    
    // 将第i个位置之后的元素前移
    for (int j = i; j < length; j++) {
        data[j-1] = data[j];
    }
    
    length--;
    return true;
}

// 打印线性表
void SList::display() const {
    if (isEmpty()) {
        std::cout << "线性表为空！" << std::endl;
        return;
    }
    
    std::cout << "线性表内容：";
    for (int i = 0; i < length; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

#endif