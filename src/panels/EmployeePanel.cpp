// EmployeePanel.cpp
#include "EmployeePanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include "DataManager.h"
#include <wx/statline.h> // Include wxStaticLine header
#include "AttendanceRecord.h"
// Include other dashboards as needed

BEGIN_EVENT_TABLE(EmployeePanel, wxPanel)
EVT_SHOW(EmployeePanel::OnShow)
EVT_BUTTON(ID_LEAVE_PORTAL, EmployeePanel::OnLeavePortal)
EVT_BUTTON(ID_PREV_WEEK, EmployeePanel::OnPrevWeek)
EVT_BUTTON(ID_NEXT_WEEK, EmployeePanel::OnNextWeek)
END_EVENT_TABLE()

EmployeePanel::EmployeePanel(wxWindow *parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    this->dm = dm;

    // Add padding
    mainSizer->AddSpacer(10);

    // title of employee panel
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "Weekly Report", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    // write the date range (for example, "12/1/2021 - 12/7/2021")
    wxBoxSizer *dateRangeSizer = new wxBoxSizer(wxHORIZONTAL);

    // Add left button
    wxButton *leftButton = new wxButton(this, ID_PREV_WEEK, "<");
    leftButton->SetMaxSize(wxSize(30, -1));
    dateRangeSizer->Add(leftButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // Add date range label
    dateRangeText = new wxStaticText(this, wxID_ANY, "12/1/2021 - 12/7/2021", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    dateRangeSizer->Add(dateRangeText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // Add right button
    wxButton *rightButton = new wxButton(this, ID_NEXT_WEEK, ">");
    rightButton->SetMaxSize(wxSize(30, -1));
    dateRangeSizer->Add(rightButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // add center sizer to main sizer
    mainSizer->Add(dateRangeSizer, 0, wxALIGN_CENTER_HORIZONTAL);

    // create a fake bar
    m_barGraphWeekly = new HorizontalBar(this, 7);
    mainSizer->Add(m_barGraphWeekly, 0, wxALL | wxEXPAND, 10);

    // add a horizontal separator
    mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);

    wxStaticText *title2 = new wxStaticText(this, wxID_ANY, "Month's Report", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title2->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title2, 0, wxALL | wxEXPAND, 10);

    month_dateRangeText = new wxStaticText(this, wxID_ANY, "12/1/2021 - 12/7/2021", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    mainSizer->Add(month_dateRangeText, 0, wxALL | wxALIGN_CENTER, 10);


    // add a horizontal bar with duration of 30
    m_barGraphMonthly = new HorizontalBar(this, 30);
    mainSizer->Add(m_barGraphMonthly, 0, wxALL | wxEXPAND, 10);
    m_barGraphMonthly->SetData(70, 8, 3, 0);

    // add a horizontal separator
    mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);

    // add a button that says "Open Leave Portal"
    wxButton *leavePortalButton = new wxButton(this, ID_LEAVE_PORTAL, "Open Leave Portal");
    mainSizer->Add(leavePortalButton, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &EmployeePanel::OnShow, this);
}

EmployeePanel::~EmployeePanel()
{
}

void EmployeePanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        // Update the date range text
        std::shared_ptr<Employee> current_employee = dm->getCurrentEmployee();
        weekStart = wxDateTime::Now();
        // set hours to 0
        weekStart.SetHour(0);
        weekStart.SetMinute(0);
        weekStart.SetSecond(0);

        // Get the current day of the week
        int day_of_week = weekStart.GetWeekDay();
        // Subtract the current day of the week to get the start of the week
        weekStart = weekStart.Subtract(wxTimeSpan((day_of_week - 1) * 24, 0, 0, 0));
        weekEnd = weekStart;
        // Add the remaining days to get the end of the week
        weekEnd = weekEnd.Add(wxTimeSpan(7 * 23, 59, 59, 59));

        // Set the date range text
        dateRangeText->SetLabelText(weekStart.Format("%d/%m/%Y") + " - " + weekEnd.Format("%d/%m/%Y"));
        // dateRangeText->SetLabel("12/1/2021 - 12/7/2021");
        int hours = current_employee->getAttendanceRecord()->getHourWorkInWeek(weekStart.GetTicks());
        std::map<std::string, int> leaveCount = current_employee->getLeaveInWeek(weekStart.GetTicks());
        // set bar Data
        
        time_t now = time(0);

        m_barGraphWeekly->SetData(hours, leaveCount["Casual Leave"], leaveCount["Earned Leave"], leaveCount["Official Leave"]);
        hours = current_employee->getAttendanceRecord()->getHourWorkInMonth(now);
        leaveCount = current_employee->getLeaveInMonth(now);
        // set bar Data
        m_barGraphMonthly->SetData(hours, leaveCount["Casual Leave"], leaveCount["Earned Leave"], leaveCount["Official Leave"]);
    }
    event.Skip(); // Ensure the default handling of the event
}

void EmployeePanel::OnLeavePortal(wxCommandEvent &event)
{
    wxSimplebook *simplebook = dynamic_cast<wxSimplebook *>(this->GetParent());
    InterfaceFrame *frame = dynamic_cast<InterfaceFrame *>(simplebook->GetParent());
    simplebook->SetSelection(InterfaceFrame::PID_PAGE_LEAVE);
    frame->updateStatusBar("Opening Leave Portal.", 1);
}

void EmployeePanel::OnPrevWeek(wxCommandEvent &event)
{
    weekStart = weekStart.Subtract(wxTimeSpan(7 * 24, 0, 0, 0));
    weekEnd = weekEnd.Subtract(wxTimeSpan(7 * 24, 0, 0, 0));
    dateRangeText->SetLabelText(weekStart.Format("%d/%m/%Y") + " - " + weekEnd.Format("%d/%m/%Y"));
    std::shared_ptr<Employee> current_employee = dm->getCurrentEmployee();
    int hours = current_employee->getAttendanceRecord()->getHourWorkInWeek(weekStart.GetTicks());
    std::map<std::string, int> leaveCount = current_employee->getLeaveInWeek(weekStart.GetTicks());
    // set bar Data
    m_barGraphWeekly->SetData(hours, leaveCount["Casual Leave"], leaveCount["Earned Leave"], leaveCount["Official Leave"]);
}

void EmployeePanel::OnNextWeek(wxCommandEvent &event)
{
    weekStart = weekStart.Add(wxTimeSpan(7 * 24, 0, 0, 0));
    weekEnd = weekEnd.Add(wxTimeSpan(7 * 24, 0, 0, 0));
    dateRangeText->SetLabelText(weekStart.Format("%d/%m/%Y") + " - " + weekEnd.Format("%d/%m/%Y"));

    std::shared_ptr<Employee> current_employee = dm->getCurrentEmployee();
    int hours = current_employee->getAttendanceRecord()->getHourWorkInWeek(weekStart.GetTicks());
    std::map<std::string, int> leaveCount = current_employee->getLeaveInWeek(weekStart.GetTicks());
    // set bar Data
    m_barGraphWeekly->SetData(hours, leaveCount["Casual Leave"], leaveCount["Earned Leave"], leaveCount["Official Leave"]);
}
