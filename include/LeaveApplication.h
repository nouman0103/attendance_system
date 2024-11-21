#pragma once
#include <memory>
#include <string>
#include <vector>
#include <ctime>
enum class LeaveStatus
{
    PENDING,
    APPROVED,
    REJECTED
};
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
    std::string getTaskType() override;
};

class CasualLeaveApplication : public LeaveApplication
{
public:
    CasualLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    CasualLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    std::string getTaskType() override;
};

class UnpaidLeaveApplication : public LeaveApplication
{
public:
    UnpaidLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    UnpaidLeaveApplication(json j);
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    std::string getTaskType() override;
};

class EarnedLeaveApplication : public LeaveApplication
{
public:
    EarnedLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status);
    EarnedLeaveApplication(json j);
    bool applyForApproval(std::shared_ptr<Employee> approver) override;
    bool approve(std::shared_ptr<Employee> approver) override;
    bool reject(std::shared_ptr<Employee> approver) override;
    std::string getTaskType() override;
};