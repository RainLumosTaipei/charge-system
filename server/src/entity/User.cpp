//
// Created by zhou_zhengming on 2025/6/7.
//

#include "entity/User.h"
#include "util/JsonHelper.h"

User::User(std::string name, std::string password, UserType type)
        : name(std::move(name)), password(std::move(password)), type(type) {}

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

size_t User::getId() const {
    return id;
}

void User::setId(size_t id) {
    User::id = id;
}

UserType User::getType() const {
    return type;
}

void User::setType(UserType type) {
    User::type = type;
}

void to_json(nlohmann::json& j, const User& u) {
    j["id"] = u.getId();
    j["name"] = u.getName();
    j["password"] = u.getPassword();
    j["type"] = u.getType();
    j["orders"] = u.getOrders();
}