# GaudiTutorials for DRD6

This repository hosts tutorials for using the `Gaudi` software.

## Instructions for building the repository
```bash
# Login to an Alma9 machine with CVMFS mounted, e.g. lxplus
source /cvmfs/sw.hsf.org/key4hep/setup.sh -r 2025-05-29
git clone git@github.com:s6anloes/GaudiTutorials.git
cd GaudiTutorials
k4_local_repo # To ensure the system can locate the DD4hep detector builders:
mkdir build install
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install 
make install -j 8
cd ..
