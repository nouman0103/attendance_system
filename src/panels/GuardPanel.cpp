// GuardPanel.cpp
#include "GuardPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include <wx/datectrl.h>
#include <wx/datetimectrl.h>
// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(GuardPanel, wxPanel)
    EVT_BUTTON(ID_CHECKIN, GuardPanel::OnCheckIn)
    EVT_BUTTON(ID_CHECKOUT, GuardPanel::OnCheckOut)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a GuardPanel object.
 * @param parent The parent window.
 */
GuardPanel::GuardPanel(wxWindow* parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Employee List
    wxBoxSizer* employeeSizer = new wxBoxSizer(wxHORIZONTAL);
    employeeSizer->Add(new wxStaticText(this, wxID_ANY, "Employee:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    employeeList = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    this->dm = dm;
    std::shared_ptr<std::vector<Employee>> employees = dm->getEmployees();
    for (Employee e : *employees)
    {
        // wxLogDebug(e.getName());
        employeeList->Append(e.getName());
    }

    // for (Employee e : employees) {
    //     employeeList->Append(e.getName());
    // }
    employeeList->SetSelection(0);

    employeeSizer->Add(employeeList, 1, wxALL | wxEXPAND, 5);

    mainSizer->Add(employeeSizer, 0, wxEXPAND);

    // Component for date picker
    wxBoxSizer* dateSizer = new wxBoxSizer(wxHORIZONTAL);
    dateSizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    datePicker = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    dateSizer->Add(datePicker, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(dateSizer, 0, wxEXPAND);

    // Component for time picker
    wxBoxSizer* timeSizer = new wxBoxSizer(wxHORIZONTAL);
    timeSizer->Add(new wxStaticText(this, wxID_ANY, "Time:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    timePicker = new wxTimePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    timeSizer->Add(timePicker, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(timeSizer, 0, wxEXPAND);



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
    // Get the selected date and time
    wxDateTime date = datePicker->GetValue();
    wxDateTime time = timePicker->GetValue();
    // Combine the date and time into a single datetime object
    wxDateTime checkInTime(date.GetDay(), date.GetMonth(), date.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
    if (!checkInTime.IsValid())
    {
        wxLogMessage("Invalid date or time.");
        return;
    }
    // convert to unix timestamp
    time_t timestamp = checkInTime.GetTicks();

    wxMessageBox("Checked in: " + employee + " at " + checkInTime.FormatTime() + " On " + checkInTime.FormatDate() + " (" + std::to_string(timestamp) + ")", "Check In", wxOK | wxICON_INFORMATION);
}


/**
 * @brief Handles the check out button click event.
 * @param event The event object.
 */
void GuardPanel::OnCheckOut(wxCommandEvent& event)
{
    wxString employee = employeeList->GetValue();
    // Get the selected date and time
    wxDateTime date = datePicker->GetValue();
    wxDateTime time = timePicker->GetValue();
    // Combine the date and time into a single datetime object
    wxDateTime checkOutTime(date.GetDay(), date.GetMonth(), date.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
    if (!checkOutTime.IsValid())
    {
        wxLogMessage("Invalid date or time.");
        return;
    }
    // convert to unix timestamp
    time_t timestamp = checkOutTime.GetTicks();

    wxMessageBox("Checked out: " + employee + " at " + checkOutTime.FormatTime() + " On " + checkOutTime.FormatDate() + " (" + std::to_string(timestamp) + ")", "Check Out", wxOK | wxICON_INFORMATION);
    
    
}
// GuardPanel.cpp