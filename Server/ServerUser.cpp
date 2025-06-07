#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

//
// Created by zhou_zhengming on 2025/6/5.
//

#include <iostream>
#include "ServerUser.h"

using std::cout;
using std::endl;

// 打印单个 UserClient 的信息
void ServerUser::printUser() {
    std::cout << "用户ID: " << userId
        << ", 用户名: " << userName
        << ", 电池容量: " << car_Capacity << " 度" << std::endl;
}

