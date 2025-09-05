from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc

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

from Configurables import MoliereRadiusSolution
moliere_radius = MoliereRadiusSolution  ("MoliereRadius",
                                InputCaloHitCollection=["simplecaloRO"],
                                InputBarycenter=eventStats_functional.OutputEnergyBarycentre,
                                InputTotalEnergy=eventStats_functional.OutputTotalEnergy)

app_mgr = ApplicationMgr(
    TopAlg=[eventStats_functional, moliere_radius],
    EvtSel='NONE',
    EvtMax=-1,
    ExtSvc=[EventDataSvc("EventDataSvc")],
    StopOnSignal=True,
)
