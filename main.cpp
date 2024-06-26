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



// operator>>����������ʵ��
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





// ��ȡ�û�����ĸ�������
//std::string getInput(const std::string& prompt) {
//    std::string input;
//    std::cout << prompt;
//    std::getline(std::cin, input);
//    return input;
//}
//
//// ��ȡ����ĸ�������
//std::string getPassword() {
//    std::string password;
//    std::cout << "Enter password: ";
//    char ch;
//    while ((ch = _getch()) != '\r') { // ʹ�� _getch() �޻�������
//        if (ch == '\b') { // �����˸�
//            if (!password.empty()) {
//                password.pop_back();
//                std::cout << "\b \b"; // ���ǰ��һλ��ɾ����ʾ���Ǻ�
//            }
//        } else {
//            password += ch;
//            std::cout << '*'; // ��ʾ�Ǻ�
//        }
//    }
//    std::cout << std::endl;
//    return password;
//}



//// �������Ԥ����¼��


//��¼����
void show() {
    cout << "===============================================" << endl;
    cout << endl;
    cout << "��ӭʹ�ý���ԤԼϵͳ��" << endl;
    cout << "===============================================" << endl;
    cout << "1.��½    2.����Ա��½   3.��ͨ��ʦע��     4.�˳�ϵͳ" << endl;
    int i;
    cout << "���������" << endl;
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
//����
/**�༭ʱ��:24-6-26 ����12:49
*�����ˣ������
*/
//std::string getPassword() { //����������� ʱ�䣺2024.6.26 00��51��
//    char* password = pass(); // ���� pass() ������ȡ����
//    std::string passwordStr(password); // �� char* ת��Ϊ std::string
//    delete[] password; // �ͷŶ�̬������ڴ�
//
//    // ȥ��ĩβ�Ļ��з�
//    if (!passwordStr.empty() && passwordStr.back() == '\n') {
//        passwordStr.pop_back();
//    }
//
//    return passwordStr;
//}
//sql���  ��������ѯ

// ����: ����¼
// ����:
// - teacherNumber: ��ʦ���
// - password: ��ʦ����
// ����:
// - �����¼�ɹ����� true�����򷵻� false
//
/**�༭ʱ��:24-6-26 ����1:23
*�����ˣ������
*/
//bool CheckLogin(int teacherNumber, const std::string& password) {
//    // ��ʼ�� MySQL ���Ӿ��
//    MYSQL* mysql = mysql_init(NULL);
//
//    // �������ӵ� MySQL ���ݿ�
//    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
//        // �������ʧ�ܣ���ӡ������Ϣ������ false
//        std::cout << "Connection error: " << mysql_error(mysql) << std::endl;
//        return false;
//    }
//
//    // ����Ԥ���������
//    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
//    // SQL ��ѯ��䣬ʹ�� ? ռλ������ʵ�ʲ���
//    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=?";
//
//    // ׼�� SQL ���
//    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
//        // ���׼��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
//        std::cout << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // ����󶨲������飬����������TeacherNumber �� Password
//    MYSQL_BIND bind[2];
//    memset(bind, 0, sizeof(bind));  // ��ʼ���󶨲�������
//
//    // �� TeacherNumber ����
//    bind[0].buffer_type = MYSQL_TYPE_LONG;  // ��������Ϊ����
//    bind[0].buffer = (char*)&teacherNumber; // ָ�� TeacherNumber ��ָ��
//    bind[0].is_null = 0;                    // ��Ϊ��
//    bind[0].length = 0;                     // ��������Ϊ 0
//
//    // �� Password ����
//    bind[1].buffer_type = MYSQL_TYPE_STRING;     // ��������Ϊ�ַ���
//    bind[1].buffer = (char*)password.c_str();    // ָ�������ַ���
//    bind[1].buffer_length = password.length();   // �����ַ�������
//    bind[1].is_null = 0;                         // ��Ϊ��
//    bind[1].length = 0;                          // ��������Ϊ 0
//
//    // �󶨲�����Ԥ�������
//    if (mysql_stmt_bind_param(stmt, bind)) {
//        // �����ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
//        std::cout << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // ִ��Ԥ�������
//    if (mysql_stmt_execute(stmt)) {
//        // ���ִ��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
//        std::cout << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // ��ȡ��ѯ�����Ԫ���ݣ���������Ľṹ��
//    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
//    int num_fields = mysql_num_fields(res);  // ��ȡ����е��ֶ���
//    // ����󶨽�����飬��ʼ��Ϊ 0
//    MYSQL_BIND result_bind[num_fields];
//    memset(result_bind, 0, sizeof(result_bind));
//
//    // ����һ���ַ������������ڴ洢��ѯ���
//    char buffer[256];
//    for (int i = 0; i < num_fields; ++i) {
//        // ����ÿ���ֶεĻ�������Ϣ
//        result_bind[i].buffer_type = MYSQL_TYPE_STRING;  // �ֶ�����Ϊ�ַ���
//        result_bind[i].buffer = buffer;                  // ָ�򻺳���
//        result_bind[i].buffer_length = sizeof(buffer);   // ��������С
//        result_bind[i].is_null = 0;                      // ��Ϊ��
//        result_bind[i].length = 0;                       // ��������Ϊ 0
//    }
//
//    // �󶨽����������Ԥ�������
//    if (mysql_stmt_bind_result(stmt, result_bind)) {
//        // �����ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
//        std::cout << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
//        mysql_stmt_close(stmt);
//        mysql_close(mysql);
//        return false;
//    }
//
//    // ����ѯ����洢�ڷ�������
//    mysql_stmt_store_result(stmt);
//    // ����Ƿ��в�ѯ������Ƿ���ƥ��ļ�¼��
//    bool login_successful = (mysql_stmt_num_rows(stmt) > 0);
//
//    // �ͷŽ����
//    mysql_free_result(res);
//    // �ر�Ԥ�������
//    mysql_stmt_close(stmt);
//    // �ر� MySQL ����
//    mysql_close(mysql);
//
//    return login_successful;  // ���ص�¼�Ƿ�ɹ�
//}
//

// �鿴�Լ���Ԥ����¼

// ���ʱ��ͽ��ҳ�ͻ
//bool CheckConflict(int roomID, const std::string& bookingDate) {
//    // �������ݿ⣨ʡ�ԣ�
//    // �����ѯ���
//    std::string query = "SELECT * FROM BookingRecord WHERE RoomID = " + std::to_string(roomID) +
//                        " AND BookingDate = '" + bookingDate + "'";
//    // ִ�в�ѯ
//    if (mysql_query(&mysql, query.c_str())) {
//        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
//        return true; // ��ѯ����Ĭ�Ϸ��س�ͻ��ʵ��Ӧ����������������
//    }
//    // ��ȡ�����
//    MYSQL_RES *result = mysql_store_result(&mysql);
//    if (!result) {
//        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
//        return true; // ��ȡ�����ʧ��Ĭ�Ϸ��س�ͻ��ʵ��Ӧ����������������
//    }
//    // ����м�¼����ʾ��ͻ
//    bool conflict = (mysql_num_rows(result) > 0);
//    // �ͷŽ����
//    mysql_free_result(result);
//    // �ر����ݿ����ӣ�ʡ�ԣ�
//    return conflict;
//}
//// �޸�Ԥ���Ľ��Һ�ʱ��

// ����������
int main(){

    show();
    return 0;
//    NormalTeacher teacher;
//    teacher.teacher_register();
    return 0;
}