//
// Created by zhou_zhengming on 2025/6/7.
//

#include "Order.h"


const size_t Order::getId() const {
    return id;
}

void Order::setId(size_t id) {
    Order::id = id;
}

const size_t Order::getUid() const {
    return uid;
}

void Order::setUid(size_t uid) {
    Order::uid = uid;
}

const float Order::getCost() const {
    return cost;
}

void Order::setCost(float cost) {
    Order::cost = cost;
}

time_t Order::getStart() const {
    return start;
}

void Order::setStart(time_t start) {
    Order::start = start;
}

time_t Order::getEnd() const {
    return end;
}

void Order::setEnd(time_t anEnd) {
    end = anEnd;
}

ChargingType Order::getType() const {
    return type;
}

void Order::setType(ChargingType type) {
    Order::type = type;
}

void to_json(nlohmann::json &j, const Order &o) {
    j["id"] = o.getId();
    j["uid"] = o.getUid();
}

void from_json(const nlohmann::json &j, Order &o) {
    j.at("id").get_to(o.id);
    j.at("uid").get_to(o.uid);
}
