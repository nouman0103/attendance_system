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

    // horizontal line
    wxStaticLine *line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(line, 0, wxALL | wxEXPAND, 10);


    // leave application type dropdown
    // Leave Type
    const int verticalSpacing = 5; // Define a variable for vertical spacing
    
    
    // create a table to display leave history
    // format: Sr | Leave Type | Start Date | End Date | Reason | Status
        // Create a scrolled window
        wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    
    // Create a grid sizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(8, 3, 3);

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
    
    // Add data
    for (int i = 0; i < 10; i++)
    {
        wxStaticText* data1 = new wxStaticText(scrolledWindow, wxID_ANY, "1");
        wxStaticText* data2 = new wxStaticText(scrolledWindow, wxID_ANY, "john");
        wxStaticText* data3 = new wxStaticText(scrolledWindow, wxID_ANY, "Official Leave");
        wxStaticText* data4 = new wxStaticText(scrolledWindow, wxID_ANY, "12/1/2021");
        wxStaticText* data5 = new wxStaticText(scrolledWindow, wxID_ANY, "12/7/2021");
        wxStaticText* data6 = new wxStaticText(scrolledWindow, wxID_ANY, "Vacation");
        wxStaticText* data7 = new wxStaticText(scrolledWindow, wxID_ANY, "Pending");
        // add two buttons for approve and reject
        wxButton* approve = new wxButton(scrolledWindow, wxID_ANY, "Approve");
        wxButton* reject = new wxButton(scrolledWindow, wxID_ANY, "Reject");
    
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
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        buttonSizer->Add(approve, 0, wxALIGN_CENTER | wxEXPAND);
        buttonSizer->Add(reject, 0, wxALIGN_CENTER | wxEXPAND);
        gridSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxEXPAND);
    }
    
    // Set the sizer for the scrolled window
    scrolledWindow->SetSizer(gridSizer);
    gridSizer->Fit(scrolledWindow);
    
    // Add the scrolled window to the main sizer
    mainSizer->Add(scrolledWindow, 1, wxALL | wxEXPAND, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &ApprovalPanel::OnShow, this);
}

void ApprovalPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
    }
    event.Skip(); // Ensure the default handling of the event
}


// ApprovalPanel.cpp