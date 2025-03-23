#include <wx/wx.h>
#include <modbus/modbus.h>
#include "atmega.h"
#include "frame.h"

#ifndef PANEL
#define PANEL



class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, MyFrame* frame);

    void setPickupLocation();
    void setDropoffLocation();
    
    void OnClick(wxCommandEvent &);

    void setX(uint16_t val);
    void setY(uint16_t val);
    void setZ(uint16_t val);

    void setX_drop(uint16_t val);
    void setY_drop(uint16_t val);
    void setZ_drop(uint16_t val);
    


    void setCO(uint16_t val);
    void setWait_Close(uint16_t val);
    void setWait_Open(uint16_t val);
    
    private:
    MyFrame* frame;

    wxDECLARE_EVENT_TABLE();
};



enum ButtonId
{
    PickUp_button_id = wxID_LAST + 1,
    Stop_button_id = wxID_LAST + 2,
    OpenGripper_id = wxID_LAST + 3
    
};

#endif