// LoginPanel.cpp
#include "AdminPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include "DataManager.h"
#include <wx/statline.h> // Include wxStaticLine header
// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(AdminPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, AdminPanel::OnAddUser)
wxEND_EVENT_TABLE()


AdminPanel::AdminPanel(wxWindow* parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->dm = dm;

    // get list of all employees
    // DataManager dm;
    // std::vector<Employee> employees = dm.readEmployee();
    // for (Employee e : employees) {
    //     std::cout<<e.getName()<<std::endl;
    // }

    // Show the list of employees in a wxListBox
    
    employeeList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, 0);
    updateEmployeeList();

    mainSizer->Add(employeeList, 0, wxEXPAND);

    // add a horizontal separator
    mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);




    // --- Add New User ---

    // Select User Type (Employee, Supervisor, Director, Guard)
    wxBoxSizer* userTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    userTypeSizer->Add(new wxStaticText(this, wxID_ANY, "User Type:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    wxArrayString userTypes;
    userTypes.Add("Employee");
    userTypes.Add("Supervisor");
    userTypes.Add("Director");
    userTypes.Add("Guard");
    userTypeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, userTypes);
    userTypeChoice->SetSelection(0);
    userTypeSizer->Add(userTypeChoice, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(userTypeSizer, 0, wxEXPAND);

    // User Name
    wxBoxSizer* userNameSizer = new wxBoxSizer(wxHORIZONTAL);
    userNameSizer->Add(new wxStaticText(this, wxID_ANY, "User Name:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    userNameCtrl = new wxTextCtrl(this, wxID_ANY);
    userNameSizer->Add(userNameCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(userNameSizer, 0, wxEXPAND);

    // Initial Password
    wxBoxSizer* passwordSizer = new wxBoxSizer(wxHORIZONTAL);
    passwordSizer->Add(new wxStaticText(this, wxID_ANY, "Initial Password:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    passwordCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passwordSizer->Add(passwordCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(passwordSizer, 0, wxEXPAND);


    // Add User Button
    addUserButton = new wxButton(this, wxID_ANY, "Add User");
    mainSizer->Add(addUserButton, 0, wxALL | wxALIGN_CENTER, 10);


    SetSizer(mainSizer);
    
}

AdminPanel::~AdminPanel()
{
    
}

void AdminPanel::updateEmployeeList()
{
    // get list of all employees
    // DataManager dm;
    std::shared_ptr<std::vector<Employee>> employees = dm->getEmployees();
    wxArrayString employeeNames;
    for (Employee e : *employees) {
        employeeNames.Add(e.getName() + " (" + e.getPosition() + ")");
    }
    employeeList->Clear();
    employeeList->InsertItems(employeeNames, 0);
}

void AdminPanel::OnAddUser(wxCommandEvent& event)
{
    std::cout << "Add user button clicked" << std::endl;
    
    // get the values from the form
    wxString userType = userTypeChoice->GetStringSelection();
    wxString userName = userNameCtrl->GetValue();
    wxString password = passwordCtrl->GetValue();

    // validate the form
    if (userName.IsEmpty() || password.IsEmpty()) {
        wxMessageBox("Please fill in all fields", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // add the user to the database
    // DataManager dm;
    Employee newEmployee(userName.ToStdString(), 0, password.ToStdString(), userType.ToStdString(), nullptr, nullptr);
    // dm.writeEmployee(newEmployee);
    bool success = dm->writeEmployee(newEmployee);
    if (!success) {
        wxMessageBox("User already exists", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // clear the form
    userNameCtrl->Clear();
    passwordCtrl->Clear();
    
    wxMessageBox("User added successfully", "Success", wxOK | wxICON_INFORMATION);

    updateEmployeeList();

}