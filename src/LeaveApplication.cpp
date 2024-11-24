#include "LeaveApplication.h"

LeaveApplication::LeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status)
{
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
    return this->startDate;
}

time_t LeaveApplication::getEndDate()
{
    return this->endDate;
}

std::string LeaveApplication::getReason()
{
    return this->reason;
}

time_t LeaveApplication::getApplicationDate()
{
    return this->applicationDate;
}

time_t LeaveApplication::getApprovalDate()
{
    return this->approvalDate;
}

LeaveStatus LeaveApplication::getStatus()
{
    return this->status;
}

std::shared_ptr<Employee> LeaveApplication::getEmployee()
{
    return this->employee;
}

OfficialLeaveApplication::OfficialLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
}

OfficialLeaveApplication::OfficialLeaveApplication(json j) : LeaveApplication(j)
{
}

json CasualLeaveApplication::to_json()
{
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
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool OfficialLeaveApplication::reject(Employee approver)
{
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string OfficialLeaveApplication::getTaskType()
{
    return "Official Leave";
}



CasualLeaveApplication::CasualLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
}

CasualLeaveApplication::CasualLeaveApplication(json j) : LeaveApplication(j)
{
}



bool CasualLeaveApplication::approve(Employee approver)
{

    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool CasualLeaveApplication::reject(Employee approver)
{
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string CasualLeaveApplication::getTaskType()
{
    return "Casual Leave";
}

EarnedLeaveApplication::EarnedLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
}

EarnedLeaveApplication::EarnedLeaveApplication(json j) : LeaveApplication(j)
{
}



bool EarnedLeaveApplication::approve(Employee approver)
{
    if (approver.getPosition() != "Director")
    {
        return false;
    }
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool EarnedLeaveApplication::reject(Employee approver)
{
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}

std::string EarnedLeaveApplication::getTaskType()
{
    return "Earned Leave";
}

UnpaidLeaveApplication::UnpaidLeaveApplication(std::shared_ptr<Employee> employee, time_t startDate, time_t endDate, std::string reason, time_t applicationDate, time_t approvalDate, LeaveStatus status) : LeaveApplication(employee, startDate, endDate, reason, applicationDate, approvalDate, status)
{
}

UnpaidLeaveApplication::UnpaidLeaveApplication(json j) : LeaveApplication(j)
{
}

bool UnpaidLeaveApplication::approve(Employee approver)
{
    if (approver.getPosition() != "Director" && approver.getPosition() != "Supervisor")
    {
        return false;
    }
    
    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool UnpaidLeaveApplication::reject(Employee approver)
{
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}



std::string UnpaidLeaveApplication::getTaskType()
{
    return "Unpaid Leave";
}