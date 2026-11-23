
#ifndef RELIEF_CARGO_H
#define RELIEF_CARGO_H

#include <iostream>

namespace ReliefOps {
namespace Inventory {

class ReliefCargo {
private:
    char* cargoName;
    int quantity;
    double weightPerUnit;
    int priority;

    void setCargoName(const char* name);

public:
    // Default constructor
    ReliefCargo();

    // Parameterized / Dynamic constructor
    ReliefCargo(const char* name, int qty,
                double weight, int priorityLevel);

    // Deep copy constructor
    ReliefCargo(const ReliefCargo& other);

    // Copy assignment operator
    ReliefCargo& operator=(const ReliefCargo& other);

    // Destructor
    ~ReliefCargo();

    // Getters
    const char* getName() const;
    int getQuantity() const;
    double getTotalWeight() const;
    double getWeightPerUnit() const; 
    int getPriority() const;

    // Operator overloading
    ReliefCargo& operator+=(const ReliefCargo& other);
    ReliefCargo& operator-=(const ReliefCargo& other);

    bool operator==(const ReliefCargo& other) const;

    // Stream operators
    friend std::ostream& operator<<(
        std::ostream& out, const ReliefCargo& cargo
    );

    friend std::istream& operator>>(
        std::istream& in, ReliefCargo& cargo
    );
};

}
}

#endif
