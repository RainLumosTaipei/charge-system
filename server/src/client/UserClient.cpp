//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "client/UserClient.h"

using std::cout;
using std::endl;

Vehicle* UserClient::submitRequest(size_t uid, ChargingType mode, double power) {
        Vehicle* veh = new Vehicle(uid, mode, power);
        if (server.waitingArea.addVehicle(*veh)) {
            server.schedule();
            myRequests.push_back(*veh);
        }
        else veh=nullptr;
    return veh;
}

void UserClient::viewPileStatus(nlohmann::json &j) {
    for (auto& p:server.fastPiles) j.push_back(p);
    for (auto& p:server.tricklePiles) j.push_back(p);
}

bool UserClient::modifyMode(size_t queueNum, ChargingType newMode) {
    for (auto& req : myRequests) {
        if (req.queueId == queueNum) {
            if (server.waitingArea.modifyMode(req, newMode)) return true;
            break;
        }
    }
    return false;
}

bool UserClient::modifyPower(size_t queueNum, double newPower) {
    for (auto& req : myRequests) {
        if (req.queueId == queueNum) {
            if (server.waitingArea.modifyPower(req, newPower)) return true;
            break;
        }
    }
    return false;
}

void UserClient::cancelCharge(size_t queueNum, bool isInCharging) {
    for (auto req = myRequests.begin(); req != myRequests.end(); ++req) {
        if (req->queueId == queueNum) {
            if (server.waitingArea.cancelCharge(req, isInCharging)) {
                cout << "cancel success" << endl;
            } else {
                cout << "cancel failed" << endl;
            }
            myRequests.erase(req);
            return ;
        }
    }
    cout << "can not find id" << endl;
}

