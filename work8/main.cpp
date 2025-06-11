#include<iostream>
#include<fstream>
#include<string>
#include<cstdint>
using namespace std;

void copy(){
    fstream file;
    char ch;
    file.open("work8.txt", ios::in | ios::out | ios::app);
    if (!file) {
        cout << "文件打开失败！" << endl;
        return;
    }
    

    fstream copyFile;
    copyFile.open("work8_copy.txt", ios::out);
    if (!copyFile) {
        cout << "复制文件打开失败！" << endl;
        return;
    }
    file.clear();
    file.seekg(0);
    while (file.get(ch)) {
        copyFile << ch;
    }
    copyFile.close();
    file.close();
}

void multiplication(){
    fstream file;
    file.open("Multiplication.txt", ios::out);
    if (!file) {
        cout << "文件打开失败！" << endl;
        return;
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            file << i << " * " << j << " = " << i * j << "\t";
        }
        file << endl;
        
    }
    file.close();
}

// BMP文件头结构体
#pragma pack(1)  // 设置1字节对齐
struct BMPHeader {
    char signature[2];     // 文件类型
    uint32_t fileSize;     // 文件大小
    uint16_t reserved1;    // 保留字段1
    uint16_t reserved2;    // 保留字段2
    uint32_t dataOffset;   // 数据偏移量
};

struct BMPInfoHeader {
    uint32_t headerSize;   // 信息头大小
    int32_t width;        // 图像宽度
    int32_t height;       // 图像高度
    uint16_t planes;      // 平面数
    uint16_t bitsPerPixel;// 每像素位数
    uint32_t compression; // 压缩类型
    uint32_t imageSize;   // 图像大小
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack()

void copy(const string& sourceFile, const string& destFile) {
    fstream file(sourceFile, ios::in | ios::binary);
    if (!file) {
        cout << "源文件打开失败！" << endl;
        return;
    }

    fstream copyFile(destFile, ios::out | ios::binary);
    if (!copyFile) {
        cout << "目标文件打开失败！" << endl;
        return;
    }

    char ch;
    while (file.get(ch)) {
        copyFile.put(ch);
    }

    file.close();
    copyFile.close();
}

void multiplication() {
    fstream file;
    file.open("Multiplication.txt", ios::out);
    if (!file) {
        cout << "文件打开失败！" << endl;
        return;
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            file << i << " * " << j << " = " << i * j << "\t";
        }
        file << endl;
    }
    file.close();
}

void processBMP(const string& sourceFile, const string& destFile) {
    fstream inFile(sourceFile, ios::in | ios::binary);
    if (!inFile) {
        cout << "BMP文件打开失败！" << endl;
        return;
    }

    // 读取文件头
    BMPHeader header;
    BMPInfoHeader infoHeader;
    inFile.read(reinterpret_cast<char*>(&header), sizeof(header));
    inFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // 显示BMP信息
    cout << "BMP文件信息：" << endl;
    cout << "文件大小: " << header.fileSize << " 字节" << endl;
    cout << "图像宽度: " << infoHeader.width << " 像素" << endl;
    cout << "图像高度: " << infoHeader.height << " 像素" << endl;
    cout << "色深: " << infoHeader.bitsPerPixel << " 位" << endl;

    // 创建输出文件
    fstream outFile(destFile, ios::out | ios::binary);
    if (!outFile) {
        cout << "输出文件创建失败！" << endl;
        inFile.close();
        return;
    }

    // 复制文件头
    outFile.write(reinterpret_cast<char*>(&header), sizeof(header));
    outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // 计算中心位置
    int centerX = infoHeader.width / 2;
    int centerY = infoHeader.height / 2;
    int padding = (4 - (infoHeader.width * 3) % 4) % 4;

    // 复制图像数据，修改中心9x9区域
    for (int y = 0; y < infoHeader.height; y++) {
        for (int x = 0; x < infoHeader.width; x++) {
            unsigned char pixel[3];
            inFile.read(reinterpret_cast<char*>(pixel), 3);

            // 修改中心9x9区域
            if (x >= centerX - 4 && x <= centerX + 4 &&
                y >= centerY - 4 && y <= centerY + 4) {
                int row = (y - (centerY - 4)) % 3;
                switch (row) {
                    case 0: pixel[0] = 255; pixel[1] = 0; pixel[2] = 0; break;  // 红
                    case 1: pixel[0] = 0; pixel[1] = 255; pixel[2] = 0; break;  // 绿
                    case 2: pixel[0] = 0; pixel[1] = 0; pixel[2] = 255; break;  // 蓝
                }
            }
            outFile.write(reinterpret_cast<char*>(pixel), 3);
        }
        // 处理填充字节
        char padding_data = 0;
        for (int p = 0; p < padding; p++) {
            inFile.read(&padding_data, 1);
            outFile.write(&padding_data, 1);
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    // 测试文件复制
    copy("work8.txt", "work8_copy.txt");
    
    // 生成乘法表
    multiplication();
    
    // 处理BMP文件
    processBMP("source.bmp", "modified.bmp");
    
    return 0;
}