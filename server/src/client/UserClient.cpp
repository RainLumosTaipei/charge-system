//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "client/UserClient.h"

using std::cout;
using std::endl;

void UserClient::submitRequest(std::string mode, double power) {
        Vehicle veh(mode, (mode == "F") ? 30 : 7, power);
        if (server.waitingArea.addVehicle(veh)) {
            myRequests.push_back(veh);
            cout << "submit success! id: " << veh.queueNum << endl;
        } else {
            cout << "waiting area has already no spaces, please wait..." << endl;
        }
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

void UserClient::modifyPower(std::string queueNum, double newPower) {
        for (auto& req : myRequests) {
            if (req.queueNum == queueNum) {
                if (server.waitingArea.modifyPower(req, newPower)) {
                    cout << "power modify success" << endl;
                } else {
                    cout << "modify failed" << endl;
                }
                return;
            }
        }
        cout << "can not find id" << endl;
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

