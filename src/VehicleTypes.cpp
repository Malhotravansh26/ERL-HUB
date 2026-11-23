
#include "VehicleTypes.h"

namespace ReliefOps {
namespace Logistics {

// AerialTransport

AerialTransport::AerialTransport(
    int id, double fuelAmount,
    double capacity, double vehicleSpeed
) : ReliefVehicle(
        id, fuelAmount, capacity, vehicleSpeed
    ) {}

void AerialTransport::evaluateRoute() const {

    std::cout << "Route: Aerial route selected.\n";

    if (fuel < 20) {
        std::cout << "Warning: Low helicopter fuel!\n";
    } else {
        std::cout << "Aerial route is operational.\n";
    }
}

void AerialTransport::displayInfo() const {

    std::cout << "\n[AERIAL TRANSPORT]\n";
    std::cout << "Vehicle ID: " << vehicleId << "\n";
    std::cout << "Fuel: " << fuel << " litres\n";
    std::cout << "Payload: " << payloadCapacity << " kg\n";
    std::cout << "Speed: " << speed << " km/h\n";

    gps.displayLocation();
}

// GroundConvoy

GroundConvoy::GroundConvoy(
    int id, double fuelAmount,
    double capacity, double vehicleSpeed
) : ReliefVehicle(
        id, fuelAmount, capacity, vehicleSpeed
    ) {}

void GroundConvoy::evaluateRoute() const {

    std::cout << "Route: Ground road selected.\n";

    if (fuel < 20) {
        std::cout << "Warning: Low truck fuel!\n";
    } else {
        std::cout << "Ground route is operational.\n";
    }
}

void GroundConvoy::displayInfo() const {

    std::cout << "\n[GROUND CONVOY]\n";
    std::cout << "Vehicle ID: " << vehicleId << "\n";
    std::cout << "Fuel: " << fuel << " litres\n";
    std::cout << "Payload: " << payloadCapacity << " kg\n";

    gps.displayLocation();
}

// AmphibiousCraft

AmphibiousCraft::AmphibiousCraft(
    int id, double fuelAmount,
    double capacity, double vehicleSpeed
) : ReliefVehicle(
        id, fuelAmount, capacity, vehicleSpeed
    ) {}

void AmphibiousCraft::evaluateRoute() const {

    std::cout << "Route: Waterway route selected.\n";

    if (fuel < 20) {
        std::cout << "Warning: Low boat fuel!\n";
    } else {
        std::cout << "Water route is operational.\n";
    }
}

void AmphibiousCraft::displayInfo() const {

    std::cout << "\n[AMPHIBIOUS CRAFT]\n";
    std::cout << "Vehicle ID: " << vehicleId << "\n";
    std::cout << "Fuel: " << fuel << " litres\n";
    std::cout << "Payload: " << payloadCapacity << " kg\n";

    gps.displayLocation();
}

// HybridMedicalUnit

HybridMedicalUnit::HybridMedicalUnit(
    int id, double fuelAmount,
    double capacity, double vehicleSpeed
)
    : ReliefVehicle(
        id, fuelAmount, capacity, vehicleSpeed
      ),
      GroundConvoy(
        id, fuelAmount, capacity, vehicleSpeed
      ),
      AmphibiousCraft(
        id, fuelAmount, capacity, vehicleSpeed
      ) {}

void HybridMedicalUnit::evaluateRoute() const {

    std::cout << "Route: Hybrid ground/water route selected.\n";
    std::cout << "Medical emergency route evaluation complete.\n";
}

void HybridMedicalUnit::displayInfo() const {

    std::cout << "\n[HYBRID MEDICAL UNIT]\n";
    std::cout << "Vehicle ID: " << vehicleId << "\n";
    std::cout << "Fuel: " << fuel << " litres\n";
    std::cout << "Payload: " << payloadCapacity << " kg\n";

    gps.displayLocation();

    std::cout << "Life Support: "
              << (lifeSupport.isActive() ? "ACTIVE" : "INACTIVE")
              << "\n";
}

}
}
