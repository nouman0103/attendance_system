// MyApp.cpp
#include "Interface.h"
#include "InterfaceFrame.h"

bool Interface::OnInit()
{
    // Initialize all available image handlers (optional, useful if using images)
    //wxInitAllImageHandlers();

    // Create the main application window
    InterfaceFrame* frame = new InterfaceFrame("Attendance and Leave Management System");

    // Set the frame as the top window
    SetTopWindow(frame);

    // Show the main frame
    frame->Show(true);

    return true;
}

int Interface::OnExit()
{
    // Perform any cleanup tasks if necessary
    return 0;
}
