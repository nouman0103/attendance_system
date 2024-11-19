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

    //DataManager* dm;
    std::shared_ptr<DataManager> dm;

    HorizontalBar* m_barGraph;

    wxStaticText* dateRangeText;


    wxDECLARE_EVENT_TABLE();

};

#endif // EMPLOYEEPANEL_H