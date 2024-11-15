#pragma once
#include "User.h"
#include "AttendanceRecord.h"
#include "LeaveBalance.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


class Employee : public User
{
public:
    Employee(std::string name, unsigned int id, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveBalance>  leaveBalance);
    Employee(std::vector<std::string> in);
    ~Employee();
    void applyForLeave();
    void viewAttendance();
    void viewLeaveDetails();
    void setLeaveBalance(std::shared_ptr<LeaveBalance> leaveBalance);
    std::shared_ptr<LeaveBalance>  getLeaveBalance();
    void setPosition(std::string position);
    std::string getPosition();
    void setAttendanceRecord(std::shared_ptr<AttendanceRecord> attendanceRecord);
    std::shared_ptr<AttendanceRecord> getAttendanceRecord();
    friend std::ostream &operator<<(std::ostream &out, const Employee &employee);

private:
    std::string position;
    std::shared_ptr<AttendanceRecord> attendanceRecord;
    std::shared_ptr<LeaveBalance>  leaveBalance;
};
