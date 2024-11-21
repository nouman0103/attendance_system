#pragma once
#include "Employee.h"
#include "AttendanceRecord.h"
#include "AttendanceEntry.h"
#include "LeaveBalance.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
class DataManager
{
private:
    std::ofstream write;
    std::ifstream read;
    std::vector<Employee> employees;
    // Dictory of employees id and password
    std::map<std::string, std::shared_ptr<Employee>> employeeDict;
    std::vector<AttendanceRecord> attendanceRecords;
    std::shared_ptr<Employee> currentEmployee;

    // std::vector<LeaveBalance> leaveBalances;

public:
    DataManager();
    bool writeEmployee(Employee employee);
    void updateEmployees();
    bool setEmployee(std::shared_ptr<Employee> employee);
    std::shared_ptr<Employee> getCurrentEmployee();
    std::shared_ptr<std::vector<Employee>> getEmployees();

    std::shared_ptr<Employee> getEmployee(std::string name);
    void writeAttendanceRecord(AttendanceEntry attendanceEntry);
    void readAttendanceRecord();
    // void writeLeaveBalance(LeaveBalance leaveBalance);
    // std::vector<LeaveBalance> readLeaveBalance();
    // void writeGuard(Guard guard);
    // std::vector<Guard> readGuard();
    // void writeSupervisor(Supervisor supervisor);
    // std::vector<Supervisor> readSupervisor();
    // void writeDirector(Director director);
    // std::vector<Director> readDirector();
    // void writeAttendance(Attendance attendance);
    // std::vector<Attendance> readAttendance();
    // void writeLeave(Leave leave);
    // std::vector<Leave> readLeave();
};
;
