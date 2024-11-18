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
    readAttendanceRecord();
    // readLeaveBalance();
}
bool DataManager::writeEmployee(Employee employee)
{
    // Check if employee already exists
    if (employeeDict.find(employee.getName()) != employeeDict.end())
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
    employeeDict[employee.getName()] = std::make_shared<Employee>(employees.back());

    std::ofstream write("employee.json");
    write << j.dump(4);
    write.close();

    std::ifstream attendance("record.json");
    /*
    name: {
    attendance:[],
    leave:[]
    leaveBalance : number
    }
    */
    json record;
    attendance >> record;
    record[employee.getName()]["attendance"] = json::array();
    record[employee.getName()]["leave"] = json::array();
    record[employee.getName()]["leaveBalance"] = 0;
    attendance.close();

    std::ofstream writeAttendance("record.json");
    writeAttendance << record.dump(4);
    writeAttendance.close();

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
        employeeDict[e.getName()] = std::make_shared<Employee>(e);
        employees.push_back(e);
    }
    return;
}

std::shared_ptr<std::vector<Employee>> DataManager::getEmployees()
{
    return std::make_shared<std::vector<Employee>>(employees);
}


void DataManager::writeAttendanceRecord(AttendanceEntry attendanceEntry)
{
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    std::string name = attendanceEntry.getID();
    json record = j[name];
    record["attendance"].push_back(attendanceEntry.to_json());
    j[name] = record;
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
}

void DataManager::readAttendanceRecord()
{
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    
    for (auto &employee : j.items())
    {
        std::string name = employee.key();
        std::vector<AttendanceEntry> attendances;
        for (auto &attendance : employee.value()["attendance"])
        {
            AttendanceEntry a(attendance["id"], attendance["type"], attendance["time"]);
            
            attendances.push_back(a);
        }
        attendanceRecords.push_back(AttendanceRecord(employeeDict[employee.key()], attendances));
        employeeDict[employee.key()]->setAttendanceRecord(std::make_shared<AttendanceRecord>(attendanceRecords.back()));

        
        // attendanceRecords.push_back(record);
    }
}

std::shared_ptr<Employee> DataManager::getEmployee(std::string name)
{
    if (employeeDict.find(name) == employeeDict.end())
    {
        return nullptr;
    }
    return employeeDict[name];
}
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
