//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "AdminClient.h"

using std::cout;
using std::endl;

void AdminClient::viewPileStatus() {
        cout << "Fast Pile Status:" << endl;
        for (auto& pile : server.fastPiles) {
            cout << "type: fast, err: " << (pile.isFaulty ? "yes" : "no")
                 << ", len: " << pile.queue.size() << endl;
        }
        cout << "Slow Pile Status:" << endl;
        for (auto& pile : server.tricklePiles) {
            cout << "type: slow, err: " << (pile.isFaulty ? "yes" : "no")
                 << ", len:" << pile.queue.size() << endl;
        }
}

void AdminClient::viewWaitingVehicles() {
        cout << "Waiting Vehicles:" << endl;
        for (auto& veh : server.waitingArea.vehicles) {
            cout << "mode: " << veh.mode << ", id: " << veh.queueNum
                 << ", power: " << veh.reqPower << endl;
        }
}
