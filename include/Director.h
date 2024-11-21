#include "Employee.h"
#include "DataManager.h"


class Director : public Employee
{
    Director(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveApplication> leaveBalance);
    Director(json j);
    bool ApproveApplication(LeaveApplication& leave);
    bool RejectApplication(LeaveApplication& leave);
    // vector<LeaveApplication> viewLeaveApplications(std::shared_ptr<DataManager> dataManager);

};