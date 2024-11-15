// MyApp.h
#ifndef INTERFACE_H
#define INTERFACE_H

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

/*
This class initializes the application by creating and displaying the main frame.
*/
class Interface : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;
};

#endif
