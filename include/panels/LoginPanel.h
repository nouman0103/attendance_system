// LoginPanel.h
#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <wx/wx.h>

/**
 * @class LoginPanel
 * @brief Panel for user authentication.
 *
 * This panel allows users to enter their credentials and attempt to log in.
 */
class LoginPanel : public wxPanel
{
public:
    /**
     * @brief Constructs a LoginPanel object.
     * @param parent The parent window.
     */
    LoginPanel(wxWindow* parent);

private:
    /**
     * @brief Handles the login button click event.
     * @param event The event object.
     */
    void OnLogin(wxCommandEvent& event);

    // UI Components
    wxTextCtrl* m_usernameCtrl;
    wxTextCtrl* m_passwordCtrl;
    wxButton* m_loginButton;

    wxDECLARE_EVENT_TABLE();
};

#endif // LOGINPANEL_H