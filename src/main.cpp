#include <iostream>
#include <algorithm>
#include <cmath>
#include "server/Server.h"
#include "client/UserClient.h"
#include "client/AdminClient.h"

using namespace std;


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