// MyAppFrame.h
#ifndef INTERFACEFRAME_H
#define INTERFACEFRAME_H

#include <wx/wx.h>

/*
This class sets up the main window, including menus, status bars, and initial panels.
*/
class InterfaceFrame : public wxFrame
{
public:
    /**
     * @brief Constructs a MyAppFrame object.
     * @param title The title of the window.
     */
    InterfaceFrame(const wxString& title);

private:
    /**
     * @brief Initializes the menu bar.
     */
    void InitializeMenu();

    /**
     * @brief Initializes the status bar.
     */
    void InitializeStatusBar();

    /**
     * @brief Displays the specified panel in the main frame.
     * @param panel Pointer to the wxPanel to display.
     */
    void ShowPanel(wxPanel* panel);

    // Add pointers to various panels as needed
    // Example:
    // LoginPanel* loginPanel;
    // EmployeeDashboard* employeeDashboard;
    // SupervisorDashboard* supervisorDashboard;
    // Add other panels here
};

#endif // INTERFACEFRAME_H
