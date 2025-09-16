// Gaudi
#include "Gaudi/Property.h"
#include <GaudiKernel/SmartIF.h>

// k4FWCore
#include "k4FWCore/Transformer.h"

// k4Interface
#include <k4Interface/IUniqueIDGenSvc.h>

// edm4hep
#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"

// STL
#include <string>
#include <random>

struct RandomNoiseDigitizer final
    : k4FWCore::MultiTransformer<
          std::tuple<edm4hep::CalorimeterHitCollection> 
          ( 
                const edm4hep::SimCalorimeterHitCollection&, 
                const edm4hep::EventHeaderCollection&
          )
    > {

public:
    // Constructor
    RandomNoiseDigitizer(const std::string& name, ISvcLocator* svcLoc)
        : MultiTransformer(
            name, 
            svcLoc,
            // Input collections for the transformer
            {
                KeyValues("InputCaloSimHitCollection", {"simplecaloRO"}),
                KeyValues("HeaderName", {"EventHeader"})
            },
            // Output collections for the transformer
            {
                KeyValues("OutputCaloDigiHitCollection", {"RndNoiseCaloDigiHits"})
            }
        ) { }  

    // Initialize
    StatusCode initialize() override {

        // Retrieve the UniqueIDGenSvc for generating reproducable random seed
        m_uniqueIDSvc = serviceLocator()->service(""); // Replace with the value from the property for the UniqueIDGenSvc name
        if (!m_uniqueIDSvc) {
            error() << "Unable to locate UniqueIDGenSvc with name: " << /* PROPERTY.value() << */ endmsg;
            return StatusCode::FAILURE;
        }


        return StatusCode::SUCCESS;

    }


    // Operator: transforms a SimCalorimeterHitCollection into digitized CalorimeterHitCollection
    std::tuple<edm4hep::CalorimeterHitCollection> 
    operator()(const edm4hep::SimCalorimeterHitCollection& InputCaloSimHitCollection,
               const edm4hep::EventHeaderCollection& header) const override {

        // Define a UserDataCollections for digitized output
        auto CaloDigiHits = edm4hep::CalorimeterHitCollection();

        // Initialise and seed random engine for noise generation
        std::mt19937_64 random_engine;
        auto engine_seed = m_uniqueIDSvc->getUniqueID(header, this->name());
        random_engine.seed(engine_seed);

        // Create the random distributions for smearing the hit energy
        std::normal_distribution<double> gaussian_noise{0.0, 0.0}; // Replace with mean and width from properties


        // Loop over the input hits
        for (const auto& hit : InputCaloSimHitCollection) {
            auto digihit = CaloDigiHits.create();

            double noise = gaussian_noise(random_engine); 

            digihit.setCellID(hit.getCellID());
            // Use the EDM4hep yaml file to get and set the remaining members of CalorimeterHit
        }

        // Store the result in the output collection
        return std::make_tuple(std::move(CaloDigiHits));
    }

private:

    SmartIF<IUniqueIDGenSvc> m_uniqueIDSvc{nullptr};
    // Create a property for the UniqueIDGenSvc name (specified in the steering file)

    // Create two Gaudi::Property members for the noise mean and width

};

DECLARE_COMPONENT(RandomNoiseDigitizer)
