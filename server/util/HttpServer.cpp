//
// Created by zhou_zhengming on 2025/6/7.
//

#include "HttpServer.h"
#include "../entity/User.h"
#include "JsonHelper.h"
#include "../client/UserClient.h"

using namespace std;

void HttpServer::start() {
    Server chargeServer;
    UserClient charger(chargeServer,"main");
    std::vector<User> preUsers{//第一个是用户名，第二个是密码
            {"zzm", "zzm"},
            {"jyx", "jyx"},
    };

    std::vector<User> users(std::move(preUsers));
    
    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    server.Get("/user/all", [&](const httplib::Request &, httplib::Response &res) {
        nlohmann::json j = users;
        std::cout << j << std::endl;
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/login",[&](const httplib::Request &req, httplib::Response &res)
    {
        bool same_flag=false;
        std::multimap<std::string, std::string>::const_iterator message = req.params.begin();
        string user_name=message->second;
        ++message;
        string password = message->second;
        for (int i=0;i<users.size();++i)
        {
            if (users.at(i).getName()==user_name)
            {
                if (users.at(i).getPassword()==password)same_flag=true;
                break;
            }
        }
        nlohmann::json j;
        if (same_flag) j["return"]=true;
        else j["return"]=false;
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/CreateNewAccount",[&](const httplib::Request & req, httplib::Response &res)
    {
        bool same_flag=false;
        std::multimap<std::string, std::string>::const_iterator message = req.params.begin();
        string user_name=message->second;
        ++message;
        string password = message->second;
        for (int i=0;i<users.size();++i)
        {
            if (users.at(i).getName()==user_name)
            {
                same_flag=true;
                break;
            }
        }
        nlohmann::json j;
        if (same_flag) j["return"]=false;
        else
        {
            User tmp=User(user_name,password);
           users.push_back(tmp);
           j["return"]=true;
        }
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/set_Pwd",[&](const httplib::Request & req, httplib::Response &res){
        bool success_flag=false;
        std::multimap<std::string, std::string>::const_iterator message = req.params.begin();
        string user_name=message->second;
        ++message;
        string password = message->second;
        for (int i=0;i<users.size();++i)
        {
            if (users.at(i).getName()==user_name)
            {
                users.at(i).setPassword(password);
                success_flag=true;
                break;
            }
        }
        nlohmann::json j;
        if (success_flag)j["return"]=true;
        else j["return"]=false;
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });
    
    server.Post("/E_chargingRequest",[&](const httplib::Request &req, httplib::Response &res)
    {
        nlohmann::json body=nlohmann::json::parse(req.body);
        int Request_Amount = body["Request_Amount"];//即充电量
        string Request_Mode = body["Request_Mode"];
        Vehicle* veh = charger.submitRequest(Request_Mode, Request_Amount);
        nlohmann::json j;
        if (veh==nullptr) j["return"]=false;
        else
        {
            j["return"]=true;
            j["queueNum"]=veh->queueNum;
            j["chargeTime"]=veh->chargeTime;
        }
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });

    server.Post("/Modify_Amount",[&](const httplib::Request &req, httplib::Response &res)//仅支持对未开始充电的车辆进行修改
    {
        nlohmann::json body=nlohmann::json::parse(req.body);
        string queueNum = body["QueueNum"];
        int chargeTime = body["ChargeTime"];
        nlohmann::json j;
        if (charger.modifyPower(queueNum, chargeTime))j["return"]=true;
        else j["return"]=false;
        res.set_content(j.dump(), "application/json");
    });
    
    server.listen("0.0.0.0", 8080);
}