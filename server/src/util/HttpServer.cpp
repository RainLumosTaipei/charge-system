//
// Created by zhou_zhengming on 2025/6/7.
//

#include "util/HttpServer.h"
#include "entity/User.h"
#include "util/JsonHelper.h"
#include "client/UserClient.h"

using namespace std;

void HttpServer::start() {
    std::vector<User> preUsers{//第一个是用户名，第二个是密码
            {"zzm", "zzm",0},
            {"jyx", "jyx",0},
    };

    std::vector<User> users(std::move(preUsers));
    Server chargeServer(users);
    UserClient charger(chargeServer,"main");

    charger.submitRequest(100000, FAST, 90);
    charger.submitRequest(100000, FAST, 90);
    charger.submitRequest(100000, FAST, 90);
    charger.submitRequest(100000, FAST, 90);
    //获取所有用户
    server.Get("/user/all", [&](const httplib::Request &, httplib::Response &res) {
        chargeServer.schedule();
        nlohmann::json j = users;
        std::cout << j << std::endl;
        res.set_content(j.dump(), "application/json");
    });
    //登录
    server.Get("/user/login",[&](const httplib::Request &req, httplib::Response &res)
    {
        auto message = req.params.begin();
        string user_name=message->second;
        ++message;
        string password = message->second;
        nlohmann::json j;
        j["id"]=-1;
        for (int i=0;i<users.size();++i)
        {
            if (users.at(i).getName()==user_name)
            {
                if (users.at(i).getPassword()==password) {
                    j["id"] = users.at(i).getUid();
                    j["type"]=users.at(i).getType();
                }
                break;
            }
        }
        cout << j.dump() << endl;
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/user/register",[&](const httplib::Request & req, httplib::Response &res)
    {
        bool same_flag=false;
        auto message = req.params.begin();
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
        if (same_flag) j["id"]=-1;
        else
        {
            User tmp=User(user_name,password,1);
           users.push_back(tmp);
           j["id"]=tmp.getUid();
        }
        j["type"]=1;
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/user/update/password",[&](const httplib::Request & req, httplib::Response &res){
        bool success_flag=false;
        auto message = req.params.begin();
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
    
    server.Post("/user/charge",[&](const httplib::Request &req, httplib::Response &res)
    {
        nlohmann::json body=nlohmann::json::parse(req.body);
        size_t uid=body["uid"];
        double Request_Amount = body["amount"];//即充电量
        ChargingType Request_Mode = body["type"];


        Vehicle* veh = charger.submitRequest(uid, Request_Mode, Request_Amount);
        nlohmann::json j;
        if (veh==nullptr) j["return"]=false;
        else
        {
            j["return"]=true;
            j["queueId"]=veh->queueId;
            j["chargeTime"]=veh->chargeTime;
        }
        printf("%s\n",j.dump().c_str());
        res.set_content(j.dump(), "application/json");
    });

    server.Post("/user/charge/stop",[&](const httplib::Request &req, httplib::Response &res){
        nlohmann::json body=nlohmann::json::parse(req.body);
        size_t queueNum = body["queueId"];
        bool isInCharging = body["isCharging"];
        charger.cancelCharge(queueNum,isInCharging);

        nlohmann::json j;
        j["return"] = true;
        res.set_content(j.dump(),"application/json");
    });

    server.Post("/user/charge/update",[&](const httplib::Request &req, httplib::Response &res)//仅支持对未开始充电的车辆进行修改
    {
        chargeServer.schedule();
        nlohmann::json body=nlohmann::json::parse(req.body);
        size_t queueNum = body["queueId"];
        double chargeTime = body["chargeTime"];

        nlohmann::json j;
        if (charger.modifyPower(queueNum, chargeTime))j["return"]=true;
        else j["return"]=false;
        res.set_content(j.dump(), "application/json");
    });

    server.Post("/user/mode/update",[&](const httplib::Request &req, httplib::Response &res){
        chargeServer.schedule();
        nlohmann::json body=nlohmann::json::parse(req.body);
        size_t queueNum = body["queueId"];
        ChargingType chargeMode = body["chargeMode"];

        nlohmann::json j;
        if (charger.modifyMode(queueNum, chargeMode))j["return"]=true;
        else j["return"]=false;
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/pile/all", [&](const httplib::Request & req, httplib::Response &res){
        chargeServer.schedule();
        nlohmann::json j;
        charger.viewPileStatus(j);
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/order",[&](const httplib::Request & req, httplib::Response &res) {
        chargeServer.schedule();
        auto message = req.params.begin();
        int uid=stoi(message->second);
        nlohmann::json j;
        std::vector<Order> v;
        for (auto &user:users) {
            if (user.getUid()==uid) {
                for (Order* tmp : user.getOrders()){
                    v.push_back(*tmp);
                }
            }
        }
        j = v;
        cout << j.dump() << endl;
        res.set_content(j.dump(), "application/json");
    });

    server.Post("/pile/update/cost",[&](const httplib::Request &req, httplib::Response &res){
        nlohmann::json body=nlohmann::json::parse(req.body);
        double peekCost = body["peekCost"];
        double shoulderCost = body["shoulderCost"];
        double valleyCost = body["valleyCost"];

        ChargingPile::peekCost=peekCost;
        ChargingPile::shoulderCost=shoulderCost;
        ChargingPile::valleyCost=valleyCost;

        nlohmann::json j;
        j["return"] = true;
        res.set_content(j.dump(), "application/json");
    });

    server.Get("/pile/update/state", [&](const httplib::Request & req, httplib::Response &res){
        auto message = req.params.begin();
        size_t id = stoi(message->second);  // id
        ++message;
        size_t state = stoi(message->second);  // 0 off, 1 on

        ChargingPile* aim;
        if(id==200000)aim=&chargeServer.fastPiles[0];
        else if (id==200001) aim=&chargeServer.fastPiles[1];
        else if (id==200002) aim=&chargeServer.tricklePiles[0];
        else if (id==200003) aim=&chargeServer.tricklePiles[1];
        else aim=&chargeServer.tricklePiles[2];

        if (state)chargeServer.handleFault(*aim);
        else chargeServer.handleOpen(*aim);

        nlohmann::json j;
        j["return"] = true;
        res.set_content(j.dump(), "application/json");
    });


    
    server.listen("0.0.0.0", 8080);
}