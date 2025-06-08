//
// Created by zhou_zhengming on 2025/6/7.
//

#include "entity/User.h"
#include "util/JsonHelper.h"

size_t User::id_count = 100000;

User::User(std::string name, std::string password,int type)
        : id(id_count++), name(std::move(name)), password(std::move(password)),type(type) {}

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

const std::vector<Order*> &User::getOrders() const {
    return orders;
}

// void User::setOrders(const std::vector<Order> &orders) {
//     User::orders = orders;
// }

void User::addOrder(Order* order) {
    orders.push_back(order);
}

const size_t User::getUid() const{
    return id;
}

const int User::getType(){
    return type;
}

void to_json(nlohmann::json& j, const User& u) {
    j["id"]=u.getUid();
    j["name"] = u.getName();
    j["password"] = u.getPassword();
    for (Order* tmp:u.getOrders())j["orders"].push_back(*tmp);
}