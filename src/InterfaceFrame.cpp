// MyAppFrame.cpp
#include "InterfaceFrame.h"
#include "DataManager.h"
// Include other panel headers as necessary

/**
 * @brief Constructs the main application frame.
 * @param title The title of the window.
 */
InterfaceFrame::InterfaceFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    // Initialize the menu and status bar
    InitializeMenu();
    InitializeStatusBar();
    std::shared_ptr<DataManager> dm = std::make_shared<DataManager>();

    // Create and display the initial panel (e.g., LoginPanel)
    // Assuming you have a LoginPanel class derived from wxPanel
    // loginPanel = new LoginPanel(this);
    // ShowPanel(loginPanel);

    simplebook = new wxSimplebook(this, wxID_ANY);

    // Add pages to the simplebook
    loginPanel = new LoginPanel(simplebook,dm);
    guardPanel = new GuardPanel(simplebook, dm);
    adminPanel = new AdminPanel(simplebook,dm);
    employeePanel = new EmployeePanel(simplebook,dm);
    leavePanel = new LeavePanel(simplebook,dm);
    approvalPanel = new ApprovalPanel(simplebook, dm);

    simplebook->AddPage(loginPanel, "Login");
    simplebook->AddPage(guardPanel, "Guard");
    simplebook->AddPage(adminPanel, "Admin");
    simplebook->AddPage(employeePanel, "Employee");
    simplebook->AddPage(leavePanel, "Leave");
    simplebook->AddPage(approvalPanel, "Approval");

    ShowPage(PID_PAGE_LOGIN);

    // Use a sizer to manage layout
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(simplebook, 1, wxEXPAND);
    SetSizer(sizer);
    Layout();

    // Assuming you have a GuardPanel class derived from wxPanel
    // guardPanel = new GuardPanel(this);
    // ShowPanel(guardPanel);

    // For demonstration, we'll just display a simple message
    // wxPanel* initialPanel = new wxPanel(this, wxID_ANY);
    // wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    // sizer->Add(new wxStaticText(initialPanel, wxID_ANY, "Welcome to the Attendance and Leave Management System"),
    //            0, wxALL | wxALIGN_CENTER, 15);
    // initialPanel->SetSizer(sizer);
    // ShowPanel(initialPanel);
}

/**
 * @brief Initializes the menu bar with basic menus.
 *
 * You can expand this method to add more menus and menu items as needed.
 */
void InterfaceFrame::InitializeMenu()
{
    wxIcon icon;
    if (icon.LoadFile("icon.ico", wxBITMAP_TYPE_ICO))
    {
        SetIcon(icon); // Set the frame's icon
    }
    else
    {
        wxLogError("Could not load icon 'icon.ico'.");
    }

    wxMenuBar *menuBar = new wxMenuBar;

    // File Menu
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-W", "Quit this program");
    menuBar->Append(fileMenu, "&File");

    // Help Menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    menuBar->Append(helpMenu, "&Help");
    
    // Account Menu
    wxMenu *accountMenu = new wxMenu;
    accountMenu->Append(wxID_CANCEL, "Logout\tAlt-X", "Logout from the system");
    menuBar->Append(accountMenu, "&Account");

    // Set the menu bar
    SetMenuBar(menuBar);

    // Bind menu events
    Bind(wxEVT_MENU, [=](wxCommandEvent &)
         { Close(true); }, wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent &)
         { wxMessageBox("Attendance and Leave Management System\nVersion 1.0",
                        "About", wxOK | wxICON_INFORMATION); }, wxID_ABOUT);
    Bind(wxEVT_MENU, [=](wxCommandEvent &)
            {
                // get the current page
                int currentPage = simplebook->GetSelection();
                // check if the current page is the login page
                if (currentPage == PID_PAGE_LOGIN)
                {
                    wxMessageBox("You are already logged out", "Logout", wxOK | wxICON_INFORMATION);
                    return;
                }
                // show the login page
                ShowPage(PID_PAGE_LOGIN);
                loginPanel->clearFields();

                wxMessageBox("You have been logged out", "Logout", wxOK | wxICON_INFORMATION);

            }, wxID_CANCEL);

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

void InterfaceFrame::updateStatusBar(const wxString &text, int field)
{
    SetStatusText(text, field);
}

/**
 * @brief Displays the specified panel in the main frame.
 *
 * This method removes any existing panels and adds the new one.
 * @param panel Pointer to the wxPanel to display.
 */
void InterfaceFrame::ShowPage(int pageId)
{
    simplebook->SetSelection(pageId);
}