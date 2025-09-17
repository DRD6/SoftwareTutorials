from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc, AuditorSvc, ChronoAuditor

io_svc = IOSvc("IOSvc")
## For maintenance purposes, this version of the steering file
# does not initialize the input/output file within the Python script.
# Instead, it expects the input file to be provided as a command-line argument.
# Example:
#   k4run runEventStatsSolution.py --IOSvc.Input "../../data/simpleCalo_simulation.root" --IOSvc.Output "../../data/simpleCalo_eventStats.root"

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
