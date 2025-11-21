#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include<string>
using namespace std;

mutex mtx;                  
atomic<bool> running(false); 

//Creating a fille wiper_log.txt for saving the Rain and spped data
ofstream logFile("wiper_log.txt");

// Wiper Modes making current mode as OFF
enum WiperMode { OFF, INTERMITTENT, LOW, MEDIUM, HIGH };
WiperMode currentMode = OFF;

//Sensor Values Taking 0 at the start
int rainIntensity = 0;   
int vehicleSpeed = 0;    
bool faultActive = false;

//Function to store the message alerts to the file
void logEvent(const string &msg) {
    lock_guard<mutex> lock(mtx);
    cout << msg << endl;
    logFile << msg << endl;
}

//This function is used to convert the enum modes to strings
string ModeToString(WiperMode M){
    switch(M){
        case OFF:
            return "OFF";
        case INTERMITTENT:
            return "INTERMITTENT";
        case LOW:
            return "LOW";
        case MEDIUM:
            return "MEDIUM";
        case HIGH:
            return "HIGH";
    }
}

//FR3	Auto Mode Logic	Auto-switch mode using if- else-if
void AutoAdjustWiper(){
    if(faultActive) 
        return;

    if(rainIntensity==0){
        currentMode = OFF;
    }
    else if(rainIntensity<30){
        currentMode = INTERMITTENT;
    }
    else if(rainIntensity<60){
        currentMode = LOW;
    }
    else{
        currentMode = HIGH;
    }
    cout<<"[System] Auto Adjust -> Wiper Mode:"<<currentMode<<endl;
    logEvent("[System] Auto Adjust → Wiper Mode: " + ModeToString(currentMode));
}

//this function is to create a thread for the rain sensor
void RainSensorThread() {
    while (running) {
        //rand() function is used to caliculate the rain nintensity randomly
        rainIntensity = rand() % 100; 
        cout<<"[RainSensor] Intensity : "<<rainIntensity<<"%"<<endl;
        logEvent("[RainSensor] Intensity : " + to_string(rainIntensity) + "%");
        AutoAdjustWiper();
        this_thread::sleep_for(chrono::seconds(2)); // thread to sleep for 2 seconds
    }
}

//this function is to create a thread for thr speed sensor
void SpeedSensorThread(){
    while(running){
        //same as above we are using rand function to take speed randomly(just assumtion only)
        vehicleSpeed = rand() % 80; 
        cout<<"[Speed Sensor] Speed :"<<vehicleSpeed<<"km/h"<<endl;
        logEvent("[SpeedSensor]  Speed: " + to_string(vehicleSpeed) + " km/h");
        AutoAdjustWiper();
        this_thread::sleep_for(chrono::seconds(3)); // thread to sleep for 3 seconds
    }
}

//this function is to create a thread for the fault module
void FaultModule(){
    while(running){
        this_thread::sleep_for(chrono::seconds(5)); //' thread to sleep for 5 seconds
        //same as above just to check the chance of fault randomly 
        int chance = rand() % 10;
        if (chance < 3) {  
            faultActive = true;
            cout<<"[Fault] Motor Jam"<<endl;
            cout<<"[System] System Malfunction"<<endl;
            logEvent("[Fault]  Motor Jam ");
            logEvent("[System] System Malfunction");
            this_thread::sleep_for(chrono::seconds(2));
            faultActive = false;
            logEvent("[Fault]  Motor Restored.");
        }

    }
}

// Wiper App classs handeles the menu and running of the threads using is else-if
class WiperApp{
    public:
    void menu() {
        cout << "\n===== VEHICLE WIPER CONTROL SYSTEM =====\n";
        cout << "1. Start Simulation\n";
        cout << "2. Stop Simulation\n";
        cout << "3. Show Current Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice ";
    }
    void Running(){
    logEvent("====== WIPER SYSTEM STARTED ======");
    cout<<"======= WIPER SYSTEM STARTED ========";
    int choice;
    thread t1, t2, t3;
    while (true) {
        menu();
        cin >> choice;
        if (choice == 1) {
            if (!running) {
                running = true;
                t1 = thread(RainSensorThread);
                t2 = thread(SpeedSensorThread);
                t3 = thread(FaultModule);
                logEvent("System Simulation Started.");
                cout<<"System Simulation Started"<<endl;
            } else {
                cout << "Already Running.\n";
            }
        }
        else if (choice == 2) {
            if (running) {
                running = false;
                t1.join();
                t2.join();
                t3.join();
                logEvent("Simulation Stopped.");
                cout<<"simulation stopped"<<endl;
            } else {
                cout << "System not running.\n";
            }
        }

        else if (choice == 3) {
            cout << "\n----- CURRENT STATUS -----\n";
            cout << "Rain Intensity : " << rainIntensity << "%\n";
            cout << "Vehicle Speed  : " << vehicleSpeed << " km/h\n";
            cout << "Wiper Mode     : " << ModeToString(currentMode) << "\n";
            cout << "Fault Active   : " << (faultActive ? "YES" : "NO") << "\n";
        }
        else if (choice == 4) {
            if (running) {
                running = false;
                t1.join();
                t2.join();
                t3.join();
            }
            logEvent("====== SYSTEM SHUTDOWN COMPLETE ======");
            cout<<"======= SYSTEM SHUTDOWN COMPLETE=====";
            break;
        }

        else {
            cout << "Invalid option.\n";
        }
    }

    logFile.close();

    }
};

//Main method
int main() {
    WiperApp APP;
    APP.Running();
    return 0;
}




