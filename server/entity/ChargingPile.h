//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_CHARGINGPILE_H
#define CHARGE_SYSTEM_CHARGINGPILE_H

#include <string>
#include <vector>
#include "Vehicle.h"

// 充电桩类
class ChargingPile {
public:
    std::string type;       // Fast / Trickle
    double power;      // 功率（度/时）
    std::vector<Vehicle> queue; // 队列（最多2辆车：1充电，1排队）
    bool isFaulty;     // 是否故障
    int count;         // 累计充电次数
    double totalTime;  // 累计充电时长（小时）
    double totalPower; // 累计充电电量（度）

    ChargingPile(std::string t, double p);

    bool hasSpace() const { return queue.size() < 2; } // 队列有空位（<2）
    // 添加车辆（计算启动/结束时间）
    void addVehicle(Vehicle& veh, time_t now) ;
    // 处理充电完成（移除已完成车辆，更新队列）
    void processCompletion(time_t now) ;
private:
    // 计算电费（根据时间区间）
    void calculateBill(Vehicle& veh);
};

#endif //CHARGE_SYSTEM_CHARGINGPILE_H
