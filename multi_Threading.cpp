#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
void readSpeedSensor(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate delay
        std::cout << "Speed Sensor: 60 km/h\n";
    }
}

void readTemperatureSensor(int iterations) {    

    for (int i = 0; i < iterations; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(700)); // Simulate delay
        std::cout << "Temperature Sensor: 75°C\n";
    }
}

int main() {
    int iterations = 10;  // Number of readings for each sensor

    // Create threads for sensors
    std::thread speedThread(readSpeedSensor, iterations);
    std::thread tempThread(readTemperatureSensor, iterations);

    // Wait for threads to finish
    speedThread.join();
    tempThread.join();

    return 0;
}
