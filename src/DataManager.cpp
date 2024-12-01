#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Guard.h"

using json = nlohmann::json;

DataManager::DataManager()
{
    // Read the employee data from the file
    updateEmployees();
    readAttendanceRecord();
    // readLeaveBalance();
    readLeaveApplication();
}
bool DataManager::writeEmployee(std::shared_ptr<Employee> employee)
{
    // Check if employee already exists
    if (employeeDict.find(employee->getName()) != employeeDict.end())
    {
        return false;
    }
    // read the json file
    std::ifstream read("employee.json");
    if (!read.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }
    json j;
    read >> j;
    read.close();
    // add the new employee to the json file

    json employeeJson = employee->to_json();
    int newID = j["count"].get<int>() + 1;
    employeeJson["id"] = newID;
    j["count"] = newID;
    j["employees"].push_back(employeeJson);
    employee->setID(newID);
    employees.push_back(*employee);
    employeeDict[employee->getName()] = employee;
    leaveBalances[employee->getName()] = std::make_shared<LeaveBalance>();
    leavesDict[employee->getName()] = employee->getLeaveApplications();
    // write the json file

    std::ofstream write("employee.json");
    write << j.dump(4);
    write.close();

    // Add the employee to the attendance record

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
    record[employee->getName()]["attendance"] = json::array();
    record[employee->getName()]["leave"] = json::array();
    record[employee->getName()]["leaveBalance"] = 0;
    attendance.close();

    // write the attendance record

    std::ofstream writeAttendance("record.json");
    writeAttendance << record.dump(4);
    writeAttendance.close();

    return true;
}

void DataManager::updateEmployees()
{
    // read the json file
    std::ifstream read;
    read.open("employee.json");
    // parse the json file
    json j;
    read >> j;
    read.close();
    // iterate over the employees
    for (json employee : j["employees"])
    {
        // create the employee object
        if (employee["role"] == "Guard")
        {
            // create the guard object
            Guard g(employee);
            employeeDict[g.getName()] = std::make_shared<Employee>(g);
            // add the employee to the list
            employees.push_back(g);
        }
        else
        {
            // create the employee object
            Employee e(employee);
            employeeDict[e.getName()] = std::make_shared<Employee>(e);
            // add the employee to the list
            employees.push_back(e);
        }
    }
    return;
}

std::shared_ptr<std::vector<Employee>> DataManager::getEmployees()
{
    // return the list of employees
    return std::make_shared<std::vector<Employee>>(employees);
}

bool DataManager::setEmployee(std::shared_ptr<Employee> employee)
{
    // set the current employee
    currentEmployee = employee;
    if (currentEmployee)
        return true;
    return false;
}
std::shared_ptr<Employee> DataManager::getCurrentEmployee()
{
    // return the current employee
    return currentEmployee;
}

void DataManager::writeAttendanceRecord(AttendanceEntry attendanceEntry)
{
    // read the json file
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    // add the attendance to the json file
    std::string name = attendanceEntry.getID();
    json record = j[name];
    record["attendance"].push_back(attendanceEntry.to_json());
    j[name] = record;
    // write the json file
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
}

void DataManager::readAttendanceRecord()
{
    // read the json file
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    // iterate over the employees
    for (auto &employee : j.items())
    {
        // create the attendance record object
        std::string name = employee.key();
        std::vector<AttendanceEntry> attendances;
        for (auto &attendance : employee.value()["attendance"])
        {
            // create the attendance entry object
            AttendanceEntry a(employee.key(), attendance["type"], attendance["time"]);
            attendances.push_back(a);
        }
        // add the attendance record to the list
        std::shared_ptr<AttendanceRecord> record = std::make_shared<AttendanceRecord>(employeeDict[employee.key()], attendances);
        employeeDict[employee.key()]->setAttendanceRecord(record);

        // attendanceRecords.push_back(record);
    }
}

std::shared_ptr<Employee> DataManager::getEmployee(std::string name)
{
    // return the employee object
    if (employeeDict.find(name) == employeeDict.end())
    {
        return nullptr;
    }
    return employeeDict[name];
}

void DataManager::writeLeaveApplication(std::shared_ptr<LeaveApplication> leaveApplication)
{
    // read the json file
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    // add the leave application to the json file
    std::string name = leaveApplication.get()->getEmployee()->getName();
    json record = j[name];
    record["leave"].push_back(leaveApplication.get()->to_json());
    j[name] = record;
    // write the json file
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
    // add the leave application to the list
    leavesDict[name]->push_back(leaveApplication);
}

void DataManager::readLeaveApplication()
{
    // read the json file
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    /* {
                "applicationDate": 1732213029,
                "approvalDate": 0,
                "endDate": 1732215600,
                "reason": "123",
                "startDate": 1732129200,
                "status": 0,
                "taskType": "Casual Leave"
            },*/

    // iterate over the employees
    for (auto &employee : j.items())
    {
        // create the leave application object
        std::string name = employee.key();
        std::map<int, int> casualLeave;
        std::map<int, int> earnedLeave;
        std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaves = std::make_shared<std::vector<std::shared_ptr<LeaveApplication>>>();
        // Iterate over the leaves
        for (auto &leave : employee.value()["leave"])
        {
            // create the leave application object
            if (leave["taskType"] == "Casual Leave")
            {
                // add the leave application to the list
                std::shared_ptr<CasualLeaveApplication> a = std::make_shared<CasualLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                casualLeave[get_year(leave["startDate"].get<int>())] += ceil((leave["endDate"].get<int>() - leave["startDate"].get<int>()) / (24 * 60 * 60)) + 1;
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Earned Leave")
            {
                // add the leave application to the list
                std::shared_ptr<EarnedLeaveApplication> a = std::make_shared<EarnedLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                earnedLeave[get_year(leave["startDate"].get<int>())] += ceil((leave["endDate"].get<int>() - leave["startDate"].get<int>()) / (24 * 60 * 60)) + 1;
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Official Leave")
            {
                // add the leave application to the list
                std::shared_ptr<OfficialLeaveApplication> a = std::make_shared<OfficialLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Unpaid Leave")
            {
                // add the leave application to the list
                std::shared_ptr<UnpaidLeaveApplication> a = std::make_shared<UnpaidLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                leaves->push_back(a);
            }
        }
        // add the leave application to the list
        leavesDict[employee.key()] = leaves;
        employeeDict[employee.key()]->setLeaveApplication(leaves);
        leaveBalances[employee.key()] = std::make_shared<LeaveBalance>(casualLeave, earnedLeave);
    }
    return;
}
bool DataManager::updateLeaveApplication(std::shared_ptr<Employee> employee)
{
    // read the json file
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    // add the leave application to the json file
    std::string name = employee->getName();
    json record = j[name];
    record["leave"] = json::array();
    // Iterate over the leaves
    for (auto &leave : *employee->getLeaveApplications())
    {
        // create the leave application object
        record["leave"].push_back(leave->to_json());
    }
    // write the json file
    j[name] = record;
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
    return true;
}

std::vector<std::shared_ptr<LeaveApplication>> DataManager::getAllLeaveApplications()
{
    // return the list of leave applications
    std::vector<std::shared_ptr<LeaveApplication>> allLeaves;
    for (auto &employee : leavesDict)
    {
        // create the leave application object
        for (auto &leave : *employee.second)
        {
            allLeaves.push_back(leave);
        }
    }
    return allLeaves;
}

std::shared_ptr<LeaveBalance> DataManager::getLeaveBalance(std::string name)
{
    // return the leave balance object
    return leaveBalances[name];
}