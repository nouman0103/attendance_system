#include "AttendanceRecord.h"

AttendanceRecord::AttendanceRecord(std::shared_ptr<Employee> employee, std::vector<AttendanceEntry> attendances)
    : attendances(attendances), employee(employee) {
}
void AttendanceRecord::addAttendance(AttendanceEntry attendance)
{
    attendances.push_back(attendance);
}

std::shared_ptr<Employee> AttendanceRecord::getEmployee() const
{
    return employee;
}

Attendance AttendanceRecord::getLastStatus() const
{
    return attendances.back().getType();
}