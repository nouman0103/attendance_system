#include "Employee.h"

class Superviser : public Employee
{
    Superviser(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications);
    Superviser(json j);
    bool ApproveApplication(
        std::shared_ptr<LeaveApplication> leave);
    
    bool RejectApplication(
        std::shared_ptr<LeaveApplication> leave
    );
    // vector<LeaveApplication> viewLeaveApplications(std::shared_ptr<DataManager> dataManager);

};