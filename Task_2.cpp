#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
// Class to store vehicle data
class VehicleData {
private:
    float speed;          // Speed in km/h
    float fuelLevel;      // Fuel level in percentage
    float engineTemp;     // Engine temperature in °C
    mutex mtx;            // Mutex for thread safety
    bool running;         // Flag to indicate if the vehicle is running
public:
    VehicleData() : speed(0), fuelLevel(100), engineTemp(90), running(true) {} // Default values

    void updateData() {
        lock_guard<mutex> lock(mtx);
        if (fuelLevel > 0) {
            speed = rand() % 121; // Random speed between 0 and 120 km/h
            fuelLevel = max(0.0f, fuelLevel - (rand() % 5) * 0.5f); // Decrease fuel slightly
            engineTemp = 80 + rand() % 30; // Random temperature between 80°C and 110°C
            if (fuelLevel == 0) {
                running = false; // Stop the vehicle when fuel is depleted
            }
        }
    }

    void getData(float &outSpeed, float &outFuel, float &outTemp, bool &isRunning) {
        lock_guard<mutex> lock(mtx);
        outSpeed = speed;
        outFuel = fuelLevel;
        outTemp = engineTemp;
        isRunning = running;
    }
    bool isRunning() {
        lock_guard<mutex> lock(mtx);
        return running;
    }
};
// Class to display vehicle data
class Display {
public:
    static void showData(VehicleData &data) {
        while (data.isRunning()) {
            float speed, fuel, temp;
            bool isRunning;
            data.getData(speed, fuel, temp, isRunning);
            system("clear"); // Clear console for real-time effect (use "cls" on Windows)
            cout << "==== Instrument Cluster ====" << endl;
            cout << fixed << setprecision(1);
            cout << "Speed: " << speed << " km/h" << endl;
            cout << "Fuel Level: " << fuel << "%" << endl;
            cout << "Engine Temperature: " << temp << "°C" << endl;

            if (temp > 100) {
                cout << "WARNING: Engine overheating!" << endl;
            }
            if (fuel < 10 && fuel > 0) {
                cout << "WARNING: Low fuel!" << endl;
            }
            if (!isRunning) {
                cout << "Vehicle stopped: Fuel depleted!" << endl;
            }

            this_thread::sleep_for(chrono::seconds(1)); // Update every second
        }
    }
};
void updateVehicleData(VehicleData &data) {
    while (data.isRunning()) {
        data.updateData();
        this_thread::sleep_for(chrono::seconds(1)); // Update every second
    }
}
int main() {
    srand(time(0)); // Seed random number generator
    VehicleData vehicleData; // Create vehicle data object
    // Start threads for updating and displaying data
    thread updater(updateVehicleData, ref(vehicleData));
    thread displayer(Display::showData, ref(vehicleData));
    updater.join();  // Wait for the updater thread to finish
    displayer.join(); // Wait for the displayer thread to finish

    cout << "Simulation ended. Refuel to continue.\n";
    return 0;
}
