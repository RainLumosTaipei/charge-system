//
// Created by zhou_zhengming on 2025/6/7.
//

#ifndef CHARGE_SYSTEM_ORDER_H
#define CHARGE_SYSTEM_ORDER_H


#include "ChargingType.h"
#include <ctime>
#include "util/JsonHelper.h"

class Order {
public:
    const size_t getId() const;

    void setId(size_t id);

    const size_t getUid() const;

    void setUid(size_t uid);

    const float getCost() const;

    void setCost(float cost);

    time_t getStart() const;

    void setStart(time_t start);

    time_t getEnd() const;

    void setEnd(time_t anEnd);

    ChargingType getType() const;

    void setType(ChargingType type);

    friend void from_json(const nlohmann::json& j, Order& o);

    Order(size_t uid, time_t start, time_t end, ChargingType type);

private:
    size_t id;
    size_t uid;
    float cost;
    time_t start;
    time_t end;
    ChargingType type;

    size_t static id_count;
};

void to_json(nlohmann::json& j, const Order& o);

#endif //CHARGE_SYSTEM_ORDER_H
