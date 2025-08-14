#include <wx/wx.h>
#include "../client.h"

class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, "CppWinsock", wxDefaultPosition, wxSize(800, 60)) {
        // auto* sizer = new wxBoxSizer(wxHORIZONTAL);
        
    }



};

class MyAPP : public wxApp {

public: 
    bool OnInit() override {
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyAPP);