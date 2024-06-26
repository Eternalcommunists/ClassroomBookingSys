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

void textMysql(string sql);//���Է���
bool ConnectMysql();//�������ݿ�
bool QueryDatabase(string sql);//��ѯ��������
void outMysql();//�����ѯ���
bool updateData(string sql);//����ɾ���޸Ĳ���
void FreeConnect();//�ͷ���Դ

//---------------�ⲿ�ַ�Դ�ļ�------------------------

MYSQL mysql;
MYSQL_RES *res;//����ṹ�������е�һ����ѯ�����
MYSQL_ROW column;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ

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

// �����������
enum RoomType { LAB = 1, MULTIMEDIA = 2, RECORDING = 3 };

// ���������
class Room {
protected:
    int roomNumber;//���Һ�
    string roomName;//��������
    int capacity;//��������
    bool isOccupied;//��ǰռ��״̬
    //RoomType roomType;//�����������
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    virtual void display() = 0; // pure virtual function
    friend ostream& operator<<(ostream& os, const Room& room);//�����������room����Ϣ���������
    friend istream& operator>>(istream& is, Room& room);//��������������Ϣ���뵽room����
    void saveToFile(ofstream& file);//��room��Ϣ�����ļ�
    void loadFromFile(ifstream& file);//��room��Ϣ���ؽ�����
};
// display����������ʵ��
void Room::display() {
    cout << "Room roomNumber: " << roomNumber<< endl;
    cout<<"Room roomName: "<<roomName<<endl;
    //cout << "Room Type: " << roomType<< endl;
    cout << "Room capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}

// operator<<����������ʵ��
ostream& operator<<(ostream& os, const Room& room) {
    os << "Room roomNumber: " << room.roomNumber << endl;
    os<<"Room roomName: "<<room.roomName<<endl;
    // os << "Room Type: " << room.roomType << endl;
    os << "Room capacity: " << room.capacity << endl;
    os << "Is Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
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

// saveToFile����������ʵ��
void Room::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName<< endl;
    // file << roomType << endl;
    file << capacity<< endl;
    file<<isOccupied<<endl;
}

// loadFromFile����������ʵ��
void Room::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file >> roomName;
    //file >> roomType;
    file >> capacity;
    file >> isOccupied;
}


// ����ʵ������
class Lab : public Room {
    int labType;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const Lab& lab);//�����������lab����Ϣ���������
    friend istream& operator>>(istream& is, Lab& lab);//��������������Ϣ���뵽lab����
    void saveToFile(ofstream& file);//��room��Ϣ�����ļ�
    void loadFromFile(ifstream& file);//��room��Ϣ���ؽ�����
    void setRoomNumber(int number) { roomNumber = number; }
    void setRoomName(const string& name) { roomName = name; }
    void setCapacity(int cap) { capacity = cap; }
    void setLabType(int type) { labType = type; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

};
// display����������ʵ��
void Lab::display() {
    cout << "Lab roomNumber: " << roomNumber << endl;
    cout<<"Lab roomName: "<<roomName<<endl;
    // cout << "Lab Type: " << labType << endl;
    cout << "Lab Capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}

// operator<<����������ʵ��
ostream& operator<<(ostream& os, const Lab& lab) {
    os << "Lab roomNumber: " << lab.roomNumber << endl;
    os<<"Lab roomName: "<<lab.roomName<<endl;
    //os << "Lab Type: " << lab.labType << endl;
    os << "Lab Capacity: " << lab.capacity << endl;
    os << "Is Occupied: " << (lab.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// operator>>����������ʵ��
istream& operator>>(istream& is, Lab& lab) {
    cout << "Enter Lab roomNumber: ";
    is >> lab.roomNumber;
    cout<<"Enter Lab roomName: ";
    is>>lab.roomName;
    cout << "Enter Lab Type: ";
    //is >> lab.labType;
    cout << "Enter Lab capacity: ";
    is >> lab.capacity;
    cout << "Is the Room Occupied? (1 for Yes, 0 for No): ";
    is >> lab.isOccupied;
    return is;
}
// saveToFile����������ʵ��
void Lab::saveToFile(ofstream& file) {
    file << roomNumber<< endl;
    file << roomName << endl;
    //file << labType << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// loadFromFile����������ʵ��
void Lab::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file.ignore();
    getline(file, roomName);
    file >> capacity;
    file >> labType;
    file >> isOccupied;
}
// �����ý�������
class MultimediaRoom : public Room {
    int airConditioners;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const MultimediaRoom& room); // ����������
    friend istream& operator>>(istream& is, MultimediaRoom& room); // �����������
    void saveToFile(ofstream& file); // ��MultimediaRoom��Ϣ�����ļ�
    void loadFromFile(ifstream& file); // ��MultimediaRoom��Ϣ���ؽ�����
};
// ʵ��display����
void MultimediaRoom::display() {
    cout << "Room Number: " << roomNumber << endl;
    cout << "Room Name: " << roomName << endl;
    cout << "Air Conditioners: " << airConditioners << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}
// ʵ������������
ostream& operator<<(ostream& os, const MultimediaRoom& room) {
    os << "Room Number: " << room.roomNumber << endl;
    os << "Room Name: " << room.roomName << endl;
    os << "Air Conditioners: " << room.airConditioners << endl;
    os << "Capacity: " << room.capacity << endl;
    os << "Is Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// ʵ�������������
istream& operator>>(istream& is, MultimediaRoom& room) {
    cout << "Enter Room Number: ";
    is >> room.roomNumber;
    cout << "Enter Room Name: ";
    is >> room.roomName;
    cout << "Enter Air Conditioners: ";
    is >> room.airConditioners;
    cout << "Enter Capacity: ";
    is >> room.capacity;
    cout << "Is the room occupied (1 for Yes, 0 for No): ";
    is >> room.isOccupied;
    return is;
}
// ʵ�ֱ��浽�ļ�����
void MultimediaRoom::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName << endl;
    file << airConditioners << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// ʵ�ִ��ļ����غ���
void MultimediaRoom::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file.ignore(); // ���Ի��з�
    getline(file, roomName);
    file >> airConditioners;
    file >> capacity;
    file >> isOccupied;
}
// ����¼�ν�����
class RecordingRoom : public Room {
    int cameras;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    //��RecordingRoom����Ϣ���ؽ�����
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const RecordingRoom& room);//�����������RecordingRoom����Ϣ���������
    friend istream& operator>>(istream& is, RecordingRoom& room);//������������RecordingRoom����Ϣ���������
    void saveToFile(ofstream& file);//��RecordingRoom����Ϣ�����ļ�
    void loadFromFile(ifstream& file);
};
// display����������ʵ��
void RecordingRoom::display() {
    cout << "Room Number: " << roomNumber << endl;
    cout << "Room Name: " << roomName << endl;
    cout << "Cameras: " << cameras << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}
// operator<<����������ʵ��
ostream& operator<<(ostream& os, const RecordingRoom& room) {
    os << "Room Number: " << room.roomNumber << endl;
    os << "Room Name: " << room.roomName << endl;
    os << "Cameras: " << room.cameras << endl;
    os << "Capacity: " << room.capacity << endl;
    os << "Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// operator>>����������ʵ��
istream& operator>>(istream& is, RecordingRoom& room) {
    cout << "Enter Room Number: ";
    is >> room.roomNumber;
    cout << "Enter Room Name: ";
    is >> room.roomName;
    cout << "Enter Cameras: ";
    is >> room.cameras;
    cout << "Enter Capacity: ";
    is >> room.capacity;
    cout << "Is Occupied (1 for Yes, 0 for No): ";
    is >> room.isOccupied;
    return is;
}
// saveToFile����������ʵ��
void RecordingRoom::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName << endl;
    file << cameras << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// loadFromFile����������ʵ��
void RecordingRoom::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file >> roomName;
    file >> cameras;
    file >> capacity;
    file >> isOccupied;
}
class Teacher {
protected:
    int TeacherID;
    int TeacherNumber; // ��ʦ����
    string TeacherName; // ��ʦ����
    int PermissionLevel; // Ȩ�޵ȼ�
    string PhoneNumber; // �绰����
    string OfficeName; // �칫������
private:
    string Password;//����������� ʱ�䣺2024.6.26 00��54��
    // other attributes
public:
    // ���캯��������������getter��setter��
    virtual void display() const = 0; // ���麯����ǿ������ʵ��
    virtual void saveToFile(ofstream& file) const = 0; // �麯��
    virtual void loadFromFile(ifstream& file) = 0; // �麯��
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

    bool ModifyBooking(int bookingID, int roomID, const string &bookingDate);
};
class NormalTeacher : public Teacher {
public:
    // ���캯��������������getter��setter��
    void display() const override; // ���Ǹ���Ĵ��麯��
    void saveToFile(ofstream& file) const override; // ���Ǹ�����麯��
    void loadFromFile(ifstream& file) override; // ���Ǹ�����麯��
    // ��Ԫ��������
    friend ostream& operator<<(ostream& os, const NormalTeacher& teacher);
    friend istream& operator>>(istream& is, NormalTeacher& teacher);

    void teacher_register();
};
// display������ʵ��
void NormalTeacher::display() const {
    cout << "Teacher Number: " << TeacherNumber << endl;
    cout << "Teacher Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}
// saveToFile������ʵ��
void NormalTeacher::saveToFile(ofstream& file) const {
    if (!file) {
        cerr << "Error: File could not be opened for writing!ByTeacher" << endl;
        return;
    }
    file << TeacherNumber << endl;
    file << TeacherName << endl;
    file << PermissionLevel << endl;
    file << PhoneNumber << endl;
    file << OfficeName << endl;
}

// loadFromFile������ʵ��
void NormalTeacher::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By NormalTeacher" << endl;
        return;
    }
    file >> TeacherNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, TeacherName);
    file >> PermissionLevel;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, PhoneNumber);
    getline(file, OfficeName);

    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
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

// ��ȡ�û�����ĸ�������
std::string getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
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
// ע���ʦ������ʵ��
void NormalTeacher::teacher_register() {
    // ��ȡ�û��������ϸ��Ϣ
    int teacherNumber = std::stoi(getInput("Enter Teacher Number: "));
    std::string teacherName = getInput("Enter Teacher Name: ");
    int permissionLevel = std::stoi(getInput("Enter Permission Level (e.g., 1 for Normal Teacher): "));
    std::string phoneNumber = getInput("Enter Phone Number: ");
    std::string officeName = getInput("Enter Office Name: ");
    std::string password = getPassword();

    // �������ݿ�
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "admin", "school", 3306, NULL, 0)) {
        std::cout << "Error connecting to database: " << mysql_error(&mysql) << std::endl;
        return;
    }

    // ������� SQL ���
    std::string query = "INSERT INTO Teacher (TeacherNumber, TeacherName, PermissionLevel, PhoneNumber, OfficeName, Password) VALUES ("
                        + std::to_string(teacherNumber) + ", '"
                        + teacherName + "', "
                        + std::to_string(permissionLevel) + ", '"
                        + phoneNumber + "', '"
                        + officeName + "', '"
                        + password + "')";

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
    void saveToFile(ofstream& file) const override; // ���Ǹ�����麯��
    void loadFromFile(ifstream& file) override; // ���Ǹ�����麯��

    // ��Ԫ��������
    friend ostream& operator<<(ostream& os, const Admin& admin);
    friend istream& operator>>(istream& is, Admin& admin);

    void admin_enter();
    bool CheckConflict(int roomID, const std::string& bookingDate);
    bool ApproveBooking(int bookingID);

    void ViewAllBookings();

    bool GetBookingDetails(int bookingID, int &roomID, string &bookingDate);

    bool CancelBooking(int bookingID);
};
// display������ʵ��
void Admin::display() const {
    cout << "Admin Number: " << TeacherNumber << endl;
    cout << "Admin Name: " << TeacherName << endl;
    cout << "Permission Level: " << PermissionLevel << endl;
    cout << "Phone Number: " << PhoneNumber << endl;
    cout << "Office Name: " << OfficeName << endl;
}
// saveToFile������ʵ��
void Admin::saveToFile(ofstream& file) const {
    if (!file) {
        cerr << "Error: File could not be opened for writing!FROM ADMIN" << endl;
        return;
    }
    file << TeacherNumber << endl;
    file << TeacherName << endl;
    file << PermissionLevel << endl;
    file << PhoneNumber << endl;
    file << OfficeName << endl;
}
// loadFromFile������ʵ��
void Admin::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By Admin" << endl;
        return;
    }
    file >> TeacherNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, TeacherName);
    file >> PermissionLevel;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, PhoneNumber);
    getline(file, OfficeName);
    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
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

}

//// �������Ԥ����¼��
class Reservation {
    int reservationNumber;
    string submissionTime;
    int roomNumber;
    string reservationDate;
    // other attributes
public:
    // Constructor
    Reservation(int rNumber = 0, const string& sTime = "", const string& rDate = "") :
            reservationNumber(rNumber), submissionTime(sTime), roomNumber(rNumber), reservationDate(rDate) {}

    // Getters and Setters
    int getReservationNumber() const { return reservationNumber; }
    void setReservationNumber(int number) { reservationNumber = number; }

    string getSubmissionTime() const { return submissionTime; }
    void setSubmissionTime(const string& time) { submissionTime = time; }

    int getRoomNumber() const { return roomNumber; }
    void setRoomNumber(int number) { roomNumber = number; }

    string getReservationDate() const { return reservationDate; }
    void setReservationDate(const string& date) { reservationDate = date; }

    // Friend functions for input and output
    friend ostream& operator<<(ostream& os, const Reservation& reservation);
    friend istream& operator>>(istream& is, Reservation& reservation);

    // File operations
    void saveToFile(ofstream& file) const;
    void loadFromFile(ifstream& file);

    // Display function
    void display() const; // ��ȷ������ display ����
};

void Reservation::display() const {
    cout << "Reservation Number: " << reservationNumber << endl;
    cout << "Submission Time: " << submissionTime << endl;
    cout << "Room Number: " << roomNumber << endl;
    cout << "Reservation Date: " << reservationDate << endl;
}

// operator<< ������ʵ��
ostream& operator<<(ostream& os, const Reservation& reservation) {
    os << "Reservation Number: " << reservation.reservationNumber << endl;
    os << "Submission Time: " << reservation.submissionTime << endl;
    os << "Room Number: " << reservation.roomNumber << endl;
    os << "Reservation Date: " << reservation.reservationDate << endl;
    return os;
}
// operator>> ������ʵ��
istream& operator>>(istream& is, Reservation& reservation) {
    cout << "Enter Reservation Number: ";
    is >> reservation.reservationNumber;
    is.ignore(); // ���Ի��з�

    cout << "Enter Submission Time: ";
    getline(is, reservation.submissionTime);

    cout << "Enter Room Number: ";
    is >> reservation.roomNumber;
    is.ignore(); // ���Ի��з�

    cout << "Enter Reservation Date: ";
    getline(is, reservation.reservationDate);

    return is;
}
// saveToFile ������ʵ��
void Reservation::saveToFile(ofstream& file) const {
    if (!file) {
        cerr << "Error: File could not be opened for writing!FOR Reservation" << endl;
        return;
    }
    file << reservationNumber << endl;
    file << submissionTime << endl;
    file << roomNumber << endl;
    file << reservationDate << endl;
}
// loadFromFile ������ʵ��
void Reservation::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By reservation" << endl;
        return;
    }
    file >> reservationNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, submissionTime);
    file >> roomNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ������β���з�
    getline(file, reservationDate);

    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
}

void saveToFile(const string& filename, Lab lab, const NormalTeacher& teacher, const Reservation& reservation) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "�޷����ļ� " << filename << " ����д��." << endl;
        return;
    }

    try {
        lab.saveToFile(outfile);
        cout << "���lab����-->save" << endl;

        teacher.saveToFile(outfile);
        cout << "���teacher����-->save" << endl;

        reservation.saveToFile(outfile);
        cout << "���reservation����-->save" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    outfile.close();
}

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
    // SQL ��ѯ��䣬ʹ�� ? ռλ������ʵ�ʲ���
    const char* query = "SELECT * FROM teacher WHERE TeacherNumber=? AND Password=?";

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


bool Teacher:: teacher_enter() {
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
            if (cnt == 3) { cout << "��������Ѵ����ޣ�ϵͳ�رգ�" << endl;return false; }
        }
    }
}
/**�༭ʱ��:24-6-26 ����1:36
                *�����ˣ������
                */
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

// �鿴����Ԥ����Ϣ
void Admin::ViewAllBookings() {
    // �������ݿ⣨ʡ�ԣ�

    // �����ѯ���
    std::string query = "SELECT * FROM BookingRecord";

    // ִ�в�ѯ
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
        return;
    }

    // ��ȡ�����
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
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
            std::cout << row[i] << '\t';
        }
        std::cout << std::endl;
    }

    // �ͷŽ����
    mysql_free_result(result);

    // �ر����ݿ����ӣ�ʡ�ԣ�
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
    // 1. �����ѯ���
    std::string query = "SELECT COUNT(*) FROM BookingRecord "
                        "WHERE RoomID = " + std::to_string(roomID) +
                        " AND BookingDate = '" + bookingDate + "'"
                                                               " AND IsApproved = true";

    // 2. ִ�в�ѯ
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error checking conflict: " << mysql_error(&mysql) << std::endl;
        return true;
    }

    // 3. ��ȡ�����
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return true;
    }

    // 4. ��ȡ������
    MYSQL_ROW row = mysql_fetch_row(result);
    int conflictCount = std::stoi(row[0]);

    // 5. �ͷŽ����
    mysql_free_result(result);

    // 6. �����Ƿ��г�ͻ
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
// ����Ԥ������ĺ���������һ��Ԥ����Ψһ��ʶ bookingID ��Ϊ����
bool Admin::ApproveBooking(int bookingID) {

    // 1. ��ѯ��ǰԤ���ķ��������
    // ���� SQL ��ѯ��䣬��ѯ���� bookingID ��Ӧ�� RoomID �� BookingDate
    std::string query = "SELECT RoomID, BookingDate FROM BookingRecord WHERE BookingID = " + std::to_string(bookingID);

    // 2. ִ�в�ѯ
    // ʹ�� mysql_query ִ�� SQL ��ѯ
    if (mysql_query(&mysql, query.c_str())) {
        // �����ѯʧ�ܣ����������Ϣ������ false
        std::cout << "Error querying booking record: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 3. ��ȡ�����
    // mysql_store_result ���ڻ�ȡ��ѯ�Ľ����
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        // �����ȡ�����ʧ�ܣ����������Ϣ������ false
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 4. ����Ƿ��н��
    // ʹ�� mysql_num_rows ����������Ƿ��м�¼
    if (mysql_num_rows(result) == 0) {
        // ��������Ϊ�գ�˵��û���ҵ���Ӧ��Ԥ���������Ϣ���ͷŽ������Ȼ�󷵻� false
        std::cout << "No booking found with ID " << bookingID << std::endl;
        mysql_free_result(result);
        return false;
    }

    // 5. ��ȡ RoomID �� BookingDate
    // ʹ�� mysql_fetch_row �ӽ�����л�ȡһ������
    MYSQL_ROW row = mysql_fetch_row(result);
    int roomID = std::stoi(row[0]); // ����һ�У�RoomID��ת��Ϊ����
    std::string bookingDate = row[1]; // ��ȡ�ڶ��У�BookingDate�����ַ���

    // 6. �ͷŽ����
    // �ͷŲ�ѯ��������ڴ�
    mysql_free_result(result);

    // 7. ����Ƿ����ʱ��ͽ��ҳ�ͻ
    // ���� CheckConflict �������Ԥ���Ƿ������еİ��ų�ͻ
    if (CheckConflict(roomID, bookingDate)) {
        // ����г�ͻ�������ͻ��Ϣ������ false
        std::cout << "Booking conflicts with existing schedule. Please choose another room or time." << std::endl;
        return false;
    }

    // 8. ���������䣬��׼Ԥ��
    // ���� BookingRecord ������ IsApproved Ϊ true ��ʾ��׼Ԥ��
    query = "UPDATE BookingRecord SET IsApproved = true WHERE BookingID = " + std::to_string(bookingID);

    // 9. ִ�и���
    // ʹ�� mysql_query ִ�� SQL �������
    if (mysql_query(&mysql, query.c_str())) {
        // �������ʧ�ܣ����������Ϣ������ false
        std::cout << "Error approving booking: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    // 10. ����ɹ���Ϣ������ true
    // ������³ɹ�������ɹ���Ϣ������ true
    std::cout << "Booking with ID " << bookingID << " approved successfully." << std::endl;
    return true;
}

// �鿴�Լ���Ԥ����¼

// ���ʱ��ͽ��ҳ�ͻ
bool CheckConflict(int roomID, const std::string& bookingDate) {
    // �������ݿ⣨ʡ�ԣ�
    // �����ѯ���
    std::string query = "SELECT * FROM BookingRecord WHERE RoomID = " + std::to_string(roomID) +
                        " AND BookingDate = '" + bookingDate + "'";
    // ִ�в�ѯ
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
        return true; // ��ѯ����Ĭ�Ϸ��س�ͻ��ʵ��Ӧ����������������
    }
    // ��ȡ�����
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return true; // ��ȡ�����ʧ��Ĭ�Ϸ��س�ͻ��ʵ��Ӧ����������������
    }
    // ����м�¼����ʾ��ͻ
    bool conflict = (mysql_num_rows(result) > 0);
    // �ͷŽ����
    mysql_free_result(result);
    // �ر����ݿ����ӣ�ʡ�ԣ�
    return conflict;
}
// �޸�Ԥ���Ľ��Һ�ʱ��
bool Teacher::ModifyBooking(int bookingID, int roomID, const std::string& bookingDate) {
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

// ����������
int main(){

    show();
    return 0;
//    NormalTeacher teacher;
//    teacher.teacher_register();
    return 0;
}