
#ifndef DISPATCH_MANAGER_H
#define DISPATCH_MANAGER_H

#include "Mission.h"
#include "DistributionDepot.h"
#include "ReliefVehicle.h"

namespace ReliefOps {
namespace Logistics {

class DispatchManager {
public:
    bool executeMission(
        const Mission& mission,
        Inventory::DistributionDepot& depot,
        ReliefVehicle& vehicle
    ) const;
};

}
}

#endif
