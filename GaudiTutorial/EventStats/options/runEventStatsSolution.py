from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc, AuditorSvc, ChronoAuditor

io_svc = IOSvc("IOSvc")
io_svc.Input = "../../data/simpleCalo_simulation.root"
io_svc.Output = "../../data/simpleCalo_eventStats.root"

chra = ChronoAuditor()
audsvc = AuditorSvc()
audsvc.Auditors = [chra]

from Configurables import EventStats

eventStats_functional = EventStats("EventStats",
    InputCaloHitCollection = ["simplecaloRO"],
    OutputEnergyBarycentre = ["EnergyBarycentreX", "EnergyBarycentreY", "EnergyBarycentreZ"],
    OutputTotalEnergy = ["TotalEnergy"],
    SaveHistograms = True,
    OutputLevel = INFO
)

app_mgr = ApplicationMgr(
    TopAlg = [eventStats_functional],
    EvtSel = 'NONE',
    EvtMax = -1,
    ExtSvc = [EventDataSvc("EventDataSvc"), audsvc],
    StopOnSignal = True,
)
