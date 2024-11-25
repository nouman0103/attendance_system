#include "LeaveApplication.h"
#include <ctime>
#include <memory>
#include <map>
#define MAX_CASUAL_LEAVE 15
#define MAX_EARNED_LEAVE 21
class LeaveBalance
{
    public:
        LeaveBalance();
        int getCasualLeave(int year);
        int getEarnedLeave(int year);
        void setCasualLeave(int casualLeave,int year);
        void setEarnedLeave(int earnedLeave,int year);
        bool applyCasualLeave(int days,int year);
        bool applyEarnedLeave(int days,int year);
      
    private:
        std::map<int, int> casualLeave;
        std::map<int, int> earnedLeave;
        
};