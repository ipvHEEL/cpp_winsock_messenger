// client_gui.cpp
#include <wx/wx.h>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

// ---- Forward declare only the class, not use it yet ----
class ChatFrame;

// ---- TCPClient: теперь с отложенными методами ----
class TCPClient {
private:
    SOCKET m_sock;
    ChatFrame* m_frame;
    std::thread m_recvThread;
    bool m_running;

public:
    TCPClient(ChatFrame* frame);

    bool Connect();
    void Send(const std::string& msg);
    void ReceiveLoop();

    // Метод будет определён позже, когда ChatFrame будет известен
    void PostLog(const std::string& msg);

    ~TCPClient();
};

// ---- Теперь определяем ChatFrame ----
class ChatFrame : public wxFrame {
private:
    wxTextCtrl* m_input;
    wxTextCtrl* m_output;
    wxButton*   m_sendBtn;
    TCPClient*  m_client;

public:
    ChatFrame() : wxFrame(nullptr, wxID_ANY, "Chat Client", wxDefaultPosition, wxSize(600, 400)) {
        auto* sizer = new wxBoxSizer(wxVERTICAL);

        m_output = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
        m_input = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        m_sendBtn = new wxButton(this, wxID_ANY, "Send");

        sizer->Add(m_output, 1, wxEXPAND | wxALL, 5);
        sizer->Add(m_input, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
        sizer->Add(m_sendBtn, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

        SetSizer(sizer);

        m_client = new TCPClient(this);

        if (m_client->Connect()) {
            m_output->SetDefaultStyle(wxTextAttr(*wxBLUE));
            m_output->AppendText("Connected to server.\n");
        } else {
            m_output->SetDefaultStyle(wxTextAttr(*wxRED));
            m_output->AppendText("Failed to connect.\n");
        }

        m_sendBtn->Bind(wxEVT_BUTTON, &ChatFrame::OnSend, this);
        m_input->Bind(wxEVT_TEXT_ENTER, &ChatFrame::OnSend, this);
        Bind(wxEVT_THREAD, &ChatFrame::OnThreadEvent, this);
    }

    void OnSend(wxCommandEvent& event) {
        wxString msg = m_input->GetValue();
        if (!msg.IsEmpty()) {
            m_client->Send(msg.ToStdString());
            m_input->Clear();
        }
    }

    void OnThreadEvent(wxThreadEvent& event) {
        wxString text = event.GetString();
        m_output->AppendText(text + "\n");
    }

    ~ChatFrame() {
        delete m_client;
    }
};

// ---- Теперь можно определить методы TCPClient ----
TCPClient::TCPClient(ChatFrame* frame)
    : m_frame(frame), m_sock(INVALID_SOCKET), m_running(false) {}

bool TCPClient::Connect() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        PostLog("WSAStartup failed!");
        return false;
    }

    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET) {
        PostLog("Socket creation failed!");
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1111);

    PostLog("Connecting to server...");

    if (::connect(m_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        PostLog("Connect failed!");
        closesocket(m_sock);
        WSACleanup();
        return false;
    }

    PostLog("Connected to server!");
    m_running = true;
    m_recvThread = std::thread(&TCPClient::ReceiveLoop, this);
    return true;
}

void TCPClient::Send(const std::string& msg) {
    if (m_sock != INVALID_SOCKET && m_running) {
        ::send(m_sock, msg.c_str(), msg.length(), 0);
        PostLog("You: " + msg);
    }
}

void TCPClient::ReceiveLoop() {
    char buffer[256];
    while (m_running) {
        int bytes = recv(m_sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            std::string reply = "Server: ";
            reply += buffer;
            PostLog(reply);
        } else {
            PostLog("Connection closed by server.");
            break;
        }
    }
    m_running = false;
    closesocket(m_sock);
    WSACleanup();
}

void TCPClient::PostLog(const std::string& msg) {
    wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
    event.SetString(msg.c_str());
    wxQueueEvent(m_frame, event.Clone());  // Теперь ChatFrame полностью определён
}

TCPClient::~TCPClient() {
    m_running = false;
    if (m_recvThread.joinable()) {
        m_recvThread.join();
    }
}

// ---- wxApp ----
class MyApp : public wxApp {
public:
    bool OnInit() override {
        ChatFrame* frame = new ChatFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);