//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_SERVER_H
#define CHARGE_SYSTEM_SERVER_H

#include "entity/ChargingPile.h"
#include "entity/WaitingArea.h"
#include <vector>
#include <ctime>
#include "entity/User.h"

// 服务器端（调度、计费、故障处理）
class Server {
public:
    std::vector<User> *users;
    std::vector<ChargingPile> fastPiles;   // 快充桩（默认2个）
    std::vector<ChargingPile> tricklePiles; // 慢充桩（默认3个）
    WaitingArea waitingArea;          // 等候区（容量6）

    Server(std::vector<User> &users,int fastNum = 2, int trickleNum = 3, int waitSize = 6) ;

    // 调度策略：选择使车辆完成时长（等待+充电）最短的充电桩队列
    void schedule() ;

    // 故障处理：标记充电桩故障，重新调度队列车辆（优先级调度）
    void handleFault(ChargingPile& pile) ;

    //启动充电桩之后，进行调度车辆
    void handleOpen(ChargingPile& pile);

private:
    // 辅助函数：调度单个车辆到目标桩集合
    void scheduleVehicle(time_t now,Vehicle& veh, std::vector<ChargingPile>& piles);
};


#endif //CHARGE_SYSTEM_SERVER_H
