//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "client/AdminClient.h"

using std::cout;
using std::endl;


void AdminClient::viewWaitingVehicles() {
        cout << "Waiting Vehicles:" << endl;
        for (auto& veh : server.waitingArea.vehicles) {
            cout << "mode: " << veh.mode << ", id: " << veh.queueId
                 << ", power: " << veh.reqPower << endl;
        }
}
