#ifndef EMPLOYEEPANEL_H
#define EMPLOYEEPANEL_H

#include <wx/wx.h>
#include <memory>
#include "DataManager.h"
#include "HorizontalBar.h"

class EmployeePanel : public wxPanel
{
public:
    EmployeePanel(wxWindow* parent, std::shared_ptr<DataManager> dm);
    ~EmployeePanel();

private:
    void OnShow(wxShowEvent& event);
    void OnLeavePortal(wxCommandEvent& event);
    void OnPrevWeek(wxCommandEvent& event);
    void OnNextWeek(wxCommandEvent& event);

    //DataManager* dm;
    std::shared_ptr<DataManager> dm;
    wxDateTime weekStart;
    wxDateTime weekEnd;
    HorizontalBar* m_barGraphWeekly;
    HorizontalBar* m_barGraphMonthly;
    wxStaticText* dateRangeText;


    wxDECLARE_EVENT_TABLE();

};

enum ButtonID
{
    ID_PREV_WEEK = 1,
    ID_NEXT_WEEK = 2,
    ID_LEAVE_PORTAL = 3

};

#endif // EMPLOYEEPANEL_H