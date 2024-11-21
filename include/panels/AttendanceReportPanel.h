// AttendanceReportPanel.h
#ifndef ATTENDANCEREPORTPANEL_H
#define ATTENDANCEREPORTPANEL_H

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
 * @class AttendanceReport
 * @brief Panel for attendance report
 */
class AttendanceReportPanel : public wxPanel
{
public:
    /**
    * @brief Constructs a ApprovalPanel object.
    * @param parent The parent window.
     */
    AttendanceReportPanel(wxWindow* parent,std::shared_ptr<DataManager> dm);

private:

    void OnShow(wxShowEvent &event);
    void OnBack(wxCommandEvent &event);


    std::shared_ptr<DataManager> dm;
    wxDECLARE_EVENT_TABLE();
};


#endif // ATTENDANCEREPORTPANEL_H
