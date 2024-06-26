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

void textMysql(string sql);//测试方法
bool ConnectMysql();//连接数据库
bool QueryDatabase(string sql);//查询并输出结果
void outMysql();//输出查询结果
bool updateData(string sql);//插入删除修改操作
void FreeConnect();//释放资源

//---------------这部分放源文件------------------------

MYSQL mysql;
MYSQL_RES *res;//这个结构代表返回行的一个查询结果集
MYSQL_ROW column;//一个行数据的类型安全(type-safe)的表示

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

// 定义教室类型
enum RoomType { LAB = 1, MULTIMEDIA = 2, RECORDING = 3 };

// 定义教室类
class Room {
protected:
    int roomNumber;//教室号
    string roomName;//教室名称
    int capacity;//容纳人数
    bool isOccupied;//当前占用状态
    //RoomType roomType;//教室类型类号
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    virtual void display() = 0; // pure virtual function
    friend ostream& operator<<(ostream& os, const Room& room);//“输出流”将room类信息输出到界面
    friend istream& operator>>(istream& is, Room& room);//“输入流”将信息输入到room类里
    void saveToFile(ofstream& file);//将room信息存入文件
    void loadFromFile(ifstream& file);//将room信息加载进界面
};
// display函数的主体实现
void Room::display() {
    cout << "Room roomNumber: " << roomNumber<< endl;
    cout<<"Room roomName: "<<roomName<<endl;
    //cout << "Room Type: " << roomType<< endl;
    cout << "Room capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}

// operator<<函数的主体实现
ostream& operator<<(ostream& os, const Room& room) {
    os << "Room roomNumber: " << room.roomNumber << endl;
    os<<"Room roomName: "<<room.roomName<<endl;
    // os << "Room Type: " << room.roomType << endl;
    os << "Room capacity: " << room.capacity << endl;
    os << "Is Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
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

// saveToFile函数的主体实现
void Room::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName<< endl;
    // file << roomType << endl;
    file << capacity<< endl;
    file<<isOccupied<<endl;
}

// loadFromFile函数的主体实现
void Room::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file >> roomName;
    //file >> roomType;
    file >> capacity;
    file >> isOccupied;
}


// 定义实验室类
class Lab : public Room {
    int labType;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const Lab& lab);//“输出流”将lab类信息输出到界面
    friend istream& operator>>(istream& is, Lab& lab);//“输入流”将信息输入到lab类里
    void saveToFile(ofstream& file);//将room信息存入文件
    void loadFromFile(ifstream& file);//将room信息加载进界面
    void setRoomNumber(int number) { roomNumber = number; }
    void setRoomName(const string& name) { roomName = name; }
    void setCapacity(int cap) { capacity = cap; }
    void setLabType(int type) { labType = type; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

};
// display函数的主体实现
void Lab::display() {
    cout << "Lab roomNumber: " << roomNumber << endl;
    cout<<"Lab roomName: "<<roomName<<endl;
    // cout << "Lab Type: " << labType << endl;
    cout << "Lab Capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}

// operator<<函数的主体实现
ostream& operator<<(ostream& os, const Lab& lab) {
    os << "Lab roomNumber: " << lab.roomNumber << endl;
    os<<"Lab roomName: "<<lab.roomName<<endl;
    //os << "Lab Type: " << lab.labType << endl;
    os << "Lab Capacity: " << lab.capacity << endl;
    os << "Is Occupied: " << (lab.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// operator>>函数的主体实现
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
// saveToFile函数的主体实现
void Lab::saveToFile(ofstream& file) {
    file << roomNumber<< endl;
    file << roomName << endl;
    //file << labType << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// loadFromFile函数的主体实现
void Lab::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file.ignore();
    getline(file, roomName);
    file >> capacity;
    file >> labType;
    file >> isOccupied;
}
// 定义多媒体教室类
class MultimediaRoom : public Room {
    int airConditioners;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const MultimediaRoom& room); // 输出流运算符
    friend istream& operator>>(istream& is, MultimediaRoom& room); // 输入流运算符
    void saveToFile(ofstream& file); // 将MultimediaRoom信息存入文件
    void loadFromFile(ifstream& file); // 将MultimediaRoom信息加载进界面
};
// 实现display函数
void MultimediaRoom::display() {
    cout << "Room Number: " << roomNumber << endl;
    cout << "Room Name: " << roomName << endl;
    cout << "Air Conditioners: " << airConditioners << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}
// 实现输出流运算符
ostream& operator<<(ostream& os, const MultimediaRoom& room) {
    os << "Room Number: " << room.roomNumber << endl;
    os << "Room Name: " << room.roomName << endl;
    os << "Air Conditioners: " << room.airConditioners << endl;
    os << "Capacity: " << room.capacity << endl;
    os << "Is Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// 实现输入流运算符
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
// 实现保存到文件函数
void MultimediaRoom::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName << endl;
    file << airConditioners << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// 实现从文件加载函数
void MultimediaRoom::loadFromFile(ifstream& file) {
    file >> roomNumber;
    file.ignore(); // 忽略换行符
    getline(file, roomName);
    file >> airConditioners;
    file >> capacity;
    file >> isOccupied;
}
// 定义录课教室类
class RecordingRoom : public Room {
    int cameras;
    // other attributes
public:
    // constructor, destructor, getters, setters, etc.
    //将RecordingRoom类信息加载进界面
    void display() override; // override the pure virtual function
    friend ostream& operator<<(ostream& os, const RecordingRoom& room);//“输出流”将RecordingRoom类信息输出到界面
    friend istream& operator>>(istream& is, RecordingRoom& room);//“输入流”将RecordingRoom类信息输出到界面
    void saveToFile(ofstream& file);//将RecordingRoom类信息存入文件
    void loadFromFile(ifstream& file);
};
// display函数的主体实现
void RecordingRoom::display() {
    cout << "Room Number: " << roomNumber << endl;
    cout << "Room Name: " << roomName << endl;
    cout << "Cameras: " << cameras << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Occupied: " << (isOccupied ? "Yes" : "No") << endl;
}
// operator<<函数的主体实现
ostream& operator<<(ostream& os, const RecordingRoom& room) {
    os << "Room Number: " << room.roomNumber << endl;
    os << "Room Name: " << room.roomName << endl;
    os << "Cameras: " << room.cameras << endl;
    os << "Capacity: " << room.capacity << endl;
    os << "Occupied: " << (room.isOccupied ? "Yes" : "No") << endl;
    return os;
}
// operator>>函数的主体实现
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
// saveToFile函数的主体实现
void RecordingRoom::saveToFile(ofstream& file) {
    file << roomNumber << endl;
    file << roomName << endl;
    file << cameras << endl;
    file << capacity << endl;
    file << isOccupied << endl;
}
// loadFromFile函数的主体实现
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
    int TeacherNumber; // 教师工号
    string TeacherName; // 教师姓名
    int PermissionLevel; // 权限等级
    string PhoneNumber; // 电话号码
    string OfficeName; // 办公室名称
private:
    string Password;//修正：吴培浩 时间：2024.6.26 00点54分
    // other attributes
public:
    // 构造函数、析构函数、getter、setter等
    virtual void display() const = 0; // 纯虚函数，强制子类实现
    virtual void saveToFile(ofstream& file) const = 0; // 虚函数
    virtual void loadFromFile(ifstream& file) = 0; // 虚函数
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

    bool ModifyBooking(int bookingID, int roomID, const string &bookingDate);
};
class NormalTeacher : public Teacher {
public:
    // 构造函数、析构函数、getter、setter等
    void display() const override; // 覆盖父类的纯虚函数
    void saveToFile(ofstream& file) const override; // 覆盖父类的虚函数
    void loadFromFile(ifstream& file) override; // 覆盖父类的虚函数
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
// saveToFile函数的实现
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

// loadFromFile函数的实现
void NormalTeacher::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By NormalTeacher" << endl;
        return;
    }
    file >> TeacherNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, TeacherName);
    file >> PermissionLevel;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, PhoneNumber);
    getline(file, OfficeName);

    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
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

// 获取用户输入的辅助函数
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
    void saveToFile(ofstream& file) const override; // 覆盖父类的虚函数
    void loadFromFile(ifstream& file) override; // 覆盖父类的虚函数

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
// saveToFile函数的实现
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
// loadFromFile函数的实现
void Admin::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By Admin" << endl;
        return;
    }
    file >> TeacherNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, TeacherName);
    file >> PermissionLevel;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, PhoneNumber);
    getline(file, OfficeName);
    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
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

//// 定义教室预订记录类
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
    void display() const; // 正确地声明 display 函数
};

void Reservation::display() const {
    cout << "Reservation Number: " << reservationNumber << endl;
    cout << "Submission Time: " << submissionTime << endl;
    cout << "Room Number: " << roomNumber << endl;
    cout << "Reservation Date: " << reservationDate << endl;
}

// operator<< 函数的实现
ostream& operator<<(ostream& os, const Reservation& reservation) {
    os << "Reservation Number: " << reservation.reservationNumber << endl;
    os << "Submission Time: " << reservation.submissionTime << endl;
    os << "Room Number: " << reservation.roomNumber << endl;
    os << "Reservation Date: " << reservation.reservationDate << endl;
    return os;
}
// operator>> 函数的实现
istream& operator>>(istream& is, Reservation& reservation) {
    cout << "Enter Reservation Number: ";
    is >> reservation.reservationNumber;
    is.ignore(); // 忽略换行符

    cout << "Enter Submission Time: ";
    getline(is, reservation.submissionTime);

    cout << "Enter Room Number: ";
    is >> reservation.roomNumber;
    is.ignore(); // 忽略换行符

    cout << "Enter Reservation Date: ";
    getline(is, reservation.reservationDate);

    return is;
}
// saveToFile 函数的实现
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
// loadFromFile 函数的实现
void Reservation::loadFromFile(ifstream& file) {
    if (!file) {
        cerr << "Error: File could not be opened for reading!By reservation" << endl;
        return;
    }
    file >> reservationNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, submissionTime);
    file >> roomNumber;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略行尾换行符
    getline(file, reservationDate);

    if (!file) {
        cerr << "Error: Failed to read from file!" << endl;
    }
}

void saveToFile(const string& filename, Lab lab, const NormalTeacher& teacher, const Reservation& reservation) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "无法打开文件 " << filename << " 进行写入." << endl;
        return;
    }

    try {
        lab.saveToFile(outfile);
        cout << "完成lab保存-->save" << endl;

        teacher.saveToFile(outfile);
        cout << "完成teacher保存-->save" << endl;

        reservation.saveToFile(outfile);
        cout << "完成reservation保存-->save" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    outfile.close();
}

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


bool Teacher:: teacher_enter() {
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
            if (cnt == 3) { cout << "错误次数已达上限，系统关闭！" << endl;return false; }
        }
    }
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

// 查看自己的预定记录

// 检查时间和教室冲突
bool CheckConflict(int roomID, const std::string& bookingDate) {
    // 连接数据库（省略）
    // 构造查询语句
    std::string query = "SELECT * FROM BookingRecord WHERE RoomID = " + std::to_string(roomID) +
                        " AND BookingDate = '" + bookingDate + "'";
    // 执行查询
    if (mysql_query(&mysql, query.c_str())) {
        std::cout << "Error querying bookings: " << mysql_error(&mysql) << std::endl;
        return true; // 查询出错默认返回冲突，实际应根据需求处理错误情况
    }
    // 获取结果集
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (!result) {
        std::cout << "Error retrieving result: " << mysql_error(&mysql) << std::endl;
        return true; // 获取结果集失败默认返回冲突，实际应根据需求处理错误情况
    }
    // 如果有记录，表示冲突
    bool conflict = (mysql_num_rows(result) > 0);
    // 释放结果集
    mysql_free_result(result);
    // 关闭数据库连接（省略）
    return conflict;
}
// 修改预定的教室和时间
bool Teacher::ModifyBooking(int bookingID, int roomID, const std::string& bookingDate) {
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

// 定义主函数
int main(){

    show();
    return 0;
//    NormalTeacher teacher;
//    teacher.teacher_register();
    return 0;
}