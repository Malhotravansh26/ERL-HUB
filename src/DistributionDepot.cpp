
#include "DistributionDepot.h"

#include <iomanip>
#include <stdexcept>

namespace ReliefOps {
namespace Inventory {

// Initialize static members
int DistributionDepot::totalDepots = 0;

double DistributionDepot::totalDispatchedTonnage = 0.0;

// Constructor
DistributionDepot::DistributionDepot(
    int id,
    const std::string& name
) : depotId(id), depotName(name) {

    if (id <= 0 || name.empty()) {
        throw std::invalid_argument("Invalid depot details");
    }

    totalDepots++;
}

// Destructor
DistributionDepot::~DistributionDepot() {
    totalDepots--;
}

// Add cargo or restock existing cargo
void DistributionDepot::addCargo(const ReliefCargo& cargo) {

    std::string name = cargo.getName();

    auto it = inventory.find(name);

    if (it != inventory.end()) {

        it->second += cargo;

    } else {

        inventory.emplace(name, cargo);

    }

    std::cout << name << " added/restocked successfully.\n";
}

// Dispatch cargo
bool DistributionDepot::dispatchCargo(
    const std::string& name,
    int quantity
) {

    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }

    auto it = inventory.find(name);

    if (it == inventory.end()) {
        std::cout << "Cargo not found!\n";
        return false;
    }

    if (it->second.getQuantity() < quantity) {
        std::cout << "Insufficient stock!\n";
        return false;
    }

    // Temporary cargo for deduction
    ReliefCargo dispatched(
        name.c_str(),
        quantity,
        0.0,
        1
    );

    double dispatchedWeight =
        static_cast<double>(quantity) *
        (it->second.getTotalWeight() /
         it->second.getQuantity());

    it->second -= dispatched;

    totalDispatchedTonnage += dispatchedWeight / 1000.0;

    std::cout << quantity << " units of "
              << name << " dispatched successfully.\n";

    return true;
}

// Return cargo using reference
ReliefCargo& DistributionDepot::getCargo(
    const std::string& name
) {

    auto it = inventory.find(name);

    if (it == inventory.end()) {
        throw std::out_of_range("Cargo not found in depot");
    }

    return it->second;
}

// Display complete inventory
void DistributionDepot::displayInventory() const {

    std::cout << "\n========================================\n";
    std::cout << "       DISTRIBUTION DEPOT REPORT\n";
    std::cout << "========================================\n";

    std::cout << "Depot ID   : " << depotId << "\n";
    std::cout << "Depot Name : " << depotName << "\n";

    std::cout << "\nCargo Name\t\tQuantity\tWeight\n";

    for (const auto& item : inventory) {

        std::cout << std::left << std::setw(24)
                  << item.first
                  << std::setw(12)
                  << item.second.getQuantity()
                  << item.second.getTotalWeight()
                  << " kg\n";
    }

    std::cout << "========================================\n";
}

// Static functions
int DistributionDepot::getTotalDepots() {
    return totalDepots;
}

double DistributionDepot::getTotalDispatchedTonnage() {
    return totalDispatchedTonnage;
}

int DistributionDepot::getDepotId() const {
    return depotId;
}

const std::string& DistributionDepot::getDepotName() const {
    return depotName;
}

// IncidentCommander: emergency restocking
void IncidentCommander::emergencyRestock(
    DistributionDepot& depot,
    const ReliefCargo& cargo
) {

    std::cout << "\n[COMMANDER] Emergency restocking initiated!\n";

    // Direct access to private inventory
    auto it = depot.inventory.find(cargo.getName());

    if (it != depot.inventory.end()) {

        it->second += cargo;

    } else {

        depot.inventory.emplace(cargo.getName(), cargo);

    }

    std::cout << "[COMMANDER] Emergency stock updated.\n";
}

// Direct private inventory inspection
void IncidentCommander::inspectDepot(
    const DistributionDepot& depot
) const {

    std::cout << "\n[COMMANDER AUDIT REPORT]\n";

    for (const auto& item : depot.inventory) {

        std::cout << item.first
                  << " : "
                  << item.second.getQuantity()
                  << " units\n";
    }
}

}
}
