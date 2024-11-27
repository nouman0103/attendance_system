#include "LeaveBalance.h"

LeaveBalance::LeaveBalance()
{
    // Constructor for LeaveBalance
    //Get current year
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    casualLeave[year] = 0;
    earnedLeave[year] = 0;
}
LeaveBalance::LeaveBalance(std::map<int, int> casualLeave, std::map<int, int> earnedLeave)
{
    // Constructor for LeaveBalance with casualLeave and earnedLeave
    this->casualLeave = casualLeave;
    this->earnedLeave = earnedLeave;
}


int LeaveBalance::getCasualLeave(int year)
{
    // getCasualLeave: Get the casual leave balance for a given year
    return MAX_CASUAL_LEAVE- casualLeave[year];
}

int LeaveBalance::getEarnedLeave(int year)
{
    // getEarnedLeave: Get the earned leave balance for a given year
    return MAX_EARNED_LEAVE- earnedLeave[year];
}

void LeaveBalance::setCasualLeave(int casualLeave, int year)
{
    // setCasualLeave: Set the casual leave balance for a given year
    this->casualLeave[year] = casualLeave;
}

void LeaveBalance::setEarnedLeave(int earnedLeave, int year)
{
    // setEarnedLeave: Set the earned leave balance for a given year
    this->earnedLeave[year] = earnedLeave;
}
void LeaveBalance::setCasualLeave(std::map<int, int> casualLeave)
{
    // setCasualLeave: Set the casual leave balance for all years
    this->casualLeave = casualLeave;
}

void LeaveBalance::setEarnedLeave(std::map<int, int> earnedLeave)
{
    // setEarnedLeave: Set the earned leave balance for all years
    this->earnedLeave = earnedLeave;
}

bool LeaveBalance::applyCasualLeave(int days, int year)
{
    // applyCasualLeave: Apply for casual leavea

    //Check if year is present in map if not add it
    if (casualLeave.find(year) == casualLeave.end())
    {
        casualLeave[year] = 0;
    }
    // Check if the leave is less than 5 days
    if (days > 4)
    {
        return false;
    }
    // Check if the leave balance is sufficient
    if (casualLeave[year]+days <= MAX_CASUAL_LEAVE)
    {
        casualLeave[year] += days;
        return true;
    }
    // Return false if the leave balance is insufficient
    return false;
}

bool LeaveBalance::applyEarnedLeave(int days, int year)
{
    // applyEarnedLeave: Apply for earned leave
    if (earnedLeave[year]+days <= MAX_EARNED_LEAVE)
    {
        // Check if the leave balance is sufficient
        earnedLeave[year] += days;
        return true;
    }
    return false;
}

