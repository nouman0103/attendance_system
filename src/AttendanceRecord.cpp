#include "AttendanceRecord.h"

AttendanceRecord::AttendanceRecord(std::shared_ptr<Employee> employee, std::vector<AttendanceEntry> attendances)
    : attendances(attendances), employee(employee) {
}
void AttendanceRecord::addAttendance(AttendanceEntry attendance)
{
    // Add the attendance to the list
    attendances.push_back(attendance);
}

std::shared_ptr<Employee> AttendanceRecord::getEmployee() const
{
    // Return the employee
    return employee;
}

Attendance AttendanceRecord::getLastStatus() const
{
    // If there are no attendances, return NONE
    if (attendances.empty())
    {
        // Return NONE
        return Attendance::NONE;
    }
    // Return the type of the last attendance
    return attendances.back().getType();
}

time_t AttendanceRecord::getLastTime() const
{
    // If there are no attendances, return 0
    if (attendances.empty())
    {
        return 0;
    }
    // Return the timestamp of the last attendance
    return attendances.back().getTimestamp();
}

int AttendanceRecord::getHourWorkInWeek(time_t weekstart)
{
    // getHourWorkInWeek: Calculate the total hours worked in a week
    int total = 0;
    time_t weekend = weekstart + 7 * 24 * 60 * 60;
    time_t last_checkin = -1;


    for (auto &attendance : attendances)
    {
        // Check if the attendance is within the week
        if (attendance.getTimestamp() >= weekstart && attendance.getTimestamp() < weekend)
        {
            // Check if the attendance is a check-in
            if (attendance.getType() == Attendance::CHECK_IN)
            {
                last_checkin = attendance.getTimestamp();
            }
            else if (attendance.getType() == Attendance::CHECK_OUT)
            {
                // Check if there was a check-in before
                if (last_checkin != -1)
                {
                    total += (attendance.getTimestamp() - last_checkin) / 3600;
                    last_checkin = -1;
                }
            }
        }
    }
    return total;
}
std::time_t get_start_of_month(std::time_t timestamp) {
    // get_start_of_month: Get the start of the month for a given timestamp

    std::tm* time_info = std::localtime(&timestamp);
    time_info->tm_mday = 1;     // Set day to the 1st
    time_info->tm_hour = 0;     // Reset time to midnight
    time_info->tm_min = 0;
    time_info->tm_sec = 0;
    return std::mktime(time_info);
}

std::time_t get_end_of_month(std::time_t timestamp) {   
    // get_end_of_month: Get the end of the month for a given timestamp

    std::tm* time_info = std::localtime(&timestamp);
    time_info->tm_mday = 1;     // Set day to the 1st of the current month
    time_info->tm_mon += 1;     // Move to the next month
    time_info->tm_hour = 0;
    time_info->tm_min = 0;
    time_info->tm_sec = 0;
    std::time_t next_month = std::mktime(time_info);
    return next_month - 1;      // Subtract one second for the last moment of the current month
}

int get_year(std::time_t timestamp) {
    // get_year: Get the year for a given timestamp
    std::tm* time_info = std::localtime(&timestamp);
    return time_info->tm_year + 1900;
}

int AttendanceRecord::getHourWorkInMonth(time_t monthstart)
{
    // getHourWorkInMonth: Calculate the total hours worked in a month
    int total = 0;
    monthstart = get_start_of_month(monthstart);
    time_t monthend = get_end_of_month(monthstart);
    time_t last_checkin = -1;

    if (attendances.empty())
    {
        return 0;
    }

    for (auto &attendance : attendances)
    {
        // Check if the attendance is within the month
        if (attendance.getTimestamp() >= monthstart && attendance.getTimestamp() < monthend)
        {
            // Check if the attendance is a check-in
            if (attendance.getType() == Attendance::CHECK_IN)
            {
                last_checkin = attendance.getTimestamp();
            }
            else if (attendance.getType() == Attendance::CHECK_OUT)
            {
                // Check if there was a check-in before
                if (last_checkin != -1)
                {
                    total += (attendance.getTimestamp() - last_checkin) / 3600;
                    last_checkin = -1;
                }
            }
        }
    }
    return total;
}

