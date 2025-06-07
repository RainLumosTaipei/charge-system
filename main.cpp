#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <sstream>
#include"Charging.h"
#include"ServerUser.h"



#pragma comment(lib, "Ws2_32.lib")

void UserRegister(SOCKET &clientSocket,ServerUser &user)
{
    // 接收和发送数据
    char recvBuffer[1024];
    int bytesReceived;

    std::string userId; //用户ID
    std::string userName;//用户名
    std::string car_Capacity;//车辆电池总容量（度）


        //响应客户端，进入用户注册模式，等待用户传来的数据包，数据包格式“id+name+car_Capacity+”
        bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0'; // 确保字符串以null结尾
            std::cout << "收到消息: " << recvBuffer << std::endl;
           std:: cout << recvBuffer << std::endl;

           //，解析数据包，划分对应字段
           std::istringstream iss(recvBuffer);
         
           // 使用 '+' 作为分隔符读取字段
           std::getline(iss, userId, '+');
           std::getline(iss, userName, '+');
           std::getline(iss, car_Capacity, '+');

           double Capacity = std::stod(car_Capacity);//汽车电量转为double类型

           //初始化用户
           user.userId = userId;
           user.car_Capacity = Capacity;
           user.userName = userName;

           // 输出结果
           std::cout << "ID: " << user.userId << std::endl;
           std::cout << "用户名: " << user.userName << std::endl;
           std::cout << "车辆电池容量: " << user.car_Capacity << std::endl;


        }
        else if (bytesReceived == 0) {
            std::cout << "客户端已断开连接" << std::endl;
        }
        else {
            std::cerr << "接收失败: " << WSAGetLastError() << std::endl;
        }
}

int TCPServer() {
    
    //初始化用户和用户队列
    ServerUser user;//用户
    std::vector<ServerUser> users;//存放所有用户信息


    // 初始化Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup失败: " << result << std::endl;
        return 1;
    }

    // 创建服务器套接字
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "socket创建失败: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // 绑定IP和端口
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 监听所有可用接口
    serverAddr.sin_port = htons(8888);  // 使用8888端口

    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "绑定失败: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // 开始监听
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "监听失败: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "服务器启动，等待连接..." << std::endl;

    // 接受连接
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "接受连接失败: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "客户端已连接" << std::endl;

    // 接收和发送数据
    char recvBuffer[1024];
    int bytesReceived;

    do {
        // 接收数据
        bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0'; // 确保字符串以null结尾
            std::cout << "收到消息: " << recvBuffer << std::endl;

            //用户注册
            if (strcmp(recvBuffer, "r") == 0 || strcmp(recvBuffer, "R") == 0)
            {
                std::cout << "进入用户注册模式" << std::endl;
                UserRegister(clientSocket,user);
                users.push_back(user);

                // 遍历并打印所有用户信息，验证是否注册成功，加入用户队列
                for (auto& user : users) {
                    std::cout << "用户队列" << std::endl;
                    user.printUser();
                   }
                continue;
            }

            // 发送响应
            std::string response = "服务器已收到消息: ";
            response += recvBuffer;
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        else if (bytesReceived == 0) {
            std::cout << "客户端已断开连接" << std::endl;
        }
        else {
            std::cerr << "接收失败: " << WSAGetLastError() << std::endl;
        }
    } while (bytesReceived > 0);

    // 关闭连接
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}





int main() {
    ChargingStation station;

    const int CARS_PER_BATCH = 6;        // 每批次车辆数
    const int BATCH_INTERVAL = 30;        // 批次间隔（秒）
    const int CAR_ARRIVAL_INTERVAL = 2;   // 车辆到达间隔（秒）

    int batchCount = 0;  // 记录批次数

    while (true) {
        batchCount++;
        cout << "\n=== 开始第 " << batchCount << " 轮充电服务 ===\n" << endl;

        // 直接在主线程中提交请求
        for (int i = 1; i <= CARS_PER_BATCH; i++) {
            string carId = "Car_" + to_string(batchCount) + "_" + to_string(i);
            bool isFastCharge = (i % 2 == 0);
            double requestPower = isFastCharge ? 10.0 : 5.0;

            station.submitRequest(carId, isFastCharge, requestPower);
            this_thread::sleep_for(chrono::seconds(CAR_ARRIVAL_INTERVAL));
        }

        cout << "\n=== 第 " << batchCount << " 轮车辆已全部进入等候区 ===\n" << endl;
        this_thread::sleep_for(chrono::seconds(BATCH_INTERVAL));
    }

    return 0;
}