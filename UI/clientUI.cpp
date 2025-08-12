#include <wx/wx.h>
#include <iostream>
#include client.cpp


class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, "CppWinSock", 
                         wxDefaultPosition, wxSize(800, 600)) {
        auto* sizer = new wxBoxSizer(wxHORIZONTAL);
        
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(1, "&Hello...",
                            "Help string");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);
        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);
        n_button = new wxButton(this, wxID_ANY, "password");
        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuHelp, "&Help");
            
        SetMenuBar( menuBar );
            
        CreateStatusBar();
        SetStatusText("Online");
            
        // Bind(wxEVT_MENU, &wxFrame::OnHello, this, ID_Hello);
        // Bind(wxEVT_MENU, &wxFrame::OnAbout, this, wxID_ABOUT);
        // Bind(wxEVT_MENU, &wxFrame::OnExit, this, wxID_EXIT);
        m_text = new wxTextCtrl(this, wxID_ANY, "Sup!", 
                               wxDefaultPosition, wxDefaultSize, 
                               wxTE_MULTILINE);
        m_btn = new wxButton(this, wxID_ANY, "Click me");
        // n_btn = new wxButton(this, wxID_ANY, "Password");
        // two_btn = new wxButton(this, wxID_ANY, "Нажми меня");
        
        sizer->Add(m_text, 1, wxEXPAND | wxALL, 10);
        sizer->Add(m_btn, 0, wxALIGN_RIGHT | wxALL, 10);
        sizer->Add(n_button, 0, wxALIGN_RIGHT | wxALL, 10);
        // sizer->Add(two_btn, 0, wxALIGN_RIGHT | wxALL, 10);
        
        SetSizer(sizer);
        
        
        m_btn->Bind(wxEVT_BUTTON, &MainFrame::OnButton, this);
        n_button->Bind(wxEVT_BUTTON, &MainFrame::OnnButton, this);
    }

private:
    wxTextCtrl* m_text;
    wxButton* m_btn;
    wxButton* n_button;

    void OnnButton(wxCommandEvent& event) {
        wxMessageBox("Очистить историю?", "Подтверждение", wxYES_NO | wxICON_QUESTION);
    }

    void OnButton(wxCommandEvent& event) {
        m_text->AppendText("\nButtonIsClicked!");

        // std::string str;
        // m_text->text
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);