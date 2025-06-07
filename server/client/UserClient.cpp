//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "UserClient.h"

using std::cout;
using std::endl;

Vehicle* UserClient::submitRequest(std::string mode, double power) {
        Vehicle* veh = new Vehicle(mode, power);
        if (server.waitingArea.addVehicle(*veh)) {
            server.schedule();
            myRequests.push_back(*veh);
        }
        else veh=nullptr;
    return veh;
}

void UserClient::modifyMode(std::string queueNum, std::string newMode) {
        for (auto& req : myRequests) {
            if (req.queueNum == queueNum) {
                if (server.waitingArea.modifyMode(req, newMode)) {
                    cout << "mode modify success, new id: " << req.queueNum << endl;
                } else {
                    cout << "modify failed" << endl;
                }
                return;
            }
        }
        cout << "can not find id" << endl;
}

bool UserClient::modifyPower(std::string queueNum, double newPower) {
    for (auto& req : myRequests) {
        if (req.queueNum == queueNum) {
            if (server.waitingArea.modifyPower(req, newPower))return true;
            break;
        }
    }
    return false;
}

void UserClient::cancelCharge(std::string queueNum, bool isInCharging) {
        for (auto req = myRequests.begin(); req != myRequests.end(); ++req) {
            if (req->queueNum == queueNum) {
                if (server.waitingArea.cancelCharge(req, isInCharging)) {
                    cout << "cancel success" << endl;
                } else {
                    cout << "cancel failed" << endl;
                }
                myRequests.erase(req);
                return;
            }
        }
        cout << "can not find id" << endl;
}

