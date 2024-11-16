#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using json = nlohmann::json;

DataManager::DataManager()
{
    updateEmployees();
    // readAttendanceRecord();
    // readLeaveBalance();
}
bool DataManager::writeEmployee(Employee employee)
{
    //Check if employee already exists
    if (employeePassword.find(employee.getName()) != employeePassword.end())
    {
        return false;
    }
    std::ifstream read("employee.json");
    if (!read.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }
    json j;
    read >> j;
    read.close();

    json employeeJson = employee.to_json();
    int newID = j["count"].get<int>() + 1;
    employeeJson["id"] = newID;
    j["count"] = newID;
    j["employees"].push_back(employeeJson);
    employee.setID(newID);
    employees.push_back(employee);
    employeePassword[employee.getName()] = employeeJson["password"];


    std::ofstream write("employee.json");
    write << j.dump(4);
    write.close();
    return true;
}

void DataManager::updateEmployees()
{

    std::ifstream read;
    read.open("employee.json");
    // parse the json file
    json j;
    read >> j;
    read.close();
    for (json employee : j["employees"])
    {
        Employee e(employee);
        employeePassword[e.getName()] = employee["password"];
        employees.push_back(e);
    }
    return;
}

std::shared_ptr<std::vector<Employee>> DataManager::getEmployees()
{
    return std::make_shared<std::vector<Employee>>(employees);
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
