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
    updateEmployees();
    readAttendanceRecord();
    // readLeaveBalance();
    readLeaveApplication();
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
        if (employee["role"] == "Guard")
        {
            Guard g(employee);
            employeeDict[g.getName()] = std::make_shared<Employee>(g);
            employees.push_back(g);
        }
        else
        {
            Employee e(employee);
            employeeDict[e.getName()] = std::make_shared<Employee>(e);
            employees.push_back(e);
        }
    }
    return;
}

std::shared_ptr<std::vector<Employee>> DataManager::getEmployees()
{
    return std::make_shared<std::vector<Employee>>(employees);
}

bool DataManager::setEmployee(std::shared_ptr<Employee> employee)
{
    currentEmployee = employee;
    if (currentEmployee)
        return true;
    return false;
}
std::shared_ptr<Employee> DataManager::getCurrentEmployee()
{
    return currentEmployee;
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
            AttendanceEntry a(employee.key(), attendance["type"], attendance["time"]);

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

void DataManager::writeLeaveApplication(std::shared_ptr<LeaveApplication> leaveApplication)
{
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    std::string name = leaveApplication.get()->getEmployee()->getName();
    json record = j[name];
    record["leave"].push_back(leaveApplication.get()->to_json());
    j[name] = record;
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
    leavesDict[name]->push_back(leaveApplication);
}

void DataManager::readLeaveApplication()
{
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

    for (auto &employee : j.items())
    {
        std::string name = employee.key();
        std::map<int, int> casualLeave;
        std::map<int, int> earnedLeave;
        std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaves = std::make_shared<std::vector<std::shared_ptr<LeaveApplication>>>();
        for (auto &leave : employee.value()["leave"])
        {
            if (leave["taskType"] == "Casual Leave")
            {
                std::shared_ptr<CasualLeaveApplication> a = std::make_shared<CasualLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                casualLeave[get_year(leave["startDate"].get<int>())] += ceil((leave["endDate"].get<int>() - leave["startDate"].get<int>()) / (24 * 60 * 60)) + 1;
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Earned Leave")
            {
                std::shared_ptr<EarnedLeaveApplication> a = std::make_shared<EarnedLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                earnedLeave[get_year(leave["startDate"].get<int>())] += ceil((leave["endDate"].get<int>() - leave["startDate"].get<int>()) / (24 * 60 * 60)) + 1;
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Official Leave")
            {
                std::shared_ptr<OfficialLeaveApplication> a = std::make_shared<OfficialLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                leaves->push_back(a);
            }
            else if (leave["taskType"] == "Unpaid Leave")
            {
                std::shared_ptr<UnpaidLeaveApplication> a = std::make_shared<UnpaidLeaveApplication>(
                    employeeDict[employee.key()], leave["startDate"], leave["endDate"], leave["reason"], leave["applicationDate"], leave["approvalDate"], leave["status"]);
                leaves->push_back(a);
            }
        }
        // leaveApplications.push_back(LeaveApplication(employeeDict[employee.key()], leaves));
        leavesDict[employee.key()] = leaves;
        employeeDict[employee.key()]->setLeaveApplication(leaves);
        leaveBalances[employee.key()] = std::make_shared<LeaveBalance>(casualLeave, earnedLeave);
    }
    return;
}
bool DataManager::updateLeaveApplication(std::shared_ptr<Employee> employee)
{
    std::ifstream read("record.json");
    json j;
    read >> j;
    read.close();
    std::string name = employee->getName();
    json record = j[name];
    record["leave"] = json::array();
    for (auto &leave : *employee->getLeaveApplications())
    {
        record["leave"].push_back(leave->to_json());
    }
    j[name] = record;
    std::ofstream write("record.json");
    write << j.dump(4);
    write.close();
    return true;
}

std::vector<std::shared_ptr<LeaveApplication>> DataManager::getAllLeaveApplications()
{
    std::vector<std::shared_ptr<LeaveApplication>> allLeaves;
    for (auto &employee : leavesDict)
    {
        for (auto &leave : *employee.second)
        {
            allLeaves.push_back(leave);
        }
    }
    return allLeaves;
}