//
// Created by ����� on 24-6-26.
//
#include <iostream>
#include<string>

MYSQL mysql;
MYSQL_RES *res;//����ṹ�������е�һ����ѯ�����
MYSQL_ROW column;

#ifndef UNTITLED1_ROOM_H
#define UNTITLED1_ROOM_H

#endif //UNTITLED1_ROOM_H
using namespace std;
// �����������
//enum RoomType { LAB = 1, MULTIMEDIA = 2, RECORDING = 3 };


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
