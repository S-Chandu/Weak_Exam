#include<iostream>                                                  
                                                    
using namespace std;                                                    
                                                    
class Vehicle{                                                  
    private:                                                    
        string brand;                                                   
        float speed;                                                    
    public:                                                 
        Vehicle(string b, float s): brand(b), speed(s) {}                                                   
       virtual void displayInfo(){                                                  
            cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << endl;                                                  
        }                                                   
                                                        
       virtual void start(){                                                    
            cout<<"Vehicle started."<<endl;                                                 
        }                                                   
                                                        
};                                                  
                                                    
class car : public Vehicle{                                                 
    public:                                                 
        car(string b, float s): Vehicle(b, s) {}                                                    
        void displayInfo() override {                                                   
            cout << "Car Info - ";                                                  
            Vehicle::displayInfo();                                                 
        }                                                   
        void start() override {                                                 
            cout<<"Car started with a roar!"<<endl;                                                 
        }                                                   
                                                        
};                                                  
                                                    
class bike : public Vehicle{                                                    
    public:                                                 
        bike(string b, float s): Vehicle(b, s) {}                                                   
        void displayInfo() override {                                                   
            cout << "Bike Info - ";                                                 
            Vehicle::displayInfo();                                                 
        }                                                   
        void start() override {                                                 
            cout<<"Bike started with a vroom!"<<endl;                                                   
        }                                                   
                                                        
};                                                  
                                                    
                                                    
class Application{                                                  
    public:                                                 
        void run(){                                                 
                                                            
            displaymenu();                                                  
            int choice;                                                 
            cout<<"Enter your choice: ";                                                    
            cin>>choice;                                                    
            Vehicle* vehicles[10];                                                  
            int count = 0;                                                  
            if(count>=10){                                                  
                cout<<"Vehicle limit reached."<<endl;                                                   
                return;                                                 
            }                                                   
            if(choice == 1){                                                    
                string brand;                                                   
                float speed;                                                    
                cout<<"Enter car brand: ";                                                  
                cin>>brand;                                                 
                cout<<"Enter car speed: ";                                                  
                cin>>speed;                                                 
                vehicles[count++] = new car(brand, speed);                                                  
            }                                                   
            else if(choice == 2){                                                   
                string brand;                                                   
                float speed;                                                    
                cout<<"Enter bike brand: ";                                                 
                cin>>brand;                                                 
                cout<<"Enter bike speed: ";                                                 
                cin>>speed;                                                 
                vehicles[count++] = new bike(brand, speed);                                                 
            }                                                   

            
            else if(choice == 3){                                                   
                for(int i=0; i<count; i++){                                                 
                    car* c = dynamic_cast<car*>(vehicles[i]);                                                   
                    if(c){                                                  
                        c->displayInfo();                                                   
                        c->start();                                                 
                    }                                                   
                }                                                   
            }                                                   
            else if(choice == 4){                                                   
                for(int i=0; i<count; i++){                                                 
                    bike* b = dynamic_cast<bike*>(vehicles[i]);                                                 
                    if(b){                                                  
                        b->displayInfo();                                                   
                        b->start();                                                 
                    }                                                   
                }                                                   
            }                                                   
            else if(choice == 5){                                                   
                cout<<"Exiting application."<<endl;                                                 
                return;                                                 
            }                                                   
            else{                                                   
                cout<<"Invalid choice."<<endl;                                                  
            }                                                   
                                                                
        }                                                   
                                                        
                                                        
    void displaymenu(){                                                 
                                                            
        cout<<"1.Enter Car Details"<<endl;                                                  
        cout<<"2.Enter Bike Details"<<endl;                                                 
        cout<<"3.Display car details"<<endl;                                                    
        cout<<"4.Display bike details"<<endl;                                                   
        cout<<"5.Exit"<<endl;                                                   
                                                            
    }                                                   
};                                                  
                                                    
                                                    
                                                    
int main(){                                                 
    Application app;                                                    
    app.run();                                                  
    return 0;                                                   
}                                                   