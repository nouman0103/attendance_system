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
    Employee(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications);
    Employee(json j);
    Employee(const Employee &employee);
    virtual ~Employee();

    void applyForLeave();
    void viewAttendance();
    void viewLeaveDetails();
    void setLeaveApplication(std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications);
    std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> getLeaveApplications();
    void setPosition(std::string position);
    std::string getPosition();
    void setAttendanceRecord(std::shared_ptr<AttendanceRecord> attendanceRecord);
    std::shared_ptr<AttendanceRecord> getAttendanceRecord();
    int getAttendancePercentage(int month, int year);
    friend std::ostream &operator<<(std::ostream &out, const Employee &employee);
    json to_json();
    std::map<std::string,int> getLeaveInWeek(time_t weekstart);
    std::map<std::string,int> getLeaveInMonth(time_t monthstart);
    int getPendingLeaves(time_t monthstart);


private:
    std::string position;
    std::shared_ptr<AttendanceRecord> attendanceRecord;
    std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications;
};
