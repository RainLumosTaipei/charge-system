//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_ADMINCLIENT_H
#define CHARGE_SYSTEM_ADMINCLIENT_H


#include "server/Server.h"

// 管理员客户端（查看状态、报表）
class AdminClient {
public:
    Server& server;

    explicit AdminClient(Server& s) : server(s) {}

    // 查看充电桩状态
    void viewPileStatus() ;

    // 查看等候区车辆
    void viewWaitingVehicles() ;
};



#endif //CHARGE_SYSTEM_ADMINCLIENT_H
