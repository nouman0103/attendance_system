#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <wx/wx.h>

class AdminPanel : public wxPanel
{
public:
    AdminPanel(wxWindow* parent);
    ~AdminPanel();

    void addUser();
    void removeUser();

private:
    // Add private member variables and methods here

    void OnAddUser(wxCommandEvent& event);

    // UI Components
    wxListBox* employeeList;
    wxChoice* userTypeChoice;
    wxTextCtrl* userNameCtrl;
    wxTextCtrl* userIDCtrl;
    wxTextCtrl* passwordCtrl;
    wxButton* addUserButton;

    wxDECLARE_EVENT_TABLE();

};

#endif // ADMINPANEL_H