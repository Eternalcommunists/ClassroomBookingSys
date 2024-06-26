//
// Created by 吴培浩 on 24-6-26.
//

#ifndef UNTITLED1_TEACHER_H
#define UNTITLED1_TEACHER_H

#endif //UNTITLED1_TEACHER_H
#include <iostream>
#include <mysql.h>
#include <limits>
#include <conio.h>
#include "Room.h"

using namespace std;
bool isValidDay(int year, int month, int day) {
    if (month == 2) {
        // 闰年判断
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (leap ? 29 : 28);
    }

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day <= daysInMonth[month - 1];
}

bool isDateInRange(const std::string& date) {
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    // 例如，检查年份范围在 1900 到 2100 年之间
    if (year < 1900 || year > 2100) return false;

    // 检查月份和日期
    if (month < 1 || month > 12) return false;

    if (day < 1 || day > 31) return false; // 简单示例，实际检查时应考虑月份和闰年情况

    return true;
}
bool isValidDate(const std::string& date) {
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    return isValidDay(year, month, day);
}

//一个行数据的类型安全(type-safe)的表示
class Teacher {
protected:
    int TeacherID;
    int TeacherNumber; // 教师工号
    string TeacherName; // 教师姓名
    int PermissionLevel; // 权限等级
    string PhoneNumber; // 电话号码
    string OfficeName;
public:
    int getTeacherId() const;
    int getTeacherNumber() const;
    const string &getTeacherName() const;
    int getPermissionLevel() const;
    const string &getPhoneNumber() const;
    const string &getOfficeName() const;
    // 办公室名称
private:
    string Password;//修正：吴培浩 时间：2024.6.26 00点54分
    // other attributes
public:
    // 构造函数、析构函数、getter、setter等
    virtual void display() const = 0; // 纯虚函数，强制子类实现
//    virtual void saveToFile(ofstream& file) const = 0; // 虚函数
//    virtual void loadFromFile(ifstream& file) = 0; // 虚函数
    // 虚拟析构函数，确保派生类对象被正确销毁
    virtual ~Teacher() = default;
    void setTeacherNumber(int number) { TeacherNumber = number; }
    void setTeacherName(const string& name) { TeacherName = name; }
    void setPermissionLevel(int level) { PermissionLevel = level; }
    void setPhoneNumber(const string& number) { PhoneNumber = number; }
    void setOfficeName(const string& name) { OfficeName = name; }
    void setpassword(const string&pass){Password=pass;}//修正：吴培浩 时间：2024.6.26 00点54分
    bool teacher_enter();
    void ViewAvailableRooms();
    void ViewBookings();
    bool CancelBooking(int bookingID);
    static bool ModifyBooking(int bookingID, int roomID, const string &bookingDate);
    void OptionChoice();
    void getDateFromTeacher(string &bookingDate);
    bool isDateAvailable(int roomID, const string &bookingDate);
    bool BookRoom(int roomID, const string &bookingDate);

    void Loginshow();
};
class NormalTeacher : public Teacher {
public:
    // 构造函数、析构函数、getter、setter等
    void display() const override; // 覆盖父类的纯虚函数
//    void saveToFile(ofstream& file) const override; // 覆盖父类的虚函数
//    void loadFromFile(ifstream& file) override; // 覆盖父类的虚函数
    // 友元函数声明
    friend ostream& operator<<(ostream& os, const NormalTeacher& teacher);
    friend istream& operator>>(istream& is, NormalTeacher& teacher);

    void teacher_register();
};
// display函数的实现
void NormalTeacher::display() const {
    cout << "Teacher Number: " << TeacherNumber << endl;
    cout << "Teacher Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}

std::string getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}
// 获取密码的辅助函数
std::string getPassword() {
    std::string password;
    std::cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != '\r') { // 使用 _getch() 无回显输入
        if (ch == '\b') { // 处理退格
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // 光标前移一位并删除显示的星号
            }
        } else {
            password += ch;
            std::cout << '*'; // 显示星号
        }
    }
    std::cout << std::endl;
    return password;
}

// operator<<函数的实现
ostream& operator<<(ostream& os, const NormalTeacher& teacher) {
    os << "Teacher Number: " << teacher.TeacherNumber << endl;
    os << "Teacher Name: " << teacher.TeacherName << endl;
    os << "Permission Level: " << teacher.PermissionLevel << endl;
    os << "Phone Number: " << teacher.PhoneNumber << endl;
    os << "Office Name: " << teacher.OfficeName << endl;
    return os;
}
// operator>>函数的实现
istream& operator>>(istream& is, NormalTeacher& teacher) {
    cout << "Enter Teacher Number: ";
    is >> teacher.TeacherNumber;
    is.ignore(); // 忽略换行符
    cout << "Enter Teacher Name: ";
    getline(is, teacher.TeacherName);
    cout << "Enter Permission Level: ";
    is >> teacher.PermissionLevel;
    is.ignore(); // 忽略换行符
    cout << "Enter Phone Number: ";
    getline(is, teacher.PhoneNumber);
    cout << "Enter Office Name: ";
    getline(is, teacher.OfficeName);
    return is;
}
// 注册教师函数的实现
void NormalTeacher::teacher_register() {
    // 获取用户输入的详细信息
    int teacherNumber = std::stoi(getInput("Enter Teacher Number: "));
    std::string teacherName = getInput("Enter Teacher Name: ");
    int permissionLevel = std::stoi(getInput("Enter Permission Level (e.g., 1 for Normal Teacher): "));
    std::string phoneNumber = getInput("Enter Phone Number: ");
    std::string officeName = getInput("Enter Office Name: ");
    std::string password = getPassword();

    // 连接数据库
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cout << "Error connecting to database: " << mysql_error(&mysql) << std::endl;
        return;
    }

    // 构造插入 SQL 语句
    std::string query = "INSERT INTO Teacher (TeacherNumber, TeacherName, PermissionLevel, PhoneNumber, OfficeName, Password) VALUES ("
                        + std::to_string(teacherNumber) + ", '"
                        + teacherName + "', "
                        + std::to_string(permissionLevel) + ", '"
                        + phoneNumber + "', '"
                        + officeName + "', '"
                        + password + "')";

    // 执行 SQL 语句
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error inserting teacher: " << mysql_error(&mysql) << std::endl;
        mysql_close(&mysql);
        return;
    }

    std::cout << "Teacher registered successfully." << std::endl;

    // 关闭数据库连接
    mysql_close(&mysql);
}



// 定义系统管理员类
class Admin : public Teacher {
    // other attributes
public:
    // 构造函数、析构函数、getter、setter等
    void display() const override; // 覆盖父类的纯虚函数
//    void saveToFile(ofstream& file) const override; // 覆盖父类的虚函数
//    void loadFromFile(ifstream& file) override; // 覆盖父类的虚函数

    // 友元函数声明
    friend ostream& operator<<(ostream& os, const Admin& admin);
    friend istream& operator>>(istream& is, Admin& admin);

    void admin_enter();
    bool CheckConflict(int roomID, const std::string& bookingDate);
    bool ApproveBooking(int bookingID);

    void ViewAllBookings();

    bool GetBookingDetails(int bookingID, int &roomID, string &bookingDate);

    bool CancelBooking(int bookingID);
};
// display函数的实现
void Admin::display() const {
    cout << "Admin Number: " << TeacherNumber << endl;
    cout << "Admin Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}


// operator<<函数的实现
ostream& operator<<(ostream& os, const Admin& admin) {
    os << "Admin Number: " << admin.TeacherNumber << endl;
    os << "Admin Name: " << admin.TeacherName << endl;
    os << "Permission Level: " << admin.PermissionLevel << endl;
    os << "Phone Number: " << admin.PhoneNumber << endl;
    os << "Office Name: " << admin.OfficeName << endl;
    return os;
}
// operator>>函数的实现
istream& operator>>(istream& is, Admin& admin) {
    cout << "Enter Admin Number: ";
    is >> admin.TeacherNumber;
    is.ignore(); // 忽略换行符
    cout << "Enter Admin Name: ";
    getline(is, admin.TeacherName);
    cout << "Enter Permission Level: ";
    is >> admin.PermissionLevel;
    is.ignore(); // 忽略换行符
    cout << "Enter Phone Number: ";
    getline(is, admin.PhoneNumber);
    cout << "Enter Office Name: ";
    getline(is, admin.OfficeName);
    return is;
}

void Admin::admin_enter() {

}
/**编辑时间:24-6-26 上午1:23
*创建人：吴培浩
*/
bool CheckLogin(int teacherNumber, const std::string& password) {
    // 初始化 MySQL 连接句柄
    MYSQL* mysql = mysql_init(NULL);

    // 尝试连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        // 如果连接失败，打印错误信息并返回 false
        std::cout << "Connection error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    // 创建预处理语句句柄
    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
    // SQL 查询语句，使用 ? 占位符代替实际参数
    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=?";

    // 准备 SQL 语句
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        // 如果准备失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cout << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 定义绑定参数数组，两个参数：TeacherNumber 和 Password
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));  // 初始化绑定参数数组

    // 绑定 TeacherNumber 参数
    bind[0].buffer_type = MYSQL_TYPE_LONG;  // 参数类型为整数
    bind[0].buffer = (char*)&teacherNumber; // 指向 TeacherNumber 的指针
    bind[0].is_null = 0;                    // 不为空
    bind[0].length = 0;                     // 长度设置为 0

    // 绑定 Password 参数
    bind[1].buffer_type = MYSQL_TYPE_STRING;     // 参数类型为字符串
    bind[1].buffer = (char*)password.c_str();    // 指向密码字符串
    bind[1].buffer_length = password.length();   // 设置字符串长度
    bind[1].is_null = 0;                         // 不为空
    bind[1].length = 0;                          // 长度设置为 0

    // 绑定参数到预处理语句
    if (mysql_stmt_bind_param(stmt, bind)) {
        // 如果绑定失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cout << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 执行预处理语句
    if (mysql_stmt_execute(stmt)) {
        // 如果执行失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cout << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 获取查询结果的元数据（描述结果的结构）
    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
    int num_fields = mysql_num_fields(res);  // 获取结果中的字段数
    // 定义绑定结果数组，初始化为 0
    MYSQL_BIND result_bind[num_fields];
    memset(result_bind, 0, sizeof(result_bind));

    // 定义一个字符缓冲区，用于存储查询结果
    char buffer[256];
    for (int i = 0; i < num_fields; ++i) {
        // 设置每个字段的缓冲区信息
        result_bind[i].buffer_type = MYSQL_TYPE_STRING;  // 字段类型为字符串
        result_bind[i].buffer = buffer;                  // 指向缓冲区
        result_bind[i].buffer_length = sizeof(buffer);   // 缓冲区大小
        result_bind[i].is_null = 0;                      // 不为空
        result_bind[i].length = 0;                       // 长度设置为 0
    }

    // 绑定结果缓冲区到预处理语句
    if (mysql_stmt_bind_result(stmt, result_bind)) {
        // 如果绑定失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cout << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 将查询结果存储在服务器上
    mysql_stmt_store_result(stmt);
    // 检查是否有查询结果（是否有匹配的记录）
    bool login_successful = (mysql_stmt_num_rows(stmt) > 0);

    // 释放结果集
    mysql_free_result(res);
    // 关闭预处理语句
    mysql_stmt_close(stmt);
    // 关闭 MySQL 连接
    mysql_close(mysql);

    return login_successful;  // 返回登录是否成功
}

bool Teacher:: teacher_enter(){
    //read_all_the_teachers(); //读取用户列表
    string str;
    int cnt = 0;
    while (cnt < 3) {
        //int teachernumber;
        cout << "输入教师工号：";
        cin >> TeacherNumber;
        cout << "输入密码：";
        str = getPassword();//扫描密码
        setpassword(str);//无显密码
        bool identifier = CheckLogin(TeacherNumber, str);
        cout<<"验证结果"<<identifier<<endl;
        int i, user_num = 3;
        if(identifier == 1)
        {
            cout << "*******" << endl;
            cout << "登录成功！" << endl;
            cout << "*******" << endl;
            return true;
        }
        if (identifier == 0) {
            for (i = 0; i < user_num; i++) {
                str = getPassword();//扫描密码
                setpassword(str);//无显密码
                if (CheckLogin(TeacherNumber, str) == 0) {
                    cout << "*******" << endl;
                    cout << "登录成功！" << endl;
                    cout << "*******" << endl;
                    // teacher_operate(); //跳转普通教师操作UI界面
                    return true;
                } else if (i == user_num) {
                    cnt++;
                    cout << "用户名或密码错误，请再次输入用户名与密码，";
                    cout << "你还有" << 3 - cnt << "次机会" << endl;
                }
            }
            if (i > user_num)//存在逻辑问题，记得修正一下
            { return false; }
            if (cnt == 3) {
                cout << "错误次数已达上限，系统关闭！" << endl;
                return false; }
        }
    }
    return 0;
}
/**编辑时间:24-6-26 上午1:36
                *创建人：吴培浩
                */
void Teacher::ViewBookings() {
    // 初始化 MySQL 对象
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        return;
    }

    // SQL 查询语句：查找当前教师的所有预定记录
    std::string query = "SELECT b.BookingID, b.SubmissionTime, c.RoomNumber, c.RoomName, b.BookingDate, b.IsApproved "
                        "FROM BookingRecord b "
                        "JOIN Classroom c ON b.RoomID = c.RoomID "
                        "WHERE b.TeacherID = " + std::to_string(TeacherID);

    // 执行 SQL 查询
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Query error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // 获取查询结果集
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "Result error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // 遍历结果集并打印每一行数据
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Booking ID: " << row[0]
                  << ", Submission Time: " << row[1]
                  << ", Room Number: " << row[2]
                  << ", Room Name: " << row[3]
                  << ", Booking Date: " << row[4]
                  << ", Approved: " << (std::stoi(row[5]) ? "Yes" : "No") << std::endl;
    }

    // 释放结果集并关闭数据库连接
    mysql_free_result(res);
    mysql_close(mysql);
}

// 查看可用教室的函数实现
void Teacher::ViewAvailableRooms() {
    // 初始化 MySQL 对象
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        return;
    }

    // SQL 查询语句：查找所有未被占用的教室
    std::string query = "SELECT RoomID, RoomNumber, RoomName, Capacity, RoomType "
                        "FROM Classroom "
                        "WHERE IsOccupied = 0";

    // 执行 SQL 查询
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Query error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // 获取查询结果集
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "Result error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // 遍历结果集并打印每一行数据
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Room ID: " << row[0]
                  << ", Room Number: " << row[1]
                  << ", Room Name: " << row[2]
                  << ", Capacity: " << row[3]
                  << ", Room Type: " << row[4] << std::endl;
    }

    // 释放结果集并关闭数据库连接
    mysql_free_result(res);
    mysql_close(mysql);
}

// 查看所有预定信息
void Admin::ViewAllBookings() {
    // 连接数据库（省略）

    // 构造查询语句
    std::string query = "SELECT * FROM BookingRecord";

    // 执行查询
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
        return;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return;
    }

    // 输出表头
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    for (int i = 0; i < num_fields; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        std::cout << field->name << '\t';
    }
    std::cout << std::endl;

    // 输出每行数据
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            std::cout << row[i] << '\t';
        }
        std::cout << std::endl;
    }

    // 释放结果集
    mysql_free_result(result);

    // 关闭数据库连接（省略）
}
/**编辑时间:24-6-26 上午2:02
*创建人：吴培浩
*/
// 批准预定请求
//bool Admin::ApproveBooking(int bookingID) {
//
//    // 检查是否存在时间和教室冲突
//    if (CheckConflict(bookingID, bookingDate)) {
//        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
//        return false;
//    }
//
//    // 构造更新语句
//    std::string query = "UPDATE BookingRecord SET IsApproved = true WHERE BookingID = " + std::to_string(bookingID);
//
//    // 执行更新
//    if (mysql_query(&mysql, query.c_str())) {
//        std::cout << "Error approving booking: " << mysql_error(&mysql) << std::endl;
//        return false;
//    }
//
//    std::cout << "Booking with ID " << bookingID << " approved successfully." << std::endl;
//    return true;
//}
//废弃
/**编辑时间:24-6-26 下午12:40
*创建人：吴培浩
*/
// 实现检查冲突的函数
bool Admin::CheckConflict(int roomID, const std::string& bookingDate) {
    // 1. 构造查询语句
    std::string query = "SELECT COUNT(*) FROM BookingRecord "
                        "WHERE RoomID = " + std::to_string(roomID) +
                        " AND BookingDate = '" + bookingDate + "'"
                                                               " AND IsApproved = true";

    // 2. 执行查询
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error checking conflict: " << mysql_error(&mysql) << std::endl;
        return true;
    }

    // 3. 获取结果集
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return true;
    }

    // 4. 获取行数据
    MYSQL_ROW row = mysql_fetch_row(result);
    int conflictCount = std::stoi(row[0]);

    // 5. 释放结果集
    mysql_free_result(result);

    // 6. 返回是否有冲突
    return conflictCount > 0;
}

// 获取预订详细信息的辅助函数
bool Admin::GetBookingDetails(int bookingID, int &roomID, std::string &bookingDate) {
    std::string query = "SELECT RoomID, BookingDate FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);

    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error querying booking details: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error storing result: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (!row) {
        std::cout << "No booking found with ID " << bookingID << std::endl;
        mysql_free_result(result);
        return false;
    }

    roomID = std::stoi(row[0]);
    bookingDate = row[1];

    mysql_free_result(result);
    return true;
}

// 实现取消预定的函数
bool Admin::CancelBooking(int bookingID) {
    std::string query = "DELETE FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);

    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error cancelling booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    std::cout << "Booking with ID " << bookingID << " cancelled successfully." << std::endl;
    return true;
}
// 审批预定请求的函数，接受一个预定的唯一标识 bookingID 作为参数
bool Admin::ApproveBooking(int bookingID) {

    // 1. 查询当前预订的房间和日期
    // 构造 SQL 查询语句，查询给定 bookingID 对应的 RoomID 和 BookingDate
    std::string query = "SELECT RoomID, BookingDate FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);

    // 2. 执行查询
    // 使用 mysql_query 执行 SQL 查询
    if (mysql_query(&mysql, query.c_str())) {
        // 如果查询失败，输出错误信息并返回 false
        std::cout << "Error querying booking record: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 3. 获取结果集
    // mysql_store_result 用于获取查询的结果集
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        // 如果获取结果集失败，输出错误信息并返回 false
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 4. 检查是否有结果
    // 使用 mysql_num_rows 检查结果集中是否有记录
    if (mysql_num_rows(result) == 0) {
        // 如果结果集为空，说明没有找到对应的预订，输出信息并释放结果集，然后返回 false
        std::cout << "No booking found with ID " << bookingID << std::endl;
        mysql_free_result(result);
        return false;
    }

    // 5. 获取 RoomID 和 BookingDate
    // 使用 mysql_fetch_row 从结果集中获取一行数据
    MYSQL_ROW row = mysql_fetch_row(result);
    int roomID = std::stoi(row[0]); // 将第一列（RoomID）转换为整数
    std::string bookingDate = row[1]; // 获取第二列（BookingDate）的字符串

    // 6. 释放结果集
    // 释放查询结果集的内存
    mysql_free_result(result);

    // 7. 检查是否存在时间和教室冲突
    // 调用 CheckConflict 函数检查预订是否与现有的安排冲突
    if (CheckConflict(roomID, bookingDate)) {
        // 如果有冲突，输出冲突信息并返回 false
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        return false;
    }

    // 8. 构造更新语句，批准预订
    // 更新 BookingRecord 表，设置 IsApproved 为 true 表示批准预订
    query = "UPDATE BookingRecord SET IsApproved = true WHERE BookingID = " + std::to_string(bookingID);

    // 9. 执行更新
    // 使用 mysql_query 执行 SQL 更新语句
    if (mysql_query(&mysql, query.c_str())) {
        // 如果更新失败，输出错误信息并返回 false
        std::cout << "Error approving booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 10. 输出成功信息并返回 true
    // 如果更新成功，输出成功信息并返回 true
    std::cout << "Booking with ID " << bookingID << " approved successfully." << std::endl;
    return true;
}
bool Teacher::ModifyBooking(int bookingID, int roomID, const std::string& bookingDate) {
    if (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cerr << "日期格式无效或超出范围，请输入正确的日期 (YYYY-MM-DD)." << std::endl;
        return false;
    }
    // 检查是否存在时间和教室冲突
    if (CheckConflict(roomID, bookingDate)) {
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        return false;
    }

    // 构造更新语句
    std::string query = "UPDATE BookingRecord SET RoomID = " + std::to_string(roomID) +
                        ", BookingDate = '" + bookingDate + "' WHERE BookingID = " + std::to_string(bookingID);

    // 执行更新
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error modifying booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    std::cout << "Booking with ID " << bookingID << " modified successfully." << std::endl;
    return true;
}

// 取消预定的函数
bool Teacher::CancelBooking(int bookingID) {
    // 构造删除语句
    std::string query = "DELETE FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);
    // 执行删除
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error canceling booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }
    std::cout << "Booking with ID " << bookingID << " canceled successfully." << std::endl;
    return true;
}

int Teacher::getTeacherId() const {
    return TeacherID;
}

int Teacher::getTeacherNumber() const {
    return TeacherNumber;
}

const string &Teacher::getTeacherName() const {
    return TeacherName;
}

int Teacher::getPermissionLevel() const {
    return PermissionLevel;
}

const string &Teacher::getPhoneNumber() const {
    return PhoneNumber;
}

const string &Teacher::getOfficeName() const {
    return OfficeName;
}


void Teacher::getDateFromTeacher(std::string& bookingDate) {
    std::cout << "请输入预约日期 (格式: YYYY-MM-DD): ";
    std::cin >> bookingDate;

    while (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cout << "无效的日期格式或日期超出范围，请重新输入 (格式: YYYY-MM-DD): ";
        std::cin >> bookingDate;
    }
}
// 函数：检查日期是否有可用教室
bool Teacher::isDateAvailable(int roomID, const std::string& bookingDate) {
    // 初始化 MySQL 连接
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL 初始化失败！" << std::endl;
        return false;
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "数据库连接失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return false;
    }

    // 构造 SQL 查询语句
    std::string checkQuery = "SELECT * FROM bookingrecord WHERE RoomID = " + std::to_string(roomID) +
                             " AND BookingDate = '" + bookingDate + "'";

    // 执行查询
    if (mysql_query(mysql, checkQuery.c_str())) {
        std::cerr << "查询失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return false;
    }

    // 获取结果
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "获取结果失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return false;
    }

    // 检查结果行数
    int num_rows = mysql_num_rows(res);
    mysql_free_result(res); // 释放结果资源

    // 关闭连接
    mysql_close(mysql);

    return num_rows == 0; // 返回 true 表示没有冲突
}
void Teacher::Loginshow(){
    cout << "===============================================" << endl;
    cout << endl;
    cout << "欢迎使用教室预约系统！" <<getTeacherName()<< endl;
    cout << "===============================================" << endl;
    cout << "1.查询当前空余教室    2.查看您的预定   3.修改您的预定     4.退出系统" << endl;
}
// 函数：预订教室

bool Teacher::BookRoom(int roomID, const std::string& bookingDate) {
    if (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cerr << "日期格式无效或超出范围，请输入正确的日期 (YYYY-MM-DD)." << std::endl;
        return false;
    }

    if (!isDateAvailable(roomID, bookingDate)) {
        std::cerr << "该日期和教室已被预订，请选择其他日期或教室。" << std::endl;
        return false;
    }

    // 初始化 MySQL 连接
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL 初始化失败！" << std::endl;
        return false;
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "数据库连接失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return false;
    }

    // 构造 SQL 插入语句
    std::string query = "INSERT INTO bookingrecord (RoomID, TeacherID, BookingDate, IsApproved) VALUES (" +
                        std::to_string(roomID) + ", " + std::to_string(this->TeacherID) + ", '" + bookingDate + "', 0)";

    // 执行查询
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "数据库操作失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return false;
    }

    std::cout << "教室预约成功！" << std::endl;

    // 关闭连接
    mysql_close(mysql);

    return true;
}
void Teacher::OptionChoice(){
    int option;
    int BookingId,RoomId;
    int judge=1;
    string newtime;
    do {
        Loginshow();
        cout<<"输入操作"<<endl;
        cin>>option;

        switch (option) {
            case 1:
                ViewAvailableRooms();
                //插入是否预定//否的话退出函数；
                break;
            case 2:
                //查看本人预定
                ViewBookings();
                cout<<"是否需要新建本人预定？"<<endl;
                cout<<"请输入1或0代表是和否"<<endl;
                cin>>judge;
                if(judge==1){
                    cout<<"请输入教室号和预约时间(格式YYYY-MM-DD)"<<endl;
                    cin>>RoomId;
                    cin>>newtime;
                    BookRoom(RoomId,newtime);
                }else
                {
                    cout<<"结束操作"<<endl;
                }

                break;
            case 3:
                //修改本人预定
                ViewBookings();
                cout<<"需要修改哪一条预定?"<<endl;
                cout<<"输入预定编号，预期教室编号和预定时间"<<endl;
                cin>>BookingId;
                cin>>RoomId;
                cin>>newtime;
                ModifyBooking(BookingId,RoomId, newtime);
                break;
            case 4:
                cout << "欢迎下次使用！" << endl;
                break;
            default:
                cout << "无效的选项，请输入有效的操作选项（1-4）。" << endl;
                break;
        }
    } while (option != 4);


}