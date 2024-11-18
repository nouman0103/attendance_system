#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include <wx/wx.h>

class HorizontalBar : public wxPanel
{
public:
    HorizontalBar(wxWindow* parent);

    void SetData(int presentHours, int casualLeaveHours, int earnedLeaveHours, int officialLeaveHours);

private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

    int m_presentHours;
    int m_casualLeaveHours;
    int m_earnedLeaveHours;
    int m_officialLeaveHours;

    wxBrush m_presentBrush;
    wxBrush m_casualLeaveBrush;
    wxBrush m_earnedLeaveBrush;
    wxBrush m_officialLeaveBrush;
    wxBrush m_notMarkedBrush;




    wxDECLARE_EVENT_TABLE();
};

#endif // HORIZONTAL_H