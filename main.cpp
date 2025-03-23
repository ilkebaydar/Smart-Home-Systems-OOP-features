#include <iostream>
#include <cstring>

using std::cout;
using std::string;
using std::endl;

class SmartDevice {
private:
    static int deviceCount;
    char* name;
    char* type;
    bool status;
    int powerConsumption;
    mutable int usageCount;

public:
    SmartDevice(){
        cout<<"Default constructor invoked"<<endl;
        name = new char[9];
        strcpy(name, "Unknown");
        type= new char[9];
        strcpy(name, "Unknown");
        status= false;
        powerConsumption =0;
        usageCount = 0;
        deviceCount++;
    }

    SmartDevice(const char* deviceName, const char* deviceType, int power){
        cout<<"Parameterized constructor invoked"<<endl;
        name= new char[strlen(deviceName) +1];
        strcpy(name, deviceName);
        type = new char[strlen(deviceType)+1];
        strcpy(type, deviceType);
        powerConsumption = power;
        status = false;
        usageCount = 0;
        deviceCount++;
    }

    SmartDevice(const SmartDevice& copy){
        cout << "Copy constructor invoked"<< endl;
        name = new char[strlen(copy.name)+1];
        strcpy(name, copy.name);
        type = new char[strlen(copy.type)+1];
        strcpy(type, copy.type);
        powerConsumption = copy.powerConsumption;
        usageCount = copy.usageCount;
        status = copy.status;
        deviceCount++;
    }

    ~SmartDevice() {
        cout<<"Destructor invoked"<< endl;
        delete [] name;
        delete [] type;
        deviceCount--;
    }

    void togglePower(){
        status = !status;
        if(status)
            cout<< "Device is ON"<< endl;
        else
            cout<< " Device is OFF" << endl;
    }

    void showStatus() const{
        usageCount++;
        cout<<"Name: "<<name<< "\nType: "<< type << "\nPower Consumption: "<<
                 powerConsumption<< "\nStatus: "<< (status ? "ON" : "OFF")<<"\nUsage Count: "<<usageCount << endl;
    }

    int getUsageCount() const {
        return usageCount;
    }

    static int getDeviceCount() {
        return deviceCount;
    }

    const char* getName() const {
        return name;
    }

    void setName(const char* newName) {
        delete[] name;
        name = new char[strlen(newName)+1];
        strcpy(name,newName);
    }

};
int SmartDevice:: deviceCount = 0;

class SmartHome{
private:
    char* homeName;
    SmartDevice** devices;
    int deviceIndex;
    int maxDevices;

public:
    SmartHome(const char* name, int maxDev): deviceIndex(0), maxDevices(maxDev){
        cout<< "Parameterized constructor invoked for home"<<endl;
        homeName = new char[strlen(name)+1];
        strcpy(homeName, name);
        devices = new SmartDevice * [maxDevices];
    }
    ~SmartHome(){
        delete[] homeName;
        for(int i=0; i<deviceIndex; i++){
            delete devices[i];
        }
        delete[] devices;
    }

    void addDevice(const SmartDevice& device){
        if(deviceIndex<maxDevices){
            devices[deviceIndex] = new SmartDevice(device);
            cout<< "Added: "<<devices[deviceIndex]->getName()<<endl;
        } else {
            cout<< "Cannot add devices!" << endl;
        }
    }

    bool removeDevice(const char* deviceName){
        for(int i=0; i<deviceIndex; i++){
            if(strcmp(devices[i]->getName(), deviceName)==0){
                delete devices[i];
                for(int j=i; j<deviceIndex-1; j++){
                    devices[j]= devices[j+1];
                }
                deviceIndex--;
                cout<<"Removed: "<<deviceName<<endl;
                return true;
            }
        }
        return false;
    }

    void showDevices() const{
        cout<<"Device in "<< homeName<< ":\n";
        for(int i =0; i<deviceIndex; i++){
            devices[i]->showStatus();
        }
    }

};

int main() {
    SmartHome myHome{ "My Home" , 5 } ;
    SmartDevice device1 { " Living Room Light 1" , " Smart Light" , 10 };
    SmartDevice device2 { device1 } ;
    device2.setName ( " Living Room Light 2") ;
    SmartDevice device3 { "Bedroom AC" , " Smart Thermostat" , 1500 };
    SmartDevice device4 { " Front Door Cam" , " Security Camera" , 5 } ;

    myHome.addDevice ( device1 ) ;
    myHome.addDevice ( device2 ) ;
    myHome.addDevice ( device3 ) ;
    myHome.addDevice ( device4 ) ;

    cout << " \n All Devices \n " ;
    cout << " Device count: " << SmartDevice :: getDeviceCount() << " \n " ;
    myHome.showDevices() ;
    cout << " \nRemoving a Device\n " ;
    if (myHome.removeDevice("Living Room Light 2 ") ) {
        cout << "Removed: " << "Living Room Light 2 " << " \n " ;
    }
    cout << " Device count: " << SmartDevice :: getDeviceCount ( ) << " \n " ;
    myHome.showDevices() ;
    return 0;
}
