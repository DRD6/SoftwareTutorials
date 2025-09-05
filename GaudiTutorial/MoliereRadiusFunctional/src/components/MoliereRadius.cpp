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

struct MoliereRadius final  
    : k4FWCore::Consumer<
        void (
            const edm4hep::SimCalorimeterHitCollection&,
            const std::vector<const podio::UserDataCollection<double>*>&,
            const podio::UserDataCollection<double>&
        )
    > {

public:
    // Constructor
    MoliereRadius(const std::string& name, ISvcLocator* svcLoc)
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

        // Access the UserDataCollection
        double barycentre_x = InputBarycenter[0]->at(0);
        double barycentre_y = InputBarycenter[1]->at(0);
        double barycentre_z = InputBarycenter[2]->at(0);
        double totalEnergy = InputTotalEnergy.at(0);

        // Calculate the Moliere radius from the simhits
        double moliere_radius = 0.0;

        for (const auto& simhit: InputCaloSimHitCollection) {

        }

        info() << "---> Calculated Moliere radius: " << moliere_radius << endmsg;
        
    }
};

DECLARE_COMPONENT(MoliereRadius)
