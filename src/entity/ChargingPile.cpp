//
// Created by zhou_zhengming on 2025/6/5.
//

#include <ctime>
#include "entity/ChargingPile.h"

ChargingPile::ChargingPile(std::string t, double p)
: type(t), power(p), isFaulty(false), count(0), totalTime(0), totalPower(0) {

}

// 添加车辆（计算启动/结束时间）
void ChargingPile::addVehicle(Vehicle &veh, time_t now) {
    if (queue.empty()) {
        veh.start = now;
        veh.end = now + veh.chargeTime * 3600; // 转换为秒
        queue.push_back(veh);
        count++;
        totalTime += veh.chargeTime;
        totalPower += veh.reqPower;
    } else {
        queue.push_back(veh); // 加入排队（第二个车位）
    }
}

void ChargingPile::processCompletion(time_t now) {
    std::vector<Vehicle> newQueue;
    for (auto& v : queue) {
        if (v.end > now) newQueue.push_back(v); // 未完成，保留
        else calculateBill(v); // 完成，计算费用（假设已实现）
    }
    queue = newQueue;
}

void ChargingPile::calculateBill(Vehicle &veh) {
    struct tm* tmStart = localtime(&veh.start);
    struct tm* tmEnd = localtime(&veh.end);
    double peak = 0, flat = 0, valley = 0;

    // 分割充电时段（简化处理，实际需遍历每小时）
    int startHour = tmStart->tm_hour;
    int endHour = tmEnd->tm_hour;
    double duration = difftime(veh.end, veh.start) / 3600; // 总时长（小时）

    // 峰时（10-15, 18-21）
    if ((startHour >= 10 && startHour < 15) || (startHour >= 18 && startHour < 21)) {
        veh.elecFee = 1.0 * veh.reqPower;
    }
    // 平时（7-10, 15-18, 21-23）
    else if ((startHour >= 7 && startHour < 10) || (startHour >= 15 && startHour < 18) || (startHour >= 21 && startHour < 23)) {
        veh.elecFee = 0.7 * veh.reqPower;
    }
    // 谷时（23-7）
    else {
        veh.elecFee = 0.4 * veh.reqPower;
    }
    veh.servFee = 0.8 * veh.reqPower;
    veh.totalFee = veh.elecFee + veh.servFee;
}




