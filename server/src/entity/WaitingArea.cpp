//
// Created by zhou_zhengming on 2025/6/5.
//


#include "entity/WaitingArea.h"

bool WaitingArea::addVehicle(Vehicle &veh) {
    if (vehicles.size() >= maxSize) return false;
    if (veh.mode == ChargingType::FAST)
    {
        veh.queueId = fCount ;
        fCount++;
    }
    else
    {
        veh.queueId = tCount;
        tCount++;
    }
    vehicles.push_back(veh);
    return true;
}

bool WaitingArea::modifyMode(Vehicle &veh, ChargingType newMode) {
           for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (it->queueId == veh.queueId) {
                veh.mode = newMode;
                vehicles.erase(it);
                return addVehicle(veh); // 重新加入（生成新排队号，添加到末尾）
            }
        }
        return false;
}

bool WaitingArea::modifyPower(Vehicle &veh, double newPower) {
            for (auto& v : vehicles) {
            if (v.queueId == veh.queueId) {
                v.reqPower = newPower;
                v.chargeTime = newPower / (v.mode == ChargingType::FAST ? 30 : 7);
                return true;
            }
        }
        return false;
}

bool WaitingArea::cancelCharge(std::list<Vehicle>::iterator &veh) {
    vehicles.erase(veh);
    return true;
}


