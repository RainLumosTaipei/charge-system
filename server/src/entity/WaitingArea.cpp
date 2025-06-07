//
// Created by zhou_zhengming on 2025/6/5.
//


#include "entity/WaitingArea.h"

bool WaitingArea::addVehicle(Vehicle &veh) {
    if (vehicles.size() >= maxSize) return false;
    if (veh.mode == "F")
    {
        veh.queueNum = "F" + std::to_string(1) ;
        fCount++;
    }
    else
    {
        veh.queueNum = "T" + std::to_string(1);
        tCount++;
    }
    vehicles.push_back(veh);
    return true;
}

bool WaitingArea::modifyMode(Vehicle &veh, std::string newMode) {
           for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (it->queueNum == veh.queueNum) {
                veh.mode = newMode;
                vehicles.erase(it);
                return addVehicle(veh); // 重新加入（生成新排队号，添加到末尾）
            }
        }
        return false;
}

bool WaitingArea::modifyPower(Vehicle &veh, double newPower) {
            for (auto& v : vehicles) {
            if (v.queueNum == veh.queueNum) {
                v.reqPower = newPower;
                v.chargeTime = newPower / (v.mode == "F" ? 30 : 7);
                return true;
            }
        }
        return false;
}

bool WaitingArea::cancelCharge(std::list<Vehicle>::iterator &veh, bool isInCharging) {
    if (isInCharging) {
        return addVehicle(*veh); // 重新加入等候区
    } else {
        vehicles.erase(veh);
        return true;
    }
}


