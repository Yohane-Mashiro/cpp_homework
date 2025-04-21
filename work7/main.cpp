#include <iostream>
#include <string>
using namespace std;

// 基类：People
class People {
protected:
    string name;
    int age;
public:
    People(const string& n = "Unknown", int a = 0) : name(n), age(a) {
        cout << "People constructor called. Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~People() {
        cout << "People destructor called. Name: " << name << endl;
    }
    
    void showBasicInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// 第二层：两个派生类通过虚拟继承People
class Student : virtual public People {
protected:
    string studentID;
    float gpa;
public:
    Student(const string& n = "Unknown", int a = 0, 
            const string& sid = "00000", float g = 0.0) 
        : People(n, a), studentID(sid), gpa(g) {
        cout << "Student constructor called. ID: " << studentID << ", GPA: " << gpa << endl;
    }
    
    ~Student() {
        cout << "Student destructor called. ID: " << studentID << endl;
    }
    
    void showStudentInfo() const {
        cout << "Student ID: " << studentID << ", GPA: " << gpa << endl;
    }
};

class Employee : virtual public People {
protected:
    string employeeID;
    double salary;
public:
    Employee(const string& n = "Unknown", int a = 0, 
             const string& eid = "E0000", double s = 0.0) 
        : People(n, a), employeeID(eid), salary(s) {
        cout << "Employee constructor called. ID: " << employeeID << ", Salary: " << salary << endl;
    }
    
    ~Employee() {
        cout << "Employee destructor called. ID: " << employeeID << endl;
    }
    
    void showEmployeeInfo() const {
        cout << "Employee ID: " << employeeID << ", Salary: " << salary << endl;
    }
};

// 第三层：多重继承自Student和Employee
class TeachingAssistant : public Student, public Employee {
private:
    string department;
    int workHours;
public:
    TeachingAssistant(const string& n = "TA", int a = 22, 
                      const string& sid = "S1234", float g = 3.5,
                      const string& eid = "E5678", double s = 2000,
                      const string& dept = "Computer Science", int hours = 20) 
        : People(n, a),  // 必须显式调用虚基类的构造函数
          Student(n, a, sid, g),
          Employee(n, a, eid, s),
          department(dept),
          workHours(hours) {
        cout << "TeachingAssistant constructor called. Department: " << department 
             << ", Work Hours: " << workHours << endl;
    }
    
    ~TeachingAssistant() {
        cout << "TeachingAssistant destructor called. Department: " << department << endl;
    }
    
    void showTAInfo() const {
        // 通过虚拟继承，可以直接访问People的成员，不会产生歧义
        showBasicInfo();
        showStudentInfo();
        showEmployeeInfo();
        cout << "Department: " << department << ", Work Hours: " << workHours << " hrs/week" << endl;
    }
};

int main() {
    cout << "Creating a TeachingAssistant object:" << endl;
    TeachingAssistant ta("Zhang San", 24, "S2023001", 3.8, "E2023045", 3000, "Computer Science", 15);
    
    cout << "\nTeaching Assistant information:" << endl;
    ta.showTAInfo();
    
    // 验证没有歧义
    cout << "\nDirectly accessing People members from TeachingAssistant:" << endl;
    ta.showBasicInfo(); // 如果不使用虚拟继承，这一行会导致编译错误，因为存在歧义
    
    return 0;
}