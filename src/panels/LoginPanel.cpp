// LoginPanel.cpp
#include "LoginPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(LoginPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, LoginPanel::OnLogin)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a LoginPanel object.
 * @param parent The parent window.
 */
LoginPanel::LoginPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Username
    wxBoxSizer* userSizer = new wxBoxSizer(wxHORIZONTAL);
    userSizer->Add(new wxStaticText(this, wxID_ANY, "Username:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    m_usernameCtrl = new wxTextCtrl(this, wxID_ANY);
    userSizer->Add(m_usernameCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(userSizer, 0, wxEXPAND);

    // Password
    wxBoxSizer* passSizer = new wxBoxSizer(wxHORIZONTAL);
    passSizer->Add(new wxStaticText(this, wxID_ANY, "Password:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    m_passwordCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passSizer->Add(m_passwordCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(passSizer, 0, wxEXPAND);

    // Login Button
    m_loginButton = new wxButton(this, wxID_ANY, "Login");
    mainSizer->Add(m_loginButton, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(mainSizer);
}

/**
 * @brief Handles the login button click event.
 * @param event The event object.
 */
void LoginPanel::OnLogin(wxCommandEvent& event)
{
    wxString username = m_usernameCtrl->GetValue();
    wxString password = m_passwordCtrl->GetValue();
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;

    // TODO: Implement actual authentication logic
    // For demonstration, we'll assume any non-empty credentials are valid
    if (!username.IsEmpty() && !password.IsEmpty())
    {
        // Determine user role based on username/password
        // This is a placeholder. Replace with actual role determination.
        std::string role = "Employee"; // Example roles: Employee, Supervisor, Director, Guard

        // tell the parent frame to show the guard panel

        if (username == "admin" && password == "admin") {
            wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_ADMIN);
        } else {
            wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_GUARD);
        }

        // Create the appropriate dashboard based on role
        // wxPanel* newPanel = nullptr;
        // if (role == "Employee")
        // {
        //     newPanel = new EmployeeDashboard(this->GetParent());
        // }
        // else if (role == "Supervisor")
        // {
        //     newPanel = new SupervisorDashboard(this->GetParent());
        // }
        // else if (role == "Director")
        // {
        //     // newPanel = new DirectorDashboard(this->GetParent());
        // }
        // else if (role == "Guard")
        // {
        //     // newPanel = new GuardPanel(this->GetParent());
        // }

        // if (newPanel)
        // {
        //     // Show the new panel
        //     MyAppFrame* frame = dynamic_cast<MyAppFrame*>(GetParent());
        //     if (frame)
        //     {
        //         frame->ShowPanel(newPanel);
        //     }
        // }
        // else
        // {
        //     wxMessageBox("Invalid user role!", "Error", wxOK | wxICON_ERROR);
        // }

        wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);


    }
    else
    {
        wxMessageBox("Please enter both username and password.", "Error", wxOK | wxICON_ERROR);
    }
}
