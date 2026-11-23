
#include "ReliefVehicle.h"

#include <stdexcept>

namespace ReliefOps {
namespace Logistics {

// GPSBeacon implementation

GPSBeacon::GPSBeacon()
    : latitude(0.0), longitude(0.0) {}

void GPSBeacon::updateLocation(double lat, double lon) {

    if (lat < -90 || lat > 90 ||
        lon < -180 || lon > 180) {

        throw std::invalid_argument("Invalid GPS coordinates");
    }

    latitude = lat;
    longitude = lon;
}

void GPSBeacon::displayLocation() const {

    std::cout << "GPS Location: "
              << latitude << ", "
              << longitude << "\n";
}

// EmergencyLifeSupportUnit implementation

EmergencyLifeSupportUnit::EmergencyLifeSupportUnit()
    : active(false) {}

void EmergencyLifeSupportUnit::activate() {
    active = true;
}

void EmergencyLifeSupportUnit::deactivate() {
    active = false;
}

bool EmergencyLifeSupportUnit::isActive() const {
    return active;
}

// Initialize static member
int ReliefVehicle::totalVehicles = 0;

// ReliefVehicle constructor

ReliefVehicle::ReliefVehicle(
    int id,
    double fuelAmount,
    double capacity,
    double vehicleSpeed
) : vehicleId(id),
    fuel(fuelAmount),
    payloadCapacity(capacity),
    speed(vehicleSpeed) {

    if (id <= 0 || fuelAmount < 0 ||
        capacity <= 0 || vehicleSpeed <= 0) {

        throw std::invalid_argument("Invalid vehicle details");
    }

    totalVehicles++;
}

// Virtual destructor

ReliefVehicle::~ReliefVehicle() {
    totalVehicles--;
}

int ReliefVehicle::getVehicleId() const {
    return vehicleId;
}
double ReliefVehicle::getPayloadCapacity() const {
    return payloadCapacity;
}
int ReliefVehicle::getTotalVehicles() {
    return totalVehicles;
}


// Composition functionality

void ReliefVehicle::updateGPS(double lat, double lon) {
    gps.updateLocation(lat, lon);
}

void ReliefVehicle::activateLifeSupport() {
    lifeSupport.activate();
}

}
}
