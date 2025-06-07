//
// Created by zhou_zhengming on 2025/6/7.
//

#include "util/HttpServer.h"
#include "repo/UserDB.h"
#include "util/JsonHelper.h"

void HttpServer::start() {
    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    server.Get("/user/all", [](const httplib::Request &, httplib::Response &res) {
        nlohmann::json j = UserDB::g_User.getUsers();
        std::cout << j << std::endl;
        res.set_content(j.dump(), "application/json");
    });

    server.listen("0.0.0.0", 8080);
}