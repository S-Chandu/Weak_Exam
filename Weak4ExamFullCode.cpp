#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>
#include <random>
#include <string>

using namespace std;

mutex mtx;
ofstream logFile;

// ------------------------------
// Utility: Current Time
// ------------------------------
string currentTime() {
    time_t now = time(nullptr);
    tm* lt = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", lt);  
    return buffer;
}

// ------------------------------
// Print alert safely
// ------------------------------
void printAlert(const string &msg) {
    lock_guard<mutex> lock(mtx);
    cout << msg << endl;
    logFile << msg << " at " << currentTime() << endl;
}

// ------------------------------
// Seatbelt Alert (every 250ms)
// ------------------------------
void seatbeltAlert() {
    for (int i = 0; i < 10; i++) {  // loop fixed 10 times
        printAlert("[Seatbelt] ON");
        this_thread::sleep_for(250ms);
        printAlert("[Seatbelt] OFF");
    }
}

// ------------------------------
// ABS Alert (every 350ms)
// ------------------------------
void absAlert() {
    for (int i = 0; i < 7; i++) { // fewer cycles
        printAlert("[ABS] ON");
        this_thread::sleep_for(350ms);
        printAlert("[ABS] OFF");
    }
}

// ------------------------------
// Fuel Sensor (simple simulation)
// ------------------------------
void fuelSensor() {
    int fuel = 30; // start fuel
    for (int i = 0; i < 10; i++) {
        fuel -= 3;
        if (fuel <= 15) {
            printAlert("[Fuel] Low Fuel Warning (" + to_string(fuel) + "%)");
        }
        this_thread::sleep_for(1s);
    }
}

// ------------------------------
// Engine Sensor (simple overheat)
// ------------------------------
void engineSensor() {
    int temp = 70;
    for (int i = 0; i < 10; i++) {
        temp += 3;
        if (temp >= 90) {
            printAlert("[Engine] Overheat (" + to_string(temp) + "°C)");
        }
        this_thread::sleep_for(1s);
    }
}

// ------------------------------
// Door Sensor (random door open)
// ------------------------------
void doorSensor() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);

    for (int i = 0; i < 10; i++) {
        if (dis(gen) == 3) {
            printAlert("[Door] Front Right Door Open");
        }
        this_thread::sleep_for(1s);
    }
}

int main() {
    cout << "====== SIMPLE VEHICLE ALERT SYSTEM ======\n";
    cout << "Simulation running for 10 seconds...\n";
    
    logFile.open("alerts_log.txt");

    // Start Threads
    thread t1(seatbeltAlert);
    thread t2(absAlert);
    thread t3(fuelSensor);
    thread t4(engineSensor);
    thread t5(doorSensor);

    // Wait for all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    cout << "\nSimulation complete. Check alerts_log.txt\n";
    logFile.close();
    return 0;
}
