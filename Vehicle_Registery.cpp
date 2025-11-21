#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Vehicle {
    string regNo;
    string ownerName;
    string type;
    string company;
    int modelYear;
};

class VehicleRegistry {
private:
    vector<Vehicle> vehicles;

public:
    void registerVehicle() {
        Vehicle v;
        cout << "Enter Registration Number: ";
        cin >> v.regNo;
        cout << "Enter Owner Name: ";
        cin >> v.ownerName;
        cout << "Enter Vehicle Type: ";
        cin >> v.type;
        cout << "Enter Company: ";
        cin >> v.company;
        cout << "Enter Model Year: ";
        cin >> v.modelYear;

        vehicles.push_back(v);
        cout << "Vehicle Registered Successfully!\n";
    }

    void searchByReg() {
        string reg;
        cout << "Enter Registration Number to search: ";
        cin >> reg;

        for (auto &v : vehicles) {
            if (v.regNo == reg) {
                cout << "\nVehicle Found:\n";
                cout << "RegNo: " << v.regNo << "\n";
                cout << "Owner: " << v.ownerName << "\n";
                cout << "Type: " << v.type << "\n";
                cout << "Company: " << v.company << "\n";
                cout << "Model Year: " << v.modelYear << "\n";
                return;
            }
        }
        cout << "Vehicle Not Found.\n";
    }

    void listVehicles() {
        if (vehicles.empty()) {
            cout << "No Vehicles Registered.\n";
            return;
        }

        cout << "\nAll Registered Vehicles:\n";
        for (auto &v : vehicles) {
            cout << "----------------------------\n";
            cout << "RegNo: " << v.regNo << "\n";
            cout << "Owner: " << v.ownerName << "\n";
            cout << "Type: " << v.type << "\n";
            cout << "Company: " << v.company << "\n";
            cout << "Year: " << v.modelYear << "\n";
        }
        cout << "----------------------------\n";
    }

    void deleteVehicle() {
        string reg;
        cout << "Enter Registration Number to delete: ";
        cin >> reg;

        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].regNo == reg) {
                vehicles.erase(vehicles.begin() + i);
                cout << "Vehicle Deleted Successfully!\n";
                return;
            }
        }
        cout << "Vehicle Not Found!\n";
    }
};

int main() {
    VehicleRegistry registry;
    int choice;

    while (true) {
        cout << "\n====== VEHICLE REGISTRATION SYSTEM ======\n";
        cout << "1. Register Vehicle\n";
        cout << "2. Search Vehicle by RegNo\n";
        cout << "3. List All Vehicles\n";
        cout << "4. Delete Vehicle\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registry.registerVehicle(); break;
            case 2: registry.searchByReg(); break;
            case 3: registry.listVehicles(); break;
            case 4: registry.deleteVehicle(); break;
            case 5: 
                cout << "Exiting... Thank you!\n";
                return 0;
            default:
                cout << "Invalid Choice! Try Again.\n";
        }
    }

    return 0;
}
