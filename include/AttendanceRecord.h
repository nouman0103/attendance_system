#pragma once
#include <vector>
#include <string>
#include "AttendanceEntry.h"
#include "Employee.h"
#include <memory>
class Employee;
class AttendanceRecord
{
public:
    AttendanceRecord(std::shared_ptr<Employee> employee, std::vector<AttendanceEntry> attendances);
    void addAttendance(AttendanceEntry attendance);
    std::shared_ptr<Employee> getEmployee() const;
    std::vector<AttendanceEntry> getAttendances() const;
    Attendance getLastStatus() const;

private:
    std::vector<AttendanceEntry> attendances;
    std::shared_ptr<Employee> employee;
};