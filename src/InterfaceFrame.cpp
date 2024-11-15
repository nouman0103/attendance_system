// MyAppFrame.cpp
#include "InterfaceFrame.h"
//#include "LoginPanel.h" // Make sure to create LoginPanel.h and LoginPanel.cpp
// Include other panel headers as necessary

/**
 * @brief Constructs the main application frame.
 * @param title The title of the window.
 */
InterfaceFrame::InterfaceFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    // Initialize the menu and status bar
    InitializeMenu();
    InitializeStatusBar();

    // Create and display the initial panel (e.g., LoginPanel)
    // Assuming you have a LoginPanel class derived from wxPanel
    // loginPanel = new LoginPanel(this);
    // ShowPanel(loginPanel);

    // For demonstration, we'll just display a simple message
    wxPanel* initialPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(initialPanel, wxID_ANY, "Welcome to the Attendance and Leave Management System"),
               0, wxALL | wxALIGN_CENTER, 15);
    initialPanel->SetSizer(sizer);
    ShowPanel(initialPanel);
}

/**
 * @brief Initializes the menu bar with basic menus.
 *
 * You can expand this method to add more menus and menu items as needed.
 */
void InterfaceFrame::InitializeMenu()
{
    wxMenuBar* menuBar = new wxMenuBar;

    // File Menu
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    menuBar->Append(fileMenu, "&File");

    // Help Menu
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    menuBar->Append(helpMenu, "&Help");

    // Set the menu bar
    SetMenuBar(menuBar);

    // Bind menu events
    Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); }, wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {
        wxMessageBox("Attendance and Leave Management System\nVersion 1.0",
                     "About", wxOK | wxICON_INFORMATION);
    }, wxID_ABOUT);
}

/**
 * @brief Initializes the status bar with default messages.
 */
void InterfaceFrame::InitializeStatusBar()
{
    CreateStatusBar(2);
    SetStatusText("Welcome to the Attendance and Leave Management System", 0);
    SetStatusText("Ready", 1);
}

/**
 * @brief Displays the specified panel in the main frame.
 *
 * This method removes any existing panels and adds the new one.
 * @param panel Pointer to the wxPanel to display.
 */
void InterfaceFrame::ShowPanel(wxPanel* panel)
{
    // Remove existing children (panels)
    wxSizer* currentSizer = GetSizer();
    if (currentSizer)
    {
        currentSizer->Clear(true); // Delete the existing panel
    }
    else
    {
        currentSizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(currentSizer);
    }

    // Add the new panel
    currentSizer->Add(panel, 1, wxEXPAND | wxALL, 5);
    Layout();
}
