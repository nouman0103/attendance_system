#include "Employee.h"

class Director : public Employee
{
    Director(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveApplication> leaveBalance);
    Director(json j);
    bool ApproveApplication(LeaveApplication& leave);

};