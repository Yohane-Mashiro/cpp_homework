#include<iostream>
#include<fstream>
#include<string>
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

int main() {
    multiplication();
}