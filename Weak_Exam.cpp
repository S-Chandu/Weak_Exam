#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>

using namespace std;

mutex mtx;                       // For safe console & log access
bool running(true);             // Allows graceful stop

ofstream logFile("alerts_log.txt");
void logEvent(const string& msg) {
    lock_guard<mutex> lock(mtx);
    logFile << msg << endl;
}

// Seatbelt Alert (250 ms)
void seatbeltAlert() {
    while (running) {
        {
            lock_guard<mutex> lock(mtx);
            cout << "[Seatbelt Alert] ON" << endl;
        }
        logEvent("[Seatbelt] ON");
        this_thread::sleep_for(chrono::milliseconds(250));

        {
            lock_guard<mutex> lock(mtx);
            cout << "[Seatbelt Alert] OFF" << endl;
        }
        logEvent("[Seatbelt] OFF");
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}

// ABS Alert (350 ms)
void absAlert() {
    while (running) {
        {
            lock_guard<mutex> lock(mtx);
            cout << "[ABS Alert] ON" << endl;
        }
        logEvent("[ABS] ON");
        this_thread::sleep_for(chrono::milliseconds(350));

        {
            lock_guard<mutex> lock(mtx);
            cout << "[ABS Alert] OFF" << endl;
        }
        logEvent("[ABS] OFF");
        this_thread::sleep_for(chrono::milliseconds(350));
    }
}

// Fuel Sensor (checks every 1 second)
void fuelSensor() {
    int fuelLevel = 12;  // Low fuel simulation
    while (running) {
        if (fuelLevel < 15) {
            lock_guard<mutex> lock(mtx);
            cout << "[Fuel Alert] LOW FUEL! Level = " << fuelLevel << "%" << endl;
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}

// Engine Temp Sensor
void engineSensor() {
    int temperature = 95;   // Overheat simulation
    while (running) {
        if (temperature > 90) {
            lock_guard<mutex> lock(mtx);
            cout << "[Engine Alert] OVERHEAT! Temp = " << temperature << "°C" << endl;
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}

// Door Sensor (random)
void doorSensor() {
    while (running) {
        int r = rand() % 5;
        if (r == 1) {
            lock_guard<mutex> lock(mtx);
            cout << "[Door Alert] A DOOR IS OPEN!" << endl;
            logEvent("[Door] Open Detected");
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// MAIN
int main() {
    cout << "===== VEHICLE NOTIFICATION ALERT SYSTEM =====" << endl;
    cout << "Initializing BCM System...\n" << endl;

    logEvent("Simulation Started");

    // Start all threads
    thread t1(seatbeltAlert);
    thread t2(absAlert);
    thread t3(fuelSensor);
    thread t4(engineSensor);
    thread t5(doorSensor);

    // Let simulation run for 8 seconds (simple requirement)
    this_thread::sleep_for(chrono::seconds(5));

    // Stop everything
    running = false;

    // Wait for all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    logEvent("All alerts cleared");
    logEvent("Simulation Ended Successfully");

    cout << "\nSimulation Complete. All threads stopped safely." << endl;
    cout << "Logs saved to alerts_log.txt" << endl;

    return 0;
}
