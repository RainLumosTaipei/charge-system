//
// Created by zhou_zhengming on 2025/6/7.
//

#include "util/HttpServer.h"

void HttpServer::start() {
    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    server.listen("0.0.0.0", 8080);
}