#include "frame.h"
#include "panel.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, wxSize(800, 600))
{
    
    auto top_panel = new MyPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, this);
    top_panel->SetBackgroundColour(wxColor(200, 190, 190));

    auto top_sizer = new wxBoxSizer(wxVERTICAL);
    auto pick_up_button = new wxButton(top_panel, PickUp_button_id, "Pick and Place", wxDefaultPosition, wxDefaultSize);

    top_sizer->Add(pick_up_button, 1, wxEXPAND | wxALL, 10);
    top_panel->SetSizer(top_sizer);

    auto bottom_panel = new MyPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, this);
    bottom_panel->SetBackgroundColour(wxColor(180, 180, 200));

    auto start_button = new wxButton(bottom_panel, Stop_button_id, "Stop", wxDefaultPosition, wxSize(500, 120));
    auto my_button = new wxButton(bottom_panel, OpenGripper_id, "Open gripper", wxDefaultPosition, wxSize(500, 120));

    auto bottom_sizer = new wxBoxSizer(wxVERTICAL);
    bottom_sizer->Add(start_button, 0, wxEXPAND | wxALL, 10);
    bottom_sizer->Add(my_button, 0, wxEXPAND | wxALL, 10);

    bottom_panel->SetSizer(bottom_sizer);

    big_brick_text = new wxStaticText(this, wxID_ANY, "Big Brick count: 0");
    medium_brick_text = new wxStaticText(this, wxID_ANY, "Medium Brick count: 0");
    small_brick_text = new wxStaticText(this, wxID_ANY, "Small Brick count: 0");
    Fail_count_text = new wxStaticText(this, wxID_ANY, "Fail count: 0");

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(top_panel, 1, wxEXPAND | wxALL, 10);
    sizer->Add(bottom_panel, 1, wxEXPAND | wxALL, 10);
    sizer->Add(big_brick_text, 1, wxEXPAND | wxALL, 10);
    sizer->Add(medium_brick_text, 1, wxEXPAND | wxALL, 10);
    sizer->Add(small_brick_text, 1, wxEXPAND | wxALL, 10);
    sizer->Add(Fail_count_text, 1, wxEXPAND | wxALL, 10);
    SetSizer(sizer);
    Layout();
}
