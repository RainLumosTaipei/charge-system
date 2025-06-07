#pragma once
#ifndef CHARGE_SYSTEM_USERCLIENT_H
#define CHARGE_SYSTEM_USERCLIENT_H

#include <string>
#include <vector>
#include <list>

class ServerUser {
public:
    // Server& server;
    std::string userId; //用户ID
    // std::string car_Id;
    std::string userName;//用户名
    double car_Capacity;//车辆电池总容量（度）

    void printUser();
};
#endif