#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>
#include <atomic>
using namespace std;



// Global Data Structures
vector<string> vehicles;     // vector
set<string> sensors;         // set
map<string, int> values;     // map
SinglyList serviceHistory;   // linked list
DoublyList alertList;        // doubly linked list

// Thread control
atomic<bool> running(false);
mutex mtx;
ofstream fout("alerts_log.txt");


// Helper: Add alert to console + file
void addAlert(string msg) {
    lock_guard<mutex> lock(mtx);
    alertList.addAlert(msg);
    cout << msg << endl;
    fout << msg << endl;
}






// Simple Singly Linked List (Service History)
struct ServiceNode {
    string service;
    ServiceNode* next;
    ServiceNode(string s) : service(s), next(NULL) {}
};

class SinglyList {
public:
    ServiceNode* head = NULL;

    void addService(string s) {
        ServiceNode* n = new ServiceNode(s);
        n->next = head;
        head = n;
    }

    void display() {
        cout << "\nService History:\n";
        ServiceNode* t = head;
        while (t) {
            cout << " - " << t->service << endl;
            t = t->next;
        }
        if (!head) cout << "No service records.\n";
    }
};


// Simple Doubly Linked List (Recent Alerts)
struct AlertNode {
    string msg;
    AlertNode *prev, *next;
    AlertNode(string m) : msg(m), prev(NULL), next(NULL) {}
};

class DoublyList {
public:
    AlertNode* head = NULL;

    void addAlert(string msg) {
        AlertNode* n = new AlertNode(msg);
        n->next = head;
        if (head) head->prev = n;
        head = n;
    }

    void display() {
        cout << "\nRecent Alerts:\n";
        AlertNode* t = head;
        while (t) {
            cout << " - " << t->msg << endl;
            t = t->next;
        }
        if (!head) cout << "No alerts yet.\n";
    }
};


// Sensor Threads
void fuelSensor() {
    int fuel = 100;

    while (running) {
        this_thread::sleep_for(chrono::seconds(1));
        fuel -= 5;
        values["Fuel"] = fuel;

        if (fuel < 20) addAlert("[Fuel Alert] Low Fuel!");
        if (fuel <= 0) fuel = 100; // reset for demo
    }
}

void tempSensor() {
    int temp = 50;

    while (running) {
        this_thread::sleep_for(chrono::milliseconds(800));
        temp += 10;
        values["Temp"] = temp;

        if (temp > 90) addAlert("[Engine Alert] High Temperature!");
        if (temp > 120) temp = 50; // reset
    }
}

void speedSensor() {
    int speed = 0;
    while (running) {
        this_thread::sleep_for(chrono::milliseconds(700));
        speed += 20;
        values["Speed"] = speed;

        if (speed > 120) addAlert("[Speed Alert] Overspeed!");
        if (speed > 160) speed = 0; // reset
    }
}

// MENU
void menu() {
    cout << "\n===== VEHICLE MONITORING SYSTEM =====\n";
    cout << "1. Start Simulation\n";
    cout << "2. Stop Simulation\n";
    cout << "3. Show Sensor Values\n";
    cout << "4. Show Alerts\n";
    cout << "5. Add Service Record\n";
    cout << "6. Show Service History\n";
    cout << "7. Exit\n";
    cout << "Choose: ";
}

int main() {
    // Initial Vehicles
    vehicles.push_back("Honda City");
    vehicles.push_back("Hyundai i20");

    // Sensors
    sensors.insert("Fuel");
    sensors.insert("Temp");
    sensors.insert("Speed");

    int choice;

    thread t1, t2, t3;

    while (true) {
        menu();
        cin >> choice;

        if (choice == 1) {
            if (!running) {
                running = true;
                t1 = thread(fuelSensor);
                t2 = thread(tempSensor);
                t3 = thread(speedSensor);
                cout << "Simulation Started.\n";
            } else {
                cout << "Already running.\n";
            }

        } else if (choice == 2) {
            if (running) {
                running = false;
                t1.join();
                t2.join();
                t3.join();
                cout << "Simulation Stopped.\n";
            } else {
                cout << "Not running.\n";
            }

        } else if (choice == 3) {
            cout << "\n--- Current Sensor Values ---\n";
            for (auto &p : values)
                cout << p.first << " : " << p.second << endl;

        } else if (choice == 4) {
            alertList.display();

        } else if (choice == 5) {
            string s;
            cout << "Enter service: ";
            cin >> s;
            serviceHistory.addService(s);

        } else if (choice == 6) {
            serviceHistory.display();

        } else if (choice == 7) {
            if (running) {
                running = false;
                t1.join();
                t2.join();
                t3.join();
            }
            cout << "Exiting...\n";
            break;

        } else {
            cout << "Invalid choice.\n";
        }
    }

    fout.close();
    return 0;
}
