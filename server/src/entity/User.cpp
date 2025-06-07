//
// Created by zhou_zhengming on 2025/6/7.
//

#include "entity/User.h"
#include "util/JsonHelper.h"

User::User(std::string name, std::string password)
        : name(std::move(name)), password(std::move(password)) {}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setPassword(const std::string &password) {
    User::password = password;
}

const std::vector<Order> &User::getOrders() const {
    return orders;
}

void User::setOrders(const std::vector<Order> &orders) {
    User::orders = orders;
}

void to_json(nlohmann::json& j, const User& u) {
    j["name"] = u.getName();
    j["password"] = u.getPassword();
    j["orders"] = u.getOrders();
}