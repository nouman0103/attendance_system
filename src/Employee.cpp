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
        
    }
    //Multiply by 8 to get hours of leave
    leaveCount["Official Leave"] *= 8;
    leaveCount["Casual Leave"] *= 8;
    leaveCount["Earned Leave"] *= 8;
    leaveCount["Unpaid Leave"] *= 8;
    return leaveCount;
}

std::map<std::string,int> Employee::getLeaveInMonth(time_t monthstart) {
    //Get the end of the month
    monthstart = get_start_of_month(monthstart);
    time_t monthend = get_end_of_month(monthstart);

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
        if (leaveApplication->getStartDate() >= monthstart && leaveApplication->getEndDate() < monthend) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((leaveApplication->getEndDate() - leaveApplication->getStartDate()) / (24 * 60 * 60)) + 1;

        }
        else if (leaveApplication->getStartDate() < monthstart && leaveApplication->getEndDate() > monthend) {
            //Count the number of days
            leaveCount[leaveApplication->getTaskType()] += ceil((monthend - leaveApplication->getStartDate()) / (24 * 60 * 60)) + 1;
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


int Employee::getAttendancePercentage(int month, int year){
    std::tm time_in = {0, 0, 0, 1, month - 1, year - 1900};
    time_t monthstart = get_start_of_month(std::mktime(&time_in));
    time_t monthend = get_end_of_month(monthstart);
    int total_work_days = attendanceRecord->getHourWorkInMonth(monthstart) / 8;
    int total_days = (monthend - monthstart) / (24 * 60 * 60);
    int weekends = 0;

    for (time_t t = monthstart; t < monthend; t += 24 * 60 * 60) {
        std::tm* time_info = std::localtime(&t);
        if (time_info->tm_wday == 0 || time_info->tm_wday == 6) {
            weekends++;
        }
    }

    // account for leaves
    std::map<std::string, int> leaveCount = getLeaveInMonth(monthstart);
    total_work_days += leaveCount["Casual Leave"] / 8;
    total_work_days += leaveCount["Earned Leave"] / 8;
    total_work_days += leaveCount["Official Leave"] / 8;
    total_work_days += leaveCount["Unpaid Leave"] / 8;

    return (total_work_days * 100) / (total_days - weekends);
}

int Employee::getPendingLeaves(time_t monthstart) {
    int count = 0;
    monthstart = get_start_of_month(monthstart);
    time_t monthend = get_end_of_month(monthstart);
    for (std::shared_ptr<LeaveApplication> leaveApplication : *leaveApplications) {
        if (leaveApplication->getStatus() == LeaveStatus::PENDING && leaveApplication->getStartDate() >= monthstart && leaveApplication->getEndDate() < monthend) {
            count++;
        }
    }
    return count;
}