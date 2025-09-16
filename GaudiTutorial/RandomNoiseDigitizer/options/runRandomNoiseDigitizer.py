from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc, UniqueIDGenSvc

io_svc = IOSvc("IOSvc")
# io_svc.Input = "/afs/cern.ch/work/a/adevita/public/DD4hepTutorials/simplecalo.root"
io_svc.Input = "../../data/simplecalo1_example.root"
io_svc.Output = "output.root"

from Configurables import EventStats

eventStats_functional = EventStats("EventStats",
        
    InputCaloHitCollection=["simplecaloRO"],
    OutputEnergyBarycentre=["EnergyBarycentreX", "EnergyBarycentreY", "EnergyBarycentreZ"],
    OutputTotalEnergy=["TotalEnergy"],
    SaveHistograms=True,
    OutputLevel=INFO
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

app_mgr = ApplicationMgr(
    TopAlg=[eventStats_functional, random_noise_digitizer],
    EvtSel='NONE',
    EvtMax=-1,
    ExtSvc=[EventDataSvc("EventDataSvc"), UniqueIDGenSvc("uidSvc")],
    StopOnSignal=True,
)
