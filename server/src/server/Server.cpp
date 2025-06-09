//
// Created by zhou_zhengming on 2025/6/5.
//

#include "server/Server.h"
#include <float.h>

void Server::schedule() {
        time_t now = time(nullptr);
        std::vector<std::list<Vehicle>::iterator> toRemove;

        for (auto& pile : fastPiles)pile.processCompletion(now);
        for (auto& pile : tricklePiles)pile.processCompletion(now);

        for (auto veh = waitingArea.vehicles.begin(); veh != waitingArea.vehicles.end(); ++veh) {
            std::vector<ChargingPile>& piles = (veh->mode == FAST) ? fastPiles : tricklePiles;
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

Server::Server(std::vector<User> &users,int fastNum, int trickleNum, int waitSize) :users(&users), waitingArea(waitSize) {
        for (int i = 0; i < fastNum; ++i) fastPiles.emplace_back(ChargingType::FAST, 30);
        for (int i = 0; i < trickleNum; ++i) tricklePiles.emplace_back(ChargingType::SLOW, 7);
}

void Server::handleFault(ChargingPile &pile) {
        pile.isFaulty = true;
        time_t now = time(nullptr);
        for (auto& pile : fastPiles)pile.processCompletion(now);
        for (auto& pile : tricklePiles)pile.processCompletion(now);
        std::vector<Vehicle> faultyQueue = pile.queue;
        pile.queue.clear(); // 清空故障桩队列

        // 优先调度故障队列到同类型（快充/慢充）的其他正常桩
        std::vector<ChargingPile>& targetPiles = (pile.type == ChargingType::FAST) ? fastPiles : tricklePiles;
        for (auto& veh : faultyQueue) {
            scheduleVehicle(now,veh, targetPiles); // 自定义调度函数，确保优先处理故障队列
        }
}

void Server::handleOpen(ChargingPile &pile) {
    pile.isFaulty = false;

    time_t now = time(nullptr);
    std::vector<std::list<Vehicle>::iterator> toRemove;

    for (auto& pile : fastPiles)pile.processCompletion(now);
    for (auto& pile : tricklePiles)pile.processCompletion(now);

    for (auto veh = waitingArea.vehicles.begin(); veh != waitingArea.vehicles.end(); ++veh) {
        if (pile.type!=veh->mode||pile.isFaulty || !pile.hasSpace()) continue;

        pile.addVehicle(*veh, now);
        for (auto &user:*users)if (user.getUid()==veh->uid)user.addOrder(veh->order);
        toRemove.push_back(veh);
    }

    // 移除已调度的车辆
    for (auto& iter: toRemove) {
        waitingArea.vehicles.erase(iter);
    }
}

void Server::scheduleVehicle(time_t now, Vehicle &veh, std::vector<ChargingPile> &piles) {
        double minTime = DBL_MAX;
        ChargingPile* selected = nullptr;
        veh.order->setEnd(now);
        veh.isChanging=false;
        veh.chargeTime=(static_cast<double>(veh.end)-veh.start)/3600;
        for (auto& p : piles) {
            if (p.isFaulty || !p.hasSpace()) continue;
            double waitTime = (p.queue.empty()) ? 0 : (p.queue.back().end - now);
            waitTime = std::max(waitTime, 0.0);
            if (waitTime +veh.chargeTime  < minTime) {
                minTime = waitTime + veh.chargeTime;
                selected = &p;
            }
        }
        if (selected) selected->addVehicle(veh, now);
        else waitingArea.vehicles.push_front(veh);
}