#include "HorizontalBar.h"
#include <wx/dcbuffer.h>

wxBEGIN_EVENT_TABLE(HorizontalBar, wxPanel)
    EVT_PAINT(HorizontalBar::OnPaint)
    EVT_SIZE(HorizontalBar::OnSize)
wxEND_EVENT_TABLE()

HorizontalBar::HorizontalBar(wxWindow* parent, int duration)
    : wxPanel(parent, wxFULL_REPAINT_ON_RESIZE), m_presentHours(0), m_casualLeaveHours(0), m_earnedLeaveHours(0), m_officialLeaveHours(0)
{
    // Set the minimum size of the panel
    SetMinSize(wxSize(400, 100));
    this->duration = duration;
    // Set the colors for the different types of leave
    m_presentBrush = wxBrush(wxColour(76, 251, 126)); // Green
    m_casualLeaveBrush = wxBrush(wxColour(14,165,226)); // Blue
    m_earnedLeaveBrush = wxBrush(wxColour(26, 77, 186)); // Blue
    m_officialLeaveBrush = wxBrush(wxColour(44,44,116)); // Blue
    m_notMarkedBrush = wxBrush(wxColour(132, 132, 132)); // Grey

}

void HorizontalBar::SetData(int presentHours, int casualLeaveHours, int earnedLeaveHours, int officialLeaveHours)
{
    // Set the data for the bar
    m_presentHours = presentHours;
    m_casualLeaveHours = casualLeaveHours;
    m_earnedLeaveHours = earnedLeaveHours;
    m_officialLeaveHours = officialLeaveHours;
    Refresh(); // Trigger a repaint
}

void HorizontalBar::OnSize(wxSizeEvent& event)
{
    Refresh(); // Trigger a repaint
    event.Skip(); // Ensure the default handling of the event
}

void HorizontalBar::OnPaint(wxPaintEvent& event)
{
    // Create a device context
    wxPaintDC dc(this);
    // clear existing content
    dc.Clear();
    // Get the size of the panel
    wxSize size = GetClientSize();
    
    // Calculate the total hours
    int durationHours = (duration / 7) * 40;
    int totalHours = std::max(durationHours, m_presentHours+m_casualLeaveHours+m_earnedLeaveHours+m_officialLeaveHours);
    int barWidth = size.GetWidth();
    int barHeight = 50;

    // Calculate the width of each segment
    int presentWidth = (m_presentHours * barWidth) / totalHours;
    int casualLeaveWidth = (m_casualLeaveHours * barWidth) / totalHours;
    int earnedLeaveWidth = (m_earnedLeaveHours * barWidth) / totalHours;
    int officialLeaveWidth = (m_officialLeaveHours * barWidth) / totalHours;


    // Draw the background

    dc.SetBrush(m_notMarkedBrush);
    dc.DrawRectangle(0, 0, barWidth, barHeight);
    
    // Draw the segments
    dc.SetBrush(m_presentBrush);
    dc.DrawRectangle(0, 0, presentWidth, barHeight);

    dc.SetBrush(m_casualLeaveBrush);
    dc.DrawRectangle(presentWidth, 0, casualLeaveWidth, barHeight);

    dc.SetBrush(m_earnedLeaveBrush);
    dc.DrawRectangle(presentWidth + casualLeaveWidth, 0, earnedLeaveWidth, barHeight);

    dc.SetBrush(m_officialLeaveBrush);
    dc.DrawRectangle(presentWidth + casualLeaveWidth + earnedLeaveWidth, 0, officialLeaveWidth, barHeight);

    // draw a vertical dotted white line at 80% of the width
    dc.SetPen(wxPen(wxColour(255, 255, 255), 1, wxPENSTYLE_DOT));
    dc.DrawLine(barWidth * 0.8, 2, barWidth * 0.8, barHeight-2);

    dc.SetPen(wxPen(wxColour(0, 0, 0), 1, wxPENSTYLE_SOLID));
    

    // draw labels below the bar with a colored dot
    int dotSize = 10;
    int dotY = barHeight + 15;
    int labelY = barHeight + 10;

    int dotX = 10;
    int labelX = 30;
    int labelSpacing = 35;

    // create the labels
    std::string presentLabel = std::to_string(m_presentHours) + " Hrs Present";
    std::string casualLeaveLabel = std::to_string(m_casualLeaveHours) + " Hrs Casual Leave";
    std::string earnedLeaveLabel = std::to_string(m_earnedLeaveHours) + " Hrs Earned Leave";
    std::string officialLeaveLabel = std::to_string(m_officialLeaveHours) + " Hrs Official Leave";
    std::string notMarkedLabel = std::to_string(std::max(totalHours - m_presentHours - m_casualLeaveHours - m_earnedLeaveHours - m_officialLeaveHours,0)) + " Hrs Not Marked";

    // draw the present label
    dc.SetBrush(m_presentBrush);
    dc.DrawCircle(dotX, dotY, dotSize);
    dc.DrawText(presentLabel, labelX, labelY);
    // get the width of the text
    wxCoord textWidth, textHeight;
    dc.GetTextExtent(presentLabel, &textWidth, &textHeight);

    labelX += textWidth + labelSpacing;

    // draw the casual leave label
    dc.SetBrush(m_casualLeaveBrush);
    dc.DrawCircle(labelX, dotY, dotSize);
    dc.DrawText(casualLeaveLabel, labelX + 20, labelY);
    dc.GetTextExtent(casualLeaveLabel, &textWidth, &textHeight);

    labelX += textWidth + labelSpacing + 20;
    // if labelX + 100 > barWidth, then reset labelX to 30 and increase labelY by 20
    if (labelX + 100 > barWidth)
    {
        labelX = 10;
        labelY += 20;
        dotY += 20;
    }

    // draw the earned leave label

    dc.SetBrush(m_earnedLeaveBrush);
    dc.DrawCircle(labelX, dotY, dotSize);
    dc.DrawText(earnedLeaveLabel, labelX + 20, labelY);
    dc.GetTextExtent(earnedLeaveLabel, &textWidth, &textHeight);

    labelX += textWidth + labelSpacing + 20;

    if (labelX + 100 > barWidth)
    {
        labelX = 10;
        labelY += 20;
        dotY += 20;
    }

    // draw the official leave label

    dc.SetBrush(m_officialLeaveBrush);
    dc.DrawCircle(labelX, dotY, dotSize);
    dc.DrawText(officialLeaveLabel, labelX + 20, labelY);
    dc.GetTextExtent(officialLeaveLabel, &textWidth, &textHeight);

    labelX += textWidth + labelSpacing + 20;

    if (labelX + 100 > barWidth)
    {
        labelX = 10;
        labelY += 20;
        dotY += 20;
    }

    // draw the not marked label


    dc.SetBrush(m_notMarkedBrush);
    dc.DrawCircle(labelX, dotY, dotSize);
    dc.DrawText(notMarkedLabel, labelX + 20, labelY);

}