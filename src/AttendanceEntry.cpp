#include "AttendanceEntry.h"


AttendanceEntry::AttendanceEntry(std::string id, Attendance type, time_t time)
    : id(id), type(type)
{
    this->time = time;
}


std::string AttendanceEntry::getID() const
{
    return id;
}

Attendance AttendanceEntry::getType() const
{
    return type;
}

std::string AttendanceEntry::getTime() const
{
    return std::string(ctime(&time));
}

json AttendanceEntry::to_json() const
{
    json j;
    // j["id"] = id;
    j["type"] = static_cast<int>(type);
    j["time"] = time;
    return j;
}