#pragma once
#include "User.h"
#include "AttendanceRecord.h"
#include "LeaveApplication.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;

/*
class Employee {
    - String position
    - AttendanceRecord attendanceRecord
    - LeaveBalance leaveBalance
    + applyForLeave()
    + viewAttendance()
    + viewLeaveDetails()

}
User(std::string name, unsigned int id);
*/
class AttendanceRecord;
class LeaveApplication;

class Employee : public User
{
public:
    Employee(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<LeaveApplication>> leaveApplications);
    Employee(json j);
    Employee(const Employee &employee);
    virtual ~Employee();

    void applyForLeave();
    void viewAttendance();
    void viewLeaveDetails();
    void setLeaveApplication(std::shared_ptr<std::vector<LeaveApplication>> leaveApplications);
    std::shared_ptr<std::vector<LeaveApplication>> getLeaveApplications();
    void setPosition(std::string position);
    std::string getPosition();
    void setAttendanceRecord(std::shared_ptr<AttendanceRecord> attendanceRecord);
    std::shared_ptr<AttendanceRecord> getAttendanceRecord();
    friend std::ostream &operator<<(std::ostream &out, const Employee &employee);
    json to_json();

private:
    std::string position;
    std::shared_ptr<AttendanceRecord> attendanceRecord;
    std::shared_ptr<std::vector<LeaveApplication>> leaveApplications;
};
