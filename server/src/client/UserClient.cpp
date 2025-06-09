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

void UserClient::cancelCharge(size_t queueNum) {
    time_t now = time(nullptr);
    for (auto& pile : server.fastPiles)pile.processCompletion(now);
    for (auto& pile : server.tricklePiles)pile.processCompletion(now);

    for (auto req = myRequests.begin(); req != myRequests.end(); ++req) {
        if (req->queueId == queueNum) {
            if (req->isChanging) {
                std::vector<ChargingPile>& piles = (req->mode == ChargingType::FAST) ? server.fastPiles : server.tricklePiles;
                for (auto& pile : piles) {
                    // if (pile.isFaulty || !pile.queue.size()) continue;
                    if (pile.queue.size()==1) {
                        if (pile.queue.front().queueId == queueNum) {
                            req->end=now;
                            req->order->setEnd(now);
                            pile.queue.clear();
                        }
                    }
                    else if (pile.queue.size()==2) {
                        if (pile.queue.front().queueId == queueNum) {
                            if (pile.queue.front().queueId == queueNum) {
                                req->end=now;
                                req->order->setEnd(now);
                                pile.queue.erase(pile.queue.begin());
                            }
                            req->start = now;
                            req->end = req->start + req->chargeTime * 3600; // 转换为秒
                            req->updateOrder();
                        }else if (pile.queue.back().queueId == queueNum) {
                            pile.queue.erase(pile.queue.end());
                            req->start=now;
                            req->end=now;
                            req->updateOrder();
                            pile.totalTime -= req->chargeTime;
                            pile.totalPower -= req->reqPower;
                        }
                    }

                }
            } else server.waitingArea.cancelCharge(req);
            return ;
        }
    }
}

