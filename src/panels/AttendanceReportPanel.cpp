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
    employeeComboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, employees, wxCB_READONLY);
    employeeSizer->Add(employeeComboBox, 1, wxALL | wxEXPAND, 5);
    employeeComboBox->SetSelection(0);

    // add month and year selector
    wxBoxSizer* monthYearSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* monthLabel = new wxStaticText(this, wxID_ANY, "Month:");
    monthLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    monthYearSizer->Add(monthLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    wxArrayString months;
    months.Add("January");
    months.Add("February");
    months.Add("March");
    months.Add("April");
    months.Add("May");
    months.Add("June");
    months.Add("July");
    months.Add("August");
    months.Add("September");
    months.Add("October");
    months.Add("November");
    months.Add("December");

    monthComboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, months, wxCB_READONLY);
    monthYearSizer->Add(monthComboBox, 1, wxALL | wxEXPAND, 5);
    monthComboBox->SetSelection(0);

    wxStaticText* yearLabel = new wxStaticText(this, wxID_ANY, "Year:");
    yearLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    monthYearSizer->Add(yearLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    wxArrayString years;
    years.Add("2021");
    years.Add("2022");
    years.Add("2023");
    years.Add("2024");
    years.Add("2025");
    yearComboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, years, wxCB_READONLY);
    monthYearSizer->Add(yearComboBox, 1, wxALL | wxEXPAND, 5);
    yearComboBox->SetSelection(0);

    // set curreen month and year
    wxDateTime now = wxDateTime::Now();
    monthComboBox->SetSelection(now.GetMonth());
    yearComboBox->SetSelection(now.GetYear() - 2021);

    selectedMonth = now.GetMonth();
    selectedYear = now.GetYear() - 2021;
    
    

    mainSizer->Add(monthYearSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);

    mainSizer->Add(employeeSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);
    // bind the combobox with onSelection
    employeeComboBox->Bind(wxEVT_COMBOBOX, &AttendanceReportPanel::onSelection, this);
    // bind the combobox with onSelection
    monthComboBox->Bind(wxEVT_COMBOBOX, &AttendanceReportPanel::onSelection, this);
    // bind the combobox with onSelection
    yearComboBox->Bind(wxEVT_COMBOBOX, &AttendanceReportPanel::onSelection, this);


    // horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);

    
    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
    // Create a scrolled window
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    gridSizer = new wxFlexGridSizer(5, 3, 3);
    setHeaders();

    
    
    
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &AttendanceReportPanel::OnShow, this);
}

void AttendanceReportPanel::setHeaders(){
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
}

void AttendanceReportPanel::updateUI(){
    // clear
    gridSizer->Clear(true);

    // Add headers again
    setHeaders();
    
    // Add data
    // get all employees from the data manager
    std::shared_ptr<std::vector<Employee>> employees = dm->getEmployees();

    wxString selectedEmployee = employeeComboBox->GetStringSelection();
    
    int i = 1;
    for (Employee employee : *employees)
    {
        // update the dropdown
        if(selectedEmployeeIndex != 0 && selectedEmployee != employee.getName()){
            continue;
        }




        // get current employyee
        std::shared_ptr<Employee> currentEmployee = dm->getEmployee(employee.getName());
        std::shared_ptr<LeaveBalance> leaveBalance = dm->getLeaveBalance(currentEmployee->getName());
        // get leave balance
        int casualLeaveBalance = leaveBalance->getCasualLeave(selectedYear + 2021);
        int earnedLeaveBalance = leaveBalance->getEarnedLeave(selectedYear + 2021);
        //Create a string to display the leave balance
        std::string leaveBalanceString = "Casual - " + std::to_string(casualLeaveBalance) + ", Earned - " + std::to_string(earnedLeaveBalance);
        time_t now = time(0);

        // get pending leave applications
        int pendingLeaveApplications = currentEmployee->getPendingLeaves(now);


        // get attendance percentage
        int attendancePercentage = currentEmployee->getAttendancePercentage(selectedMonth+1, selectedYear + 2021);

        wxStaticText* data1 = new wxStaticText(scrolledWindow, wxID_ANY, std::to_string(i));
        wxStaticText* data2 = new wxStaticText(scrolledWindow, wxID_ANY, currentEmployee->getName());
        wxStaticText* data3 = new wxStaticText(scrolledWindow, wxID_ANY, std::to_string(attendancePercentage) + "%");
        wxStaticText* data4 = new wxStaticText(scrolledWindow, wxID_ANY, std::to_string(pendingLeaveApplications));
        wxStaticText* data5 = new wxStaticText(scrolledWindow, wxID_ANY, leaveBalanceString);
    
        data1->SetMaxSize(wxSize(30, -1));
        
        gridSizer->Add(data1, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data2, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data3, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data4, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data5, 0, wxALIGN_CENTER | wxEXPAND);
        i++;
    }

    
    
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    gridSizer->Layout();  // This ensures the grid layout is updated
    scrolledWindow->Layout();  // Ensure the scrolled window itself is re-laid out
    
    // You can also call Fit() if needed, but Layout() should suffice for dynamic updates
    Layout();
}

void AttendanceReportPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        // reset selected employee index
        selectedEmployeeIndex = 0;

        // get current time
        wxDateTime now = wxDateTime::Now();
        // reset selected month
        selectedMonth = now.GetMonth();
        // reset selected year
        selectedYear = now.GetYear() - 2021;

        employeeComboBox->Clear();
        employeeComboBox->Append("Show All Employees");
        std::shared_ptr<std::vector<Employee>> employees = dm->getEmployees();
        for (Employee employee : *employees)
        {
            employeeComboBox->Append(employee.getName());
        }
        employeeComboBox->SetSelection(0);


        // Update the UI
        updateUI();
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

void AttendanceReportPanel::onSelection(wxCommandEvent &event)
{
    selectedEmployeeIndex = employeeComboBox->GetSelection();
    selectedMonth = monthComboBox->GetSelection();
    selectedYear = yearComboBox->GetSelection();
    updateUI();
}

// AttendanceReportPanel.cpp