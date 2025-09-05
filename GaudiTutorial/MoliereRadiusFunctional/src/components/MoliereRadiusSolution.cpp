// k4FWCore
#include "k4FWCore/Consumer.h"

// podio
#include "podio/UserDataCollection.h"

// edm4hep
#include "edm4hep/SimCalorimeterHitCollection.h"

// STL
#include <string>
#include <vector>
#include <cmath>

struct MoliereRadiusSolution final
    : k4FWCore::Consumer<
        void (
            const edm4hep::SimCalorimeterHitCollection&,
            const std::vector<const podio::UserDataCollection<double>*>&,
            const podio::UserDataCollection<double>&
        )
    > {

public:
    // Constructor
    MoliereRadiusSolution(const std::string& name, ISvcLocator* svcLoc)
        : Consumer(
            name, 
            svcLoc,
            {
                KeyValues("InputCaloHitCollection", {"simplecaloRO"}),
                KeyValues("InputBarycenter", {"Barycenter"}),
                KeyValues("InputTotalEnergy", {"TotalEnergy"})
            }
        ) {}


    void operator()(const edm4hep::SimCalorimeterHitCollection& InputCaloSimHitCollection,
                    const std::vector<const podio::UserDataCollection<double>*>& InputBarycenter,
                    const podio::UserDataCollection<double>& InputTotalEnergy) const override {

        std::vector<HitData> radialHits;

        double barycentre_x = InputBarycenter[0]->at(0);
        double barycentre_y = InputBarycenter[1]->at(0);
        double totalEnergy = InputTotalEnergy.at(0);

        std::cout << "Barycentre: (" << barycentre_x << ", " << barycentre_y << "), Total Energy: " << totalEnergy << std::endl;

        for (const auto& hit : InputCaloSimHitCollection) {
            const auto& pos = hit.getPosition();
            double dx = pos.x - barycentre_x;
            double dy = pos.y - barycentre_y;
            double r = std::sqrt(dx * dx + dy * dy);
            double e = hit.getEnergy();
            radialHits.push_back({r, e});
        }

        // Step 3: Sort hits by radius
        std::sort(radialHits.begin(), radialHits.end(), [](const HitData& a, const HitData& b) {
            return a.r < b.r;
        });

        // Step 4: Accumulate energy and find radius at 90%
        double cumulativeEnergy = 0.0;
        double moliereRadius = 0.0;
        for (const auto& hit : radialHits) {
            cumulativeEnergy += hit.energy;
            if (cumulativeEnergy >= 0.9 * totalEnergy) {
                moliereRadius = hit.r;
                break;
            }
        }

        info() << "Moliere radius = " << moliereRadius << " mm" << endmsg;

        
    }

private:
    struct HitData {
        double r;      // Radius from barycentre
        double energy; // Energy of the hit
    };
};

DECLARE_COMPONENT(MoliereRadiusSolution)
