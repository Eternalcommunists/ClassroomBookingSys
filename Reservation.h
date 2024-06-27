//
// Created by Œ‚≈‡∫∆ on 24-6-26.
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


};

