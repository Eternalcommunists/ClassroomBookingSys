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
#include "Teacher.h"

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
//登录界面
void show1()
{
    cout << "===============================================" << endl;
    cout << endl;
    cout << "欢迎使用教室预约系统！" << endl;
    cout << "===============================================" << endl;
    cout << "1.登陆    2.管理员登陆   3.普通老师注册     4.退出系统" << endl;
}

void show() {
    show1();
    int i;
    cout << "输入操作：" << endl;
    cin >> i;
    Admin admin;
    NormalTeacher teacher;
    while (i != 4) {
        switch (i) {
            case 1:
                teacher.teacher_enter();
                teacher.Loginshow();
                teacher.OptionChoice();
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

// 定义主函数
int main(){

    show();
    return 0;

}