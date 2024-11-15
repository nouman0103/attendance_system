// GuardPanel.cpp
#include "GuardPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(GuardPanel, wxPanel)
    EVT_BUTTON(ID_CHECKIN, GuardPanel::OnCheckIn)
    EVT_BUTTON(ID_CHECKOUT, GuardPanel::OnCheckOut)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a GuardPanel object.
 * @param parent The parent window.
 */
GuardPanel::GuardPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Employee List
    wxBoxSizer* employeeSizer = new wxBoxSizer(wxHORIZONTAL);
    employeeSizer->Add(new wxStaticText(this, wxID_ANY, "Employee:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    employeeList = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    employeeList->Append("Alice");
    employeeList->Append("Bob");
    employeeList->Append("Charlie");
    employeeList->SetSelection(0);

    employeeSizer->Add(employeeList, 1, wxALL | wxEXPAND, 5);

    mainSizer->Add(employeeSizer, 0, wxEXPAND);

    // Check In Button
    checkInButton = new wxButton(this, ID_CHECKIN, "Check In");
    mainSizer->Add(checkInButton, 0, wxALL | wxALIGN_CENTER, 10);

    // Check Out Button
    checkOutButton = new wxButton(this, ID_CHECKOUT, "Check Out");
    mainSizer->Add(checkOutButton, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(mainSizer);
    }

/**
 * @brief Handles the check in button click event.
 * @param event The event object.
 */
void GuardPanel::OnCheckIn(wxCommandEvent& event)
{
    wxString employee = employeeList->GetValue();
    std::cout << "Checking in: " << employee << std::endl;
    wxMessageBox("Checked in: " + employee, "Check In", wxOK | wxICON_INFORMATION);
}


/**
 * @brief Handles the check out button click event.
 * @param event The event object.
 */
void GuardPanel::OnCheckOut(wxCommandEvent& event)
{
    wxString employee = employeeList->GetValue();
    std::cout << "Checking out: " << employee << std::endl;
    wxMessageBox("Checked out: " + employee, "Check Out", wxOK | wxICON_INFORMATION);
}
// GuardPanel.cpp