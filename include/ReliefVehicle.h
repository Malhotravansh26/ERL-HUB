
#ifndef RELIEF_VEHICLE_H
#define RELIEF_VEHICLE_H

#include <iostream>
#include <string>

namespace ReliefOps {
namespace Logistics {

// Composition class 1
class GPSBeacon {
private:
    double latitude;
    double longitude;

public:
    GPSBeacon();

    void updateLocation(double lat, double lon);

    void displayLocation() const;
};

// Composition class 2
class EmergencyLifeSupportUnit {
private:
    bool active;

public:
    EmergencyLifeSupportUnit();

    void activate();
    void deactivate();

    bool isActive() const;
};

// Abstract base class
class ReliefVehicle {
protected:
    int vehicleId;
    double fuel;
    double payloadCapacity;
    double speed;

    GPSBeacon gps;
    EmergencyLifeSupportUnit lifeSupport;

    static int totalVehicles;

public:
    ReliefVehicle(
        int id,
        double fuelAmount,
        double capacity,
        double vehicleSpeed
    );

    // Pure virtual functions
    virtual void evaluateRoute() const = 0;

    virtual void displayInfo() const = 0;

    // Virtual destructor
    virtual ~ReliefVehicle();

    int getVehicleId() const;
    double getPayloadCapacity() const; 

    static int getTotalVehicles();

    void updateGPS(double lat, double lon);

    void activateLifeSupport();
};

}
}

#endif
