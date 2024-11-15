    // MyApp.h
    #ifndef WINDOW_H
    #define WINDOW_H

    #include <wx/wxprec.h>
    
    #ifndef WX_PRECOMP
        #include <wx/wx.h>
    #endif

    /*
    This class initializes the application by creating and displaying the main frame.

    WINDOW -> InterfaceFrame -> Panels (LoginPanel, EmployeeDashboard, SupervisorDashboard, etc.) 
    */
    class Window : public wxApp
    {
    public:
        virtual bool OnInit() override;
        virtual int OnExit() override;
    };

    #endif
