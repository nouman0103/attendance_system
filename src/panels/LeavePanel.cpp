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
    
    wxComboBox* leaveType = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, leaveTypes, wxCB_READONLY);
    leaveTypeSizer->Add(leaveType, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(leaveTypeSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // Start Date
    wxBoxSizer* startDateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* startDateLabel = new wxStaticText(this, wxID_ANY, "Start Date:");
    startDateLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    startDateSizer->Add(startDateLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    wxDateTime dt = wxDateTime::Now();
    wxDatePickerCtrl* startDate = new wxDatePickerCtrl(this, wxID_ANY, dt, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    startDateSizer->Add(startDate, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(startDateSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // End Date
    wxBoxSizer* endDateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* endDateLabel = new wxStaticText(this, wxID_ANY, "End Date:");
    endDateLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    endDateSizer->Add(endDateLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    wxDatePickerCtrl* endDate = new wxDatePickerCtrl(this, wxID_ANY, dt, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    endDateSizer->Add(endDate, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(endDateSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // Reason
    wxBoxSizer* reasonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* reasonLabel = new wxStaticText(this, wxID_ANY, "Reason:");
    reasonLabel->SetMinSize(wxSize(100, -1)); // Set constant width for the label
    reasonSizer->Add(reasonLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, verticalSpacing);
    
    wxTextCtrl* reason = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    reasonSizer->Add(reason, 1, wxALL | wxEXPAND, verticalSpacing);
    mainSizer->Add(reasonSizer, 0, wxLEFT | wxRIGHT | wxEXPAND, verticalSpacing);
    
    // Submit Button
    wxButton* submit = new wxButton(this, wxID_ANY, "Submit");
    mainSizer->Add(submit, 0, wxALL | wxALIGN_CENTER, verticalSpacing);


    // add horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);

    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
        // Create a scrolled window
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    wxGridSizer* gridSizer = new wxGridSizer(6, 5, 5);
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
    
    // Add data
    for (int i = 0; i < 10; i++)
    {
        wxStaticText* data1 = new wxStaticText(scrolledWindow, wxID_ANY, "1");
        wxStaticText* data2 = new wxStaticText(scrolledWindow, wxID_ANY, "Casual Leave");
        wxStaticText* data3 = new wxStaticText(scrolledWindow, wxID_ANY, "12/1/2021");
        wxStaticText* data4 = new wxStaticText(scrolledWindow, wxID_ANY, "12/7/2021");
        wxStaticText* data5 = new wxStaticText(scrolledWindow, wxID_ANY, "Vacation");
        wxStaticText* data6 = new wxStaticText(scrolledWindow, wxID_ANY, "Approved");
    
        data1->SetMaxSize(wxSize(10, -1));
        // Set max width for data5
        data5->SetMaxSize(wxSize(200, -1));
    
        // Change data6 color based on status
        if (data6->GetLabel() == "Approved")
        {
            data6->SetForegroundColour(wxColour(0, 128, 0));
        }
        else if (data6->GetLabel() == "Pending")
        {
            data6->SetForegroundColour(wxColour(255, 165, 0));
        }
        else
        {
            data6->SetForegroundColour(wxColour(255, 0, 0));
        }
    
        gridSizer->Add(data1, 0, wxALIGN_CENTER);
        gridSizer->Add(data2, 0, wxALIGN_CENTER);
        gridSizer->Add(data3, 0, wxALIGN_CENTER);
        gridSizer->Add(data4, 0, wxALIGN_CENTER);
        gridSizer->Add(data5, 0, wxALIGN_CENTER);
        gridSizer->Add(data6, 0, wxALIGN_CENTER);
    }
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &LeavePanel::OnShow, this);
}

void LeavePanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
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

// LeavePanel.cpp