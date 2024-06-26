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

void textMysql(string sql);//���Է���
bool ConnectMysql();//�������ݿ�
bool QueryDatabase(string sql);//��ѯ��������
void outMysql();//�����ѯ���
bool updateData(string sql);//����ɾ���޸Ĳ���
void FreeConnect();//�ͷ���Դ

//---------------�ⲿ�ַ�Դ�ļ�------------------------

//MYSQL mysql;
//MYSQL_RES *res;//����ṹ�������е�һ����ѯ�����
//MYSQL_ROW column;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ
//���Դ���
void textMysql(string sql) {
    ConnectMysql();
    QueryDatabase(sql);
    FreeConnect();
}
//�������ݿ�
bool ConnectMysql() {
    mysql_init(&mysql);//��ʼ��mysql
    if (!(mysql_real_connect(&mysql,
                             "localhost",//���� �����Զ�̾͸ĳɷ�������ip��ַ
                             "root",//�û���
                             "admin",//����
                             "school",//���ݿ��� �������Ѿ����ڵ� �ҵ�mysql��Сд������
                             3306,//�˿ں� Ĭ�ϵ�0����3306
                             NULL, 0//������������ĳ���д�� ��������������
    ))) {
        cout << "Error connecting to database:" + (string) mysql_error(&mysql) << endl;
        return false;
    } else {
        cout << "Connected..." << endl;
        return true;
    }
}

//���е����ݿ����������д��sql���
//Ȼ����mysql_query(&mysql,query)�����
//�����������ݿ��� ��ɾ�Ĳ�
bool updateData(string sql){
    mysql_query(&mysql, "set names utf8");//���ñ����ʽ ����mysql����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "Update failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "Update success..." << endl;
        return true;
    }
}
//��ѯ�����
bool QueryDatabase(string sql) {
    mysql_query(&mysql, "set names gbk");//���ñ����ʽ ����cmd����������
    // ִ��SQL���
    // 0 ִ�гɹ�
    // 1 ִ��ʧ��
    if (mysql_query(&mysql, sql.c_str())) {//mysql_query�ڶ�������ֻ����const cahr* ��Ҫ��string����ת��
        cout << "Query failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    } else {
        cout << "query success" << endl;
    }

    //��ý���� MYSQL_RES *res;
    if (!(res = mysql_store_result(&mysql))) {
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    outMysql();//��ӡ���
    return true;
}
//������
void outMysql() {
    //��ӡ��������
    cout << "number of dataline returned: " << mysql_affected_rows(&mysql) << endl;

    char *field[32];//�ֶ���

    int num = mysql_num_fields(res);//��ȡ����
    for (int i = 0; i < num; ++i) {//��ȡ�ֶ���
        field[i] = mysql_fetch_field(res)->name;
    }

    for (int i = 0; i < num; ++i) {
        cout << (string) field[i] << "    ";
    }
    cout << endl;

    while (column = mysql_fetch_row(res)) {//��ȡһ������
        for (int i = 0; i < num; ++i) {
            cout << column[i] << "    ";
        }
        cout << endl;
    }
}

//�ͷ���Դ
void FreeConnect() {
    mysql_free_result(res);
    mysql_close(&mysql);
}
//��¼����
void show1()
{
    cout << "===============================================" << endl;
    cout << endl;
    cout << "��ӭʹ�ý���ԤԼϵͳ��" << endl;
    cout << "===============================================" << endl;
    cout << "1.��½    2.����Ա��½   3.��ͨ��ʦע��     4.�˳�ϵͳ" << endl;
}

void show() {
    show1();
    int i;
    cout << "���������" << endl;
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
                cout << "����Ĳ���ָ�" << endl;
                break;
        }
        cout<< "===============================================" << endl;
        cout << "1.��½    2.����Ա��½   3.��ͨ��ʦע��     4.�˳�ϵͳ" << endl;
        cout << "���������" << endl;
        cin >> i;
    }
    cout << "��ӭ�´�ʹ�ã�" << endl;
}
//�û���¼���� ���ӹ��ܣ����������ʾ����������//�˴��ѱ�����Ϊ����ָ����� ����������� ʱ�䣺2024.6.26 00��51��
char* pass() {
    // ��̬�����ڴ棬ȷ���ں�������Ȼ��Ч
    char* password = new char[64];
    char ch;
    int i = 0;
    while (true) {
        ch = _getch(); // �޻�������
        if (ch == '\r') { // Enter ����ʾ�������
            password[i] = '\0';
            break;
        }
        password[i++] = ch;
        putchar('*'); // ��ʾ * ���������ַ�
    }
    return password;
}

// ����������
int main(){

    show();
    return 0;

}