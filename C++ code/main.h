#include <wx/wx.h>

#ifndef APP
#define APP

class MyApp : public wxApp{
    public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

#endif