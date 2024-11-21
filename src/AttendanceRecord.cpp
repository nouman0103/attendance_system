#include "AttendanceRecord.h"

AttendanceRecord::AttendanceRecord(std::shared_ptr<Employee> employee, std::vector<AttendanceEntry> attendances)
    : attendances(attendances), employee(employee) {
}
void AttendanceRecord::addAttendance(AttendanceEntry attendance)
{
    attendances.push_back(attendance);
}

std::shared_ptr<Employee> AttendanceRecord::getEmployee() const
{
    return employee;
}

Attendance AttendanceRecord::getLastStatus() const
{
    if (attendances.empty())
    {
        return Attendance::NONE;
    }
    return attendances.back().getType();
}

time_t AttendanceRecord::getLastTime() const
{
    if (attendances.empty())
    {
        return 0;
    }
    return attendances.back().getTimestamp();
}

int AttendanceRecord::getHourWorkInWeek(time_t weekstart)
{
    int total = 0;
    time_t weekend = weekstart + 7 * 24 * 60 * 60;
    time_t last_checkin = -1;


    for (auto &attendance : attendances)
    {
        if (attendance.getTimestamp() >= weekstart && attendance.getTimestamp() < weekend)
        {
            if (attendance.getType() == Attendance::CHECK_IN)
            {
                last_checkin = attendance.getTimestamp();
            }
            else if (attendance.getType() == Attendance::CHECK_OUT)
            {
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