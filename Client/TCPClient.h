#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class TCPClient {
public:
    TCPClient();
    ~TCPClient();

    bool connectToServer(const std::string& serverIP, int port);
    void disconnect();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    SOCKET clientSocket_;
    bool isConnected_;
    WSADATA wsaData_;
};