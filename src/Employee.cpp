#include "Employee.h"

Employee::Employee(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<LeaveApplication>> leaveApplications)
    : User(name, id,password) {
    this->position = position;
    this->attendanceRecord = attendanceRecord;
    this->leaveApplications = leaveApplications;
}

Employee::Employee(json j) : User(j)
 {
    this->position = j["position"];
    this->attendanceRecord = nullptr;
    this->leaveApplications = nullptr;
}
Employee::Employee(const Employee &employee) : User(employee) {
    this->position = employee.position;
    this->attendanceRecord = employee.attendanceRecord;
    this->leaveApplications = employee.leaveApplications;
}

Employee::~Employee()
{
    // Destructor implementation
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

void Employee::setLeaveApplication(std::shared_ptr<std::vector<LeaveApplication>> leaveApplications) {
    this->leaveApplications = leaveApplications;
}

std::shared_ptr<std::vector<LeaveApplication>> Employee::getLeaveApplications()
{
    return leaveApplications;
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
