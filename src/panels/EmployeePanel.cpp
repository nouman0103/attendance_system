// EmployeePanel.cpp
#include "EmployeePanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include "DataManager.h"
#include <wx/statline.h> // Include wxStaticLine header
// Include other dashboards as needed

BEGIN_EVENT_TABLE(EmployeePanel, wxPanel)
    EVT_SHOW(EmployeePanel::OnShow)
    EVT_BUTTON(ID_LEAVE_PORTAL, EmployeePanel::OnLeavePortal)
    EVT_BUTTON(ID_PREV_WEEK, EmployeePanel::OnPrevWeek)
    EVT_BUTTON(ID_NEXT_WEEK, EmployeePanel::OnNextWeek)
END_EVENT_TABLE()


EmployeePanel::EmployeePanel(wxWindow* parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->dm = dm;
    
    // Add padding
    mainSizer->AddSpacer(10);

    // title of employee panel
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Weekly Report", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(title, 0, wxALL | wxEXPAND, 10);

    // write the date range (for example, "12/1/2021 - 12/7/2021")
    wxBoxSizer* dateRangeSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // Add left button
    wxButton* leftButton = new wxButton(this, ID_PREV_WEEK, "<");
    leftButton->SetMaxSize(wxSize(30, -1));
    dateRangeSizer->Add(leftButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    

    // Add date range label
    dateRangeText = new wxStaticText(this, wxID_ANY, "12/1/2021 - 12/7/2021", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    dateRangeSizer->Add(dateRangeText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    
    // Add right button
    wxButton* rightButton = new wxButton(this, ID_NEXT_WEEK, ">");
    rightButton->SetMaxSize(wxSize(30, -1));
    dateRangeSizer->Add(rightButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // add center sizer to main sizer
    mainSizer->Add(dateRangeSizer,0, wxALIGN_CENTER_HORIZONTAL);




    // create a fake bar
    m_barGraph = new HorizontalBar(this);
    mainSizer->Add(m_barGraph, 0, wxALL | wxEXPAND, 10);
    
    // add a horizontal separator
    mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);

    // add a button that says "Open Leave Portal"
    wxButton* leavePortalButton = new wxButton(this, ID_LEAVE_PORTAL, "Open Leave Portal");
    mainSizer->Add(leavePortalButton, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &EmployeePanel::OnShow, this);
}

EmployeePanel::~EmployeePanel()
{
    
}

void EmployeePanel::OnShow(wxShowEvent& event)
{
    if (event.IsShown())
    {
        // Update the date range text

        dateRangeText->SetLabel("12/1/2021 - 12/7/2021");


        // set bar Data
        m_barGraph->SetData(16, 5, 5, 5);
    

    }
    event.Skip(); // Ensure the default handling of the event
}

void EmployeePanel::OnLeavePortal(wxCommandEvent& event)
{
    wxSimplebook* simplebook = dynamic_cast<wxSimplebook*>(this->GetParent());
    InterfaceFrame* frame = dynamic_cast<InterfaceFrame*>(simplebook->GetParent());
    simplebook->SetSelection(InterfaceFrame::PID_PAGE_LEAVE);
    frame->updateStatusBar("Opening Leave Portal.", 1);
}

void EmployeePanel::OnPrevWeek(wxCommandEvent& event)
{
    wxMessageBox("Previous week", "Info", wxOK | wxICON_INFORMATION);
}

void EmployeePanel::OnNextWeek(wxCommandEvent& event)
{
    wxMessageBox("Next week", "Info", wxOK | wxICON_INFORMATION);
}
