//
// Created by ����� on 24-6-26.
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
        // �����ж�
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (leap ? 29 : 28);
    }

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day <= daysInMonth[month - 1];
}

bool isDateInRange(const std::string& date) {
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    // ���磬�����ݷ�Χ�� 1900 �� 2100 ��֮��
    if (year < 1900 || year > 2100) return false;

    // ����·ݺ�����
    if (month < 1 || month > 12) return false;

    if (day < 1 || day > 31) return false; // ��ʾ����ʵ�ʼ��ʱӦ�����·ݺ��������

    return true;
}
bool isValidDate(const std::string& date) {
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    return isValidDay(year, month, day);
}

//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ
class Teacher {
protected:
    int TeacherID;
    int TeacherNumber; // ��ʦ����
    string TeacherName; // ��ʦ����
    int PermissionLevel; // Ȩ�޵ȼ�
    string PhoneNumber; // �绰����
    string OfficeName;
public:
    int getTeacherId() const;
    int getTeacherNumber() const;
    const string &getTeacherName() const;
    int getPermissionLevel() const;
    const string &getPhoneNumber() const;
    const string &getOfficeName() const;
    // �칫������
private:
    string Password;//����������� ʱ�䣺2024.6.26 00��54��
    // other attributes
public:
    // ���캯��������������getter��setter��
    virtual void display() const = 0; // ���麯����ǿ������ʵ��
//    virtual void saveToFile(ofstream& file) const = 0; // �麯��
//    virtual void loadFromFile(ifstream& file) = 0; // �麯��
    // ��������������ȷ�������������ȷ����
    virtual ~Teacher() = default;
    void setTeacherNumber(int number) { TeacherNumber = number; }
    void setTeacherName(const string& name) { TeacherName = name; }
    void setPermissionLevel(int level) { PermissionLevel = level; }
    void setPhoneNumber(const string& number) { PhoneNumber = number; }
    void setOfficeName(const string& name) { OfficeName = name; }
    void setpassword(const string&pass){Password=pass;}//����������� ʱ�䣺2024.6.26 00��54��
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
    // ���캯��������������getter��setter��
    void display() const override; // ���Ǹ���Ĵ��麯��
//    void saveToFile(ofstream& file) const override; // ���Ǹ�����麯��
//    void loadFromFile(ifstream& file) override; // ���Ǹ�����麯��
    // ��Ԫ��������
    friend ostream& operator<<(ostream& os, const NormalTeacher& teacher);
    friend istream& operator>>(istream& is, NormalTeacher& teacher);


};
// display������ʵ��
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
// ��ȡ����ĸ�������
std::string getPassword() {
    std::string password;
    std::cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != '\r') { // ʹ�� _getch() �޻�������
        if (ch == '\b') { // �����˸�
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // ���ǰ��һλ��ɾ����ʾ���Ǻ�
            }
        } else {
            password += ch;
            std::cout << '*'; // ��ʾ�Ǻ�
        }
    }
    std::cout << std::endl;
    return password;
}

// operator<<������ʵ��
ostream& operator<<(ostream& os, const NormalTeacher& teacher) {
    os << "Teacher Number: " << teacher.TeacherNumber << endl;
    os << "Teacher Name: " << teacher.TeacherName << endl;
    os << "Permission Level: " << teacher.PermissionLevel << endl;
    os << "Phone Number: " << teacher.PhoneNumber << endl;
    os << "Office Name: " << teacher.OfficeName << endl;
    return os;
}
// operator>>������ʵ��
istream& operator>>(istream& is, NormalTeacher& teacher) {
    cout << "Enter Teacher Number: ";
    is >> teacher.TeacherNumber;
    is.ignore(); // ���Ի��з�
    cout << "Enter Teacher Name: ";
    getline(is, teacher.TeacherName);
    cout << "Enter Permission Level: ";
    is >> teacher.PermissionLevel;
    is.ignore(); // ���Ի��з�
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
    std::cout << "������һ������: ";
    cin>>input;

    // ��������Ƿ�Ϊ��
    if (input.empty()) {
        std::cout << "δ�����κ����ݣ����������롣\n";
        return -1;
    }

    std::stringstream ss(input);
    if (!(ss >> value)) {
        std::cout << "������Ч��������һ��������\n";
        return -1;
    }

    return value;
}

/**�༭ʱ��:24-6-27 ����3:21
*�����ˣ������
*/
// ע���ʦ������ʵ��
void Teacher::teacher_register() {
    // ��ȡ�û��������ϸ��Ϣ
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
    // �������ݿ�
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cout << "Error connecting to database: " << mysql_error(&mysql) << std::endl;
      return;
    }

    // ������� SQL ���
    std::string query = "INSERT INTO Teacher (TeacherNumber, TeacherName, PermissionLevel, PhoneNumber, OfficeName, Password) VALUES ("
                        + std::to_string(getTeacherNumber()) + ", '"
                        + getTeacherName() + "', "
                        + std::to_string(getPermissionLevel()) + ", '"
                        + getPhoneNumber() + "', '"
                        + getOfficeName() + "', '"
                        + getPassword() + "')";

    // ִ�� SQL ���
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error inserting teacher: " << mysql_error(&mysql) << std::endl;
        mysql_close(&mysql);
        return;
    }

    std::cout << "Teacher registered successfully." << std::endl;

    // �ر����ݿ�����
    mysql_close(&mysql);
}



// ����ϵͳ����Ա��
class Admin : public Teacher {
    // other attributes
public:
    // ���캯��������������getter��setter��
    void display() const override; // ���Ǹ���Ĵ��麯��
//    void saveToFile(ofstream& file) const override; // ���Ǹ�����麯��
//    void loadFromFile(ifstream& file) override; // ���Ǹ�����麯��

    // ��Ԫ��������
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
// display������ʵ��
void Admin::display() const {
    cout << "Admin Number: " << TeacherNumber << endl;
    cout << "Admin Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}


// operator<<������ʵ��
ostream& operator<<(ostream& os, const Admin& admin) {
    os << "Admin Number: " << admin.TeacherNumber << endl;
    os << "Admin Name: " << admin.TeacherName << endl;
    os << "Permission Level: " << admin.PermissionLevel << endl;
    os << "Phone Number: " << admin.PhoneNumber << endl;
    os << "Office Name: " << admin.OfficeName << endl;
    return os;
}
// operator>>������ʵ��
istream& operator>>(istream& is, Admin& admin) {
    cout << "Enter Admin Number: ";
    is >> admin.TeacherNumber;
    is.ignore(); // ���Ի��з�
    cout << "Enter Admin Name: ";
    getline(is, admin.TeacherName);
    cout << "Enter Permission Level: ";
    is >> admin.PermissionLevel;
    is.ignore(); // ���Ի��з�
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
        cout<<"��½�ɹ�~~~~~~~~~~~~~~"<<endl;
        OptionChoice();
    }else{
        cout<<"��½ʧ�ܣ������԰ɣ�"<<endl;
    }
}
/**�༭ʱ��:24-6-26 ����1:23
*�����ˣ������
*/
bool CheckLogin(int teacherNumber, const std::string& password) {
    // ��ʼ�� MySQL ���Ӿ��
    MYSQL* mysql = mysql_init(NULL);

    // �������ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        // �������ʧ�ܣ���ӡ������Ϣ������ false
        std::cout << "Connection error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    // ����Ԥ���������
    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
    // SQL ��ѯ��䣬ʹ�� ? ռλ������ʵ�ʲ���AND PermissionLevel=2
    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=? ";

    // ׼�� SQL ���
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        // ���׼��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cout << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ����󶨲������飬����������TeacherNumber �� Password
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));  // ��ʼ���󶨲�������

    // �� TeacherNumber ����
    bind[0].buffer_type = MYSQL_TYPE_LONG;  // ��������Ϊ����
    bind[0].buffer = (char*)&teacherNumber; // ָ�� TeacherNumber ��ָ��
    bind[0].is_null = 0;                    // ��Ϊ��
    bind[0].length = 0;                     // ��������Ϊ 0

    // �� Password ����
    bind[1].buffer_type = MYSQL_TYPE_STRING;     // ��������Ϊ�ַ���
    bind[1].buffer = (char*)password.c_str();    // ָ�������ַ���
    bind[1].buffer_length = password.length();   // �����ַ�������
    bind[1].is_null = 0;                         // ��Ϊ��
    bind[1].length = 0;                          // ��������Ϊ 0

    // �󶨲�����Ԥ�������
    if (mysql_stmt_bind_param(stmt, bind)) {
        // �����ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cout << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ִ��Ԥ�������
    if (mysql_stmt_execute(stmt)) {
        // ���ִ��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cout << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ��ȡ��ѯ�����Ԫ���ݣ���������Ľṹ��
    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
    int num_fields = mysql_num_fields(res);  // ��ȡ����е��ֶ���
    // ����󶨽�����飬��ʼ��Ϊ 0
    MYSQL_BIND result_bind[num_fields];
    memset(result_bind, 0, sizeof(result_bind));

    // ����һ���ַ������������ڴ洢��ѯ���
    char buffer[256];
    for (int i = 0; i < num_fields; ++i) {
        // ����ÿ���ֶεĻ�������Ϣ
        result_bind[i].buffer_type = MYSQL_TYPE_STRING;  // �ֶ�����Ϊ�ַ���
        result_bind[i].buffer = buffer;                  // ָ�򻺳���
        result_bind[i].buffer_length = sizeof(buffer);   // ��������С
        result_bind[i].is_null = 0;                      // ��Ϊ��
        result_bind[i].length = 0;                       // ��������Ϊ 0
    }

    // �󶨽����������Ԥ�������
    if (mysql_stmt_bind_result(stmt, result_bind)) {
        // �����ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cout << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ����ѯ����洢�ڷ�������
    mysql_stmt_store_result(stmt);
    // ����Ƿ��в�ѯ������Ƿ���ƥ��ļ�¼��
    bool login_successful = (mysql_stmt_num_rows(stmt) > 0);

    // �ͷŽ����
    mysql_free_result(res);
    // �ر�Ԥ�������
    mysql_stmt_close(stmt);
    // �ر� MySQL ����
    mysql_close(mysql);

    return login_successful;  // ���ص�¼�Ƿ�ɹ�
}

bool Teacher:: teacher_enter(){
    //read_all_the_teachers(); //��ȡ�û��б�
    string str;
    int cnt = 0;
    while (cnt < 3) {
        //int teachernumber;
        cout << "�����ʦ���ţ�";
        cin >> TeacherNumber;
        cout << "�������룺";
        str = getPassword();//ɨ������
        setpassword(str);//��������
        bool identifier = CheckLogin(TeacherNumber, str);
        cout<<"��֤���"<<identifier<<endl;
        int i, user_num = 3;
        if(identifier == 1)
        {
            cout << "*******" << endl;
            cout << "��¼�ɹ���" << endl;
            cout << "*******" << endl;
            return true;
        }
        if (identifier == 0) {
            for (i = 0; i < user_num; i++) {
                str = getPassword();//ɨ������
                setpassword(str);//��������
                if (CheckLogin(TeacherNumber, str) == 0) {
                    cout << "*******" << endl;
                    cout << "��¼�ɹ���" << endl;
                    cout << "*******" << endl;
                    // teacher_operate(); //��ת��ͨ��ʦ����UI����
                    return true;
                } else if (i == user_num) {
                    cnt++;
                    cout << "�û���������������ٴ������û��������룬";
                    cout << "�㻹��" << 3 - cnt << "�λ���" << endl;
                }
            }
            if (i > user_num)//�����߼����⣬�ǵ�����һ��
            { return false; }
            if (cnt == 3) {
                cout << "��������Ѵ����ޣ�ϵͳ�رգ�" << endl;
                return false; }
        }
    }
    return 0;
}

/**�༭ʱ��:24-6-26 ����1:36
                *�����ˣ������
                */

bool Admin::admin_login() {
    string str;
    int cnt = 0;
    int max_attempts = 3; // ����Դ���
    int user_num = 3; // �û���������������Ŀ�������Ҫ���ݾ�����û��б���е���

    while (cnt < max_attempts) {
        cout << "���������Ա���ţ�";
        cin >> TeacherNumber;
        cout << "���������룺";
        str = getPassword(); // ��ȡ����
        setpassword(str); // �������룬ͨ���������ػ���ܴ���

        bool identifier = CheckLogin_forAdmin(TeacherNumber, str); // ������Ա��¼

        if (identifier) {
            cout << "*******" << endl;
            cout << "����Ա��¼�ɹ���" << endl;
            cout << "*******" << endl;
            // ������������ӹ���Ա�����Ĺ��ܵ��û������ת
             // ʾ���е��ù���Ա��������
            return true;
        } else {
            cnt++;
            cout << "�û���������������������롣";
            cout << "�㻹�� " << max_attempts - cnt << " �λ���" << endl;
        }
    }

    if (cnt == max_attempts) {
        cout << "��������Ѵ����ޣ�ϵͳ�رգ�" << endl;
        return false;
    }

    return false;
}

void Teacher::ViewBookings() {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        return;
    }

    // SQL ��ѯ��䣺���ҵ�ǰ��ʦ������Ԥ����¼
    std::string query = "SELECT b.BookingID, b.SubmissionTime, c.RoomNumber, c.RoomName, b.BookingDate, b.IsApproved "
                        "FROM BookingRecord b "
                        "JOIN Classroom c ON b.RoomID = c.RoomID "
                        "WHERE b.TeacherID = " + std::to_string(TeacherID);

    // ִ�� SQL ��ѯ
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Query error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // ��ȡ��ѯ�����
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "Result error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // �������������ӡÿһ������
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Booking ID: " << row[0]
                  << ", Submission Time: " << row[1]
                  << ", Room Number: " << row[2]
                  << ", Room Name: " << row[3]
                  << ", Booking Date: " << row[4]
                  << ", Approved: " << (std::stoi(row[5]) ? "Yes" : "No") << std::endl;
    }

    // �ͷŽ�������ر����ݿ�����
    mysql_free_result(res);
    mysql_close(mysql);
}

// �鿴���ý��ҵĺ���ʵ��
void Teacher::ViewAvailableRooms() {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        return;
    }

    // SQL ��ѯ��䣺��������δ��ռ�õĽ���
    std::string query = "SELECT RoomID, RoomNumber, RoomName, Capacity, RoomType "
                        "FROM Classroom "
                        "WHERE IsOccupied = 0";

    // ִ�� SQL ��ѯ
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Query error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // ��ȡ��ѯ�����
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "Result error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // �������������ӡÿһ������
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Room ID: " << row[0]
                  << ", Room Number: " << row[1]
                  << ", Room Name: " << row[2]
                  << ", Capacity: " << row[3]
                  << ", Room Type: " << row[4] << std::endl;
    }

    // �ͷŽ�������ر����ݿ�����
    mysql_free_result(res);
    mysql_close(mysql);
}
/**�༭ʱ��:24-6-27 ����6:15
*�����ˣ������
*/
//Admin::ViewAllBookings()��ɶ���Ԥ����ʦ�嵥�Ĳ鿴
//
void Admin::ViewAllBookings() {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }
    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return;
    }
    // �����ѯ���
    std::string query = "SELECT * FROM BookingRecord";

    // ִ�в�ѯ
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Error querying bookings: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return;
    }

    // ��ȡ�����
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result) {
        std::cerr << "Error retrieving result: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return;
    }

    // �����ͷ
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    for (int i = 0; i < num_fields; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        std::cout << field->name << '\t';
    }
    std::cout << std::endl;

    // ���ÿ������
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            std::cout << (row[i] ? row[i] : "NULL") << '\t'; // �����ֵ
        }
        std::cout << std::endl;
    }

    // �ͷŽ����
    mysql_free_result(result);

    // �ر����ݿ�����
    mysql_close(mysql);
}

/**�༭ʱ��:24-6-26 ����2:02
*�����ˣ������
*/
// ��׼Ԥ������
//bool Admin::ApproveBooking(int bookingID) {
//
//    // ����Ƿ����ʱ��ͽ��ҳ�ͻ
//    if (CheckConflict(bookingID, bookingDate)) {
//        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
//        return false;
//    }
//
//    // ����������
//    std::string query = "UPDATE BookingRecord SET IsApproved = true WHERE BookingID = " + std::to_string(bookingID);
//
//    // ִ�и���
//    if (mysql_query(&mysql, query.c_str())) {
//        std::cout << "Error approving booking: " << mysql_error(&mysql) << std::endl;
//        return false;
//    }
//
//    std::cout << "Booking with ID " << bookingID << " approved successfully." << std::endl;
//    return true;
//}
//����
/**�༭ʱ��:24-6-26 ����12:40
*�����ˣ������
*/
// ʵ�ּ���ͻ�ĺ���
bool Admin::CheckConflict(int roomID, const std::string& bookingDate) {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL ��ʼ��ʧ�ܣ�" << std::endl;
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "���ݿ�����ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // �����ѯ���
    const char* query = "SELECT COUNT(*) FROM BookingRecord WHERE RoomID = ? AND BookingDate = ? AND IsApproved = true";
    MYSQL_STMT* stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        std::cerr << "Statement ��ʼ��ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // ׼����ѯ
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Statement ׼��ʧ��: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // �󶨲���
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
        std::cerr << "������ʧ��: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // ִ�в�ѯ
    if (mysql_stmt_execute(stmt)) {
        std::cerr << "��ѯִ��ʧ��: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // �󶨽��
    int conflictCount;
    MYSQL_BIND resultBind[1];
    memset(resultBind, 0, sizeof(resultBind));

    resultBind[0].buffer_type = MYSQL_TYPE_LONG;
    resultBind[0].buffer = (char*)&conflictCount;
    resultBind[0].is_null = 0;
    resultBind[0].length = nullptr;

    if (mysql_stmt_bind_result(stmt, resultBind)) {
        std::cerr << "�����ʧ��: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // ��ȡ���
    if (mysql_stmt_fetch(stmt)) {
        std::cerr << "�����ȡʧ��: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return true; // ���س�ͻ��ʵ��Ӧ����������������
    }

    // �ͷ���Դ
    mysql_stmt_close(stmt);
    mysql_close(mysql);

    // �ж��Ƿ���ڳ�ͻ
    return conflictCount > 0;
}

// ��ȡԤ����ϸ��Ϣ�ĸ�������
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

// ʵ��ȡ��Ԥ���ĺ���
bool Admin::CancelBooking(int bookingID) {
    std::string query = "DELETE FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);

    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error cancelling booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }
    std::cout << "Booking with ID " << bookingID << " cancelled successfully." << std::endl;
    return true;
}

/**�༭ʱ��:24-6-27 ����5:50
*�����ˣ������
*/
bool Admin::ApproveBooking(int bookingID) {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL ��ʼ��ʧ�ܣ�" << std::endl;
        return false;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "���ݿ�����ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    // ׼����ѯ RoomID �� BookingDate ��Ԥ�������
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

    // �󶨲���
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

    // ִ�в�ѯ
    if (mysql_stmt_execute(stmt_select)) {
        std::cerr << "Statement execution failed: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // �󶨽��
    int roomID;
    char bookingDate[11]; // �������ڸ�ʽΪ YYYY-MM-DD
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

    // �洢���
    if (mysql_stmt_store_result(stmt_select)) {
        std::cerr << "Failed to store result: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // ����Ƿ��н��
    if (mysql_stmt_num_rows(stmt_select) == 0) {
        std::cerr << "No booking found with ID " << bookingID << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // ��ȡ���
    if (mysql_stmt_fetch(stmt_select)) {
        std::cerr << "Failed to fetch result: " << mysql_stmt_error(stmt_select) << std::endl;
        mysql_stmt_close(stmt_select);
        mysql_close(mysql);
        return false;
    }

    // �ͷŲ�ѯ���
    mysql_stmt_close(stmt_select);

    // ����Ƿ����ʱ��ͽ��ҳ�ͻ
    if (CheckConflict(roomID, bookingDate)) {
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        mysql_close(mysql);
        return false;
    }

    // ׼��������䣬��׼Ԥ��
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

    // ִ�и���
    if (mysql_stmt_execute(stmt_update)) {
        std::cerr << "Error approving booking: " << mysql_stmt_error(stmt_update) << std::endl;
        mysql_stmt_close(stmt_update);
        mysql_close(mysql);
        return false;
    }

    // �رո����������ݿ�����
    mysql_stmt_close(stmt_update);
    mysql_close(mysql);

    // ����ɹ���Ϣ
    std::cout << "Booking with ID " << bookingID << " approved successfully." << std::endl;
    return true;
}

bool Teacher::ModifyBooking(int bookingID, int roomID, const std::string& bookingDate) {
    if (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cerr << "���ڸ�ʽ��Ч�򳬳���Χ����������ȷ������ (YYYY-MM-DD)." << std::endl;
        return false;
    }
    // ����Ƿ����ʱ��ͽ��ҳ�ͻ
    if (CheckConflict(roomID, bookingDate)) {
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        return false;
    }

    // ����������
    std::string query = "UPDATE BookingRecord SET RoomID = " + std::to_string(roomID) +
                        ", BookingDate = '" + bookingDate + "' WHERE BookingID = " + std::to_string(bookingID);

    // ִ�и���
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error modifying booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    std::cout << "Booking with ID " << bookingID << " modified successfully." << std::endl;
    return true;
}

// ȡ��Ԥ���ĺ���
bool Teacher::CancelBooking(int bookingID) {
    // ����ɾ�����
    std::string query = "DELETE FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);
    // ִ��ɾ��
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
    std::cout << "������ԤԼ���� (��ʽ: YYYY-MM-DD): ";
    std::cin >> bookingDate;

    while (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cout << "��Ч�����ڸ�ʽ�����ڳ�����Χ������������ (��ʽ: YYYY-MM-DD): ";
        std::cin >> bookingDate;
    }
}
// ��������������Ƿ��п��ý���
bool Teacher::isDateAvailable(int roomID, const std::string& bookingDate) {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(nullptr);
    if (!mysql) {
        std::cerr << "MySQL ��ʼ��ʧ�ܣ�" << std::endl;
        return false;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, nullptr, 0)) {
        std::cerr << "���ݿ�����ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return false;
    }

    // ���� SQL ��ѯ���
    std::string checkQuery = "SELECT * FROM bookingrecord WHERE RoomID = " + std::to_string(roomID) +
                             " AND BookingDate = '" + bookingDate + "'";

    // ִ�в�ѯ
    if (mysql_query(mysql, checkQuery.c_str())) {
        std::cerr << "��ѯʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return false;
    }

    // ��ȡ���
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "��ȡ���ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return false;
    }

    // ���������
    int num_rows = mysql_num_rows(res);
    mysql_free_result(res); // �ͷŽ����Դ

    // �ر�����
    mysql_close(mysql);

    return num_rows == 0; // ���� true ��ʾû�г�ͻ
}
void Teacher::Loginshow(){
    cout << "===============================================" << endl;
    cout << endl;
    cout << "��ӭʹ�ý���ԤԼϵͳ��" <<getTeacherName()<< endl;
    cout << "===============================================" << endl;
    cout << "1.��ѯ��ǰ�������    2.�鿴����Ԥ��   3.�޸�����Ԥ��     4.�˳�ϵͳ" << endl;
}
// ������Ԥ������

bool Teacher::BookRoom(int roomID, const std::string& bookingDate) {
    if (!isValidDate(bookingDate) || !isDateInRange(bookingDate)) {
        std::cerr << "���ڸ�ʽ��Ч�򳬳���Χ����������ȷ������ (YYYY-MM-DD)." << std::endl;
        return false;
    }

    if (!isDateAvailable(roomID, bookingDate)) {
        std::cerr << "�����ںͽ����ѱ�Ԥ������ѡ���������ڻ���ҡ�" << std::endl;
        return false;
    }

    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL ��ʼ��ʧ�ܣ�" << std::endl;
        return false;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "���ݿ�����ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return false;
    }

    // ���� SQL �������
    std::string query = "INSERT INTO bookingrecord (RoomID, TeacherID, BookingDate, IsApproved) VALUES (" +
                        std::to_string(roomID) + ", " + std::to_string(this->TeacherID) + ", '" + bookingDate + "', 0)";

    // ִ�в�ѯ
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "���ݿ����ʧ��: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql); // �ر����ӣ���ֹ��Դй¶
        return false;
    }

    std::cout << "����ԤԼ�ɹ���" << std::endl;

    // �ر�����
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
        cout<<"�������"<<endl;
        cin>>option;

        switch (option) {
            case 1:
                ViewAvailableRooms();
                //�����Ƿ�Ԥ��//��Ļ��˳�������
                break;
            case 2:
                //�鿴����Ԥ��
                ViewBookings();
                cout<<"�Ƿ���Ҫ�½�����Ԥ����"<<endl;
                cout<<"������1��0�����Ǻͷ�"<<endl;
                cin>>judge;
                if(judge==1){
                    cout<<"��������Һź�ԤԼʱ��(��ʽYYYY-MM-DD)"<<endl;
                    cin>>RoomId;
                    cin>>newtime;
                    BookRoom(RoomId,newtime);
                }else
                {
                    cout<<"��������"<<endl;
                }

                break;
            case 3:
                //�޸ı���Ԥ��
                ViewBookings();
                cout<<"��Ҫ�޸���һ��Ԥ��?"<<endl;
                cout<<"����Ԥ����ţ�Ԥ�ڽ��ұ�ź�Ԥ��ʱ��"<<endl;
                cin>>BookingId;
                cin>>RoomId;
                cin>>newtime;
                ModifyBooking(BookingId,RoomId, newtime);
                break;
            case 4:
                cout << "��ӭ�´�ʹ�ã�" << endl;
                break;
            default:
                cout << "��Ч��ѡ���������Ч�Ĳ���ѡ�1-4����" << endl;
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
        cout << "���������ѡ�" << endl;
        cout << "1. ��ѯ�������" << endl;
        cout << "2. ����ע���ʦ" << endl;
        cout << "3. �鿴Ԥ������" << endl;
        cout << "4. ����Ԥ������" << endl;
        cout << "5. ȡ��Ԥ�����Ҳ���������" << endl;
        cout << "6. �˳�" << endl;
        cin >> option;

        switch (option) {
            case 1:
                ViewAvailableRooms();
                // �����Ƿ�Ԥ������Ļ��˳�������
                break;
            case 2:
                teacher_register(); // ����ע���ʦ
                break;
            case 3:
                ViewAllBookings(); // �鿴Ԥ������
                break;
            case 4:
                cout<<"�����������ұ��"<<endl;
                cin>>RoomId;
                Isapproved=ApproveBooking(RoomId); // ����Ԥ������
                if(Isapproved==true)
                {
                    cout<<"���������"<<endl;
                }
                break;
            case 5:
                cout << "������Ҫȡ��Ԥ����Ԥ����š�����ź�ȡ�����ɣ�" << endl;
                cin >> BookingId;
                cin.ignore(); // ���Ի��з�
                cin>>RoomId;
                getline(cin, reason); // ����ȡ������
                CancelBooking(BookingId); // ȡ��Ԥ�����Ҳ���������
                break;
            case 6:
                cout << "��ӭ�´�ʹ�ã�" << endl;
                break;
            default:
                cout << "��Ч��ѡ���������Ч�Ĳ���ѡ�1-6����\n";
                break;
        }
    } while (option != 6);
}
/**�༭ʱ��:24-6-27 ����6:11
*�����ˣ������
 *
�����Admin::CheckLogin_forAdmin��������������������ʶ��Ϳ�չ����Ա����Ϊ��
 */
bool Admin::CheckLogin_forAdmin(int teacherNumber, const std::string& password) {
    // ��ʼ�� MySQL ���Ӿ��
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "Failed to initialize MySQL connection." << std::endl;
        return false;
    }

    // �������ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        // �������ʧ�ܣ���ӡ������Ϣ���ر� MySQL ����
        std::cerr << "Connection error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return false;
    }

    // ����Ԥ���������
    MYSQL_STMT *stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        std::cerr << "Failed to initialize MySQL statement." << std::endl;
        mysql_close(mysql);
        return false;
    }

    // SQL ��ѯ��䣬ʹ�� ? ռλ������ʵ�ʲ���
    const char *query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=? AND PermissionLevel=2";

    // ׼�� SQL ���
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        // ���׼��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cerr << "Statement preparation error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ����󶨲������飬����������TeacherNumber �� Password
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));  // ��ʼ���󶨲�������

    // �� TeacherNumber ����
    bind[0].buffer_type = MYSQL_TYPE_LONG;  // ��������Ϊ����
    bind[0].buffer = (char *) &teacherNumber; // ָ�� TeacherNumber ��ָ��
    bind[0].is_null = 0;                    // ��Ϊ��

    // �洢����Ļ�����
    char passwordBuffer[100]; // ��������������� 100 �ַ�
    strncpy(passwordBuffer, password.c_str(), sizeof(passwordBuffer));
    bind[1].buffer_type = MYSQL_TYPE_STRING;     // ��������Ϊ�ַ���
    bind[1].buffer = passwordBuffer;             // ָ�����뻺����
    bind[1].buffer_length = strlen(passwordBuffer); // �����ַ�������
    bind[1].is_null = 0;                         // ��Ϊ��

    // �󶨲�����Ԥ�������
    if (mysql_stmt_bind_param(stmt, bind)) {
        // �����ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cerr << "Parameter binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ִ�в�ѯ
    if (mysql_stmt_execute(stmt)) {
        // ���ִ��ʧ�ܣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cerr << "Statement execution error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ��ȡ��ѯ�����
    MYSQL_RES *result_metadata = mysql_stmt_result_metadata(stmt);
    if (!result_metadata) {
        // ����޷���ȡ�����Ԫ���ݣ���ӡ������Ϣ���ر�������� MySQL ����
        std::cerr << "Failed to retrieve result set meta information." << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ��ȡ����Ϣ
    unsigned int column_count = mysql_num_fields(result_metadata);
    MYSQL_BIND result_bind[column_count];
    memset(result_bind, 0, sizeof(result_bind));

    // ���ڴ洢����Ļ�����
    char data[column_count][100]; // ����ÿ����� 100 �ַ�
    unsigned long data_length[column_count];

    // �󶨽��������
    for (unsigned int i = 0; i < column_count; ++i) {
        result_bind[i].buffer_type = MYSQL_TYPE_STRING;
        result_bind[i].buffer = data[i];
        result_bind[i].buffer_length = sizeof(data[i]);
        result_bind[i].length = &data_length[i];
    }

    // �󶨽�������
    if (mysql_stmt_bind_result(stmt, result_bind)) {
        std::cerr << "Result binding error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // �洢�����
    if (mysql_stmt_store_result(stmt)) {
        std::cerr << "Result storing error: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        mysql_close(mysql);
        return false;
    }

    // ����ѯ���
    bool loggedIn = false;
    if (mysql_stmt_fetch(stmt) == 0) { // 0 ��ʾ�ɹ���ȡ��һ��
        loggedIn = true;
        std::cout << "Login successful. Retrieved data:" << std::endl;
        for (unsigned int i = 0; i < column_count; ++i) {
            std::cout << "Column " << i << ": " << data[i] << ", Length: " << data_length[i] << std::endl;
        }
    } else {
        std::cout << "Login failed. No matching records found." << std::endl;
    }

    // �ͷŽ����Ԫ����
    mysql_free_result(result_metadata);

    // �ر������
    mysql_stmt_close(stmt);
    // �ر� MySQL ����
    mysql_close(mysql);

    return loggedIn;
}

/**�༭ʱ��:24-6-27 ����5:33
*�����ˣ������
*/
void Admin::CheckAllBookings() {
    // ��ʼ�� MySQL ����
    MYSQL* mysql = mysql_init(NULL);
    if (!mysql) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return;
    }

    // ���ӵ� MySQL ���ݿ�
    if (!mysql_real_connect(mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cerr << "Error connecting to database: " << mysql_error(mysql) << std::endl;
        return;
    }

    // SQL ��ѯ��䣺�������н�ʦ��Ԥ����¼
    std::string query = "SELECT b.BookingID, b.SubmissionTime, c.RoomNumber, c.RoomName, b.BookingDate, b.IsApproved, t.TeacherName "
                        "FROM BookingRecord b "
                        "JOIN Classroom c ON b.RoomID = c.RoomID "
                        "JOIN Teacher t ON b.TeacherID = t.TeacherID";

    // ִ�� SQL ��ѯ
    if (mysql_query(mysql, query.c_str())) {
        std::cerr << "Query error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // ��ȡ��ѯ�����
    MYSQL_RES* res = mysql_store_result(mysql);
    if (!res) {
        std::cerr << "Result error: " << mysql_error(mysql) << std::endl;
        mysql_close(mysql);
        return;
    }

    // �������������ӡÿһ������
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

    // �ͷŽ�������ر����ݿ�����
    mysql_free_result(res);
    mysql_close(mysql);
}
