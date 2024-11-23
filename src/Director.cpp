#include "Director.h"

Director::Director(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications) : Employee(name, id, password, position, attendanceRecord, leaveApplications)
{
}

Director::Director(json j) : Employee(j)
{
}

bool Director::ApproveApplication(std::shared_ptr<LeaveApplication> leave)
{
    return leave->approve(shared_from_this());
}

bool Director::RejectApplication(std::shared_ptr<LeaveApplication> leave)
{
    return leave->reject(shared_from_this());
}