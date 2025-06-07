#pragma once
#include <iostream>
#include <sstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <atomic>
#include <iomanip>

using namespace std;

// 充电请求类
class ChargingRequest {
public:
    string carId;
    bool isFastCharge;
    double requestPower;   // 请求充电量
    double chargedPower;   // 已充电量
    string queueNumber;
    chrono::system_clock::time_point arrivalTime;

    ChargingRequest(string id, bool fast, double power)
        : carId(id), isFastCharge(fast), requestPower(power), chargedPower(0) {
        arrivalTime = chrono::system_clock::now();
    }
};

// 充电桩类
class ChargingPile {
public:
    string id;
    bool isFastCharging;
    double power;
    queue<ChargingRequest> chargingQueue;
    static const int MAX_QUEUE_SIZE = 2;

    mutex pileMutex;
    condition_variable pileCV;
    atomic<bool> isCharging{ false };
    atomic<bool> shouldStop{ false };
    thread chargingThread;

    ChargingPile(string pileId, bool fast)
        : id(pileId), isFastCharging(fast) {
        power = fast ? 30.0 : 7.0;
        // 启动充电处理线程
        chargingThread = thread(&ChargingPile::processCharging, this);
    }

    ~ChargingPile() {
        shouldStop = true;
        pileCV.notify_all();
        if (chargingThread.joinable()) {
            chargingThread.join();
        }
    }

    bool canAcceptCar() {
        lock_guard<mutex> lock(pileMutex);
        return chargingQueue.size() < MAX_QUEUE_SIZE;
    }

    double calculateTotalTime(const ChargingRequest& request) {
        lock_guard<mutex> lock(pileMutex);
        double waitingTime = 0;
        queue<ChargingRequest> tempQueue = chargingQueue;

        while (!tempQueue.empty()) {
            auto& curr = tempQueue.front();
            waitingTime += (curr.requestPower - curr.chargedPower) / power;
            tempQueue.pop();
        }

        return waitingTime + request.requestPower / power;
    }

    // 充电处理线程的主要逻辑
    void processCharging() {
    while (!shouldStop) {
        unique_lock<mutex> lock(pileMutex);
        
        // 等待队列中有车辆
        pileCV.wait(lock, [this] { 
            return !chargingQueue.empty() || shouldStop; 
        });
        
        if (shouldStop) break;

        // 获取队首车辆进行充电
        ChargingRequest& currentCar = chargingQueue.front();
        isCharging = true;

        // 修正：计算充电时间和进度
        while (currentCar.chargedPower < currentCar.requestPower) {
            // 修正：每小时的功率转换为每秒的充电量
            double chargePerSecond = power / 3600.0;  // 功率(度/小时)转换为每秒充电量
            
            lock.unlock();
            this_thread::sleep_for(chrono::seconds(1));
            lock.lock();

            if (shouldStop) break;

            currentCar.chargedPower += chargePerSecond;
            
            // 打印充电进度
            cout << fixed << setprecision(2);
            cout << "充电桩 " << id << " 正在为车辆 " << currentCar.queueNumber 
                 << " 充电进度: " << (currentCar.chargedPower / currentCar.requestPower * 100) 
                 << "% (已充: " << currentCar.chargedPower << "度, 需求: " 
                 << currentCar.requestPower << "度)" << endl;

            // 为了演示效果，可以加快模拟速度
            // 这里可以选择增加每次充电的量，或减少sleep时间
            // 比如：将每秒模拟为每分钟
            currentCar.chargedPower += chargePerSecond * 59; // 模拟一分钟的充电量
        }

        // 充电完成，移除车辆
        cout << "车辆 " << currentCar.queueNumber << " 在充电桩 " 
             << id << " 充电完成！总共充电: " << currentCar.requestPower << "度" << endl;
        
        chargingQueue.pop();
        isCharging = false;
        
        // 通知等待的车辆
        lock.unlock();
        pileCV.notify_all();
    }
}
};

// 充电站类
class ChargingStation {
private:
    static const int WAITING_AREA_CAPACITY = 6;
    vector<unique_ptr<ChargingPile>> fastChargingPiles;
    vector<unique_ptr<ChargingPile>> slowChargingPiles;
    queue<ChargingRequest> waitingArea;

    int fastChargeCount = 0;
    int slowChargeCount = 0;

    mutex mtx;
    condition_variable waitingAreaCV;
    condition_variable scheduleCV;
    atomic<bool> shouldStop{ false };
    thread schedulerThread;

public:
    ChargingStation() {
        // 使用智能指针初始化充电桩
        fastChargingPiles.push_back(make_unique<ChargingPile>("A", true));
        fastChargingPiles.push_back(make_unique<ChargingPile>("B", true));

        slowChargingPiles.push_back(make_unique<ChargingPile>("C", false));
        slowChargingPiles.push_back(make_unique<ChargingPile>("D", false));
        slowChargingPiles.push_back(make_unique<ChargingPile>("E", false));

        // 启动调度线程
        schedulerThread = thread(&ChargingStation::scheduleCharging, this);
    }

    ~ChargingStation() {
        shouldStop = true;
        scheduleCV.notify_all();
        waitingAreaCV.notify_all();

        if (schedulerThread.joinable()) {
            schedulerThread.join();
        }
    }

    bool submitRequest(const string& carId, bool isFastCharge, double requestPower) {
        unique_lock<mutex> lock(mtx);

        // 等待等候区有空位
        while (waitingArea.size() >= WAITING_AREA_CAPACITY && !shouldStop) {
            cout << "等候区已满，车辆 " << carId << " 等待中..." << endl;
            waitingAreaCV.wait(lock);
        }

        if (shouldStop) return false;

        ChargingRequest request(carId, isFastCharge, requestPower);
        if (isFastCharge) {
            request.queueNumber = "F" + to_string(++fastChargeCount);
        }
        else {
            request.queueNumber = "T" + to_string(++slowChargeCount);
        }

        waitingArea.push(request);
        cout << "车辆 " << carId << " 进入等候区，排队号码: " << request.queueNumber << endl;

        scheduleCV.notify_one();
        return true;
    }

    void scheduleCharging() {
        while (!shouldStop) {
            unique_lock<mutex> lock(mtx);

            scheduleCV.wait(lock, [this] {
                return !waitingArea.empty() || shouldStop;
                });

            if (shouldStop) break;

            auto& request = waitingArea.front();
            auto& targetPiles = request.isFastCharge ? fastChargingPiles : slowChargingPiles;

            // 查找可用的充电桩
            vector<ChargingPile*> availablePiles;
            for (auto& pile : targetPiles) {
                if (pile->canAcceptCar()) {
                    availablePiles.push_back(pile.get());
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

                // 将车辆加入选中的充电桩队列
                {
                    lock_guard<mutex> pileLock(bestPile->pileMutex);
                    bestPile->chargingQueue.push(request);
                    cout << "车辆 " << request.queueNumber << " 被分配到充电桩 "
                        << bestPile->id << endl;
                }

                waitingArea.pop();
                waitingAreaCV.notify_one();  // 通知等待进入等候区的车辆
                bestPile->pileCV.notify_one();  // 通知充电桩处理线程
            }
            else {
                // 没有可用充电桩时等待
                lock.unlock();
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }
};

