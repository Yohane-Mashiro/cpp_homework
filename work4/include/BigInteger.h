#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

class BigInteger {
    public:
        BigInteger();
        BigInteger(const char* str);
        BigInteger(const BigInteger& other);
        ~BigInteger();

        BigInteger& operator=(const BigInteger& other);
        BigInteger operator+(const BigInteger& other) const;
        BigInteger operator-(const BigInteger& other) const;
        BigInteger operator*(const BigInteger& other) const;
        BigInteger operator/(const BigInteger& other) const;
        bool operator==(const BigInteger& other) const;
        bool operator!=(const BigInteger& other) const;
        bool operator<(const BigInteger& other) const;
        bool operator>(const BigInteger& other) const;

        friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt);
        friend std::istream& operator>>(std::istream& is, BigInteger& bigInt);

    private:
        std::vector<int> digits;  // 存储数字，个位在前（反向存储便于计算）
        bool isNegative;          // 表示正负
        void removeLeadingZeros(); // 移除前导零
};

BigInteger::BigInteger() : isNegative(false) {
    digits.push_back(0); // 默认值为0
}

BigInteger::BigInteger(const char* str) : isNegative(false) {
    if (str == nullptr || str[0] == '\0') {
        digits.push_back(0);
        return;
    }

    int start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }

    // 反向存储，从字符串末尾开始读取
    for (int i = std::strlen(str) - 1; i >= start; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            digits.push_back(str[i] - '0');
        } else {
            // 非法字符，设为0
            digits.clear();
            digits.push_back(0);
            isNegative = false;
            return;
        }
    }

    // 移除前导零
    removeLeadingZeros();
    
    // 如果是0，确保它是正数
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

BigInteger::BigInteger(const BigInteger& other) : digits(other.digits), isNegative(other.isNegative) {
}

BigInteger::~BigInteger() {
    // 向量会自动清理，不需要特殊处理
}

void BigInteger::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this != &other) {
        digits = other.digits;
        isNegative = other.isNegative;
    }
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    // 如果符号不同，转为减法
    if (isNegative != other.isNegative) {
        BigInteger temp = other;
        temp.isNegative = !temp.isNegative;
        return *this - temp;
    }

    BigInteger result;
    result.digits.clear();
    result.isNegative = isNegative; // 结果符号与原数相同

    int carry = 0;
    size_t i = 0, j = 0;

    // 逐位相加
    while (i < digits.size() || j < other.digits.size() || carry) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i++];
        if (j < other.digits.size()) sum += other.digits[j++];
        
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    result.removeLeadingZeros();
    return result;
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    // 如果符号不同，转为加法
    if (isNegative != other.isNegative) {
        BigInteger temp = other;
        temp.isNegative = !temp.isNegative;
        return *this + temp;
    }

    // 比较绝对值大小
    bool thisLarger = true;
    if (digits.size() < other.digits.size()) {
        thisLarger = false;
    } else if (digits.size() == other.digits.size()) {
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] < other.digits[i]) {
                thisLarger = false;
                break;
            } else if (digits[i] > other.digits[i]) {
                break;
            }
        }
    }

    BigInteger result;
    result.digits.clear();

    // 确定结果的符号和计算顺序
    const std::vector<int>& larger = thisLarger ? digits : other.digits;
    const std::vector<int>& smaller = thisLarger ? other.digits : digits;
    result.isNegative = isNegative ? thisLarger : !thisLarger;

    int borrow = 0;
    size_t i = 0, j = 0;

    // 逐位相减
    while (i < larger.size()) {
        int diff = larger[i] - borrow;
        if (j < smaller.size()) diff -= smaller[j++];
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits.push_back(diff);
        i++;
    }

    result.removeLeadingZeros();
    
    // 如果结果是0，确保它是正数
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.isNegative = false;
    }
    
    return result;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger result;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    result.isNegative = isNegative != other.isNegative;

    for (size_t i = 0; i < digits.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; j++) {
            int current = result.digits[i + j] + digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            result.digits[i + j] = current % 10;
            carry = current / 10;
        }
    }

    result.removeLeadingZeros();
    
    // 如果结果是0，确保它是正数
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.isNegative = false;
    }
    
    return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    // 除数为0，抛出异常
    if (other.digits.size() == 1 && other.digits[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    // 被除数为0，结果为0
    if (digits.size() == 1 && digits[0] == 0) {
        return BigInteger();
    }

    // 简单实现：反复减法
    BigInteger absThis = *this;
    absThis.isNegative = false;
    
    BigInteger absOther = other;
    absOther.isNegative = false;
    
    // 如果被除数小于除数，结果为0
    if (absThis < absOther) {
        return BigInteger();
    }

    BigInteger quotient;
    quotient.digits.clear();
    quotient.isNegative = isNegative != other.isNegative;
    
    // 从最高位开始处理
    BigInteger temp;
    std::string quotStr = "";
    
    for (int i = absThis.digits.size() - 1; i >= 0; i--) {
        // 将当前位加入临时结果的末尾
        temp.digits.insert(temp.digits.begin(), absThis.digits[i]);
        temp.removeLeadingZeros();
        
        // 计算当前位可以减去多少个除数
        int q = 0;
        while (!(temp < absOther)) {
            temp = temp - absOther;
            q++;
        }
        
        quotStr = std::to_string(q) + quotStr;
    }
    
    // 将结果转换回 BigInteger
    BigInteger finalQuotient(quotStr.c_str());
    finalQuotient.isNegative = quotient.isNegative;
    
    return finalQuotient;
}

bool BigInteger::operator==(const BigInteger& other) const {
    if (isNegative != other.isNegative || digits.size() != other.digits.size()) {
        return false;
    }
    
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    
    return true;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger& other) const {
    // 如果符号不同，负数小于正数
    if (isNegative != other.isNegative) {
        return isNegative;
    }
    
    // 如果都是负数，则比较绝对值（绝对值大的实际上更小）
    if (isNegative) {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        
        return false; // 相等的情况
    }
    
    // 如果都是正数，直接比较
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    
    return false; // 相等的情况
}

bool BigInteger::operator>(const BigInteger& other) const {
    return other < *this;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt) {
    if (bigInt.digits.empty()) {
        os << "0";
        return os;
    }
    
    if (bigInt.isNegative) {
        os << "-";
    }
    
    // 输出时反向输出，因为存储是反向的
    for (int i = bigInt.digits.size() - 1; i >= 0; --i) {
        os << bigInt.digits[i];
    }
    
    return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bigInt) {
    std::string str;
    is >> str;
    bigInt = BigInteger(str.c_str());
    return is;
}
#endif