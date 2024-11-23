#include "Superviser.h"
#include <memory>

Superviser::Superviser(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications) : Employee(name, id, password, position, attendanceRecord, leaveApplications)
{
}

Superviser::Superviser(json j) : Employee(j)
{
}

bool Superviser::ApproveApplication(std::shared_ptr<LeaveApplication> leave)
{
    return leave->approve(*this);
}

bool Superviser::RejectApplication(std::shared_ptr<LeaveApplication> leave)
{
    return leave->reject(*this);
}