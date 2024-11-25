// LeavePanel.cpp
#include "LeavePanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include <wx/datectrl.h>
#include <wx/datetimectrl.h>
#include <wx/statline.h> 

// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(LeavePanel, wxPanel)
    EVT_SHOW(LeavePanel::OnShow)
    EVT_BUTTON(wxID_ANY, LeavePanel::OnBack)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a LeavePanel object.
 * @param parent The parent window.
 */
LeavePanel::LeavePanel(wxWindow *parent, std::shared_ptr<DataManager> dm)
: wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // add padding
    mainSizer->AddSpacer(10);

    // back to attendance button
    wxButton *backButton = new wxButton(this, wxID_ANY, "Back to Attendance");
    mainSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 10);


    // title of LeavePanel
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "Leave Portal", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    this->dm = dm;

    // leave application type dropdown
    // Leave Type
    const int verticalSpacing = 5; // Define a variable for vertical spacing
    
    // Leave Type
    wxBoxSizer* leaveTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* leaveTypeLabel = new wxStaticText(this, wxID_ANY, "Leave Type:");
    leaveTypeLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    leaveTypeSizer->Add(leaveTypeLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    wxArrayString leaveTypes;
    
    leaveTypes.Add("Casual Leave");
    leaveTypes.Add("Earned Leave");
    leaveTypes.Add("Official Leave");
    leaveTypes.Add("Unpaid Leave");
    leaveType = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, leaveTypes, wxCB_READONLY);
    leaveTypeSizer->Add(leaveType, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(leaveTypeSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    // Start Date
    wxBoxSizer* startDateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* startDateLabel = new wxStaticText(this, wxID_ANY, "Start Date:");
    startDateLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    startDateSizer->Add(startDateLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    wxDateTime dt = wxDateTime::Now();
    startDate = new wxDatePickerCtrl(this, wxID_ANY, dt, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    startDateSizer->Add(startDate, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(startDateSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // End Date
    wxBoxSizer* endDateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* endDateLabel = new wxStaticText(this, wxID_ANY, "End Date:");
    endDateLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    endDateSizer->Add(endDateLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    endDate = new wxDatePickerCtrl(this, wxID_ANY, dt, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    endDateSizer->Add(endDate, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(endDateSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // Reason
    wxBoxSizer* reasonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* reasonLabel = new wxStaticText(this, wxID_ANY, "Reason:");
    reasonLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    reasonSizer->Add(reasonLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    reason = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    reasonSizer->Add(reason, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(reasonSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // Submit Button
    wxButton* submit = new wxButton(this, wxID_ANY, "Submit");
    mainSizer->Add(submit, 0, wxALL | wxALIGN_CENTER, verticalSpacing);
    // Bind the button to its event handler
    submit->Bind(wxEVT_BUTTON, &LeavePanel::OnSubmit, this);

    // add a label for leave balance
    leaveBalance = new wxStaticText(this, wxID_ANY, "Leave Balance: Casual - 10, Earned - 20", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    mainSizer->Add(leaveBalance, 0, wxALL | wxEXPAND, 10);



    // add horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);

    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
        // Create a scrolled window
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    gridSizer = new wxGridSizer(6, 5, 5);
    
    // Add data
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &LeavePanel::OnShow, this);
}

void LeavePanel::AddGridHeaders(){
    wxStaticText* header1 = new wxStaticText(scrolledWindow, wxID_ANY, "Sr");
    wxStaticText* header2 = new wxStaticText(scrolledWindow, wxID_ANY, "Leave Type");
    wxStaticText* header3 = new wxStaticText(scrolledWindow, wxID_ANY, "Start Date");
    wxStaticText* header4 = new wxStaticText(scrolledWindow, wxID_ANY, "End Date");
    wxStaticText* header5 = new wxStaticText(scrolledWindow, wxID_ANY, "Reason");
    wxStaticText* header6 = new wxStaticText(scrolledWindow, wxID_ANY, "Status");
    
    // Set header font and size and style
    header1->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header2->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header3->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header4->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header5->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header6->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    // Set max width for Sr
    header1->SetMaxSize(wxSize(10, -1));
    
    gridSizer->Add(header1, 0, wxALIGN_CENTER);
    gridSizer->Add(header2, 0, wxALIGN_CENTER);
    gridSizer->Add(header3, 0, wxALIGN_CENTER);
    gridSizer->Add(header4, 0, wxALIGN_CENTER);
    gridSizer->Add(header5, 0, wxALIGN_CENTER);
    gridSizer->Add(header6, 0, wxALIGN_CENTER);
    
}

void LeavePanel::UpdateUI(){
    leaveType->SetSelection(0);
    //Clear the form
    startDate->SetValue(wxDateTime::Now());
    endDate->SetValue(wxDateTime::Now());
    reason->Clear();
    // Clear the grid
    gridSizer->Clear(true);

    // Add the grid headers
    AddGridHeaders();

    // Get the leave applications
    std::shared_ptr<std::vector<std::shared_ptr<LeaveApplication>>> leaveApplications = dm->getCurrentEmployee()->getLeaveApplications();
    // Add the leave applications to the grid
    
    if (leaveApplications)
    {
        int i = leaveApplications->size();
        int j = 1;
        for (auto it = leaveApplications->rbegin(); it != leaveApplications->rend(); ++it)
        {
            std::shared_ptr<LeaveApplication> leaveApplication = *it;
            wxStaticText* sr = new wxStaticText(scrolledWindow, wxID_ANY, std::to_string(j));
            wxStaticText* leaveType = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getTaskType());
            wxStaticText* startDate = new wxStaticText(scrolledWindow, wxID_ANY, wxDateTime(leaveApplication->getStartDate()).FormatISODate());
            wxStaticText* endDate = new wxStaticText(scrolledWindow, wxID_ANY, wxDateTime(leaveApplication->getEndDate()).FormatISODate());
            wxStaticText* reason = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getReason());
            wxStaticText* status = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getStatus() == LeaveStatus::PENDING ? "Pending" : leaveApplication->getStatus() == LeaveStatus::APPROVED ? "Approved" : "Rejected");
            
            gridSizer->Add(sr, 0, wxALIGN_CENTER);
            gridSizer->Add(leaveType, 0, wxALIGN_CENTER);
            gridSizer->Add(startDate, 0, wxALIGN_CENTER);
            gridSizer->Add(endDate, 0, wxALIGN_CENTER);
            gridSizer->Add(reason, 0, wxALIGN_CENTER);
            gridSizer->Add(status, 0, wxALIGN_CENTER);
            
            i--;
            j++;
        }
        if (leaveApplications->size() == 0)
        {
            wxStaticText* noData = new wxStaticText(scrolledWindow, wxID_ANY, "No data available.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
            gridSizer->Add(noData, 0, wxALIGN_CENTER);
        }
    }
    else
    {
        wxStaticText* noData = new wxStaticText(scrolledWindow, wxID_ANY, "No data available!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        gridSizer->Add(noData, 0, wxALIGN_CENTER);
    }
    // Update the sizer for the scrolled window and refresh layout
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    gridSizer->Layout();  // This ensures the grid layout is updated
    scrolledWindow->Layout();  // Ensure the scrolled window itself is re-laid out
    
    // You can also call Fit() if needed, but Layout() should suffice for dynamic updates
    Layout();  // Ensure the main sizer is re-laid out
}

void LeavePanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        UpdateUI();   
    }
    event.Skip(); // Ensure the default handling of the event
}

void LeavePanel::OnBack(wxCommandEvent &event)
{
    wxSimplebook *simplebook = dynamic_cast<wxSimplebook *>(this->GetParent());
    InterfaceFrame *frame = dynamic_cast<InterfaceFrame *>(simplebook->GetParent());
    simplebook->SetSelection(InterfaceFrame::PID_PAGE_EMPLOYEE);
    frame->updateStatusBar("Back to attendance.", 1);
}

void LeavePanel::OnSubmit(wxCommandEvent &event)
{
    // Get the values from the form
    wxString leaveTypeValue = leaveType->GetStringSelection();
    wxDateTime startDateValue = wxDateTime();
    wxDateTime endDateValue = wxDateTime();
    // Get the start date
    if (startDate)
    {
        startDateValue = startDate->GetValue();
    }
    // Get the end date
    if (endDate)
    {
        endDateValue = endDate->GetValue();
    }

    // Get the reason
    wxString reasonValue = reason->GetValue();
    
    // Validate the form
    if (leaveTypeValue.IsEmpty() || reasonValue.IsEmpty())
    {
        wxMessageBox("Please fill in all fields.", "Error", wxOK | wxICON_ERROR);
        return;   
    }
    else if (startDateValue.IsLaterThan(endDateValue))
    {
        wxMessageBox("End date must be after start date.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    /*leaveTypes.Add("Casual Leave");
    leaveTypes.Add("Earned Leave");
    leaveTypes.Add("Official Leave");
    leaveTypes.Add("Unpaid Leave");*/
    std::shared_ptr<LeaveBalance> leaveBalance = dm->getLeaveBalance(dm->getCurrentEmployee()->getName());
    int year = startDateValue.GetYear();
    int days = ceil((endDateValue.GetTicks() - startDateValue.GetTicks()) / (24 * 60 * 60)) + 1;
    if (leaveTypeValue == "Casual Leave")
    {
        if (leaveBalance->applyCasualLeave( days,year) == false)
        {
            wxMessageBox("Insufficient leave balance.", "Error", wxOK | wxICON_ERROR);
            return;
        }
        
        std::shared_ptr<CasualLeaveApplication> casualLeaveApplication = std::make_shared<CasualLeaveApplication>(dm->getCurrentEmployee(), startDateValue.GetTicks(), endDateValue.GetTicks(), reasonValue.ToStdString(), wxDateTime::Now().GetTicks(), 0, LeaveStatus::APPROVED);
        
        dm->writeLeaveApplication(casualLeaveApplication);
        
        
    }
    else if (leaveTypeValue == "Earned Leave")
    {
        if (leaveBalance->applyEarnedLeave( days,year)== false)
        {
            wxMessageBox("Insufficient leave balance.", "Error", wxOK | wxICON_ERROR);
            return;
        }
        std::shared_ptr<EarnedLeaveApplication> earnedLeaveApplication = std::make_shared<EarnedLeaveApplication>(dm->getCurrentEmployee(), startDateValue.GetTicks(), endDateValue.GetTicks(), reasonValue.ToStdString(), wxDateTime::Now().GetTicks(), 0, LeaveStatus::PENDING);
        dm->writeLeaveApplication(earnedLeaveApplication);
    }
    else if (leaveTypeValue == "Official Leave")
    {
        std::shared_ptr<OfficialLeaveApplication> officialLeaveApplication = std::make_shared<OfficialLeaveApplication>(dm->getCurrentEmployee(), startDateValue.GetTicks(), endDateValue.GetTicks(), reasonValue.ToStdString(), wxDateTime::Now().GetTicks(), 0, LeaveStatus::PENDING);
        dm->writeLeaveApplication(officialLeaveApplication);
    }
    else if (leaveTypeValue == "Unpaid Leave")
    {
        std::shared_ptr<UnpaidLeaveApplication> unpaidLeaveApplication = std::make_shared<UnpaidLeaveApplication>(dm->getCurrentEmployee(), startDateValue.GetTicks(), endDateValue.GetTicks(), reasonValue.ToStdString(), wxDateTime::Now().GetTicks(), 0, LeaveStatus::PENDING);
        dm->writeLeaveApplication(unpaidLeaveApplication);
    }
    else
    {
        wxMessageBox("Please select a leave type.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxMessageBox("Leave application submitted successfully.", "Success", wxOK | wxICON_INFORMATION);
    UpdateUI();

}

// LeavePanel.cpp