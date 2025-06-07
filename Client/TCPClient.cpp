#define _CRT_SECURE_NO_WARNINGS 1
#include "TCPClient.h"
#include <iostream>

TCPClient::TCPClient() : clientSocket_(INVALID_SOCKET), isConnected_(false) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData_) != 0) {
        std::cerr << "WSAStartup失败" << std::endl;
    }
}

TCPClient::~TCPClient() {
    disconnect();
}

bool TCPClient::connectToServer(const std::string& serverIP, int port) {
    if (isConnected_) {
        disconnect();
    }

    clientSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket_ == INVALID_SOCKET) {
        std::cerr << "socket创建失败: " << WSAGetLastError() << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "连接服务器失败: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket_);
        clientSocket_ = INVALID_SOCKET;
        return false;
    }

    isConnected_ = true;
    return true;
}

void TCPClient::disconnect() {
    if (clientSocket_ != INVALID_SOCKET) {
        closesocket(clientSocket_);
        clientSocket_ = INVALID_SOCKET;
    }
    isConnected_ = false;
}

bool TCPClient::sendMessage(const std::string& message) {
    if (!isConnected_) return false;

    if (send(clientSocket_, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
        std::cerr << "发送失败: " << WSAGetLastError() << std::endl;
        disconnect();
        return false;
    }
    return true;
}

std::string TCPClient::receiveMessage() {
    if (!isConnected_) return "";

    char recvBuffer[1024];
    int bytesReceived = recv(clientSocket_, recvBuffer, sizeof(recvBuffer), 0);

    if (bytesReceived > 0) {
        return std::string(recvBuffer, bytesReceived);
    }
    else if (bytesReceived == 0) {
        std::cout << "服务器已断开连接" << std::endl;
    }
    else {
        std::cerr << "接收失败: " << WSAGetLastError() << std::endl;
    }

    disconnect();
    return "";
}