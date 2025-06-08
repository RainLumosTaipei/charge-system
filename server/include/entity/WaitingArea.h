//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_WAITINGAREA_H
#define CHARGE_SYSTEM_WAITINGAREA_H

#include "Vehicle.h"
#include <vector>
#include <string>
#include <list>

// 等候区（最大6车位，F/T队列分别计数）
class WaitingArea {
public:
    std::list<Vehicle> vehicles;
    int maxSize;
    int fCount; // F队列计数器（从1开始）
    int tCount; // T队列计数器（从1开始）

    explicit WaitingArea(int size) : maxSize(size), fCount(1), tCount(1) {}

    // 添加车辆（生成排队号）
    bool addVehicle(Vehicle& veh) ;
    // 修改充电模式（等候区：重新生成排队号，移到对应队列末尾）
    bool modifyMode(Vehicle& veh, ChargingType newMode) ;

    // 修改请求电量（等候区：排队号不变，更新电量和时长）
    bool modifyPower(Vehicle& veh, double newPower) ;
    // 取消充电（等候区：移除；充电区：重新加入等候区）
    bool cancelCharge(std::list<Vehicle>::iterator& veh, bool isInCharging);
};

#endif //CHARGE_SYSTEM_WAITINGAREA_H
