#pragma once
#include "User.h"
#include "AttendanceRecord.h"
#include "LeaveBalance.h"
#include <memory>
#include <iostream>
#include <string>
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
    ~Employee();
    void applyForLeave();
    void viewAttendance();
    void viewLeaveDetails();
    void setLeaveBalance(std::shared_ptr<LeaveBalance> leaveBalance);
    std::shared_ptr<LeaveBalance>  getLeaveBalance();
    void setPosition(string position);
    string getPosition();
    void setAttendanceRecord(std::shared_ptr<AttendanceRecord> attendanceRecord);
    std::shared_ptr<AttendanceRecord> getAttendanceRecord();
    void setEmployeeID(int employeeID);
    int getEmployeeID();

private:
    std::string position;
    std::shared_ptr<AttendanceRecord> attendanceRecord;
    std::shared_ptr<LeaveBalance>  leaveBalance;
    int employeeID;
};
