//
// Created by 吴培浩 on 24-6-26.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

#ifndef UNTITLED1_RESERVATION_H
#define UNTITLED1_RESERVATION_H

#endif //UNTITLED1_RESERVATION_H
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
