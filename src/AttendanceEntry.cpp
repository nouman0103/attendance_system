#include "AttendanceEntry.h"


AttendanceEntry::AttendanceEntry(std::string id, Attendance type, time_t time)
    : id(id), type(type)
{
    // Constructor for AttendanceEntry
    this->time = time;
}


std::string AttendanceEntry::getID() const
{
    // getID: Get the ID of the attendance entry
    return id;
}

Attendance AttendanceEntry::getType() const
{
    // getType: Get the type of the attendance entry
    return type;
}

std::string AttendanceEntry::getTime() const
{
    // getTime: Get the time of the attendance entry
    return std::string(ctime(&time));
}

time_t AttendanceEntry::getTimestamp() const
{
    // getTimestamp: Get the timestamp of the attendance entry
    return time;
}

json AttendanceEntry::to_json() const
{
    // to_json: Convert the attendance entry to json
    json j;
    // j["id"] = id;
    j["type"] = static_cast<int>(type);
    j["time"] = time;
    return j;
}