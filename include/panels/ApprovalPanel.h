// ApprovalPanel.h
#ifndef APPROVALPANEL_H
#define APPROVALPANEL_H

#include <wx/wx.h>
#include <wx/combobox.h>
#include <wx/datetime.h>
#include <wx/datetimectrl.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <vector>
#include "User.h"

#include "Employee.h"
#include "DataManager.h"


enum RoleType
{
    ROLE_NONE = 0,
    ROLE_SUPERVISOR = 1,
    ROLE_DIRETOR = 2
};


/**
 * @class ApprovalPanel
 * @brief Panel for leave approval
 */
class ApprovalPanel : public wxPanel
{
public:
    /**
    * @brief Constructs a ApprovalPanel object.
    * @param parent The parent window.
     */
    ApprovalPanel(wxWindow* parent,std::shared_ptr<DataManager> dm);
    void setLoggedInAsPosition(int role);
    int getLoggedInAsPosition();

private:
    void OnShow(wxShowEvent &event);
    void OnViewReports(wxCommandEvent &event);
    void filterOutstandingLeaves(wxCommandEvent &event);
    int loggedInAsPosition;
    bool filtered = false;
    wxButton *outstandingLeavesButton;


    std::shared_ptr<DataManager> dm;
    wxDECLARE_EVENT_TABLE();
};


#endif // APPROVALPANEL_H
