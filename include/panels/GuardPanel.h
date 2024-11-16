// GuardPanel.h
#ifndef GUARDPANEL_H
#define GUARDPANEL_H

#include <wx/wx.h>
#include <wx/combobox.h>
#include <vector>
#include "User.h"

#include "Employee.h"
#include "DataManager.h"


/**
 * @class GuardPanel
 * @brief Panel for guard operations.
 */
class GuardPanel : public wxPanel
{
public:
    /**
    * @brief Constructs a GuardPanel object.
    * @param parent The parent window.
     */
    GuardPanel(wxWindow* parent,std::shared_ptr<DataManager> dm);

private:
    
    void OnCheckIn(wxCommandEvent& event);
    void OnCheckOut(wxCommandEvent& event);

   
    // UI Components
    wxComboBox* employeeList;
    wxButton* checkInButton;
    wxButton* checkOutButton;

    User* user;
    std::shared_ptr<DataManager> dm;
    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_CHECKIN = 1,
    ID_CHECKOUT
};

#endif // GUARDPANEL_H