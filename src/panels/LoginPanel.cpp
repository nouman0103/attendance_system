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
LoginPanel::LoginPanel(wxWindow* parent, std::shared_ptr<DataManager> dm)
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
    //DataManager dm;
    this->dm = dm;

    SetSizer(mainSizer);
}

LoginPanel::~LoginPanel()
{
}

void LoginPanel::clearFields()
{
    m_usernameCtrl->Clear();
    m_passwordCtrl->Clear();
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
        // std::string role = "Employee"; // Example roles: Employee, Supervisor, Director, Guard

        // tell the parent frame to show the guard panel
        std::string role = "";
        std::shared_ptr<std::vector<Employee>> employees = this->dm->getEmployees();
        for (Employee e : *employees)
        {
            if (e.login(username.ToStdString(), password.ToStdString()))
            {
                role = e.getPosition();
                break;
            }
        }


        if (username == "admin" && password == "admin") {
            wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_ADMIN);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
        } else if (role!="") {
            wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_GUARD);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Invalid user role!", "Error", wxOK | wxICON_ERROR);
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

        


    }
    else
    {
        wxMessageBox("Please enter both username and password.", "Error", wxOK | wxICON_ERROR);
    }
}
