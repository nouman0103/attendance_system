#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <ctime> // Import the ctime library
using json = nlohmann::json;
enum class Attendance { CHECK_IN, CHECK_OUT,NONE };
class AttendanceEntry {
public:
    AttendanceEntry(std::string id, Attendance type, time_t time);
    std::string getID() const;
    Attendance getType() const;
    std::string getTime() const;
    time_t getTimestamp() const;
    void print() const;
    json to_json() const;
private:
    std::string id;
    Attendance type;
    time_t time;
};