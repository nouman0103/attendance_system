// LeavePanel.cpp
#include "LeavePanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include <wx/datectrl.h>
#include <wx/datetimectrl.h>
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