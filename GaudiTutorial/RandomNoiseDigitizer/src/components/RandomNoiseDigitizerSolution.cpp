/*
 * Copyright (c) 2020-2024 Key4hep-Project.
 *
 * This file is part of Key4hep.
 * See https://key4hep.github.io/key4hep-doc/ for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Gaudi
#include "Gaudi/Property.h"
#include <GaudiKernel/SmartIF.h>

// k4FWCore
#include "k4FWCore/Transformer.h"

// k4Interface
#include <k4Interface/IUniqueIDGenSvc.h>

// edm4hep
#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/SimCalorimeterHitCollection.h"

// STL
#include <random>
#include <string>

struct RandomNoiseDigitizerSolution final
    : k4FWCore::MultiTransformer<std::tuple<edm4hep::CalorimeterHitCollection>(
          const edm4hep::SimCalorimeterHitCollection&, const edm4hep::EventHeaderCollection&)> {

public:
  // Constructor
  RandomNoiseDigitizerSolution(const std::string& name, ISvcLocator* svcLoc)
      : MultiTransformer(
            name, svcLoc,
            // Input collections for the transformer
            {KeyValues("InputCaloSimHitCollection", {"simplecaloRO"}), KeyValues("HeaderName", {"EventHeader"})},
            // Output collections for the transformer
            {KeyValues("OutputCaloDigiHitCollection", {"RndNoiseCaloDigiHits"})}) {}

  // Initialize
  StatusCode initialize() override {

    m_uniqueIDSvc = serviceLocator()->service(m_uidSvcName);
    if (!m_uniqueIDSvc) {
      error() << "Unable to locate UniqueIDGenSvc with name: " << m_uidSvcName << endmsg;
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
    std::normal_distribution<double> gaussian_noise{m_noise_mean.value(), m_noise_width.value()};

    // Loop over the input hits
    for (const auto& hit : InputCaloSimHitCollection) {
      auto digihit = CaloDigiHits.create();

      double noise = gaussian_noise(random_engine);

      digihit.setCellID(hit.getCellID());
      digihit.setEnergy(hit.getEnergy() + noise);
      digihit.setEnergyError(m_noise_width);
      digihit.setPosition(hit.getPosition());
    }

    // Store the result in the output collection
    return std::make_tuple(std::move(CaloDigiHits));
  }

private:
  SmartIF<IUniqueIDGenSvc> m_uniqueIDSvc{nullptr};
  Gaudi::Property<std::string> m_uidSvcName{
      this, "uidSvcName", "UniqueIDGenSvc",
      "The name of the service for generating unique, but reproducable random seeds"};

  Gaudi::Property<double> m_noise_mean{this, "NoiseMean", 0.0, "Mean of the Gaussian noise to be added"};
  Gaudi::Property<double> m_noise_width{this, "NoiseWidth", 0.1, "Width of the Gaussian noise to be added"};
};

DECLARE_COMPONENT(RandomNoiseDigitizerSolution)
