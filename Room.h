//
// Created by 吴培浩 on 24-6-26.
//
#include <iostream>
#include<string>

MYSQL mysql;
MYSQL_RES *res;//这个结构代表返回行的一个查询结果集
MYSQL_ROW column;

#ifndef UNTITLED1_ROOM_H
#define UNTITLED1_ROOM_H

#endif //UNTITLED1_ROOM_H
using namespace std;
// 定义教室类型
//enum RoomType { LAB = 1, MULTIMEDIA = 2, RECORDING = 3 };


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
