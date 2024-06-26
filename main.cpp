#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <filesystem> //
#include <mysql.h>
#include <bits/stdc++.h>
#include <conio.h>
#include <wingdi.h>
#include <format>
using namespace std;
#include"Room.h"
void textMysql(string sql);//测试方法
bool ConnectMysql();//连接数据库
bool QueryDatabase(string sql);//查询并输出结果
void outMysql();//输出查询结果
bool updateData(string sql);//插入删除修改操作
void FreeConnect();//释放资源

//---------------这部分放源文件------------------------

//MYSQL mysql;
//MYSQL_RES *res;//这个结构代表返回行的一个查询结果集
//MYSQL_ROW column;//一个行数据的类型安全(type-safe)的表示
//测试代码
void textMysql(string sql) {
    ConnectMysql();
    QueryDatabase(sql);
    FreeConnect();
}
//连接数据库
bool ConnectMysql() {
    mysql_init(&mysql);//初始化mysql
    if (!(mysql_real_connect(&mysql,
                             "localhost",//主机 如果是远程就改成服务器的ip地址
                             "root",//用户名
                             "admin",//密码
                             "school",//数据库名 必须是已经存在的 我的mysql大小写不敏感
                             3306,//端口号 默认的0或者3306
                             NULL, 0//最后两个参数的常用写法 几乎都是这两个
    ))) {
        cout << "Error connecting to database:" + (string) mysql_error(&mysql) << endl;
        return false;
    } else {
        cout << "Connected..." << endl;
        return true;
    }
}

//所有的数据库操作都是先写个sql语句
//然后用mysql_query(&mysql,query)来完成
//包括创建数据库或表 增删改查
bool updateData(string sql){
    mysql_query(&mysql, "set names utf8");//设置编码格式 否则mysql里中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const cahr* 需要将string类型转化
        cout << "Update failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "Update success..." << endl;
        return true;
    }
}

//查询并输出
bool QueryDatabase(string sql) {
    mysql_query(&mysql, "set names gbk");//设置编码格式 否则cmd下中文乱码
    // 执行SQL语句
    // 0 执行成功
    // 1 执行失败
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query第二个参数只接受const cahr* 需要将string类型转化
        cout << "Query failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "query success" << endl;
    }

    //获得结果集 MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    outMysql();//打印结果
    return true;
}

//输出结果
void outMysql() {
    //打印数据行数
    cout << "number of dataline returned: " << mysql_affected_rows(&mysql) << endl;

    char *field[32];//字段名

    int num = mysql_num_fields(res);//获取列数
    for (int i = 0; i < num; ++i) {//获取字段名
        field[i] = mysql_fetch_field(res)->name;
    }

    for (int i = 0; i < num; ++i) {
        cout << (string) field[i] << "    ";
    }
    cout << endl;

    while (column = mysql_fetch_row(res)) {//获取一行数据
        for (int i = 0; i < num; ++i) {
            cout << column[i] << "    ";
        }
        cout << endl;
    }
}

//释放资源
void FreeConnect() {
    mysql_free_result(res);
    mysql_close(&mysql);
}



// operator>>函数的主体实现
/*istream& operator>>(istream& is, RoomType& roomType) {
    cout << "Enter Room Type: ";
    is >> roomType.roomType;
    return is;
}*/
/*istream& operator>>(istream& is, Room& room) {
    cout << "Enter Room number: ";
    int i;
    is >> room.roomNumber;
    cout<<"Enter Room name: ";
    is>>room.roomName;
    cout << "Enter Room Type: ";
    is >>room.roomType;
    cout << "Enter Room capacity: ";
    is >> room.capacity;
    cout << "Is the Room Occupied? (1 for Yes, 0 for No): ";
    is >> room.isOccupied;
    return is;
}*/





// 获取用户输入的辅助函数
//std::string getInput(const std::string& prompt) {
//    std::string input;
//    std::cout << prompt;
//    std::getline(std::cin, input);
//    return input;
//}
//
//// 获取密码的辅助函数
//std::string getPassword() {
//    std::string password;
//    std::cout << "Enter password: ";
//    char ch;
//    while ((ch = _getch()) != '\r') { // 使用 _getch() 无回显输入
//        if (ch == '\b') { // 处理退格
//            if (!password.empty()) {
//                password.pop_back();
//                std::cout << "\b \b"; // 光标前移一位并删除显示的星号
//            }
//        } else {
//            password += ch;
//            std::cout << '*'; // 显示星号
//        }
//    }
//    std::cout << std::endl;
//    return password;
//}



//// 定义教室预订记录类


//登录界面
void show() {
    cout << "===============================================" << endl;
    cout << endl;
    cout << "欢迎使用教室预约系统！" << endl;
    cout << "===============================================" << endl;
    cout << "1.登陆    2.管理员登陆   3.普通老师注册     4.退出系统" << endl;
    int i;
    cout << "输入操作：" << endl;
    cin >> i;
    Admin admin;
    NormalTeacher teacher;
    while (i != 4) {
        switch (i) {
            case 1:
                teacher.teacher_enter();
                teacher.ViewAvailableRooms();
                break;
            case 2:
                admin.admin_enter();
                break;
            case 3:
                //admin.admin_enter();
                teacher.teacher_register();
                break;
            default:
                cout << "错误的操作指令！" << endl;
                break;
        }
        cout<< "===============================================" << endl;
        cout << "1.登陆    2.管理员登陆   3.普通老师注册     4.退出系统" << endl;
        cout << "输入操作：" << endl;
        cin >> i;
    }
    cout << "欢迎下次使用！" << endl;
}
//用户登录界面 附加功能：密码错误提示及次数上限//此处已被修正为返回指针参数 修正：吴培浩 时间：2024.6.26 00点51分
char* pass() {
    // 动态分配内存，确保在函数外依然有效
    char* password = new char[64];
    char ch;
    int i = 0;
    while (true) {
        ch = _getch(); // 无回显输入
        if (ch == '\r') { // Enter 键表示输入结束
            password[i] = '\0';
            break;
        }
        password[i++] = ch;
        putchar('*'); // 显示 * 代替输入字符
    }
    return password;
}
//废弃
/**编辑时间:24-6-26 下午12:49
*创建人：吴培浩
*/
//std::string getPassword() { //修正：吴培浩 时间：2024.6.26 00点51分
//    char* password = pass(); // 调用 pass() 函数获取密码
//    std::string passwordStr(password); // 将 char* 转换为 std::string
//    delete[] password; // 释放动态分配的内存
//
//    // 去除末尾的换行符
//    if (!passwordStr.empty() && passwordStr.back() == '\n') {
//        passwordStr.pop_back();
//    }
//
//    return passwordStr;
//}
//sql语句  参数化查询

// 函数: 检查登录
// 参数:
// - teacherNumber: 教师编号
// - password: 教师密码
// 返回:
// - 如果登录成功返回 true，否则返回 false
//
/**编辑时间:24-6-26 上午1:23
*创建人：吴培浩
*/
//bool CheckLogin(int teacherNumber, const std::string& password) {
//    // 初始化 MySQL 连接句柄
//    MYSQL* mysql = mysql_init(NULL);
//
//    // 尝试连接到 MySQL 数据库
//    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
//        // 如果连接失败，打印错误信息并返回 false
//        std::cout << "Connection error: " << mysql_error(mysql) << std::endl;
//        return false;
//    }
//
//    // 创建预处理语句句柄
//    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
//    // SQL 查询语句，使用 ? 占位符代替实际参数
//    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=?";
//
//    // 准备 SQL 语句
//    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
//        // 如果准备失败，打印错误信息并关闭语句句柄和 MySQL 连接
//        std::cout << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // 定义绑定参数数组，两个参数：TeacherNumber 和 Password
//    MYSQL_BIND bind[2];
//    memset(bind, 0, sizeof(bind));  // 初始化绑定参数数组
//
//    // 绑定 TeacherNumber 参数
//    bind[0].buffer_type = MYSQL_TYPE_LONG;  // 参数类型为整数
//    bind[0].buffer = (char*)&teacherNumber; // 指向 TeacherNumber 的指针
//    bind[0].is_null = 0;                    // 不为空
//    bind[0].length = 0;                     // 长度设置为 0
//
//    // 绑定 Password 参数
//    bind[1].buffer_type = MYSQL_TYPE_STRING;     // 参数类型为字符串
//    bind[1].buffer = (char*)password.c_str();    // 指向密码字符串
//    bind[1].buffer_length = password.length();   // 设置字符串长度
//    bind[1].is_null = 0;                         // 不为空
//    bind[1].length = 0;                          // 长度设置为 0
//
//    // 绑定参数到预处理语句
//    if (mysql_stmt_bind_param(stmt, bind)) {
//        // 如果绑定失败，打印错误信息并关闭语句句柄和 MySQL 连接
//        std::cout << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // 执行预处理语句
//    if (mysql_stmt_execute(stmt)) {
//        // 如果执行失败，打印错误信息并关闭语句句柄和 MySQL 连接
//        std::cout << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // 获取查询结果的元数据（描述结果的结构）
//    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
//    int num_fields = mysql_num_fields(res);  // 获取结果中的字段数
//    // 定义绑定结果数组，初始化为 0
//    MYSQL_BIND result_bind[num_fields];
//    memset(result_bind, 0, sizeof(result_bind));
//
//    // 定义一个字符缓冲区，用于存储查询结果
//    char buffer[256];
//    for (int i = 0; i < num_fields; ++i) {
//        // 设置每个字段的缓冲区信息
//        result_bind[i].buffer_type = MYSQL_TYPE_STRING;  // 字段类型为字符串
//        result_bind[i].buffer = buffer;                  // 指向缓冲区
//        result_bind[i].buffer_length = sizeof(buffer);   // 缓冲区大小
//        result_bind[i].is_null = 0;                      // 不为空
//        result_bind[i].length = 0;                       // 长度设置为 0
//    }
//
//    // 绑定结果缓冲区到预处理语句
//    if (mysql_stmt_bind_result(stmt, result_bind)) {
//        // 如果绑定失败，打印错误信息并关闭语句句柄和 MySQL 连接
//        std::cout << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // 将查询结果存储在服务器上
//    mysql_stmt_store_result(stmt);
//    // 检查是否有查询结果（是否有匹配的记录）
//    bool login_successful = (mysql_stmt_num_rows(stmt) > 0);
//
//    // 释放结果集
//    mysql_free_result(res);
//    // 关闭预处理语句
//    mysql_stmt_close(stmt);
//    // 关闭 MySQL 连接
//    mysql_close(mysql);
//
//    return login_successful;  // 返回登录是否成功
//}
//

// 查看自己的预定记录

// 检查时间和教室冲突
//bool CheckConflict(int roomID, const std::string& bookingDate) {
//    // 连接数据库（省略）
//    // 构造查询语句
//    std::string query = "SELECT * FROM BookingRecord WHERE RoomID = " + std::to_string(roomID) +
//                        " AND BookingDate = '" + bookingDate + "'";
//    // 执行查询
//    if (mysql_query(&mysql, query.c_str())) {
//        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
//        return true; // 查询出错默认返回冲突，实际应根据需求处理错误情况
//    }
//    // 获取结果集
//    MYSQL_RES *result = mysql_store_result(&mysql);
//    if (!result) {
//        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
//        return true; // 获取结果集失败默认返回冲突，实际应根据需求处理错误情况
//    }
//    // 如果有记录，表示冲突
//    bool conflict = (mysql_num_rows(result) > 0);
//    // 释放结果集
//    mysql_free_result(result);
//    // 关闭数据库连接（省略）
//    return conflict;
//}
//// 修改预定的教室和时间

// 定义主函数
int main(){

    show();
    return 0;
//    NormalTeacher teacher;
//    teacher.teacher_register();
    return 0;
}