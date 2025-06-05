//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_USERCLIENT_H
#define CHARGE_SYSTEM_USERCLIENT_H

#include <string>
#include <vector>
#include <list>
#include "server/Server.h"

// 用户客户端（注册、提交请求、修改、取消）
class UserClient {
public:
    Server& server;
    std::string userId;
    std::list<Vehicle> myRequests; // 我的充电请求

    UserClient(Server& s, std::string id) : server(s), userId(id) {}

    // 提交充电请求
    void submitRequest(std::string mode, double power) ;

    // 修改充电模式（等候区）
    void modifyMode(std::string queueNum, std::string newMode) ;
    // 修改请求电量（等候区）
    void modifyPower(std::string queueNum, double newPower) ;

    // 取消充电（等候区/充电区）
    void cancelCharge(std::string queueNum, bool isInCharging);
};


#endif //CHARGE_SYSTEM_USERCLIENT_H
