//
// Created by zhou_zhengming on 2025/6/5.
//
#define _CRT_SECURE_NO_WARNINGS 1
#include "util/TimeHelper.h"
#include "entity/ChargingPile.h"

size_t ChargingPile::id_count = 200000;
double ChargingPile::peekCost = 1.0;
double ChargingPile::shoulderCost = 0.7;
double ChargingPile::valleyCost = 0.4;


ChargingPile::ChargingPile(ChargingType t, double p)
: id(id_count++), type(t), power(p), isFaulty(false), count(0), totalTime(0), totalPower(0) {

}

// 添加车辆（计算启动/结束时间）
void ChargingPile::addVehicle(Vehicle &veh, time_t now) {
    if (queue.empty()) veh.start = now;
    else  veh.start=queue.back().end;
    veh.isChanging=true;
    veh.totalFee=0;
    veh.end = veh.start + veh.chargeTime * 3600; // 转换为秒
    veh.updateOrder();
    queue.push_back(veh); // 加入排队（第二个车位）
    count++;
    totalTime += veh.chargeTime;
    totalPower += veh.reqPower;
}

void ChargingPile::processCompletion(time_t now) {
    std::vector<Vehicle> newQueue;
    for (auto& v : queue) {
        if (v.start>=now) newQueue.push_back(v);
        else if (v.end > now) {
            time_t tmp=v.end;
            v.end=now;
            calculateBill(v);
            v.start=now;
            v.end=tmp;
            v.order->setCost(v.totalFee);
            newQueue.push_back(v);
        } // 未完成，保留
        else {
            calculateBill(v);
            v.order->setCost(v.totalFee);
        } // 完成，计算费用（假设已实现）
    }
    queue = newQueue;
}

void ChargingPile::calculateBill(Vehicle &veh) {
    //std::cout<<"calcuteBill"<< std::endl;

    double peak = 0;
    double flat = 0;
    double valley = 0;
    // 分别统计峰时、平时、谷时的电量

    time_t currentTime = veh.start;
    time_t currentEndTime = veh.end;
    // std::cout<<"start"<<veh.start<<std::endl;
    // std::cout<<"end"<<veh.end<<std::endl;
    // std::cout<<"current"<<currentTime<<std::endl;

    while (currentTime < currentEndTime) {
        // 计算当前小时内的充电时长（以秒为单位）
        double remainingTime = difftime(currentEndTime, currentTime);//剩余时间
        double hourDurationInSeconds = std::min(remainingTime, 3600.0);
        // 转换为小时数
        double hourDuration = hourDurationInSeconds / 3600;

        //计算当前这个小时的用电费用
        struct tm tmCurrent;//临时变量
        localtime_s(&tmCurrent, &currentTime);//每个小时算一次电费
        int currentHour = tmCurrent.tm_hour;
        // 峰时（10-15, 18-21）
        if ((currentHour >= 10 && currentHour < 15) || (currentHour >= 18 && currentHour < 21)) {
            peak += hourDuration *(veh.mode == ChargingType::FAST ? 30 : 7);//根据模式计算每小时充电量
            // std::cout<<"peak "<<peak<< std::endl;
        }
        // 平时（7-10, 15-18, 21-23）
        else if ((currentHour >= 7 && currentHour < 10) || (currentHour >= 15 && currentHour < 18) || (currentHour >= 21 && currentHour < 23)) {
            flat += hourDuration*(veh.mode == ChargingType::FAST ? 30 : 7) ;
            // std::cout<<"flat "<<flat<< std::endl;
        }
        // 谷时（23-7）
        else {
            valley += hourDuration * (veh.mode == ChargingType::FAST ? 30 : 7);
            // std::cout<<"valley "<<valley<< std::endl;
        }

        // 动态更新时间
        currentTime += static_cast<time_t>(hourDurationInSeconds);

    }

    // 计算总电费
    veh.elecFee += peak * 1.0 + flat * 0.7 + valley * 0.4;
    veh.servFee += (peak+flat+valley)*0.8;// 服务费固定为0.8倍请求电量
    veh.totalFee = veh.elecFee + veh.servFee;
}



void to_json(nlohmann::json& j, const ChargingPile& pile){
    j["totalPower"] = pile.totalPower;
    j["totalTime"] = pile.totalTime;
    j["power"] = pile.power;
    j["count"] = pile.count;
    j["type"] = pile.type;
    j["isFaulty"] = pile.isFaulty;
    j["queue"] = pile.queue;
    j["id"] = pile.id;
}

