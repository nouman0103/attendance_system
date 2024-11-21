#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Employee.h"
#include <ctime>

enum class LeaveStatus
{
    PENDING,
    APPROVED,
    REJECTED
};
class Employee;
class LeaveApplication
{
protected:
    std::shared_ptr<Employee> employee;
    time_t startDate;
    time_t endDate;
    std::string reason;
    time_t applicationDate;
    time_t approvalDate;
    LeaveStatus status;

public:
    LeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    LeaveApplication(json j);
    std::shared_ptr<Employee> getEmployee();
    time_t getStartDate();
    time_t getEndDate();
    std::string getReason();
    time_t getApplicationDate();
    time_t getApprovalDate();
    LeaveStatus getStatus();
    
    virtual json  to_json() = 0;
    virtual bool approve(std::shared_ptr<Employee> approver) = 0;
    virtual bool reject(std::shared_ptr<Employee> approver) = 0;
    virtual std::string getTaskType() = 0;
};



class OfficialLeaveApplication : public LeaveApplication
{
public:
    OfficialLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    OfficialLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    json to_json() override;
    std::string getTaskType() override;
};

class CasualLeaveApplication : public LeaveApplication
{
public:
    CasualLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    CasualLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    json to_json() override;
    std::string getTaskType() override;
};

class UnpaidLeaveApplication : public LeaveApplication
{
public:
    UnpaidLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    UnpaidLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    json to_json() override;
    std::string getTaskType() override;
};

class EarnedLeaveApplication : public LeaveApplication
{
public:
    EarnedLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    EarnedLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    json to_json() override;
    std::string getTaskType() override;
};