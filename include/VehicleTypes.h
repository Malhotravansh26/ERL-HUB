
#ifndef VEHICLE_TYPES_H
#define VEHICLE_TYPES_H

#include "ReliefVehicle.h"

namespace ReliefOps {
namespace Logistics {

// Derived class 1
class AerialTransport : public ReliefVehicle {
public:
    AerialTransport(
        int id, double fuel,
        double capacity, double speed
    );

    void evaluateRoute() const override;

    void displayInfo() const override;
};

// Derived class 2 - Virtual inheritance
class GroundConvoy : virtual public ReliefVehicle {
public:
    GroundConvoy(
        int id, double fuel,
        double capacity, double speed
    );

    void evaluateRoute() const override;

    void displayInfo() const override;
};

// Derived class 3 - Virtual inheritance
class AmphibiousCraft : virtual public ReliefVehicle {
public:
    AmphibiousCraft(
        int id, double fuel,
        double capacity, double speed
    );

    void evaluateRoute() const override;

    void displayInfo() const override;
};

// Hybrid class - Multiple inheritance
class HybridMedicalUnit :
    public GroundConvoy,
    public AmphibiousCraft {

public:
    HybridMedicalUnit(
        int id, double fuel,
        double capacity, double speed
    );

    void evaluateRoute() const override;

    void displayInfo() const override;
};

}
}

#endif
