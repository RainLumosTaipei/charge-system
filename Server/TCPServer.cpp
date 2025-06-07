#define _CRT_SECURE_NO_WARNINGS 1
#include "TCPServer.h"
#include <iostream>
#include <thread>

TCPServer::TCPServer(int port) : port_(port), listenSocket_(INVALID_SOCKET), isRunning_(false) {}

TCPServer::~TCPServer() {
    stop();
}

bool TCPServer::start() {
    // 初始化Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData_);
    if (result != 0) {
        std::cerr << "WSAStartup失败: " << result << std::endl;
        return false;
    }

    // 创建服务器套接字
    listenSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket_ == INVALID_SOCKET) {
        std::cerr << "socket创建失败: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // 绑定IP和端口
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port_);

    if (bind(listenSocket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "绑定失败: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket_);
        WSACleanup();
        return false;
    }

    // 开始监听
    if (listen(listenSocket_, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "监听失败: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket_);
        WSACleanup();
        return false;
    }

    isRunning_ = true;
    std::cout << "服务器启动，等待连接..." << std::endl;

    // 接受连接线程
    std::thread([this]() {
        while (isRunning_) {
            SOCKET clientSocket = accept(listenSocket_, NULL, NULL);
            if (clientSocket == INVALID_SOCKET) {
                if (isRunning_) {
                    std::cerr << "接受连接失败: " << WSAGetLastError() << std::endl;
                }
                continue;
            }

            std::cout << "客户端已连接" << std::endl;

            // 为每个客户端创建处理线程
            std::thread(&TCPServer::handleClient, this, clientSocket).detach();
        }
        }).detach();

        return true;
}

void TCPServer::stop() {
    isRunning_ = false;
    if (listenSocket_ != INVALID_SOCKET) {
        closesocket(listenSocket_);
        listenSocket_ = INVALID_SOCKET;
    }
    WSACleanup();
}

void TCPServer::setMessageHandler(MessageHandler handler) {
    messageHandler_ = handler;
}

bool TCPServer::sendMessage(SOCKET clientSocket, const std::string& message) {
    if (send(clientSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
        std::cerr << "发送失败: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

void TCPServer::handleClient(SOCKET clientSocket) {
    char recvBuffer[1024];
    int bytesReceived;

    do {
        bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0';
            if (messageHandler_) {
                messageHandler_(std::string(recvBuffer, bytesReceived), clientSocket);
            }
        }
        else if (bytesReceived == 0) {
            std::cout << "客户端已断开连接" << std::endl;
        }
        else {
            std::cerr << "接收失败: " << WSAGetLastError() << std::endl;
        }
    } while (bytesReceived > 0 && isRunning_);

    closesocket(clientSocket);
}