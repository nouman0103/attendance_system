#include "Employee.h"

Employee::Employee(std::string name, unsigned int id, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveBalance> leaveBalance)
    : User(name, id) {
    this->position = position;
    this->attendanceRecord = attendanceRecord;
    this->leaveBalance = leaveBalance;
}

Employee::~Employee() {
}

void Employee::applyForLeave() {
    // Implementation of leave application
}

void Employee::viewAttendance() {
    // Implementation to view attendance records
}

void Employee::viewLeaveDetails() {
    // Implementation to view leave details
}

void Employee::setLeaveBalance(std::shared_ptr<LeaveBalance> leaveBalance) {
    this->leaveBalance = leaveBalance;
}

std::shared_ptr<LeaveBalance> Employee::getLeaveBalance() {
    return leaveBalance;
}

void Employee::setPosition(std::string position) {
    this->position = position;
}

std::string Employee::getPosition() {
    return position;
}

void Employee::setAttendanceRecord(std::shared_ptr<AttendanceRecord> attendanceRecord) {
    this->attendanceRecord = attendanceRecord;
}

std::shared_ptr<AttendanceRecord> Employee::getAttendanceRecord() {
    return attendanceRecord;
}

void Employee::setEmployeeID(int employeeID) {
    this->employeeID = employeeID;
}

int Employee::getEmployeeID() {
    return employeeID;
}