#include "LeaveApplication.h"

LeaveApplication::LeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status)
{
    // Constructor for LeaveApplication
    this->employee = employee;
    this->startDate = startDate;
    this->endDate = endDate;
    this->reason = reason;
    this->applicationDate = applicationDate;
    this->approvalDate = approvalDate;
    this->status = status;
}

LeaveApplication::LeaveApplication(json j)
{
    // Constructor for LeaveApplication from json
    this->employee = std::make_shared<Employee>(j["employee"]);
    this->startDate = j["startDate"];
    this->endDate = j["endDate"];
    this->reason = j["reason"];
    this->applicationDate = j["applicationDate"];
    this->approvalDate = j["approvalDate"];
    this->status = j["status"];
}


time_t LeaveApplication::getStartDate()
{
    // getStartDate: Get the start date of the leave application
    return this->startDate;
}

time_t LeaveApplication::getEndDate()
{
    // getEndDate: Get the end date of the leave application
    return this->endDate;
}

std::string LeaveApplication::getReason()
{
    // getReason: Get the reason for the leave application
    return this->reason;
}

time_t LeaveApplication::getApplicationDate()
{
    // getApplicationDate: Get the application date of the leave application
    return this->applicationDate;
}

time_t LeaveApplication::getApprovalDate()
{
    // getApprovalDate: Get the approval date of the leave application
    return this->approvalDate;
}

LeaveStatus LeaveApplication::getStatus()
{
    // getStatus: Get the status of the leave application
    return this->status;
}

std::shared_ptr<Employee> LeaveApplication::getEmployee()
{
    // getEmployee: Get the employee of the leave application
    return this->employee;
}

OfficialLeaveApplication::OfficialLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
    // Constructor for OfficialLeaveApplication
}

OfficialLeaveApplication::OfficialLeaveApplication(json j) : LeaveApplication(j)
{
    // Constructor for OfficialLeaveApplication from json
}

json CasualLeaveApplication::to_json()
{
    // to_json: Convert CasualLeaveApplication to json
    json j;
    j["startDate"] = this->startDate;
    j["endDate"] = this->endDate;
    j["reason"] = this->reason;
    j["applicationDate"] = this->applicationDate;
    j["approvalDate"] = this->approvalDate;
    j["status"] = this->status;
    j["taskType"] = this->getTaskType();
    return j;
}

json OfficialLeaveApplication::to_json()
{
    // to_json: Convert OfficialLeaveApplication to json
    json j;
    j["startDate"] = this->startDate;
    j["endDate"] = this->endDate;
    j["reason"] = this->reason;
    j["applicationDate"] = this->applicationDate;
    j["approvalDate"] = this->approvalDate;
    j["status"] = this->status;
    j["taskType"] = this->getTaskType();
    return j;
}
json UnpaidLeaveApplication::to_json()
{
    // to_json: Convert UnpaidLeaveApplication to json
    json j;
    j["startDate"] = this->startDate;
    j["endDate"] = this->endDate;
    j["reason"] = this->reason;
    j["applicationDate"] = this->applicationDate;
    j["approvalDate"] = this->approvalDate;
    j["status"] = this->status;
    j["taskType"] = this->getTaskType();
    return j;
}
json EarnedLeaveApplication::to_json()
{
    // to_json: Convert EarnedLeaveApplication to json
    json j;
    j["startDate"] = this->startDate;
    j["endDate"] = this->endDate;
    j["reason"] = this->reason;
    j["applicationDate"] = this->applicationDate;
    j["approvalDate"] = this->approvalDate;
    j["status"] = this->status;
    j["taskType"] = this->getTaskType();
    return j;
}


bool OfficialLeaveApplication::approve(Employee approver)
{
    // approve: Approve the leave application
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    // Check if the leave application is already rejected
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool OfficialLeaveApplication::reject(Employee approver)
{
    // reject: Reject the leave application
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    // Check if the leave application is already approved
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string OfficialLeaveApplication::getTaskType()
{
    // getTaskType: Get the task type of the leave application
    return "Official Leave";
}



CasualLeaveApplication::CasualLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
    // Constructor for CasualLeaveApplication
}

CasualLeaveApplication::CasualLeaveApplication(json j) : LeaveApplication(j)
{
    // Constructor for CasualLeaveApplication from json
}



bool CasualLeaveApplication::approve(Employee approver)
{   
    // approve: Approve the leave application
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    // Check if the leave application is already rejected
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool CasualLeaveApplication::reject(Employee approver)
{
    // reject: Reject the leave application
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    // Check if the leave application is already approved
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string CasualLeaveApplication::getTaskType()
{
    // getTaskType: Get the task type of the leave application
    return "Casual Leave";
}

EarnedLeaveApplication::EarnedLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
    // Constructor for EarnedLeaveApplication
}

EarnedLeaveApplication::EarnedLeaveApplication(json j) : LeaveApplication(j)
{
    // Constructor for EarnedLeaveApplication from json
}



bool EarnedLeaveApplication::approve(Employee approver)
{
    // approve: Approve the leave application
    if (approver.getPosition() != "Director")
    {
        return false;
    }
    // Check if the leave application is already rejected
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool EarnedLeaveApplication::reject(Employee approver)
{
    // reject: Reject the leave application
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    // Check if the leave application is already approved
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string EarnedLeaveApplication::getTaskType()
{
    // getTaskType: Get the task type of the leave application
    return "Earned Leave";
}

UnpaidLeaveApplication::UnpaidLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
    // Constructor for UnpaidLeaveApplication
}

UnpaidLeaveApplication::UnpaidLeaveApplication(json j) : LeaveApplication(j)
{
    // Constructor for UnpaidLeaveApplication from json
}

bool UnpaidLeaveApplication::approve(Employee approver)
{
    // approve: Approve the leave application
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    // Check if the leave application is already rejected
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool UnpaidLeaveApplication::reject(Employee approver)
{
    // reject: Reject the leave application
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    // Check if the leave application is already approved
    this->status = LeaveStatus::REJECTED;
    return true;
}



std::string UnpaidLeaveApplication::getTaskType()
{
    // getTaskType: Get the task type of the leave application
    return "Unpaid Leave";
}