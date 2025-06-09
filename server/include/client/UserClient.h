//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_USERCLIENT_H
#define CHARGE_SYSTEM_USERCLIENT_H

#include <string>
#include <vector>
#include <list>
#include "server/Server.h"
//#include "../entity/Vehicle.h"

// 用户客户端（注册、提交请求、修改、取消）
class UserClient {
public:
    Server& server;
    std::string userId;
    std::list<Vehicle> myRequests; // 我的充电请求

    UserClient(Server& s, std::string id) : server(s), userId(id) {}

    // 提交充电请求
    Vehicle* submitRequest(size_t uid, ChargingType mode, double power) ;

    // 查看充电桩状态
    void viewPileStatus(nlohmann::json &j) ;

    // 修改充电模式（等候区）
    bool modifyMode(size_t queueNum, ChargingType newMode) ;
    // 修改请求电量（等候区）
    bool modifyPower(size_t queueNum, double newPower) ;

    // 取消充电（等候区/充电区）
    void cancelCharge(size_t queueNum);
};


#endif //CHARGE_SYSTEM_USERCLIENT_H
