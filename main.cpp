#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <cmath>
using namespace std;

// 车辆类
class Vehicle {
public:
    string mode;       // F(快充) / T(慢充)
    string queueNum;   // 排队号
    double reqPower;   // 请求电量（度）
    double chargeTime; // 充电时长（小时，reqPower / 功率）
    time_t start;      // 启动时间（秒）
    time_t end;        // 结束时间（秒）

    // 计费信息
    double elecFee;    // 充电费
    double servFee;    // 服务费
    double totalFee;   // 总费用

    Vehicle(string m, double power, double rp) : mode(m), reqPower(rp) {
        chargeTime = rp / (m == "F" ? 30 : 7); // 快充30度/时，慢充7度/时
    }
};

// 充电桩类
class ChargingPile {
public:
    string type;       // Fast / Trickle
    double power;      // 功率（度/时）
    vector<Vehicle> queue; // 队列（最多2辆车：1充电，1排队）
    bool isFaulty;     // 是否故障
    int count;         // 累计充电次数
    double totalTime;  // 累计充电时长（小时）
    double totalPower; // 累计充电电量（度）

    ChargingPile(string t, double p) : type(t), power(p), isFaulty(false), count(0), totalTime(0), totalPower(0) {}

    bool hasSpace() const { return queue.size() < 2; } // 队列有空位（<2）

    // 添加车辆（计算启动/结束时间）
    void addVehicle(Vehicle& veh, time_t now) {
        if (queue.empty()) {
            veh.start = now;
            veh.end = now + veh.chargeTime * 3600; // 转换为秒
            queue.push_back(veh);
            count++;
            totalTime += veh.chargeTime;
            totalPower += veh.reqPower;
        } else {
            queue.push_back(veh); // 加入排队（第二个车位）
        }
    }

    // 处理充电完成（移除已完成车辆，更新队列）
    void processCompletion(time_t now) {
        vector<Vehicle> newQueue;
        for (auto& v : queue) {
            if (v.end > now) newQueue.push_back(v); // 未完成，保留
            else calculateBill(v); // 完成，计算费用（假设已实现）
        }
        queue = newQueue;
    }

private:
    // 计算电费（根据时间区间）
    void calculateBill(Vehicle& veh) {
        struct tm* tmStart = localtime(&veh.start);
        struct tm* tmEnd = localtime(&veh.end);
        double peak = 0, flat = 0, valley = 0;

        // 分割充电时段（简化处理，实际需遍历每小时）
        int startHour = tmStart->tm_hour;
        int endHour = tmEnd->tm_hour;
        double duration = difftime(veh.end, veh.start) / 3600; // 总时长（小时）

        // 峰时（10-15, 18-21）
        if ((startHour >= 10 && startHour < 15) || (startHour >= 18 && startHour < 21)) {
            veh.elecFee = 1.0 * veh.reqPower;
        }
        // 平时（7-10, 15-18, 21-23）
        else if ((startHour >= 7 && startHour < 10) || (startHour >= 15 && startHour < 18) || (startHour >= 21 && startHour < 23)) {
            veh.elecFee = 0.7 * veh.reqPower;
        }
        // 谷时（23-7）
        else {
            veh.elecFee = 0.4 * veh.reqPower;
        }
        veh.servFee = 0.8 * veh.reqPower;
        veh.totalFee = veh.elecFee + veh.servFee;
    }
};

// 等候区（最大6车位，F/T队列分别计数）
class WaitingArea {
public:
    vector<Vehicle> vehicles;
    int maxSize;
    int fCount; // F队列计数器（从1开始）
    int tCount; // T队列计数器（从1开始）

    WaitingArea(int size) : maxSize(size), fCount(1), tCount(1) {}

    // 添加车辆（生成排队号）
    bool addVehicle(Vehicle& veh) {
        if (vehicles.size() >= maxSize) return false;
        veh.queueNum = (veh.mode == "F") ? "F" + to_string(fCount++) : "T" + to_string(tCount++);
        vehicles.push_back(veh);
        return true;
    }

    // 修改充电模式（等候区：重新生成排队号，移到对应队列末尾）
    bool modifyMode(Vehicle& veh, string newMode) {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (it->queueNum == veh.queueNum) {
                veh.mode = newMode;
                vehicles.erase(it);
                return addVehicle(veh); // 重新加入（生成新排队号，添加到末尾）
            }
        }
        return false;
    }

    // 修改请求电量（等候区：排队号不变，更新电量和时长）
    bool modifyPower(Vehicle& veh, double newPower) {
        for (auto& v : vehicles) {
            if (v.queueNum == veh.queueNum) {
                v.reqPower = newPower;
                v.chargeTime = newPower / (v.mode == "F" ? 30 : 7);
                return true;
            }
        }
        return false;
    }

    // 取消充电（等候区：移除；充电区：重新加入等候区）
    bool cancelCharge(Vehicle& veh, bool isInCharging) {
        if (isInCharging) {
            return addVehicle(veh); // 重新加入等候区
        } else {
            vehicles.erase(remove(vehicles.begin(), vehicles.end(), veh), vehicles.end());
            return true;
        }
    }
};

// 服务器端（调度、计费、故障处理）
class Server {
public:
    vector<ChargingPile> fastPiles;   // 快充桩（默认2个）
    vector<ChargingPile> tricklePiles; // 慢充桩（默认3个）
    WaitingArea waitingArea;          // 等候区（容量6）

    Server(int fastNum = 2, int trickleNum = 3, int waitSize = 6) : waitingArea(waitSize) {
        for (int i = 0; i < fastNum; ++i) fastPiles.emplace_back("Fast", 30);
        for (int i = 0; i < trickleNum; ++i) tricklePiles.emplace_back("Trickle", 7);
    }

    // 调度策略：选择使车辆完成时长（等待+充电）最短的充电桩队列
    void schedule() {
        time_t now = time(nullptr);
        vector<Vehicle> toRemove;

        for (auto& veh : waitingArea.vehicles) {
            vector<ChargingPile*>& piles = (veh.mode == "F") ? fastPiles : tricklePiles;
            double minTime = __DBL_MAX__;
            ChargingPile* selected = nullptr;

            for (auto& pile : piles) {
                if (pile.isFaulty || !pile.hasSpace()) continue;
                double waitTime = (pile.queue.empty()) ? 0 : (pile.queue.back().end - now);
                waitTime = max(waitTime, 0.0); // 等待时间不能为负
                double totalTime = waitTime + veh.chargeTime;
                if (totalTime < minTime) {
                    minTime = totalTime;
                    selected = &pile;
                }
            }

            if (selected) {
                selected->addVehicle(veh, now);
                toRemove.push_back(veh);
            }
        }

        // 移除已调度的车辆
        for (auto& veh : toRemove) {
            waitingArea.vehicles.erase(remove(waitingArea.vehicles.begin(), waitingArea.vehicles.end(), veh), waitingArea.vehicles.end());
        }
    }

    // 故障处理：标记充电桩故障，重新调度队列车辆（优先级调度）
    void handleFault(ChargingPile& pile) {
        pile.isFaulty = true;
        vector<Vehicle> faultyQueue = pile.queue;
        pile.queue.clear(); // 清空故障桩队列

        // 优先调度故障队列到同类型（快充/慢充）的其他正常桩
        vector<ChargingPile*>& targetPiles = (pile.type == "Fast") ? fastPiles : tricklePiles;
        for (auto& veh : faultyQueue) {
            scheduleVehicle(veh, targetPiles); // 自定义调度函数，确保优先处理故障队列
        }
    }

private:
    // 辅助函数：调度单个车辆到目标桩集合
    void scheduleVehicle(Vehicle& veh, vector<ChargingPile*>& piles) {
        time_t now = time(nullptr);
        double minTime = __DBL_MAX__;
        ChargingPile* selected = nullptr;
        for (auto& p : piles) {
            if (p->isFaulty || !p->hasSpace()) continue;
            double waitTime = (p->queue.empty()) ? 0 : (p->queue.back().end - now);
            waitTime = max(waitTime, 0.0);
            if (waitTime + veh.chargeTime < minTime) {
                minTime = waitTime + veh.chargeTime;
                selected = p;
            }
        }
        if (selected) selected->addVehicle(veh, now);
    }
};

// 用户客户端（注册、提交请求、修改、取消）
class UserClient {
public:
    Server& server;
    string userId;
    vector<Vehicle> myRequests; // 我的充电请求

    UserClient(Server& s, string id) : server(s), userId(id) {}

    // 提交充电请求
    void submitRequest(string mode, double power) {
        Vehicle veh(mode, (mode == "F") ? 30 : 7, power);
        if (server.waitingArea.addVehicle(veh)) {
            myRequests.push_back(veh);
            cout << "提交成功！排队号：" << veh.queueNum << endl;
        } else {
            cout << "等候区已满，请稍后重试。" << endl;
        }
    }

    // 修改充电模式（等候区）
    void modifyMode(string queueNum, string newMode) {
        for (auto& req : myRequests) {
            if (req.queueNum == queueNum) {
                if (server.waitingArea.modifyMode(req, newMode)) {
                    cout << "模式修改成功，新排队号：" << req.queueNum << endl;
                } else {
                    cout << "修改失败（车辆不在等候区）。" << endl;
                }
                return;
            }
        }
        cout << "未找到该排队号的请求。" << endl;
    }

    // 修改请求电量（等候区）
    void modifyPower(string queueNum, double newPower) {
        for (auto& req : myRequests) {
            if (req.queueNum == queueNum) {
                if (server.waitingArea.modifyPower(req, newPower)) {
                    cout << "电量修改成功。" << endl;
                } else {
                    cout << "修改失败（车辆不在等候区）。" << endl;
                }
                return;
            }
        }
        cout << "未找到该排队号的请求。" << endl;
    }

    // 取消充电（等候区/充电区）
    void cancelCharge(string queueNum, bool isInCharging) {
        for (auto& req : myRequests) {
            if (req.queueNum == queueNum) {
                if (server.waitingArea.cancelCharge(req, isInCharging)) {
                    cout << "取消成功。" << endl;
                } else {
                    cout << "取消失败。" << endl;
                }
                myRequests.erase(remove(myRequests.begin(), myRequests.end(), req), myRequests.end());
                return;
            }
        }
        cout << "未找到该排队号的请求。" << endl;
    }
};

// 管理员客户端（查看状态、报表）
class AdminClient {
public:
    Server& server;

    AdminClient(Server& s) : server(s) {}

    // 查看充电桩状态
    void viewPileStatus() {
        cout << "快充桩状态：" << endl;
        for (auto& pile : server.fastPiles) {
            cout << "类型：快充，故障：" << (pile.isFaulty ? "是" : "否")
                 << "，队列长度：" << pile.queue.size() << endl;
        }
        cout << "慢充桩状态：" << endl;
        for (auto& pile : server.tricklePiles) {
            cout << "类型：慢充，故障：" << (pile.isFaulty ? "是" : "否")
                 << "，队列长度：" << pile.queue.size() << endl;
        }
    }

    // 查看等候区车辆
    void viewWaitingVehicles() {
        cout << "等候区车辆：" << endl;
        for (auto& veh : server.waitingArea.vehicles) {
            cout << "模式：" << veh.mode << "，排队号：" << veh.queueNum
                 << "，请求电量：" << veh.reqPower << "度" << endl;
        }
    }
};

// 测试主函数
int main() {
    Server server; // 默认2快充，3慢充，等候区6车位
    UserClient user(server, "user001");
    AdminClient admin(server);

    // 用户提交请求
    user.submitRequest("F", 60); // 快充60度（2小时）
    user.submitRequest("T", 21); // 慢充21度（3小时）

    // 调度车辆
    server.schedule();

    // 管理员查看状态
    admin.viewPileStatus();
    admin.viewWaitingVehicles();

    // 模拟充电桩故障（快充桩0号故障）
    server.handleFault(server.fastPiles[0]);
    admin.viewPileStatus(); // 查看故障状态

    return 0;
}