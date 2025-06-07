//
// Created by zhou_zhengming on 2025/6/7.
//

#include "repo/UserDB.h"

namespace {
    std::vector<User> preUsers{
            {"zzm", "zzm", UserType::ADMIN},
            {"jyx", "jyx", UserType::ADMIN},
    };
}

UserDB UserDB::g_User{preUsers};

UserDB::UserDB(std::vector<User> users) : users(std::move(users)) {}

const std::vector<User> &UserDB::getUsers() {
    return users;
}