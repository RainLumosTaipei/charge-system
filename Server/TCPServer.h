#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <functional>

#pragma comment(lib, "Ws2_32.lib")

class TCPServer {
public:
    using MessageHandler = std::function<void(const std::string&, SOCKET)>;

    TCPServer(int port);
    ~TCPServer();

    bool start();
    void stop();
    void setMessageHandler(MessageHandler handler);
    bool sendMessage(SOCKET clientSocket, const std::string& message);

private:
    void handleClient(SOCKET clientSocket);

    int port_;
    SOCKET listenSocket_;
    bool isRunning_;
    MessageHandler messageHandler_;
    WSADATA wsaData_;
};