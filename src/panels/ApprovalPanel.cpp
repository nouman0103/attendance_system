// ApprovalPanel.cpp
#include "ApprovalPanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include <wx/datectrl.h>
#include <wx/datetimectrl.h>
#include <wx/statline.h> 

// Include other dashboards as needed

wxBEGIN_EVENT_TABLE(ApprovalPanel, wxPanel)
    EVT_SHOW(ApprovalPanel::OnShow)
wxEND_EVENT_TABLE()

/**
 * @brief Constructs a ApprovalPanel object.
 * @param parent The parent window.
 */
ApprovalPanel::ApprovalPanel(wxWindow *parent, std::shared_ptr<DataManager> dm)
: wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // add padding
    mainSizer->AddSpacer(10);

    // title of LeavePanel
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "Leave Management Portal", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    this->dm = dm;

    // button that says monthly attendance report
    wxButton *monthlyAttendanceReport = new wxButton(this, wxID_ANY, "View Attendance Reports");
    mainSizer->Add(monthlyAttendanceReport, 0, wxALL | wxALIGN_CENTER, 10);
    // bind the button with OnViewReports
    monthlyAttendanceReport->Bind(wxEVT_BUTTON, &ApprovalPanel::OnViewReports, this);


    // horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);


    // button that says outstanding leaves
    outstandingLeavesButton = new wxButton(this, wxID_ANY, "Filter Outstanding Leaves");
    mainSizer->Add(outstandingLeavesButton, 0, wxALL | wxALIGN_CENTER, 10);
    // bind the button with filterOutstandingLeaves
    outstandingLeavesButton->Bind(wxEVT_BUTTON, &ApprovalPanel::filterOutstandingLeaves, this);

    
    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
    // Create a scrolled window
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    gridSizer = new wxFlexGridSizer(8, 3, 3);
    //AddHeaders();
    AddHeaders();
    
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &ApprovalPanel::OnShow, this);

}

void ApprovalPanel::AddHeaders(){
    // Set growable columns
    gridSizer->AddGrowableCol(0, 1); // Sr
    gridSizer->AddGrowableCol(1, 1); // Employee
    gridSizer->AddGrowableCol(2, 1); // Leave Type
    gridSizer->AddGrowableCol(3, 1); // Start Date
    gridSizer->AddGrowableCol(4, 1); // End Date
    gridSizer->AddGrowableCol(5, 1); // Reason
    gridSizer->AddGrowableCol(6, 1); // Status
    gridSizer->AddGrowableCol(7, 1); // Action


    wxStaticText* header1 = new wxStaticText(scrolledWindow, wxID_ANY, "Sr");
    wxStaticText* header2 = new wxStaticText(scrolledWindow, wxID_ANY, "Employee");
    wxStaticText* header3 = new wxStaticText(scrolledWindow, wxID_ANY, "Leave Type");
    wxStaticText* header4 = new wxStaticText(scrolledWindow, wxID_ANY, "Start Date");
    wxStaticText* header5 = new wxStaticText(scrolledWindow, wxID_ANY, "End Date");
    wxStaticText* header6 = new wxStaticText(scrolledWindow, wxID_ANY, "Reason");
    wxStaticText* header7 = new wxStaticText(scrolledWindow, wxID_ANY, "Status");
    wxStaticText* header8 = new wxStaticText(scrolledWindow, wxID_ANY, "Action");
    
    // Set header font and size and style
    header1->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header2->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header3->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header4->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header5->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header6->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header7->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    header8->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    // Set max width for Sr
    header1->SetMaxSize(wxSize(30, -1));
    
    gridSizer->Add(header1, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header2, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header3, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header4, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header5, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header6, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header7, 0, wxALIGN_CENTER | wxEXPAND);
    gridSizer->Add(header8, 0, wxALIGN_CENTER | wxEXPAND);
}

void ApprovalPanel::updateUI(){
    std::string position = dm->getCurrentEmployee()->getPosition();
    std::vector<std::shared_ptr<LeaveApplication>> leaveApplications = dm->getAllLeaveApplications();
    if (position == "Supervisor")
    {
        setLoggedInAsPosition(ROLE_SUPERVISOR);
    }
    else if (position == "Director")
    {
        setLoggedInAsPosition(ROLE_DIRETOR);
    }
    else
    {
        setLoggedInAsPosition(ROLE_NONE);
    }
    // Clear the grid sizer
    gridSizer->Clear(true);
    // Add the headers again
    AddHeaders();

    std::map<LeaveStatus, wxString> statusMap = {
        {LeaveStatus::PENDING, "Pending"},
        {LeaveStatus::APPROVED, "Approved"},
        {LeaveStatus::REJECTED, "Rejected"}
    };

    int i = 1;
    for (std::shared_ptr<LeaveApplication> leaveApplication : leaveApplications)
    {
        if (filtered){
            if (leaveApplication->getStatus() != LeaveStatus::PENDING){
                continue;
            }
        }
        wxStaticText* data1 = new wxStaticText(scrolledWindow, wxID_ANY, std::to_string(i));
        wxStaticText* data2 = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getEmployee()->getName());
        wxStaticText* data3 = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getTaskType());
        wxStaticText* data4 = new wxStaticText(scrolledWindow, wxID_ANY, wxDateTime(leaveApplication->getStartDate()).FormatISODate());
        wxStaticText* data5 = new wxStaticText(scrolledWindow, wxID_ANY, wxDateTime(leaveApplication->getEndDate()).FormatISODate());
        wxStaticText* data6 = new wxStaticText(scrolledWindow, wxID_ANY, leaveApplication->getReason());
        wxStaticText* data7 = new wxStaticText(scrolledWindow, wxID_ANY, statusMap[leaveApplication->getStatus()]);
                    
    
        data1->SetMaxSize(wxSize(30, -1));
        // Set max width for data5
        data7->SetMaxSize(wxSize(200, -1));
    
        // Change data6 color based on status
        if (data7->GetLabel() == "Approved")
        {
            data7->SetForegroundColour(wxColour(0, 128, 0));
        }
        else if (data7->GetLabel() == "Pending")
        {
            data7->SetForegroundColour(wxColour(255, 165, 0));
        }
        else
        {
            data7->SetForegroundColour(wxColour(255, 0, 0));
        }
    
        // Bind the buttons to their respective event handlers
        //approve->Bind(wxEVT_BUTTON, &ApprovalPanel::OnApprove, this);
        //reject->Bind(wxEVT_BUTTON, &ApprovalPanel::OnReject, this);
    
        gridSizer->Add(data1, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data2, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data3, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data4, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data5, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data6, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(data7, 0, wxALIGN_CENTER | wxEXPAND);
        // create a single sizer for the buttons
        if (leaveApplication->getStatus() == LeaveStatus::PENDING){ //&& !(getLoggedInAsPosition() == ROLE_SUPERVISOR && leaveApplication->getTaskType() == "Earned Leave")){
            wxButton* approve = new wxButton(scrolledWindow, wxID_ANY, "Approve");
            approve->SetClientData(new EventData(leaveApplication));
            wxButton* reject = new wxButton(scrolledWindow, wxID_ANY, "Reject");
            reject->SetClientData(new EventData(leaveApplication));
            wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
            buttonSizer->Add(approve, 0, wxALIGN_CENTER | wxEXPAND);
            buttonSizer->Add(reject, 0, wxALIGN_CENTER | wxEXPAND);
            gridSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxEXPAND);

            // Bind the buttons to their respective event handlers
            approve->Bind(wxEVT_BUTTON, &ApprovalPanel::OnApprovalButton, this);
            reject->Bind(wxEVT_BUTTON, &ApprovalPanel::OnRejectButton, this);
        }
        else{
            wxStaticText* empty = new wxStaticText(scrolledWindow, wxID_ANY, "");
            gridSizer->Add(empty, 0, wxALIGN_CENTER | wxEXPAND);
        }
        i++;
    }

    // Update the sizer for the scrolled window and refresh layout
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    gridSizer->Layout();  // This ensures the grid layout is updated
    scrolledWindow->Layout();  // Ensure the scrolled window itself is re-laid out
    
    // You can also call Fit() if needed, but Layout() should suffice for dynamic updates
    Layout();  // Ensure the main sizer is re-laid out
}

void ApprovalPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        filtered = false;
        outstandingLeavesButton->SetLabel("Filter Outstanding Leaves");
        updateUI();            
    }
    event.Skip(); // Ensure the default handling of the event
}

void ApprovalPanel::filterOutstandingLeaves(wxCommandEvent &event)
{
    if(!filtered)
    {
        filtered = true;
        outstandingLeavesButton->SetLabel("Show All Leaves");
    }
    else
    {
        filtered = false;
        outstandingLeavesButton->SetLabel("Filter Outstanding Leaves");
    }
    updateUI();
}

void ApprovalPanel::setLoggedInAsPosition(int position)
{
    loggedInAsPosition = position;
}

int ApprovalPanel::getLoggedInAsPosition()
{
    return loggedInAsPosition;
}

void ApprovalPanel::OnViewReports(wxCommandEvent &event)
{
    wxSimplebook *simplebook = dynamic_cast<wxSimplebook *>(this->GetParent());
    InterfaceFrame *frame = dynamic_cast<InterfaceFrame *>(simplebook->GetParent());
    // get the current page
    int currentPage = simplebook->GetSelection();
    // check if the current page is the login page
    if (currentPage == InterfaceFrame::PID_PAGE_ATTENDANCE_REPORT)
    {
        wxMessageBox("You are already on the Attendance Report page", "Attendance Report", wxOK | wxICON_INFORMATION);
        return;
    }
    // show the login page
    frame->ShowPage(InterfaceFrame::PID_PAGE_ATTENDANCE_REPORT);
    // loginPanel->clearFields();

    // wxMessageBox("You have been logged out", "Logout", wxOK | wxICON_INFORMATION);
}


void ApprovalPanel::OnApprovalButton(wxCommandEvent &event){
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    EventData* data = static_cast<EventData*>(button->GetClientData());
    if (data) {
        std::shared_ptr<LeaveApplication> leaveApplication = data->getLeaveApplication();
        // apply for approval
        bool approvalStatus = leaveApplication->approve(*dm->getCurrentEmployee());
        wxMessageBox("Leave Type: " + leaveApplication->getTaskType() + ", Current Employee: " + dm->getCurrentEmployee()->getName(), "Approval", wxOK | wxICON_INFORMATION);
        if (approvalStatus)
        {
            wxMessageBox("Leave Approved", "Approval", wxOK | wxICON_INFORMATION);
            updateUI();
        }
        else
        {
            wxMessageBox("Leave Approval Failed", "Approval", wxOK | wxICON_ERROR);
        }
    } else {
        wxMessageBox("Error: Client data is null", "Error", wxOK | wxICON_ERROR);
    }
}

void ApprovalPanel::OnRejectButton(wxCommandEvent &event){
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    EventData* data = static_cast<EventData*>(button->GetClientData());
    if (data) {
        std::shared_ptr<LeaveApplication> leaveApplication = data->getLeaveApplication();
        // apply for rejection
        bool rejectionStatus = leaveApplication->reject(*dm->getCurrentEmployee());
        if (rejectionStatus)
        {
            wxMessageBox("Leave Rejected", "Rejection", wxOK | wxICON_INFORMATION);
            updateUI();
        }
        else
        {
            wxMessageBox("Leave Rejection Failed", "Rejection", wxOK | wxICON_ERROR);
        }
    } else {
        wxMessageBox("Error: Client data is null", "Error", wxOK | wxICON_ERROR);
    }
}

EventData::EventData(std::shared_ptr<LeaveApplication> leaveApplication){
    this->leaveApplication = leaveApplication;
}

std::shared_ptr<LeaveApplication> EventData::getLeaveApplication(){
    return leaveApplication;
}


// ApprovalPanel.cpp