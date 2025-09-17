from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc, UniqueIDGenSvc, ChronoAuditor, AuditorSvc

chra = ChronoAuditor()
audsvc = AuditorSvc()
audsvc.Auditors = [chra]

io_svc = IOSvc("IOSvc")
io_svc.Input = "../../data/simpleCalo_eventStats.root"
io_svc.Output = "../../data/simpleCalo_moliereRadius.root"

from Configurables import EventStats

eventStats_functional = EventStats("EventStats",
    InputCaloHitCollection = ["simplecaloRO"],
    OutputEnergyBarycentre = ["EnergyBarycentreX", "EnergyBarycentreY", "EnergyBarycentreZ"],
    OutputTotalEnergy = ["TotalEnergy"],
    SaveHistograms = True,
    OutputLevel = INFO
)

from Configurables import RandomNoiseDigitizerSolution
random_noise_digitizer = RandomNoiseDigitizerSolution("RandomNoiseDigitizer",
                                InputCaloSimHitCollection=["simplecaloRO"],
                                OutputCaloDigiHitCollection=["CaloDigiHits"],
                                uidSvcName="uidSvc",
                                NoiseMean=1e-6,
                                NoiseWidth=1e-7,
                                OutputLevel=INFO
                                )

from Configurables import MoliereRadiusSolution
moliere_radius = MoliereRadiusSolution  ("MoliereRadius",
                                InputCaloHitCollection=random_noise_digitizer.OutputCaloDigiHitCollection,
                                InputBarycenter=eventStats_functional.OutputEnergyBarycentre,
                                InputTotalEnergy=eventStats_functional.OutputTotalEnergy)

app_mgr = ApplicationMgr(
    TopAlg=[eventStats_functional, random_noise_digitizer, moliere_radius],
    EvtSel='NONE',
    EvtMax=-1,
    ExtSvc=[EventDataSvc("EventDataSvc"), UniqueIDGenSvc("uidSvc"), audsvc],
    StopOnSignal=True,
)
