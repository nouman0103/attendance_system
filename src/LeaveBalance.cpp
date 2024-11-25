#include "LeaveBalance.h"

LeaveBalance::LeaveBalance()
{
    //Get current year
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    casualLeave[year] = 0;
    earnedLeave[year] = 0;
}


int LeaveBalance::getCasualLeave(int year)
{
    return casualLeave[year];
}

int LeaveBalance::getEarnedLeave(int year)
{
    return earnedLeave[year];
}

void LeaveBalance::setCasualLeave(int casualLeave, int year)
{
    this->casualLeave[year] = casualLeave;
}

void LeaveBalance::setEarnedLeave(int earnedLeave, int year)
{
    this->earnedLeave[year] = earnedLeave;
}

bool LeaveBalance::applyCasualLeave(int days, int year)
{
    //Check if year is present in map if not add it
    if (casualLeave.find(year) == casualLeave.end())
    {
        casualLeave[year] = 0;
    }
    if (days > 4)
    {
        return false;
    }
    if (casualLeave[year]+days <= MAX_CASUAL_LEAVE)
    {
        casualLeave[year] += days;
        return true;
    }
    return false;
}

bool LeaveBalance::applyEarnedLeave(int days, int year)
{
    if (earnedLeave[year]+days <= MAX_EARNED_LEAVE)
    {
        earnedLeave[year] += days;
        return true;
    }
    return false;
}

