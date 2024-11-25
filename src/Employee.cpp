#include "Employee.h"

Employee::Employee(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications)
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

void Employee::setLeaveApplication(std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications) {
    this->leaveApplications = leaveApplications;
}

std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> Employee::getLeaveApplications()
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

std::map<std::string,int> Employee::getLeaveInWeek(time_t weekstart) {
    int count = 0;
    time_t weekend = weekstart + 7 * 24 * 60 * 60;
    std::map<std::string,int> leaveCount;
    leaveCount["Official Leave"] = 0;
    leaveCount["Casual Leave"] = 0;
    leaveCount["Earned Leave"] = 0;
    leaveCount["Unpaid Leave"] = 0;
    for (std::shared_ptr<LeaveApplication> leaveApplication : *leaveApplications) {
        if (leaveApplication->getStatus() != LeaveStatus::APPROVED)
        {
            continue;
        }
        if (leaveApplication->getStartDate() >= weekstart && leaveApplication->getEndDate() < weekend) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((leaveApplication->getEndDate() - leaveApplication->getStartDate()) / (24 * 60 * 60)) + 1;
        }
        else if (leaveApplication->getStartDate() >= weekstart && leaveApplication->getEndDate() > weekend) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((leaveApplication->getStartDate() - weekend) / (24 * 60 * 60)) +1;
        }
    }
    //Multiply by 8 to get hours of leave
    leaveCount["Official Leave"] *= 8;
    leaveCount["Casual Leave"] *= 8;
    leaveCount["Earned Leave"] *= 8;
    leaveCount["Unpaid Leave"] *= 8;
    return leaveCount;
}
std::map<std::string,int> Employee::getLeaveInMonth(time_t monthstart) {
    int count = 0;
    std::map<std::string,int> leaveCount;
    leaveCount["Official Leave"] = 0;
    leaveCount["Casual Leave"] = 0;
    leaveCount["Earned Leave"] = 0;
    leaveCount["Unpaid Leave"] = 0;
    for (std::shared_ptr<LeaveApplication> leaveApplication : *leaveApplications) {
        if (leaveApplication->getStatus() != LeaveStatus::APPROVED)
        {
            continue;
        }
        if (leaveApplication->getStartDate() >= monthstart && leaveApplication->getEndDate() < monthstart + 30 * 24 * 60 * 60) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((leaveApplication->getEndDate() - leaveApplication->getStartDate()) / (24 * 60 * 60)) + 1;

        }
        else if (leaveApplication->getStartDate() < monthstart && leaveApplication->getEndDate() > monthstart + 30 * 24 * 60 * 60) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((monthstart + 30 * 24 * 60 * 60 - leaveApplication->getStartDate()) / (24 * 60 * 60)) + 1;
        }
    }

    //Multiply by 8 to get hours of leave
    leaveCount["Official Leave"] *= 8;
    leaveCount["Casual Leave"] *= 8;
    leaveCount["Earned Leave"] *= 8;
    leaveCount["Unpaid Leave"] *= 8;
    return leaveCount;
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
