#include<iostream>
#include<memory>
using namespace std;

class Vehicle{
    private:
        int Speed;
        string Type;
    public:
        void setSpeed(int speed){
            Speed = speed;
        }

        int getSpeed(){
            return Speed;
        }

        void setType(string type){
            Type = type;
        }
        string getType(){
            return Type;
        }
        virtual void displaySpeed(){
            cout <<"Vehicle is : "<<Type<<"\n"<< "Vehicle Speed: " << Speed << " km/h" << endl;
        }
};

class car : public Vehicle{
    private:
        int Gear;
    public:
        car(int speed, int gear, std::string type){
            setSpeed(speed);
            setType(type);
            Gear = gear;
        }
        void displaySpeed() override {
            Vehicle::displaySpeed();
            cout << "Car Gear: " << Gear << endl;
        }
};

class Bike : public Vehicle{
    private:
        bool hasCarrier;
    public:
        Bike(int speed, bool carrier, std::string type){
            setSpeed(speed);
            setType(type);
            hasCarrier = carrier;
        }
        void displaySpeed() override {
            Vehicle::displaySpeed();
            cout << "Bike has carrier: " << (hasCarrier ? "Yes" : "No") << endl;
        }
};

int main(){
    shared_ptr<Vehicle> v1 = make_shared<car>(120, 5, "Sedan");
     weak_ptr<Vehicle> w1 = v1;
    shared_ptr<Vehicle> v2 = v1;
   
    cout<<v1.use_count()<<endl;
    //cout<<v2.use_count()<<endl;
    cout<<w1.use_count()<<endl;
    v1->displaySpeed();
    v2->displaySpeed();
    return 0;
}