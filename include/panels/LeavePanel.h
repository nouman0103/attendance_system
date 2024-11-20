// LeavePanel.h
#ifndef LEAVEPANEL_H
#define LEAVEPANEL_H

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


/**
 * @class LeavePanel
 * @brief Panel for leave operations.
 */
class LeavePanel : public wxPanel
{
public:
    /**
    * @brief Constructs a GuardPanel object.
    * @param parent The parent window.
     */
    LeavePanel(wxWindow* parent,std::shared_ptr<DataManager> dm);

private:

    void OnShow(wxShowEvent &event);
    void OnBack(wxCommandEvent &event);



    std::shared_ptr<DataManager> dm;
    wxDECLARE_EVENT_TABLE();
};


#endif // LEAVEPANEL_H