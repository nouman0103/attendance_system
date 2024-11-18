#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <ctime> // Import the ctime library
enum class Attendance { CHECK_IN, CHECK_OUT };
class AttendanceEntry {
public:
    AttendanceEntry(std::string id, Attendance type, time_t time);
    std::string getID() const;
    Attendance getType() const;
    std::string getTime() const;
    void print() const;
private:
    std::string id;
    Attendance type;
    time_t time;
};