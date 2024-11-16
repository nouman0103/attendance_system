#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

DataManager::DataManager()
{
    readEmployee();
}
void DataManager::writeEmployee(Employee employee)
{
    write.open("employee.txt", std::ios::app);
    write << employee << std::endl;
    write.close();
    employees.push_back(employee);
}

void DataManager::readEmployee()
{
    read.open("employee.txt");
    if (!read.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(read, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token)
        {
            tokens.push_back(token);
        }
        // Process tokens as needed
        Employee employee(tokens);
        employeePassword[employee.getID()] = tokens[3];
        employees.push_back(employee);
    }
    return;
}

std::shared_ptr<std::vector<Employee>> DataManager::getEmployees()
{
    return std::make_shared<std::vector<Employee>>(employees);
}
std::string DataManager::getPassword(int id)
{
    return employeePassword[id];
}
// void DataManager::writeAttendanceRecord(AttendanceRecord attendanceRecord)
// {
//     write.open("attendanceRecord.txt", std::ios::app);
//     write << attendanceRecord;
//     write.close();
// }

// std::vector<AttendanceRecord> DataManager::readAttendanceRecord()
// {
//     std::vector<AttendanceRecord> attendanceRecords;
//     read.open("attendanceRecord.txt");
//     if (read.is_open())
//     {
//         while (!read.eof())
//         {
//             AttendanceRecord attendanceRecord;
//             read >> attendanceRecord;
//             attendanceRecords.push_back(attendanceRecord);
//         }
//         read.close();
//     }
//     return attendanceRecords;
// }

// void DataManager::writeLeaveBalance(LeaveBalance leaveBalance)
// {
//     write.open("leaveBalance.txt", std::ios::app);
//     write << leaveBalance;
//     write.close();
// }

// std::vector<LeaveBalance> DataManager::readLeaveBalance()
// {
//     std::vector<LeaveBalance> leaveBalances;
//     read.open("leaveBalance.txt");
//     if (read.is_open())
//     {
//         while (!read.eof())
//         {
//             LeaveBalance leaveBalance;
//             read >> leaveBalance;
//             leaveBalances.push_back(leaveBalance);
//         }
//         read.close();
//     }
//     return leaveBalances;
// }
