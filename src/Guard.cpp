#include "Guard.h"

Guard::Guard(std::string name, unsigned int id, std::string password, std::string position, std::shared_ptr<AttendanceRecord> attendanceRecord, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications)
    : Employee(name, id, password, position, attendanceRecord, leaveApplications)
{
    // Constructor for Guard
}
Guard::Guard(Employee employee) : Employee(employee)
{
    // Constructor for Guard from Employee
}
Guard::Guard(json j) : Employee(j)
{
    // Constructor for Guard from json
}

Guard::~Guard()
{
    // Destructor implementation
}

bool Guard::markAttendance(std::shared_ptr<Employee> employee, AttendanceEntry entry)

{
    // markAttendance: Mark the attendance of an employee
    if (employee == nullptr)
    {
        return false;
    }
    // Check if the employee is the same as the one being marked
    if (employee->getName() != entry.getID())
    {
        return false;
    }

    // Get the attendance record of the employee
    std::shared_ptr<AttendanceRecord> record = employee->getAttendanceRecord();
    if (record == nullptr)
    {
        return false;
    }   
    // Check if the employee is already checked in or checked out
    if (record.get()->getLastStatus() == Attendance::CHECK_IN && entry.getType() == Attendance::CHECK_IN)
    {
        return false;
    }
    // Check if the employee is already checked in or checked out
    if (record.get()->getLastStatus() == Attendance::CHECK_OUT && entry.getType() == Attendance::CHECK_OUT)
    {
        return false;
    }
    // check if check out time is before check in time
    if (record.get()->getLastStatus() == Attendance::CHECK_IN && entry.getType() == Attendance::CHECK_OUT)
    {
        if (record.get()->getLastTime() > entry.getTimestamp())
        {
            return false;
        }
    }
    // Add the entry to the attendance record
    record.get()->addAttendance(entry);

    return true;
}