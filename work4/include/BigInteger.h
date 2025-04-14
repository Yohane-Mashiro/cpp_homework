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

        void setDecimalPlaces(size_t places);
        size_t getDecimalPlaces() const;
        void roundToPlaces(size_t places);

    private:
        std::vector<int> digits; // 存储数字的反向表示
        bool isNegative;           // 表示正负
        size_t decimalPlaces;      // 小数位数
        void removeLeadingZeros(); // 移除前导零
        void removeTrailingZeros(); // 移除尾部多余的零
};

BigInteger::BigInteger() : isNegative(false), decimalPlaces(0) {
    digits.push_back(0); // 默认值为0
}

BigInteger::BigInteger(const char* str) : isNegative(false), decimalPlaces(0) {
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

    // 查找小数点位置
    const char* decimalPoint = strchr(str + start, '.');
    size_t decimalPos = 0;
    
    if (decimalPoint != nullptr) {
        decimalPos = decimalPoint - str;
        decimalPlaces = strlen(decimalPoint + 1);
    }

    // 反向存储数字部分
    for (int i = strlen(str) - 1; i >= start; --i) {
        if (str[i] == '.') continue;
        
        if (str[i] >= '0' && str[i] <= '9') {
            digits.push_back(str[i] - '0');
        } else {
            // 非法字符，设为0
            digits.clear();
            digits.push_back(0);
            isNegative = false;
            decimalPlaces = 0;
            return;
        }
    }

    removeLeadingZeros();
    removeTrailingZeros();
    
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
        decimalPlaces = 0;
    }
}

BigInteger::BigInteger(const BigInteger& other) : digits(other.digits), isNegative(other.isNegative), decimalPlaces(other.decimalPlaces) {
}

BigInteger::~BigInteger() {
    // 向量会自动清理，不需要特殊处理
}

void BigInteger::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

void BigInteger::removeTrailingZeros() {
    while (decimalPlaces > 0 && !digits.empty() && digits[0] == 0) {
        digits.erase(digits.begin());
        --decimalPlaces;
    }
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this != &other) {
        digits = other.digits;
        isNegative = other.isNegative;
        decimalPlaces = other.decimalPlaces;
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
    result.isNegative = isNegative; // 保持符号一致

    // 对齐小数点
    size_t maxDecimalPlaces = std::max(decimalPlaces, other.decimalPlaces);
    BigInteger a = *this;
    BigInteger b = other;
    
    // 补齐小数位
    while (a.decimalPlaces < maxDecimalPlaces) {
        a.digits.insert(a.digits.begin(), 0);
        a.decimalPlaces++;
    }
    while (b.decimalPlaces < maxDecimalPlaces) {
        b.digits.insert(b.digits.begin(), 0);
        b.decimalPlaces++;
    }

    int carry = 0;
    size_t maxLen = std::max(a.digits.size(), b.digits.size());
    
    // 确保两个数字长度相同
    while (a.digits.size() < maxLen) a.digits.push_back(0);
    while (b.digits.size() < maxLen) b.digits.push_back(0);

    // 逐位相加
    for (size_t i = 0; i < maxLen || carry; ++i) {
        int sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    result.decimalPlaces = maxDecimalPlaces;
    result.removeLeadingZeros();
    result.removeTrailingZeros();

    // 特殊情况：如果结果为0
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.isNegative = false;
        result.decimalPlaces = 0;
    }

    return result;
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    // 如果符号不同，转为加法
    if (isNegative != other.isNegative) {
        BigInteger temp = other;
        temp.isNegative = !temp.isNegative;
        return *this + temp;
    }

    // 对齐小数点
    size_t maxDecimalPlaces = std::max(decimalPlaces, other.decimalPlaces);
    BigInteger a = *this;
    BigInteger b = other;
    
    // 补齐小数位
    while (a.decimalPlaces < maxDecimalPlaces) {
        a.digits.insert(a.digits.begin(), 0);
        a.decimalPlaces++;
    }
    while (b.decimalPlaces < maxDecimalPlaces) {
        b.digits.insert(b.digits.begin(), 0);
        b.decimalPlaces++;
    }

    // 比较绝对值大小
    bool thisLarger = (a.digits.size() > b.digits.size());
    if (a.digits.size() == b.digits.size()) {
        for (int i = a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i]) {
                thisLarger = (a.digits[i] > b.digits[i]);
                break;
            }
        }
    }

    BigInteger result;
    result.digits.clear();
    result.decimalPlaces = maxDecimalPlaces;

    // 确保被减数大于减数
    const std::vector<int>& larger = thisLarger ? a.digits : b.digits;
    const std::vector<int>& smaller = thisLarger ? b.digits : a.digits;
    
    // 确定结果的符号
    result.isNegative = isNegative ? thisLarger : !thisLarger;

    int borrow = 0;
    
    // 确保两个数字长度相同
    std::vector<int> largerDigits = larger;
    std::vector<int> smallerDigits = smaller;
    while (smallerDigits.size() < largerDigits.size()) {
        smallerDigits.push_back(0);
    }

    // 逐位相减
    for (size_t i = 0; i < largerDigits.size(); ++i) {
        int diff = largerDigits[i] - borrow - smallerDigits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }

    result.removeLeadingZeros();
    result.removeTrailingZeros();

    // 如果结果为0
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.isNegative = false;
        result.decimalPlaces = 0;
    }

    return result;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger result;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    result.isNegative = isNegative != other.isNegative;
    
    // 计算结果的小数位数应该是两个操作数小数位数之和
    result.decimalPlaces = decimalPlaces + other.decimalPlaces;

    // 执行乘法运算
    for (size_t i = 0; i < digits.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; j++) {
            int current = result.digits[i + j] + 
                         digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + 
                         carry;
            result.digits[i + j] = current % 10;
            carry = current / 10;
        }
    }

    result.removeLeadingZeros();
    result.removeTrailingZeros();
    
    // 如果结果是0，确保它是正数且没有小数位
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.isNegative = false;
        result.decimalPlaces = 0;
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

    // 将小数转换为整数进行运算
    BigInteger a = *this;
    BigInteger b = other;
    
    // 计算结果的小数位数
    // 结果的小数位 = 被除数的小数位 - 除数的小数位 + 额外精度
    size_t extraPrecision = 4;  // 额外精度
    size_t resultDecimalPlaces = a.decimalPlaces + extraPrecision;
    
    // 将除数转为整数
    while (b.decimalPlaces > 0) {
        a.digits.insert(a.digits.begin(), 0);  // 被除数相应左移
        b.decimalPlaces--;
    }
    
    // 补充额外的精度位
    for (size_t i = 0; i < extraPrecision; i++) {
        a.digits.insert(a.digits.begin(), 0);
    }

    BigInteger quotient;
    quotient.digits.clear();
    quotient.isNegative = isNegative != other.isNegative;
    
    BigInteger remainder;
    remainder.digits.clear();
    
    // 执行除法运算
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        remainder.digits.insert(remainder.digits.begin(), a.digits[i]);
        remainder.removeLeadingZeros();
        
        int q = 0;
        BigInteger temp = b;
        temp.isNegative = false;
        
        while (!(remainder < temp) && remainder.digits.size() > 0) {
            remainder = remainder - temp;
            q++;
        }
        
        quotient.digits.push_back(q);
    }
    
    // 反转结果
    std::reverse(quotient.digits.begin(), quotient.digits.end());
    quotient.removeLeadingZeros();
    
    // 设置正确的小数位数
    quotient.decimalPlaces = resultDecimalPlaces;
    quotient.removeTrailingZeros();
    
    return quotient;
}

bool BigInteger::operator==(const BigInteger& other) const {
    if (isNegative != other.isNegative || digits.size() != other.digits.size() || decimalPlaces != other.decimalPlaces) {
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
    
    // 对齐小数点进行比较
    BigInteger a = *this;
    BigInteger b = other;
    
    // 补齐小数位
    size_t maxDecimalPlaces = std::max(a.decimalPlaces, b.decimalPlaces);
    while (a.decimalPlaces < maxDecimalPlaces) {
        a.digits.insert(a.digits.begin(), 0);
        a.decimalPlaces++;
    }
    while (b.decimalPlaces < maxDecimalPlaces) {
        b.digits.insert(b.digits.begin(), 0);
        b.decimalPlaces++;
    }
    
    // 如果都是负数，则比较绝对值（绝对值大的实际上更小）
    if (isNegative) {
        if (a.digits.size() != b.digits.size()) {
            return a.digits.size() > b.digits.size();
        }
        
        for (int i = a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i]) {
                return a.digits[i] > b.digits[i];
            }
        }
        
        return false; // 相等的情况
    }
    
    // 如果都是正数，直接比较
    if (a.digits.size() != b.digits.size()) {
        return a.digits.size() < b.digits.size();
    }
    
    for (int i = a.digits.size() - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] < b.digits[i];
        }
    }
    
    return false; // 相等的情况
}

bool BigInteger::operator>(const BigInteger& other) const {
    return other < *this;
}

void BigInteger::setDecimalPlaces(size_t places) {
    if (places > decimalPlaces) {
        // 需要补零
        size_t zerosToAdd = places - decimalPlaces;
        for (size_t i = 0; i < zerosToAdd; ++i) {
            digits.insert(digits.begin(), 0);
        }
    } else if (places < decimalPlaces) {
        // 需要截断或四舍五入
        roundToPlaces(places);
    }
    decimalPlaces = places;
}

size_t BigInteger::getDecimalPlaces() const {
    return decimalPlaces;
}

void BigInteger::roundToPlaces(size_t places) {
    if (places >= decimalPlaces) return;
    
    // 判断需要四舍五入的位
    if (places < decimalPlaces && places < digits.size()) {
        if (digits[decimalPlaces - places - 1] >= 5) {
            // 进位
            int carry = 1;
            size_t pos = decimalPlaces - places;
            while (pos < digits.size() && carry) {
                digits[pos] += carry;
                carry = digits[pos] / 10;
                digits[pos] %= 10;
                ++pos;
            }
            if (carry) digits.push_back(1);
        }
    }

    // 移除多余的小数位
    if (decimalPlaces > places) {
        digits.erase(digits.begin(), digits.begin() + (decimalPlaces - places));
        decimalPlaces = places;
    }
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt) {
    if (bigInt.digits.empty()) {
        os << "0";
        return os;
    }
    
    if (bigInt.isNegative) {
        os << "-";
    }
    
    size_t totalSize = bigInt.digits.size();
    
    // 如果没有小数部分
    if (bigInt.decimalPlaces == 0) {
        for (int i = totalSize - 1; i >= 0; --i) {
            os << bigInt.digits[i];
        }
        return os;
    }
    
    // 处理有小数部分的情况
    size_t integerPartSize = totalSize - bigInt.decimalPlaces;
    
    // 输出整数部分
    if (integerPartSize == 0) {
        os << "0";
    } else {
        for (int i = totalSize - 1; i >= bigInt.decimalPlaces; --i) {
            os << bigInt.digits[i];
        }
    }
    
    // 输出小数部分
    if (bigInt.decimalPlaces > 0) {
        os << ".";
        for (int i = bigInt.decimalPlaces - 1; i >= 0; --i) {
            os << bigInt.digits[i];
        }
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