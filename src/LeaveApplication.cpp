#include "LeaveApplication.h"
#include "DataManager.h"

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



bool OfficialLeaveApplication::approve(std::shared_ptr<Employee> approver)
{
    if (!approver->getPosition().compare("Director" || !approver->getPosition().compare("Supervisor")))
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

bool OfficialLeaveApplication::reject()
{
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



bool CasualLeaveApplication::approve(std::shared_ptr<Employee> approver)
{

    if (this->status == LeaveStatus::REJECTED)
    {
        return false;
    }
    this->status = LeaveStatus::APPROVED;
    return true;
}

bool CasualLeaveApplication::reject(std::shared_ptr<Employee> approver)
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



bool EarnedLeaveApplication::approve(std::shared_ptr<Employee> approver)
{
    if (!approver->getPosition().compare("Director"))
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

bool EarnedLeaveApplication::reject(std::shared_ptr<Employee> approver)
{
    if (!approver->getPosition().compare("Director"))
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

bool UnpaidLeaveApplication::approve(std::shared_ptr<Employee> approver)
{
    if (!approver->getPosition().compare("Director") || !approver->getPosition().compare("Supervisor"))
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

bool UnpaidLeaveApplication::reject(std::shared_ptr<Employee> approver)
{
    if (this->status == LeaveStatus::APPROVED)
    {
        return false;
    }
    this->status = LeaveStatus::REJECTED;
    return true;
}


