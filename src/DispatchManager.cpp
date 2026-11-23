
#include "DispatchManager.h"

#include <iostream>
#include <stdexcept>

namespace ReliefOps {
namespace Logistics {

bool DispatchManager::executeMission(
    const Mission& mission,
    Inventory::DistributionDepot& depot,
    ReliefVehicle& vehicle
) const {

    std::cout << "\n====================================\n";
    std::cout << "        MISSION EXECUTION\n";
    std::cout << "====================================\n";

    // Display mission details
    mission.displayMission();

    try {

        // Step 1: Check inventory availability
        Inventory::ReliefCargo& cargo =
            depot.getCargo(mission.getRequiredSupply());

        int availableQuantity = cargo.getQuantity();

        int requiredQuantity =
            mission.getRequiredQuantity();

        if (availableQuantity < requiredQuantity) {

            std::cout << "\nERROR: Insufficient inventory!\n";

            std::cout << "Available: "
                      << availableQuantity << "\n";

            std::cout << "Required: "
                      << requiredQuantity << "\n";

            return false;
        }

        // Step 2: Calculate required payload
        double unitWeight =
            cargo.getTotalWeight() / availableQuantity;

        double requiredWeight =
            requiredQuantity * unitWeight;

        std::cout << "\nRequired Payload: "
                  << requiredWeight << " kg\n";

        std::cout << "Vehicle Capacity: "
                  << vehicle.getPayloadCapacity() << " kg\n";

        // Step 3: Check vehicle capacity
        if (requiredWeight > vehicle.getPayloadCapacity()) {

            std::cout << "\nERROR: Vehicle capacity exceeded!\n";

            return false;
        }

        // Step 4: Deduct inventory
        bool success = depot.dispatchCargo(
            mission.getRequiredSupply(),
            requiredQuantity
        );

        if (!success) {
            return false;
        }

        // Step 5: Display assigned vehicle
        std::cout << "\nAssigned Vehicle ID: "
                  << vehicle.getVehicleId() << "\n";

        vehicle.displayInfo();

        // Step 6: Evaluate route
        vehicle.evaluateRoute();

        // Step 7: Mission completion
        std::cout << "\nMISSION DISPATCHED SUCCESSFULLY!\n";

        std::cout << "====================================\n";

        return true;

    }
    catch (const std::exception& e) {

        std::cout << "\nMISSION FAILED: "
                  << e.what() << "\n";

        return false;
    }
}

}
}
