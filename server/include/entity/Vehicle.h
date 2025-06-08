//
// Created by zhou_zhengming on 2025/6/5.
//

#ifndef CHARGE_SYSTEM_VEHICLE_H
#define CHARGE_SYSTEM_VEHICLE_H

#include <string>
#include "ChargingType.h"
#include "util/JsonHelper.h"

class Vehicle {
public:
    size_t uid;
    size_t id;
    ChargingType mode;       // F(快充) / T(慢充)
    size_t queueId;   // 排队号
    double reqPower;   // 请求电量（度）
    double chargeTime; // 充电时长（小时，reqPower / 功率）
    time_t start;      // 启动时间（秒）
    time_t end;        // 结束时间（秒）
    

    // 计费信息
    double elecFee;    // 充电费
    double servFee;    // 服务费
    double totalFee;   // 总费用

    Vehicle(size_t uid, ChargingType t, double rp)
    :uid(uid), mode(t), reqPower(rp), elecFee(0), servFee(0), totalFee(0) {
        chargeTime = rp / (t == ChargingType::FAST ? 30 : 7); // 快充30度/时，慢充7度/时
    }

    friend void to_json(nlohmann::json& , const Vehicle& );
};

#endif //CHARGE_SYSTEM_VEHICLE_H
