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
    void teacher_register();
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


};
// display函数的实现
void NormalTeacher::display() const {
    cout << "Teacher Number: " << TeacherNumber << endl;
    cout << "Teacher Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}

std::string getInput() {
    std::string input;
    cin>>input;
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
int numbergetInput() {
    std::string input;
    int value;
    cout<<endl;
    std::cout << "请输入一个整数: ";
    cin>>input;

    // 检查输入是否为空
    if (input.empty()) {
        std::cout << "未输入任何内容，请重新输入。\n";
        return -1;
    }

    std::stringstream ss(input);
    if (!(ss >> value)) {
        std::cout << "输入无效，请输入一个整数。\n";
        return -1;
    }

    return value;
}

/**编辑时间:24-6-27 下午3:21
*创建人：吴培浩
*/
// 注册教师函数的实现
void Teacher::teacher_register() {
    // 获取用户输入的详细信息
    std::cout << "Enter Teacher Number: ";
    setTeacherNumber(numbergetInput());

    std::cout << "Enter Teacher Name: ";
    setTeacherName(getInput());

    std::cout << "Enter Permission Level (e.g., 1 for Normal Teacher): ";
    setPermissionLevel (numbergetInput());

    std::cout << "Enter Phone Number: ";
    setPhoneNumber(getInput());

    std::cout << "Enter Office Name: ";
    setOfficeName( getInput());

    std::cout << "Enter Password: ";
    setpassword(getInput());
    // 连接数据库
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cout << "Error connecting to database: " << mysql_error(&mysql) << std::endl;
      return;
    }

    // 构造插入 SQL 语句
    std::string query = "INSERT INTO Teacher (TeacherNumber, TeacherName, PermissionLevel, PhoneNumber, OfficeName, Password) VALUES ("
                        + std::to_string(getTeacherNumber()) + ", '"
                        + getTeacherName() + "', "
                        + std::to_string(getPermissionLevel()) + ", '"
                        + getPhoneNumber() + "', '"
                        + getOfficeName() + "', '"
                        + getPassword() + "')";

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

    void OptionChoice();

    bool admin_login();

    bool CheckLogin_forAdmin(int teacherNumber, const string &password);

    void CheckAllBookings();
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

    bool siginal =admin_login();
    if(siginal==true)
    {
        cout<<"登陆成功~~~~~~~~~~~~~~"<<endl;
        OptionChoice();
    }else{
        cout<<"登陆失败，再试试吧！"<<endl;
    }
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
    // SQL 查询语句，使用 ? 占位符代替实际参数AND PermissionLevel=2
    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=? ";

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

bool Admin::admin_login() {
    string str;
    int cnt = 0;
    int max_attempts = 3; // 最大尝试次数
    int user_num = 3; // 用户名和密码的配对数目，这个需要根据具体的用户列表进行调整

    while (cnt < max_attempts) {
        cout << "请输入管理员工号：";
        cin >> TeacherNumber;
        cout << "请输入密码：";
        str = getPassword(); // 获取密码
        setpassword(str); // 设置密码，通常用于隐藏或加密处理

        bool identifier = CheckLogin_forAdmin(TeacherNumber, str); // 检查管理员登录

        if (identifier) {
            cout << "*******" << endl;
            cout << "管理员登录成功！" << endl;
            cout << "*******" << endl;
            // 可以在这里添加管理员操作的功能调用或界面跳转
             // 示例中调用管理员操作函数
            return true;
        } else {
            cnt++;
            cout << "用户名或密码错误，请重新输入。";
            cout << "你还有 " << max_attempts - cnt << " 次机会" << endl;
        }
    }

    if (cnt == max_attempts) {
        cout << "错误次数已达上限，系统关闭！" << endl;
        return false;
    }

    return false;
}

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
/**编辑时间:24-6-27 下午6:15
*创建人：吴培浩
*/
//Admin::ViewAllBookings()完成对于预定教师清单的查看
//
void Admin::ViewAllBookings() {
    // 初始化 MySQL 对象
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }
    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return;
    }
    // 构造查询语句
    std::string query = "SELECT * FROM BookingRecord";

    // 执行查询
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Error querying bookings: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
        return;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result) {
        std::cerr << "Error retrieving result: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // 关闭连接，防止资源泄露
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
            std::cout << (row[i] ? row[i] : "NULL") << '\t'; // 处理空值
        }
        std::cout << std::endl;
    }

    // 释放结果集
    mysql_free_result(result);

    // 关闭数据库连接
    mysql_close(mysql);
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
    // 初始化 MySQL 对象
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL 初始化失败！" << std::endl;
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "数据库连接失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 构造查询语句
    const char* query = "SELECT COUNT(*) FROM BookingRecord WHERE RoomID = ? AND BookingDate = ? AND IsApproved = true";
    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        std::cerr << "Statement 初始化失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 准备查询
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Statement 准备失败: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 绑定参数
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char*)&roomID;
    bind[0].is_null = 0;
    bind[0].length = nullptr;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)bookingDate.c_str();
    bind[1].buffer_length = bookingDate.length();
    bind[1].is_null = 0;
    bind[1].length = nullptr;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "参数绑定失败: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 执行查询
    if (mysql_stmt_execute(stmt)) {
        std::cerr << "查询执行失败: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 绑定结果
    int conflictCount;
    MYSQL_BIND resultBind[1];
    memset(resultBind, 0, sizeof(resultBind));

    resultBind[0].buffer_type = MYSQL_TYPE_LONG;
    resultBind[0].buffer = (char*)&conflictCount;
    resultBind[0].is_null = 0;
    resultBind[0].length = nullptr;

    if (mysql_stmt_bind_result(stmt, resultBind)) {
        std::cerr << "结果绑定失败: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 获取结果
    if (mysql_stmt_fetch(stmt)) {
        std::cerr << "结果获取失败: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // 返回冲突，实际应根据需求处理错误情况
    }

    // 释放资源
    mysql_stmt_close(stmt);
    mysql_close(mysql);

    // 判断是否存在冲突
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

/**编辑时间:24-6-27 下午5:50
*创建人：吴培浩
*/
bool Admin::ApproveBooking(int bookingID) {
    // 初始化 MySQL 对象
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL 初始化失败！" << std::endl;
        return false;
    }

    // 连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "数据库连接失败: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    // 准备查询 RoomID 和 BookingDate 的预处理语句
    const char* query_select = "SELECT RoomID, BookingDate FROM BookingRecord WHERE BookingID = ?";
    MYSQL_STMT* stmt_select = mysql_stmt_init(mysql);
    if (!stmt_select) {
        std::cerr << "Statement initialization failed: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    if (mysql_stmt_prepare(stmt_select, query_select, strlen(query_select))) {
        std::cerr << "Statement preparation failed: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 绑定参数
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &bookingID;
    if (mysql_stmt_bind_param(stmt_select, bind)) {
        std::cerr << "Parameter binding failed: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt_select)) {
        std::cerr << "Statement execution failed: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 绑定结果
    int roomID;
    char bookingDate[11]; // 假设日期格式为 YYYY-MM-DD
    MYSQL_BIND result_bind[2];
    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &roomID;
    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = bookingDate;
    result_bind[1].buffer_length = sizeof(bookingDate);

    if (mysql_stmt_bind_result(stmt_select, result_bind)) {
        std::cerr << "Result binding failed: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 存储结果
    if (mysql_stmt_store_result(stmt_select)) {
        std::cerr << "Failed to store result: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 检查是否有结果
    if (mysql_stmt_num_rows(stmt_select) == 0) {
        std::cerr << "No booking found with ID " << bookingID << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 获取结果
    if (mysql_stmt_fetch(stmt_select)) {
        std::cerr << "Failed to fetch result: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // 释放查询语句
    mysql_stmt_close(stmt_select);

    // 检查是否存在时间和教室冲突
    if (CheckConflict(roomID, bookingDate)) {
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        mysql_close(mysql);
        return false;
    }

    // 准备更新语句，批准预订
    const char* query_update = "UPDATE BookingRecord SET IsApproved = true WHERE BookingID = ?";
    MYSQL_STMT* stmt_update = mysql_stmt_init(mysql);
    if (!stmt_update) {
        std::cerr << "Statement initialization failed: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    if (mysql_stmt_prepare(stmt_update, query_update, strlen(query_update))) {
        std::cerr << "Statement preparation failed: " << mysql_stmt_error(stmt_update) << std::endl;
        mysql_stmt_close(stmt_update);
        mysql_close(mysql);
        return false;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &bookingID;
    if (mysql_stmt_bind_param(stmt_update, bind)) {
        std::cerr << "Parameter binding failed: " << mysql_stmt_error(stmt_update) << std::endl;
        mysql_stmt_close(stmt_update);
        mysql_close(mysql);
        return false;
    }

    // 执行更新
    if (mysql_stmt_execute(stmt_update)) {
        std::cerr << "Error approving booking: " << mysql_stmt_error(stmt_update) << std::endl;
        mysql_stmt_close(stmt_update);
        mysql_close(mysql);
        return false;
    }

    // 关闭更新语句和数据库连接
    mysql_stmt_close(stmt_update);
    mysql_close(mysql);

    // 输出成功信息
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
void Admin::OptionChoice(){

    int option;
    int BookingId, RoomId;
    int judge = 1;
    bool Isapproved=false;
    string newtime,reason;
    do {
        //Loginshow();
        cout << "请输入操作选项：" << endl;
        cout << "1. 查询空余教室" << endl;
        cout << "2. 增加注册教师" << endl;
        cout << "3. 查看预定教室" << endl;
        cout << "4. 审批预定教室" << endl;
        cout << "5. 取消预定教室并给出理由" << endl;
        cout << "6. 退出" << endl;
        cin >> option;

        switch (option) {
            case 1:
                ViewAvailableRooms();
                // 插入是否预定，否的话退出函数；
                break;
            case 2:
                teacher_register(); // 增加注册教师
                break;
            case 3:
                ViewAllBookings(); // 查看预定教室
                break;
            case 4:
                cout<<"输入审批教室编号"<<endl;
                cin>>RoomId;
                Isapproved=ApproveBooking(RoomId); // 审批预定教室
                if(Isapproved==true)
                {
                    cout<<"完成审批！"<<endl;
                }
                break;
            case 5:
                cout << "请输入要取消预定的预定编号、房间号和取消理由：" << endl;
                cin >> BookingId;
                cin.ignore(); // 忽略换行符
                cin>>RoomId;
                getline(cin, reason); // 输入取消理由
                CancelBooking(BookingId); // 取消预定教室并给出理由
                break;
            case 6:
                cout << "欢迎下次使用！" << endl;
                break;
            default:
                cout << "无效的选项，请输入有效的操作选项（1-6）。\n";
                break;
        }
    } while (option != 6);
}
/**编辑时间:24-6-27 下午6:11
*创建人：吴培浩
 *
完成了Admin::CheckLogin_forAdmin函数的修正，可以正常识别和开展管理员的行为了
 */
bool Admin::CheckLogin_forAdmin(int teacherNumber, const std::string& password) {
    // 初始化 MySQL 连接句柄
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "Failed to initialize MySQL connection." << std::endl;
        return false;
    }

    // 尝试连接到 MySQL 数据库
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        // 如果连接失败，打印错误信息并关闭 MySQL 连接
        std::cerr << "Connection error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    // 创建预处理语句句柄
    MYSQL_STMT *stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        std::cerr << "Failed to initialize MySQL statement." << std::endl;
        mysql_close(mysql);
        return false;
    }

    // SQL 查询语句，使用 ? 占位符代替实际参数
    const char *query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=? AND PermissionLevel=2";

    // 准备 SQL 语句
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        // 如果准备失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cerr << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 定义绑定参数数组，两个参数：TeacherNumber 和 Password
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));  // 初始化绑定参数数组

    // 绑定 TeacherNumber 参数
    bind[0].buffer_type = MYSQL_TYPE_LONG;  // 参数类型为整数
    bind[0].buffer = (char *) &teacherNumber; // 指向 TeacherNumber 的指针
    bind[0].is_null = 0;                    // 不为空

    // 存储密码的缓冲区
    char passwordBuffer[100]; // 假设密码最长不超过 100 字符
    strncpy(passwordBuffer, password.c_str(), sizeof(passwordBuffer));
    bind[1].buffer_type = MYSQL_TYPE_STRING;     // 参数类型为字符串
    bind[1].buffer = passwordBuffer;             // 指向密码缓冲区
    bind[1].buffer_length = strlen(passwordBuffer); // 设置字符串长度
    bind[1].is_null = 0;                         // 不为空

    // 绑定参数到预处理语句
    if (mysql_stmt_bind_param(stmt, bind)) {
        // 如果绑定失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cerr << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt)) {
        // 如果执行失败，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cerr << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 获取查询结果集
    MYSQL_RES *result_metadata = mysql_stmt_result_metadata(stmt);
    if (!result_metadata) {
        // 如果无法获取结果集元数据，打印错误信息并关闭语句句柄和 MySQL 连接
        std::cerr << "Failed to retrieve result set meta information." << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 获取列信息
    unsigned int column_count = mysql_num_fields(result_metadata);
    MYSQL_BIND result_bind[column_count];
    memset(result_bind, 0, sizeof(result_bind));

    // 用于存储结果的缓冲区
    char data[column_count][100]; // 假设每列最多 100 字符
    unsigned long data_length[column_count];

    // 绑定结果缓冲区
    for (unsigned int i = 0; i < column_count; ++i) {
        result_bind[i].buffer_type = MYSQL_TYPE_STRING;
        result_bind[i].buffer = data[i];
        result_bind[i].buffer_length = sizeof(data[i]);
        result_bind[i].length = &data_length[i];
    }

    // 绑定结果到语句
    if (mysql_stmt_bind_result(stmt, result_bind)) {
        std::cerr << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 存储结果集
    if (mysql_stmt_store_result(stmt)) {
        std::cerr << "Result storing error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // 检查查询结果
    bool loggedIn = false;
    if (mysql_stmt_fetch(stmt) == 0) { // 0 表示成功获取到一行
        loggedIn = true;
        std::cout << "Login successful. Retrieved data:" << std::endl;
        for (unsigned int i = 0; i < column_count; ++i) {
            std::cout << "Column " << i << ": " << data[i] << ", Length: " << data_length[i] << std::endl;
        }
    } else {
        std::cout << "Login failed. No matching records found." << std::endl;
    }

    // 释放结果集元数据
    mysql_free_result(result_metadata);

    // 关闭语句句柄
    mysql_stmt_close(stmt);
    // 关闭 MySQL 连接
    mysql_close(mysql);

    return loggedIn;
}

/**编辑时间:24-6-27 下午5:33
*创建人：吴培浩
*/
void Admin::CheckAllBookings() {
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

    // SQL 查询语句：查找所有教师的预定记录
    std::string query = "SELECT b.BookingID, b.SubmissionTime, c.RoomNumber, c.RoomName, b.BookingDate, b.IsApproved, t.TeacherName "
                        "FROM BookingRecord b "
                        "JOIN Classroom c ON b.RoomID = c.RoomID "
                        "JOIN Teacher t ON b.TeacherID = t.TeacherID";

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
                  << ", Approved: " << (std::stoi(row[5]) ? "Yes" : "No")
                  << ", Teacher Name: " << row[6] << std::endl;
    }

    // 释放结果集并关闭数据库连接
    mysql_free_result(res);
    mysql_close(mysql);
}
