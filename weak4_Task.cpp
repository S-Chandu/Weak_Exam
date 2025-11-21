#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <tuple>
#include <memory>
#include <chrono>
#include <string>
#include <random>

using namespace std;

// -------------------------------------------------------------
// VERY SIMPLE HMI SETTINGS
// -------------------------------------------------------------
class HmiSettings {
public:
    int volume = 50;
    int brightness = 70;
    float climate = 22.5f;

    // Return all values using tuple
    tuple<int, int, float> getAll() {
        return {volume, brightness, climate};
    }
};

// -------------------------------------------------------------
// SHARED DATA
// -------------------------------------------------------------
mutex mtx;
condition_variable cv;
queue<string> events;
atomic<bool> running(true);

// -------------------------------------------------------------
// SENSOR THREAD  (generates external temperature)
// -------------------------------------------------------------
void sensorThread(float &externalTemp) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(-2.0f, 8.0f);

    while (running) {
        this_thread::sleep_for(chrono::seconds(20));

        externalTemp = dist(gen);

        {
            lock_guard<mutex> lock(mtx);
            events.push("sensor");
        }
        cv.notify_one();
    }
}

// -------------------------------------------------------------
// INPUT THREAD (reads user commands)
// -------------------------------------------------------------
void inputThread() {
    while (running) {
        cout << "[Input] Command: ";
        string cmd;
        getline(cin, cmd);

        {
            lock_guard<mutex> lock(mtx);
            events.push(cmd);
        }
        cv.notify_one();

        if (cmd == "exit") break;
    }
}

// -------------------------------------------------------------
// DISPLAY (very simple)
// -------------------------------------------------------------
class Display {
public:
    void show(int v, int b, float c) {
        cout << "[Display] Volume: " << v
             << " | Brightness: " << b
             << " | Climate: " << c << "°C\n";
    }
};

// -------------------------------------------------------------
// CONTROLLER THREAD (processes all events)
// -------------------------------------------------------------
void controller(shared_ptr<HmiSettings> settings, float &externalTemp) {
    unique_ptr<Display> disp = make_unique<Display>();

    while (running) {
        string ev;

        // Wait for an event
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [] { return !events.empty(); });
            ev = events.front();
            events.pop();
        }

        if (ev == "exit") {
            cout << "Shutting down...\n";
            running = false;
            break;
        }

        // --- SENSOR EVENT ---
        if (ev == "sensor") {
            cout << "[Sensor] External temp: " << externalTemp << "°C\n";

            if (externalTemp <= 0.0f) {
                cout << "[Controller] Temp low → auto-increase climate\n";
                settings->climate += 2.0f;
            }
        }
        else {
            // --- HANDLE COMMANDS ---
            if (ev == "vol_up") settings->volume++;
            else if (ev == "vol_down") settings->volume--;
            else if (ev == "bright_up") settings->brightness++;
            else if (ev == "bright_down") settings->brightness--;
            else if (ev.rfind("set_vol", 0) == 0)
                settings->volume = stoi(ev.substr(8));
            else if (ev.rfind("set_bright", 0) == 0)
                settings->brightness = stoi(ev.substr(11));
            else if (ev.rfind("set_climate", 0) == 0)
                settings->climate = stof(ev.substr(12));
        }

        // Show output
        auto [v, b, c] = settings->getAll();
        disp->show(v, b, c);
    }
}

// -------------------------------------------------------------
// MAIN
// -------------------------------------------------------------
int main() {
    auto settings = make_shared<HmiSettings>();

    float externalTemp = 5.0f;

    thread tSensor(sensorThread, ref(externalTemp));
    thread tInput(inputThread);
    thread tController(controller, settings, ref(externalTemp));

    tSensor.join();
    tInput.join();
    tController.join();

    return 0;
}
