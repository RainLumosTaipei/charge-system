#pragma once
class ChargingRequest
{
};

using namespace std;

// 充电请求类
class ChargingRequest {
public:
    string carId;          // 车辆ID
    bool isFastCharge;     // 是否快充
    double requestPower;   // 请求充电量
    string queueNumber;    // 排队号码
    chrono::system_clock::time_point arrivalTime; // 到达时间

    ChargingRequest(string id, bool fast, double power)
        : carId(id), isFastCharge(fast), requestPower(power) {
        arrivalTime = chrono::system_clock::now();
    }
};

// 充电桩类
class ChargingPile {
public:
    string id;            // 充电桩ID
    bool isFastCharging;  // 是否快充
    double power;         // 充电功率
    queue<ChargingRequest> chargingQueue; // 充电队列
    static const int MAX_QUEUE_SIZE = 2;  // 最大队列长度

    ChargingPile(string pileId, bool fast)
        : id(pileId), isFastCharging(fast) {
        power = fast ? 30.0 : 7.0; // 快充30度/小时，慢充7度/小时
    }

    bool canAcceptCar() {
        return chargingQueue.size() < MAX_QUEUE_SIZE;
    }

    // 计算完成充电所需总时间
    double calculateTotalTime(const ChargingRequest& request) {
        double waitingTime = 0;
        queue<ChargingRequest> tempQueue = chargingQueue;

        // 计算等待时间
        while (!tempQueue.empty()) {
            waitingTime += tempQueue.front().requestPower / power;
            tempQueue.pop();
        }

        // 自己的充电时间
        double selfChargingTime = request.requestPower / power;

        return waitingTime + selfChargingTime;
    }
};

// 充电站类
class ChargingStation {
private:
    static const int WAITING_AREA_CAPACITY = 6;
    vector<ChargingPile> fastChargingPiles;
    vector<ChargingPile> slowChargingPiles;
    queue<ChargingRequest> waitingArea;

    int fastChargeCount = 0;
    int slowChargeCount = 0;

    mutex mtx;
    condition_variable cv;

public:
    ChargingStation() {
        // 初始化充电桩
        fastChargingPiles.emplace_back("A", true);
        fastChargingPiles.emplace_back("B", true);

        slowChargingPiles.emplace_back("C", false);
        slowChargingPiles.emplace_back("D", false);
        slowChargingPiles.emplace_back("E", false);
    }

    // 提交充电请求
    bool submitRequest(const string& carId, bool isFastCharge, double requestPower) {
        unique_lock<mutex> lock(mtx);

        if (waitingArea.size() >= WAITING_AREA_CAPACITY) {
            cout << "等候区已满，车辆 " << carId << " 无法进入" << endl;
            return false;
        }

        ChargingRequest request(carId, isFastCharge, requestPower);
        if (isFastCharge) {
            request.queueNumber = "F" + to_string(++fastChargeCount);
        }
        else {
            request.queueNumber = "T" + to_string(++slowChargeCount);
        }

        waitingArea.push(request);
        cout << "车辆 " << carId << " 进入等候区，排队号码: " << request.queueNumber << endl;

        cv.notify_one();
        return true;
    }

    // 调度车辆
    void scheduleCharging() {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [this]() { return !waitingArea.empty(); });

            auto& request = waitingArea.front();
            auto& targetPiles = request.isFastCharge ? fastChargingPiles : slowChargingPiles;

            // 查找可用的充电桩
            vector<ChargingPile*> availablePiles;
            for (auto& pile : targetPiles) {
                if (pile.canAcceptCar()) {
                    availablePiles.push_back(&pile);
                }
            }

            if (!availablePiles.empty()) {
                // 找到完成时间最短的充电桩
                ChargingPile* bestPile = *min_element(
                    availablePiles.begin(),
                    availablePiles.end(),
                    [&request](ChargingPile* a, ChargingPile* b) {
                        return a->calculateTotalTime(request) < b->calculateTotalTime(request);
                    }
                );

                bestPile->chargingQueue.push(request);
                cout << "车辆 " << request.queueNumber << " 被分配到充电桩 " << bestPile->id << endl;
                waitingArea.pop();
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};