//
// Created by zhou_zhengming on 2025/6/7.
//

#ifndef CHARGE_SYSTEM_USERDB_H
#define CHARGE_SYSTEM_USERDB_H

#include <vector>
#include "entity/User.h"

class UserDB {
private:
    std::vector<User> users;
    UserDB();
public:
    static UserDB g_User;
};


#endif //CHARGE_SYSTEM_USERDB_H
