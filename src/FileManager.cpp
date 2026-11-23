
#include "FileManager.h"
#include "CustomExceptions.h"
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace ReliefOps {
namespace Core {

namespace {

// Write primitive data
template <typename T>
void writeValue(std::ofstream& file, const T& value) {

    file.write(
        reinterpret_cast<const char*>(&value),
        sizeof(T)
    );

    if (!file) {
        throw FileException("Failed to write binary data");
    }
}

// Read primitive data
template <typename T>
T readValue(std::ifstream& file) {

    T value{};

    file.read(
        reinterpret_cast<char*>(&value),
        sizeof(T)
    );

    if (!file) {
        throw FileException("Incomplete or corrupted binary data");
    }

    return value;
}

}

// Write string into binary file
void FileManager::writeString(
    std::ofstream& file,
    const std::string& value
) {

    if (value.size() > 10000) {
        throw FileException("String is too large");
    }

    std::uint32_t length =
        static_cast<std::uint32_t>(value.size());

    writeValue(file, length);

    file.write(value.data(), length);

    if (!file) {
        throw FileException("String writing failed");
    }
}

// Read string from binary file
std::string FileManager::readString(
    std::ifstream& file
) {

    std::uint32_t length = readValue<std::uint32_t>(file);

    if (length > 10000) {
        throw FileException("Invalid string length");
    }

    std::string value(length, '\0');

    if (length > 0) {

        file.read(&value[0], length);

        if (!file) {
            throw FileException("String reading failed");
        }
    }

    return value;
}

// ======================================
// SAVE INVENTORY
// ======================================

void FileManager::saveInventory(
    const std::vector<Inventory::ReliefCargo>& inventory,
    const std::string& filename
) {

    if (inventory.size() > 100000) {
        throw FileException("Too many inventory records");
    }

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileException("Cannot open inventory file");
    }

    try {

        std::uint32_t count =
            static_cast<std::uint32_t>(inventory.size());

        writeValue(file, count);

        for (const auto& cargo : inventory) {

            writeString(file, cargo.getName());

            writeValue(file, cargo.getQuantity());

            writeValue(file, cargo.getWeightPerUnit());

            writeValue(file, cargo.getPriority());
        }

        file.close();

        if (!file) {
            throw FileException("Inventory file closing failed");
        }

        std::cout << "Inventory saved successfully!\n";
    }
    catch (...) {
        file.close();
        throw;
    }
}

// ======================================
// LOAD INVENTORY
// ======================================

std::vector<Inventory::ReliefCargo>
FileManager::loadInventory(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileException("Cannot open inventory file");
    }

    try {

        std::uint32_t count = readValue<std::uint32_t>(file);

        if (count > 100000) {
            throw FileException("Invalid inventory record count");
        }

        std::vector<Inventory::ReliefCargo> inventory;

        inventory.reserve(count);

        for (std::uint32_t i = 0; i < count; i++) {

            std::string name = readString(file);

            int quantity = readValue<int>(file);

            double weight = readValue<double>(file);

            int priority = readValue<int>(file);

            inventory.emplace_back(
                name.c_str(),
                quantity,
                weight,
                priority
            );
        }

        file.close();

        std::cout << "Inventory loaded successfully!\n";

        return inventory;
    }
    catch (...) {
        file.close();
        throw;
    }
}

// ======================================
// SAVE MISSIONS
// ======================================

void FileManager::saveMissions(
    const std::vector<Logistics::Mission>& missions,
    const std::string& filename
) {

    if (missions.size() > 100000) {
        throw FileException("Too many mission records");
    }

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileException("Cannot open mission file");
    }

    try {

        std::uint32_t count =
            static_cast<std::uint32_t>(missions.size());

        writeValue(file, count);

        for (const auto& mission : missions) {

            writeValue(file, mission.getMissionId());

            writeString(file, mission.getMissionType());

            writeString(file, mission.getDestination());

            writeValue(file, mission.getPriority());

            writeString(file, mission.getRequiredSupply());

            writeValue(file, mission.getRequiredQuantity());
        }

        file.close();

        if (!file) {
            throw FileException("Mission file closing failed");
        }

        std::cout << "Missions saved successfully!\n";
    }
    catch (...) {
        file.close();
        throw;
    }
}

// ======================================
// LOAD MISSIONS
// ======================================

std::vector<Logistics::Mission>
FileManager::loadMissions(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileException("Cannot open mission file");
    }

    try {

        std::uint32_t count = readValue<std::uint32_t>(file);

        if (count > 100000) {
            throw FileException("Invalid mission record count");
        }

        std::vector<Logistics::Mission> missions;

        missions.reserve(count);

        for (std::uint32_t i = 0; i < count; i++) {

            int id = readValue<int>(file);

            std::string type = readString(file);

            std::string destination = readString(file);

            int priority = readValue<int>(file);

            std::string supply = readString(file);

            int quantity = readValue<int>(file);

            missions.emplace_back(
                id,
                type,
                destination,
                priority,
                supply,
                quantity
            );
        }

        file.close();

        std::cout << "Missions loaded successfully!\n";

        return missions;
    }
    catch (...) {
        file.close();
        throw;
    }
}

}
}
