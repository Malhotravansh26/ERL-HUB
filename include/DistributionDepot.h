
#ifndef DISTRIBUTION_DEPOT_H
#define DISTRIBUTION_DEPOT_H

#include "ReliefCargo.h"
#include <iostream>
#include <unordered_map>
#include <string>

namespace ReliefOps {
namespace Inventory {

class IncidentCommander;

class DistributionDepot {
private:
    int depotId;
    std::string depotName;

    std::unordered_map<std::string, ReliefCargo> inventory;

    static int totalDepots;
    static double totalDispatchedTonnage;

    // Only IncidentCommander can directly inspect private inventory
    friend class IncidentCommander;

public:
    DistributionDepot(int id, const std::string& name);

    ~DistributionDepot();

    // Add or restock supplies
    void addCargo(const ReliefCargo& cargo);

    // Dispatch supplies
    bool dispatchCargo(const std::string& name, int quantity);

    // Return cargo by reference
    ReliefCargo& getCargo(const std::string& name);

    // Display inventory
    void displayInventory() const;

    // Static functions
    static int getTotalDepots();
    static double getTotalDispatchedTonnage();

    int getDepotId() const;
    const std::string& getDepotName() const;
};

// Friend class for emergency override
class IncidentCommander {
public:
    void emergencyRestock(
        DistributionDepot& depot,
        const ReliefCargo& cargo
    );

    void inspectDepot(const DistributionDepot& depot) const;
};

}
}

#endif
