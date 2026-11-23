
#ifndef MISSION_H
#define MISSION_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace ReliefOps {
namespace Logistics {

class Mission {
private:
    int missionId;
    std::string missionType;
    std::string destination;
    int priority;
    std::string requiredSupply;
    int requiredQuantity;

public:

    // Parameterized constructor
    Mission(
        int id,
        const std::string& type,
        const std::string& location,
        int priorityLevel,
        const std::string& supply,
        int quantity
    )
        : missionId(id),
          missionType(type),
          destination(location),
          priority(priorityLevel),
          requiredSupply(supply),
          requiredQuantity(quantity) {

        if (id <= 0 || type.empty() ||
            location.empty() || supply.empty() ||
            priorityLevel < 1 || priorityLevel > 4 ||
            quantity <= 0) {

            throw std::invalid_argument("Invalid mission details");
        }
    }

    // Getters
    int getMissionId() const {
        return missionId;
    }

    const std::string& getMissionType() const {
        return missionType;
    }

    const std::string& getDestination() const {
        return destination;
    }

    int getPriority() const {
        return priority;
    }

    const std::string& getRequiredSupply() const {
        return requiredSupply;
    }

    int getRequiredQuantity() const {
        return requiredQuantity;
    }

    // Display mission details
    void displayMission() const {

        std::cout << "\nMission ID: " << missionId
                  << "\nMission Type: " << missionType
                  << "\nDestination: " << destination
                  << "\nPriority: " << priority
                  << "\nRequired Supply: " << requiredSupply
                  << "\nRequired Quantity: " << requiredQuantity
                  << "\n";
    }
};

}
}

#endif
