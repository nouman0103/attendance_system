#pragma once
#include "Employee.h"
#include "AttendanceRecord.h"
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
    //Dictory of employees id and password
    std::map<std::string,std::string> employeePassword;
    // std::vector<AttendanceRecord> attendanceRecords;
    // std::vector<LeaveBalance> leaveBalances;

public:
    DataManager();
    bool writeEmployee(Employee employee);
    void updateEmployees();
    std::shared_ptr<std::vector<Employee>> getEmployees();
    

    // void writeAttendanceRecord(AttendanceRecord attendanceRecord);
    // std::vector<AttendanceRecord> readAttendanceRecord();
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
};;
