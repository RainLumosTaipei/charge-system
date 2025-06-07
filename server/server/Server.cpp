//
// Created by zhou_zhengming on 2025/6/5.
//

#include "Server.h"
#include <float.h>

void Server::schedule() {
        time_t now = time(nullptr);
        std::vector<std::list<Vehicle>::iterator> toRemove;

        for (auto veh = waitingArea.vehicles.begin(); veh != waitingArea.vehicles.end(); ++veh) {
            std::vector<ChargingPile>& piles = (veh->mode == "F") ? fastPiles : tricklePiles;
            double minTime = DBL_MAX;
            ChargingPile* selected = nullptr;

            for (auto& pile : piles) {
                if (pile.isFaulty || !pile.hasSpace()) continue;
                double waitTime = (pile.queue.empty()) ? 0 : (pile.queue.back().end - now);
                waitTime = std::max(waitTime, 0.0); // 等待时间不能为负
                double totalTime = waitTime + veh->chargeTime;
                if (totalTime < minTime) {
                    minTime = totalTime;
                    selected = &pile;
                }
            }

            if (selected) {
                selected->addVehicle(*veh, now);
                toRemove.push_back(veh);
            }
        }

        // 移除已调度的车辆
    for (auto& iter: toRemove) {
        waitingArea.vehicles.erase(iter);
    }

}

Server::Server(int fastNum, int trickleNum, int waitSize) : waitingArea(waitSize) {
        for (int i = 0; i < fastNum; ++i) fastPiles.emplace_back("Fast", 30);
        for (int i = 0; i < trickleNum; ++i) tricklePiles.emplace_back("Trickle", 7);

}

void Server::handleFault(ChargingPile &pile) {
        pile.isFaulty = true;
        std::vector<Vehicle> faultyQueue = pile.queue;
        pile.queue.clear(); // 清空故障桩队列

        // 优先调度故障队列到同类型（快充/慢充）的其他正常桩
        std::vector<ChargingPile>& targetPiles = (pile.type == "Fast") ? fastPiles : tricklePiles;
        for (auto& veh : faultyQueue) {
            scheduleVehicle(veh, targetPiles); // 自定义调度函数，确保优先处理故障队列
        }
}

void Server::scheduleVehicle(Vehicle &veh, std::vector<ChargingPile> &piles) {
            time_t now = time(nullptr);
        double minTime = DBL_MAX;
        ChargingPile* selected = nullptr;
        for (auto& p : piles) {
            if (p.isFaulty || !p.hasSpace()) continue;
            double waitTime = (p.queue.empty()) ? 0 : (p.queue.back().end - now);
            waitTime = std::max(waitTime, 0.0);
            if (waitTime + veh.chargeTime < minTime) {
                minTime = waitTime + veh.chargeTime;
                selected = &p;
            }
        }
        if (selected) selected->addVehicle(veh, now);
}

