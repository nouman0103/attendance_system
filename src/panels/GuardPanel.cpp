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
            EVT_SHOW(GuardPanel::OnShow)
                wxEND_EVENT_TABLE()

    /**
     * @brief Constructs a GuardPanel object.
     * @param parent The parent window.
     */
    GuardPanel::GuardPanel(wxWindow *parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // add padding
    mainSizer->AddSpacer(10);

    // title of guard panel
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "Mark Attendance", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    this->dm = dm;

    // Employee List
    wxBoxSizer *employeeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *employeeSelectLabel = new wxStaticText(this, wxID_ANY, "Employee:");
    employeeSelectLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    employeeSizer->Add(employeeSelectLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    employeeList = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    employeeSizer->Add(employeeList, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(employeeSizer, 0, wxEXPAND);

    // Component for date picker
    wxBoxSizer *dateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *dateSelectLabel = new wxStaticText(this, wxID_ANY, "Date:");
    dateSelectLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    dateSizer->Add(dateSelectLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    datePicker = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    dateSizer->Add(datePicker, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(dateSizer, 0, wxEXPAND);

    // Component for time picker
    wxBoxSizer *timeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *timeSelectLabel = new wxStaticText(this, wxID_ANY, "Time:");
    timeSelectLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    timeSizer->Add(timeSelectLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // Create a wxChoice control with options for each hour of the day
    wxArrayString hours;
    for (int i = 0; i < 24; ++i)
    {
        hours.Add(wxString::Format("%02d:00", i));
    }
    hourChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, hours);
    timeSizer->Add(hourChoice, 1, wxALL | wxEXPAND, 5);

    mainSizer->Add(timeSizer, 0, wxEXPAND);

    // Check In Button
    checkInButton = new wxButton(this, ID_CHECKIN, "Check In");
    mainSizer->Add(checkInButton, 0, wxALL | wxALIGN_CENTER, 10);

    // Check Out Button
    checkOutButton = new wxButton(this, ID_CHECKOUT, "Check Out");
    mainSizer->Add(checkOutButton, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &GuardPanel::OnShow, this);

    // Set the guard
}

void GuardPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        // clear the form
        employeeList->Clear();
        std::shared_ptr<std::vector<Employee>> employees = dm->getEmployees();
        for (Employee e : *employees)
        {
            employeeList->Append(e.getName());
        }
        employeeList->SetSelection(0);
        // udpate date picker
        datePicker->SetValue(wxDateTime::Now());
        // update time picker
        hourChoice->SetSelection(wxDateTime::Now().GetHour());
        guard = std::make_shared<Guard>(*dm->getCurrentEmployee().get());

        // Msg Box for Guard Detail
    }
    event.Skip(); // Ensure the default handling of the event
}

/**
 * @brief Handles the check in button click event.
 * @param event The event object.
 */
void GuardPanel::OnCheckIn(wxCommandEvent &event)
{
    wxString employee = employeeList->GetValue();
    // Get the selected date and time
    wxDateTime date = datePicker->GetValue();
    // get time from hourChoice
    int hourIndex = hourChoice->GetSelection();
    wxDateTime time(hourIndex, 0, 0);

    // Combine the date and time into a single datetime object
    wxDateTime checkInTime(date.GetDay(), date.GetMonth(), date.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
    // convert to unix timestamp
    time_t timestamp = checkInTime.GetTicks();

    AttendanceEntry entry(employee.ToStdString(), Attendance::CHECK_IN, timestamp);
    std::shared_ptr<Employee> emp = dm->getEmployee(employee.ToStdString());
    //...
    if (!guard.get()->markAttendance(emp, entry))
    {
        wxLogMessage("Cannot check in . Employee already  checked in.");
        return;
    }
    dm->writeAttendanceRecord(entry);
    wxMessageBox("Checked in: " + employee + " at " + checkInTime.FormatTime() + " On " + checkInTime.FormatDate() + " (" + std::to_string(timestamp) + ")", "Check In", wxOK | wxICON_INFORMATION);
}

/**
 * @brief Handles the check out button click event.
 * @param event The event object.
 */
void GuardPanel::OnCheckOut(wxCommandEvent &event)
{
    wxString employee = employeeList->GetValue();
    // Get the selected date and time
    wxDateTime date = datePicker->GetValue();
    // get time from hourChoice
    int hourIndex = hourChoice->GetSelection();
    wxDateTime time(hourIndex, 0, 0);

    // Combine the date and time into a single datetime object
    wxDateTime checkOutTime(date.GetDay(), date.GetMonth(), date.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
    AttendanceEntry entry(employee.ToStdString(), Attendance::CHECK_OUT, checkOutTime.GetTicks());
    std::shared_ptr<Employee> emp = dm->getEmployee(employee.ToStdString());

    if (!guard.get()->markAttendance(emp, entry))
    {
        wxLogMessage("Cannot check out. Employee Missing Maybe out of his misery.");
        return;
    }
    dm->writeAttendanceRecord(entry);

    // convert to unix timestamp
    time_t timestamp = checkOutTime.GetTicks();

    wxMessageBox("Checked out: " + employee + " at " + checkOutTime.FormatTime() + " On " + checkOutTime.FormatDate() + " (" + std::to_string(timestamp) + ")", "Check Out", wxOK | wxICON_INFORMATION);
}
// GuardPanel.cpp