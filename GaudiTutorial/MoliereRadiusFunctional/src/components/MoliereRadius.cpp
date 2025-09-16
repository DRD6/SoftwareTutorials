// Gaudi
#include "Gaudi/Accumulators.h"

// k4FWCore
#include "k4FWCore/Transformer.h"

// podio
#include "podio/UserDataCollection.h"

// edm4hep
#include "edm4hep/CalorimeterHitCollection.h"

// STL
#include <string>
#include <vector>
#include <cmath>

struct MoliereRadius final
    : k4FWCore::MultiTransformer<
          std::tuple<podio::UserDataCollection<double>> 
          ( 
                const edm4hep::CalorimeterHitCollection&,
                const std::vector<const podio::UserDataCollection<double>*>&,
                const podio::UserDataCollection<double>&
          )
    > {

public:
    // Constructor
    MoliereRadius(const std::string& name, ISvcLocator* svcLoc)
        : MultiTransformer(
            name, 
            svcLoc,
            // Input collections for the transformer
            {
                KeyValues("InputCaloHitCollection", {"RndNoiseCaloDigiHits"}),
                KeyValues("InputBarycenter", {"Barycentre"}),
                KeyValues("InputTotalEnergy", {"TotalEnergy"})
            },
            // Output collections for the transformer
            {
                KeyValues("OutputMoliereRadius", {"MoliereRadius"})
            }
        ) { }  


    // Operator: transforms a CalorimeterHitCollection into a tuple of output collections
    std::tuple<podio::UserDataCollection<double>> 
    operator()(const edm4hep::CalorimeterHitCollection& InputCaloHitCollection,
                 const std::vector<const podio::UserDataCollection<double>*>& InputBarycenter,
                 const podio::UserDataCollection<double>& InputTotalEnergy) const override {


        // Define a UserDataCollections for Moliere radius output
        auto MoliereRadiusCollection = podio::UserDataCollection<double>();
        // Variable to hold the calculated Moliere radius
        double moliereRadius = 0.0;

        // Retrieve barycentre and total energy
        double barycentre_x = InputBarycenter[0]->at(0);
        double barycentre_y = InputBarycenter[1]->at(0);
        double totalEnergy = InputTotalEnergy.at(0);


        // Step 1: Calculate radius for each hit and store with energy
        // You can use the HitData struct defined below to store the relevant information
        //
        // Step 2: Sort hits by radius
        //
        // Step 3: Loop over the sorted list, accumulate energy and find radius at 90% of total energy

        
        // How to loop over the input hits:
        for (const auto& hit : InputCaloHitCollection) {
        }

        
        info() << "---> Calculated Moliere radius: " << moliereRadius << " mm" << endmsg;

        // Step 4: Store the result in the output collection and the accumulator
        m_moliere_radius_acc += moliereRadius;
        MoliereRadiusCollection.push_back(moliereRadius);
        return std::make_tuple(std::move(MoliereRadiusCollection));
    }

    // Finalize function to print the final average Moliere radius
    StatusCode finalize() override {

        info() << "Average Moliere radius over all events: " << m_moliere_radius_acc.mean() << " mm" << endmsg;

        return StatusCode::SUCCESS;
    }

private:
    struct HitData {
        double r;      // Radius from barycentre
        double energy; // Energy of the hit
    };
    
    mutable Gaudi::Accumulators::AveragingCounter<double, Gaudi::Accumulators::atomicity::full> m_moliere_radius_acc;
};

DECLARE_COMPONENT(MoliereRadius)
