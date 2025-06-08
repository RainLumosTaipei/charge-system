//
// Created by zhou_zhengming on 2025/6/9.
//

#ifndef CHARGE_SYSTEM_TIMEHELPER_H
#define CHARGE_SYSTEM_TIMEHELPER_H

#include <ctime>

#ifdef _WIN32
#define localtime_u(result, time) \
    do { \
        localtime_s(result, time); \
    } while(0)
#else
#define localtime_u(result, time) \
    do { \
        localtime_r(time, result); \
    } while(0)
#endif

#endif //CHARGE_SYSTEM_TIMEHELPER_H
