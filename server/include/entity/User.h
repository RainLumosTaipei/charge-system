//
// Created by zhou_zhengming on 2025/6/7.
//

#ifndef CHARGE_SYSTEM_USER_H
#define CHARGE_SYSTEM_USER_H

#include <string>
#include <vector>
#include "Order.h"
#include "util/JsonHelper.h"
#include "UserType.h"

class User {
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::vector<Order> &getOrders() const;

    void setOrders(const std::vector<Order> &orders);

    User(std::string name, std::string password, UserType type);

private:
    size_t id;
    std::string name;
    std::string password;
    UserType type;
    std::vector<Order> orders;
};

void to_json(nlohmann::json& j, const User& u);

#endif //CHARGE_SYSTEM_USER_H
