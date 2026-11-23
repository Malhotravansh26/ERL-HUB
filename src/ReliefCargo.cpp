
#include "ReliefCargo.h"

#include <cstring>
#include <iomanip>
#include <string>
#include <stdexcept>

namespace ReliefOps {
namespace Inventory {

// Default constructor
ReliefCargo::ReliefCargo()
    : cargoName(nullptr),
      quantity(0),
      weightPerUnit(0.0),
      priority(1) {

    setCargoName("Unknown");
}

// Dynamic memory allocation
void ReliefCargo::setCargoName(const char* name) {

    if (name == nullptr) {
        throw std::invalid_argument("Cargo name cannot be null");
    }

    char* newName = new char[std::strlen(name) + 1];

    std::strcpy(newName, name);

    delete[] cargoName;
    cargoName = newName;
}

// Parameterized constructor
ReliefCargo::ReliefCargo(
    const char* name,
    int qty,
    double weight,
    int priorityLevel
) : cargoName(nullptr),
    quantity(qty),
    weightPerUnit(weight),
    priority(priorityLevel) {

    if (qty < 0 || weight < 0 || priorityLevel < 1) {
        throw std::invalid_argument("Invalid cargo details");
    }

    setCargoName(name);
}

// Deep copy constructor
ReliefCargo::ReliefCargo(const ReliefCargo& other)
    : cargoName(nullptr),
      quantity(other.quantity),
      weightPerUnit(other.weightPerUnit),
      priority(other.priority) {

    setCargoName(other.cargoName);
}

// Copy assignment operator
ReliefCargo& ReliefCargo::operator=(const ReliefCargo& other) {

    if (this != &other) {

        char* newName = new char[std::strlen(other.cargoName) + 1];

        std::strcpy(newName, other.cargoName);

        delete[] cargoName;

        cargoName = newName;
        quantity = other.quantity;
        weightPerUnit = other.weightPerUnit;
        priority = other.priority;
    }

    return *this;
}

// Destructor
ReliefCargo::~ReliefCargo() {
    delete[] cargoName;
}

// Getters
const char* ReliefCargo::getName() const {
    return cargoName;
}

int ReliefCargo::getQuantity() const {
    return quantity;
}

double ReliefCargo::getTotalWeight() const {
    return quantity * weightPerUnit;
}
double ReliefCargo::getWeightPerUnit() const {
    return weightPerUnit;
}

int ReliefCargo::getPriority() const {
    return priority;
}

// += Restock cargo
ReliefCargo& ReliefCargo::operator+=(const ReliefCargo& other) {

    if (!(*this == other)) {
        throw std::invalid_argument("Cannot combine different cargo");
    }

    quantity += other.quantity;

    return *this;
}

// -= Deduct cargo
ReliefCargo& ReliefCargo::operator-=(const ReliefCargo& other) {

    if (!(*this == other)) {
        throw std::invalid_argument("Cargo type mismatch");
    }

    if (other.quantity > quantity) {
        throw std::underflow_error("Insufficient cargo stock");
    }

    quantity -= other.quantity;

    return *this;
}

// Compare cargo identity
bool ReliefCargo::operator==(const ReliefCargo& other) const {

    return std::strcmp(cargoName, other.cargoName) == 0;
}

// Output operator
std::ostream& operator<<(
    std::ostream& out,
    const ReliefCargo& cargo
) {

    out << std::quoted(cargo.cargoName) << " "
        << cargo.quantity << " "
        << cargo.weightPerUnit << " "
        << cargo.priority;

    return out;
}

// Input operator
std::istream& operator>>(
    std::istream& in,
    ReliefCargo& cargo
) {

    std::string name;
    int qty;
    double weight;
    int priorityLevel;

    if (in >> std::quoted(name)
           >> qty
           >> weight
           >> priorityLevel) {

        if (qty < 0 || weight < 0 || priorityLevel < 1) {
            in.setstate(std::ios::failbit);
            return in;
        }

        ReliefCargo temp(
            name.c_str(), qty, weight, priorityLevel
        );

        cargo = temp;
    }

    return in;
}

}
}
