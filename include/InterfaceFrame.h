// MyAppFrame.h
#ifndef INTERFACEFRAME_H
#define INTERFACEFRAME_H

#include "LoginPanel.h" // Include other panel headers as necessary
#include "GuardPanel.h"
#include "AdminPanel.h"
#include "LeavePanel.h"
#include "AttendanceReportPanel.h"
#include "EmployeePanel.h"
#include "ApprovalPanel.h"
#include <wx/wx.h>
#include <wx/simplebook.h>

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

    enum EPageID
    {
        PID_PAGE_LOGIN = 0,
        PID_PAGE_GUARD = 1,
        PID_PAGE_ADMIN = 2,
        PID_PAGE_EMPLOYEE = 3,
        PID_PAGE_LEAVE = 4,
        PID_PAGE_APPROVAL = 5,
        PID_PAGE_ATTENDANCE_REPORT = 6,
        // Add other page identifiers here
    };

    /**
     * @brief Displays the specified page in the main frame.
     * @param pageId The identifier of the page to display.
     */
    void ShowPage(int pageId);
    void updateStatusBar(const wxString& text, int field);

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

    

    

    // wxSimplebook to manage different pages
    wxSimplebook* simplebook;

   

    // Add pointers to various panels as needed
    // Example:
    LoginPanel* loginPanel;
    GuardPanel* guardPanel;
    AdminPanel* adminPanel;
    EmployeePanel* employeePanel;
    LeavePanel* leavePanel;
    ApprovalPanel* approvalPanel;
    AttendanceReportPanel* attendanceReportPanel;
    // EmployeeDashboard* employeeDashboard;
    // SupervisorDashboard* supervisorDashboard;
    // Add other panels here
};



#endif // INTERFACEFRAME_H
