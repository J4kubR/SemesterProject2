#include "main.h"
#include "frame.h"
#include "atmega.h"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Interface", wxDefaultPosition, wxDefaultSize);
    frame->Centre();
    frame->Show(true);
    return true;
}

