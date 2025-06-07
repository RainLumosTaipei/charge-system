//
// Created by zhou_zhengming on 2025/6/7.
//

#ifndef CHARGE_SYSTEM_HTTPSERVER_H
#define CHARGE_SYSTEM_HTTPSERVER_H

#include "httplib/httplib.h"

class HttpServer {
private:
    httplib::Server server;
public:
    void start();
};


#endif //CHARGE_SYSTEM_HTTPSERVER_H
