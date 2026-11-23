
#ifndef PRIORITY_DISPATCH_QUEUE_H
#define PRIORITY_DISPATCH_QUEUE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "Mission.h"

namespace ReliefOps {
namespace Logistics {

// Custom Functor for priority comparison
struct MissionPriorityCompare {

    bool operator()(const Mission& a, const Mission& b) const {

        if (a.getPriority() != b.getPriority()) {
            return a.getPriority() < b.getPriority();
        }

        // If priorities are equal, smaller ID comes first
        return a.getMissionId() < b.getMissionId();
    }
};

// Generic Template Class
template <typename T>
class PriorityDispatchQueue {

private:
    std::vector<T> missions;

public:

    // Add mission to queue
    void enqueue(const T& mission) {

        missions.push_back(mission);

        std::cout << "Mission "
                  << mission.getMissionId()
                  << " added successfully.\n";
    }

    // Check whether queue is empty
    bool isEmpty() const {
        return missions.empty();
    }

    // Return queue size
    std::size_t size() const {
        return missions.size();
    }

    // Sort missions according to priority
    void sortMissions() {

        std::sort(
            missions.begin(),
            missions.end(),
            MissionPriorityCompare()
        );
    }

    // Display all missions
    void displayQueue() const {

        std::cout << "\n========== MISSION QUEUE ==========\n";

        std::for_each(
            missions.begin(),
            missions.end(),
            [](const T& mission) {
                mission.displayMission();
                std::cout << "-----------------------------------\n";
            }
        );
    }

    // Dispatch highest priority mission
    T dispatchNext() {

        if (isEmpty()) {
            throw std::underflow_error("Mission queue is empty!");
        }

        sortMissions();

        T nextMission = missions.front();

        missions.erase(missions.begin());

        return nextMission;
    }

    // Dispatch all missions
    void dispatchAll() {

        sortMissions();

        std::cout << "\n========== DISPATCH REPORT ==========\n";

        while (!missions.empty()) {

            T mission = dispatchNext();

            std::cout << "\nDispatching Mission ID: "
                      << mission.getMissionId();

            std::cout << "\nMission Type: "
                      << mission.getMissionType();

            std::cout << "\nDestination: "
                      << mission.getDestination();

            std::cout << "\nPriority: "
                      << mission.getPriority();

            std::cout << "\nMission dispatched successfully!\n";

            std::cout << "-----------------------------------\n";
        }
    }
};

}
}

#endif
