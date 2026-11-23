#include <iostream>
#include <vector>
#include "CustomExceptions.h"
#include "FileManager.h"
#include "ReliefCargo.h"
#include "Mission.h"
#include "PriorityDispatchQueue.h"
#include "DispatchManager.h"
#include "VehicleTypes.h"
#include "DistributionDepot.h"

using namespace std;
using namespace ReliefOps::Logistics;
using namespace ReliefOps::Inventory;
using namespace ReliefOps::Core;

int main() {

    cout << "\n====================================\n";
    cout << "       ERL-HUB INTEGRATED SYSTEM\n";
    cout << "====================================\n";

    try {
        // 1. Create depot
        DistributionDepot depot(101, "Delhi Relief Depot");

       
        // 2. Load inventory from binary file

        vector<ReliefCargo> inventoryData =
            ReliefOps::Core::FileManager::loadInventory();

        for (const auto& cargo : inventoryData) {
            depot.addCargo(cargo);
        }

        cout << "\nInventory loaded into depot successfully!\n";


        // 4. Create vehicles
        AerialTransport helicopter(201, 100, 500, 180);
        GroundConvoy     truck(202, 100, 2000, 70);
        AmphibiousCraft  boat(203, 80, 1000, 50);

        // 5. Create mission queue and add missions
       
        // 5. Load missions from binary file

        vector<Mission> missionList =
            ReliefOps::Core::FileManager::loadMissions();

        // Create mission queue
        PriorityDispatchQueue<Mission> queue;

        // Add loaded missions to priority queue
        for (const auto& mission : missionList) {
            queue.enqueue(mission);
        }

        cout << "\nAll missions loaded into priority queue!\n";


        // 6. Create vehicle fleet
        vector<ReliefVehicle*> fleet = {
            &helicopter,
            &truck,
            &boat
        };

        // 7. Dispatch missions
        DispatchManager manager;

        cout << "\n========== PRIORITY DISPATCH ==========\n";

        int vehicleIndex = 0;

        while (!queue.isEmpty()) {
            Mission mission = queue.dispatchNext();

            ReliefVehicle* assignedVehicle =
                fleet[vehicleIndex % fleet.size()];

            bool result = manager.executeMission(
                mission, depot, *assignedVehicle
            );

            if (result) {
                vehicleIndex++;
            }
        }

        // Save updated inventory after dispatch

        vector<ReliefCargo> updatedInventory = {
            depot.getCargo("Medicine Kits"),
            depot.getCargo("Ration Kits"),
            depot.getCargo("Water Tanks"),
            depot.getCargo("Blankets")
        };

        ReliefOps::Core::FileManager::saveInventory(
            updatedInventory
        );

        cout << "\nUpdated inventory saved successfully!\n";


        // 8. Final inventory report
        cout << "\n========== FINAL INVENTORY ==========\n";
        depot.displayInventory();

        cout << "\nTotal Dispatched Tonnage: "
             << DistributionDepot::getTotalDispatchedTonnage()
             << " tonnes\n";

        cout << "\nERL-HUB integration successful!\n";

    }
    
    catch (const ReliefOps::Core::FileException& e) {

        cout << "\nFILE SYSTEM ERROR: "
             << e.what() << "\n";

    }
    catch (const ReliefOps::Core::InventoryException& e) {

        cout << "\nINVENTORY ERROR: "
             << e.what() << "\n";

    }
    catch (const ReliefOps::Core::MissionException& e) {

        cout << "\nMISSION ERROR: "
             << e.what() << "\n";

    }
    catch (const ReliefOps::Core::VehicleException& e) {

        cout << "\nVEHICLE ERROR: "
             << e.what() << "\n";

    }
    
    catch (const ReliefOps::Core::FileException& e) {
        cout << "\nFILE ERROR: " << e.what() << "\n";
    }
    catch (const ReliefOps::Core::InventoryException& e) {
        cout << "\nINVENTORY ERROR: " << e.what() << "\n";
    }
    catch (const ReliefOps::Core::MissionException& e) {
        cout << "\nMISSION ERROR: " << e.what() << "\n";
    }
    catch (const ReliefOps::Core::VehicleException& e) {
        cout << "\nVEHICLE ERROR: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "\nSYSTEM ERROR: " << e.what() << "\n";
    }



    return 0;
}