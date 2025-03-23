#include <wx/wx.h>
#include <panel.h>

#ifndef FRAME
#define FRAME



class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    wxStaticText *big_brick_text;
    wxStaticText *medium_brick_text;
    wxStaticText *small_brick_text;
    wxStaticText *Fail_count_text;

    void updateBigBrickText(int value) // Function that updates text in the gui with the corresponding value
    {
        wxString str;
        str.Printf(wxT("Big Brick count: %d"), value);
        big_brick_text->SetLabelText(str);
    }

    void updateMediumBrickText(int value) // Function that updates text in the gui with the corresponding value
    {
        wxString str;
        str.Printf(wxT("Medium Brick count: %d"), value);
        medium_brick_text->SetLabelText(str);
    }

    void updateFailText(int value) // Function that updates text in the gui with the corresponding value
    {
        wxString str;
        str.Printf(wxT("Fail count: %d"), value);
        Fail_count_text->SetLabelText(str);
    }

    void updateSmallBrickText(int value) // Function that updates text in the gui with the corresponding value
    {
        wxString str;
        str.Printf(wxT("Small Brick count: %d"), value);
        small_brick_text->SetLabelText(str);
    }

};

#endif