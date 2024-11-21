// AttendanceReportPanel.cpp
#include "AttendanceReportPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include <wx/datectrl.h>
#include <wx/datetimectrl.h>
#include <wx/statline.h> 

// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(AttendanceReportPanel, wxPanel)
    EVT_SHOW(AttendanceReportPanel::OnShow)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a AttendanceReportPanel object.
 * @param parent The parent window.
 */
AttendanceReportPanel::AttendanceReportPanel(wxWindow *parent, std::shared_ptr<DataManager> dm)
: wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // go back to the approval panel button
    wxButton *backButton = new wxButton(this, wxID_ANY, "Back to Approval");
    mainSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 10);
    // bind the button with OnBack
    backButton->Bind(wxEVT_BUTTON, &AttendanceReportPanel::OnBack, this);


    // add padding
    mainSizer->AddSpacer(10);

    // title of LeavePanel
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "Attendance Report Portal", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    this->dm = dm;

    // filter by employee
    // Employee
    wxBoxSizer* employeeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* employeeLabel = new wxStaticText(this, wxID_ANY, "Employee:");
    employeeLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    employeeSizer->Add(employeeLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    wxArrayString employees;
    employees.Add("Show All Employees");
    employees.Add("John Doe");
    employees.Add("Jane Doe");
    employees.Add("Alice Doe");
    employees.Add("Bob Doe");
    wxComboBox* employee = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, employees, wxCB_READONLY);
    employeeSizer->Add(employee, 1, wxALL | wxEXPAND, 5);
    employee->SetSelection(0);
    mainSizer->Add(employeeSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);


    // horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);

    
    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
    // Create a scrolled window
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(5, 3, 3);

    // Set growable columns
    gridSizer->AddGrowableCol(0, 1); // Sr
    gridSizer->AddGrowableCol(1, 1); // Employee
    gridSizer->AddGrowableCol(2, 1); // Leave Type
    gridSizer->AddGrowableCol(3, 1); // Start Date
    gridSizer->AddGrowableCol(4, 1); // End Date

    wxStaticText* header1 = new wxStaticText(scrolledWindow, wxID_ANY, "Sr");
    wxStaticText* header2 = new wxStaticText(scrolledWindow, wxID_ANY, "Employee");
    wxStaticText* header3 = new wxStaticText(scrolledWindow, wxID_ANY, "Attendance Perc");
    wxStaticText* header4 = new wxStaticText(scrolledWindow, wxID_ANY, "Outstanding Leaves");
    wxStaticText* header5 = new wxStaticText(scrolledWindow, wxID_ANY, "Leave Balance");

    // Set header font and size and style
    header1->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header2->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header3->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header4->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header5->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    // Set max width for Sr
    header1->SetMaxSize(wxSize(30, -1));
    
    gridSizer->Add(header1, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header2, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header3, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header4, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header5, 0, wxALIGN_CENTER | wxEXPAND);
    
    // Add data
    for (int i = 0; i < 10; i++)
    {
        wxStaticText* data1 = new wxStaticText(scrolledWindow, wxID_ANY, "1");
        wxStaticText* data2 = new wxStaticText(scrolledWindow, wxID_ANY, "john");
        wxStaticText* data3 = new wxStaticText(scrolledWindow, wxID_ANY, "80%");
        wxStaticText* data4 = new wxStaticText(scrolledWindow, wxID_ANY, "10");
        wxStaticText* data5 = new wxStaticText(scrolledWindow, wxID_ANY, "11");
    
        data1->SetMaxSize(wxSize(30, -1));
        
        gridSizer->Add(data1, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data2, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data3, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data4, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data5, 0, wxALIGN_CENTER | wxEXPAND);
    }
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &AttendanceReportPanel::OnShow, this);
}

void AttendanceReportPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
    }
    event.Skip(); // Ensure the default handling of the event
}

void AttendanceReportPanel::OnBack(wxCommandEvent &event)
{
    // Get the parent window
    wxSimplebook *simplebook = dynamic_cast<wxSimplebook *>(this->GetParent());
    InterfaceFrame *frame = dynamic_cast<InterfaceFrame *>(simplebook->GetParent());
    // Show the approval panel
    frame->ShowPage(InterfaceFrame::PID_PAGE_APPROVAL);
}

// AttendanceReportPanel.cpp