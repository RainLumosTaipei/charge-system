//
// Created by zhou_zhengming on 2025/6/5.
//

#include "entity/Vehicle.h"

void Vehicle::updateOrder() {
    order->setCost(totalFee);
    order->setStart(start);
    order->setEnd(end);
    order->setType(mode);
}

void to_json(nlohmann::json& j, const Vehicle& v){
    j["type"] = v.mode;
    j["start"] = v.start;
    j["end"] = v.end;
    j["chargeTime"] = v.chargeTime;
    j["servFee"] = v.servFee;
    j["elecFee"] = v.elecFee;
    j["totalFee"] = v.totalFee;
    j["queueId"] = v.queueId;
    j["reqPower"] = v.reqPower;
}