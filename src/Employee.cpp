#include "Employee.h"

Employee::Employee(std::string name, unsigned int id,std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveBalance> leaveBalance)
    : User(name, id,password) {
    this->position = position;
    this->attendanceRecord = attendanceRecord;
    this->leaveBalance = leaveBalance;
}

Employee::Employee(json j) : User(j)
 {
    this->position = j["position"];
    this->attendanceRecord = nullptr;
    this->leaveBalance = nullptr;
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

std::ostream &operator<<(std::ostream &out, const Employee &employee) {
    
    out << dynamic_cast<const User &>(employee) << " " << employee.position;

    
    return out;
}


json Employee::to_json() {
    json j = User::to_json();
    j["position"] = position;
    return j;
}