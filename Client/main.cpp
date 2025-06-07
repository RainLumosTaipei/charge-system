
//Creater by HeChuan
//Client_main.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include"UserClient.h"


#pragma comment(lib, "Ws2_32.lib")


std::string Register()
{
    // 发送和接收数据
    std::string userInput;
    char recvBuffer[1024];
    int bytesReceived;

    std::string userId; //用户ID
    std::string userName;//用户名
    std::string car_Capacity;//车辆电池总容量（度）

    std::cout << "请输入用户ID" << std::endl;
    std::cin >> userId;
    std::cout << "请输入用户名" << std::endl;
    std::cin >> userName;
    std::cout << "请输入车辆电池总容量" << std::endl;
    std::cin >> car_Capacity;
   
    userInput = userId + "\+";
    userInput += userName;
    userInput += "\+";
    userInput += car_Capacity;
    userInput += "\+";//形成用户注册数据包，以+号链接各项信息

    std::cout << userInput << std::endl;

    return userInput;
}

int TCPClient() {

    UserClient user;//用户
    std::vector<UserClient> users;//存放所有用户信息

  
    // 初始化Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup失败: " << result << std::endl;
        return 1;
    }

    // 创建客户端套接字
    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "socket创建失败: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);  // 服务器端口
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);  // 服务器IP

    // 连接到服务器
    if (connect(connectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "连接失败: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "已连接到服务器" << std::endl;

    // 发送和接收数据
    std::string userInput;
    char recvBuffer[1024];
    int bytesReceived;

    while (true) {
        std::cout << "请输入消息(,按'R'注册、按'L'登录、输入'exit'退出): ";
        std::cout << "continue3" << std::endl;
        std::getline(std::cin, userInput);
        std::cout << "continue4" << std::endl;
        if (userInput == "exit") {
            break;
        }

        if (userInput == "r" || userInput == "R")
        {
            send(connectSocket, userInput.c_str(), userInput.length(), 0);//告知服务端，用户进入注册
            std::string userTmp;
            userTmp=Register();
            send(connectSocket, userTmp.c_str(), userTmp.length(), 0);//发送用户注册数据包
            std::cout << "continue1" << std::endl;
            continue;

        }
        std::cout << "continue2" << std::endl;
        // 发送数据
        if (send(connectSocket, userInput.c_str(), userInput.length(), 0) == SOCKET_ERROR) {
            std::cerr << "发送失败: " << WSAGetLastError() << std::endl;
            break;
        }

        // 接收响应
        bytesReceived = recv(connectSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0';
            std::cout << "服务器回复: " << recvBuffer << std::endl;
        }
        else if (bytesReceived == 0) {
            std::cout << "服务器已关闭连接" << std::endl;
            break;
        }
        else {
            std::cerr << "接收失败: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // 关闭连接
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}

int main()
{
    TCPClient();
    return 0;
}


