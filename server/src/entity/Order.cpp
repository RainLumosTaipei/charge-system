//
// Created by zhou_zhengming on 2025/6/7.
//

#include "entity/Order.h"


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
    j["cost"] = o.getCost();
    j["start"] = o.getStart();
    j["end"] = o.getEnd();
    j["type"] = o.getType();
}

void from_json(const nlohmann::json &j, Order &o) {
    j.at("id").get_to(o.id);
    j.at("uid").get_to(o.uid);
}

size_t Order::id_count = 0;

Order::Order(size_t uid,float cost, time_t start, time_t end, ChargingType type)
: id(id_count++),cost(cost), uid(uid), start(start), end(end), type(type){

}
