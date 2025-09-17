# Create a Python script to run the EventStats algorithm
# This script sets up the necessary services and configurations for the EventStats algorithm

# How to write the script:
# 1. Import necessary modules (e.g. services, gaudi functional, application manager)
# 2. Setup the input and output services (IOSvc)
# 3. Setup external services (e.g. ChronoAuditor, AuditorSvc)
# 4. Configure the EventStats algorithm with the required parameters
# 5. Create the Application Manager and set the top algorithms

from Gaudi.Configuration import INFO
from k4FWCore import IOSvc, ApplicationMgr
from Configurables import EventDataSvc, ChronoAuditor, AuditorSvc

io_svc = IOSvc("IOServices")

# It is possible to set the input and output files directly in the script:
io_svc.Input =  # TODO: Specify the input file path
io_svc.Output = # TODO: Specify the output file path (tip: save it in the same folder as the input file with a different name)

# But Gaudi properties can also be set via command line arguments
# Example: k4run runEventStats.py --IOServices.Input "input.root" --IOServices.Output "output.root"

chra = ChronoAuditor()
audsvc = AuditorSvc()
audsvc.Auditors = [chra]

from Configurables import EventStats

# ==========================================
# Exercise: Configure the EventStats Module
# ==========================================

# Task:
# Complete the EventStats configuration by filling in the missing input and output collections.

# Exercise:
# 1. Fill in the missing values (??????)

eventStats_functional = EventStats(
    "EventStats",
    InputCaloHitCollection = [??????],       # TODO: Specify the name of the input calorimeter hit collection
    OutputEnergyBarycentre = ["EnergyBarycentreX", "EnergyBarycentreY", "EnergyBarycentreZ"],
    ?????? = [??????],                       # TODO: Add the output collection for total energy
    ?????? = ??????,                         # TODO: Add the gaudi property to save histograms
    OutputLevel = INFO
)

# ==========================================
# Exercise: Configure the ApplicationMgr
# ==========================================

# Task:
# Add EventStats to the pipeline

# Exercise:
# 1. Fill in the missing values (??????)

app_mgr = ApplicationMgr(
    TopAlg = [??????],
    EvtSel = 'NONE',
    EvtMax = -1,
    ExtSvc = [EventDataSvc("EventDataSvc"), audsvc],
    StopOnSignal = True,
)
