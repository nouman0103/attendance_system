#pragma once
#include "Employee.h"
#include "AttendanceRecord.h"
#include "AttendanceEntry.h"
#include "LeaveApplication.h"
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
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>>> leavesDict;
    std::shared_ptr<Employee> currentEmployee;
    std::map<std::string,std::shared_ptr<LeaveBalance>> leaveBalances;


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
    void writeLeaveApplication(std::shared_ptr<LeaveApplication> leaveApplication);
    void readLeaveApplication();
    bool updateLeaveApplication(std::shared_ptr<Employee> employee);
    std::vector<std::shared_ptr<LeaveApplication>> getAllLeaveApplications();
    std::shared_ptr<LeaveBalance> getLeaveBalance(std::string name);
    
};

