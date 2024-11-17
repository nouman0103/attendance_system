// EmployeePanel.cpp
#include "EmployeePanel.h"
#include "InterfaceFrame.h" // To access ShowPanel
#include <iostream>
#include "DataManager.h"
#include <wx/statline.h> // Include wxStaticLine header
// Include other dashboards as needed


EmployeePanel::EmployeePanel(wxWindow* parent, std::shared_ptr<DataManager> dm)
    : wxPanel(parent, wxID_ANY)
{
    // Create sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->dm = dm;

    // add a horizontal separator
    mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL), 0, wxEXPAND | wxALL, 5);
    
    SetSizer(mainSizer);
}

EmployeePanel::~EmployeePanel()
{
    
}

