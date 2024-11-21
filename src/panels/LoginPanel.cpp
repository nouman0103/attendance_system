// LoginPanel.cpp
#include "LoginPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(LoginPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, LoginPanel::OnLogin)
    EVT_SHOW(LoginPanel::OnShow)
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

    // Add padding
    mainSizer->AddSpacer(10);

    // Creating a title
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Login  Portal", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    mainSizer->AddSpacer(5);

    // Username
    wxBoxSizer* userSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* userLabel = new wxStaticText(this, wxID_ANY, "Username:");
    userLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    userSizer->Add(userLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    m_usernameCtrl = new wxTextCtrl(this, wxID_ANY);
    userSizer->Add(m_usernameCtrl, 1, wxLEFT | wxRIGHT | wxEXPAND, 20); // Add horizontal padding
    mainSizer->Add(userSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 20); // Add horizontal padding
    mainSizer->AddSpacer(5);

    // Password
    wxBoxSizer* passSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* passLabel = new wxStaticText(this, wxID_ANY, "Password:");
    passLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    passSizer->Add(passLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    m_passwordCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passSizer->Add(m_passwordCtrl, 1, wxLEFT | wxRIGHT | wxEXPAND, 20); // Add horizontal padding
    mainSizer->Add(passSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 20); // Add horizontal padding

    mainSizer->AddSpacer(5);

    // Login Button
    m_loginButton = new wxButton(this, wxID_ANY, "Login");
    mainSizer->Add(m_loginButton, 0, wxALL | wxALIGN_CENTER, 10);

    // DataManager
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
                dm->setEmployee(dm->getEmployee(username.ToStdString()));

                break;
            }
        }

        wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
        InterfaceFrame *frame = dynamic_cast<InterfaceFrame*>(simplebook->GetParent());
        if (username == "admin" && password == "admin") {
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_ADMIN);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
            frame->updateStatusBar("admin logged in." + role, 1);
        } else if (role=="Guard") {
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_GUARD);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
            frame->updateStatusBar(username + " logged in as " + role, 1);
        }
        else if (role=="Employee") {
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_EMPLOYEE);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);

            // call InterfaceFrame::updateStatusBar to update the status bar
            frame->updateStatusBar(username + " logged in as " + role, 1);
        }
        else if(role=="Supervisor"){
            simplebook->SetSelection(InterfaceFrame::PID_PAGE_APPROVAL);
            wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
            frame->updateStatusBar(username + " logged in as " + role, 1);
        }
        else {
            wxMessageBox("Failed to login! Please ensure your input details are correct.", "Error", wxOK | wxICON_ERROR);
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

void LoginPanel::OnShow(wxShowEvent& event)
{
    if (event.IsShown())
    {
        clearFields();
        // update the status bar
        wxSimplebook *simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
        InterfaceFrame *frame = dynamic_cast<InterfaceFrame*>(simplebook->GetParent());
        frame->updateStatusBar("Ready", 1);
    }
    event.Skip();
}