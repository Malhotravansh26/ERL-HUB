
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ReliefCargo.h"
#include "Mission.h"
#include "CustomExceptions.h"

namespace ReliefOps {
namespace Core {

class FileManager {

private:

    // Private helper functions for binary storage
    static void writeString(
        std::ofstream& file,
        const std::string& value
    );

    static std::string readString(
        std::ifstream& file
    );

public:

    // Save inventory into binary file
    static void saveInventory(
        const std::vector<Inventory::ReliefCargo>& inventory,
        const std::string& filename = "data/inventory.dat"
    );

    // Load inventory from binary file
    static std::vector<Inventory::ReliefCargo> loadInventory(
        const std::string& filename = "data/inventory.dat"
    );

    // Save missions into binary file
    static void saveMissions(
        const std::vector<Logistics::Mission>& missions,
        const std::string& filename = "data/missions.dat"
    );

    // Load missions from binary file
    static std::vector<Logistics::Mission> loadMissions(
        const std::string& filename = "data/missions.dat"
    );

};

}
}

#endif
