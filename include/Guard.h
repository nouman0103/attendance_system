#include "Employee.h"

class Guard : public Employee
{
public:
    Guard(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<LeaveApplication> leaveBalance);
    Guard(Employee employee);
    Guard(json j);
    bool markAttendance(std::shared_ptr<Employee> employee,AttendanceEntry entry);
    ~Guard();

private:
};
