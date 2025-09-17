# GaudiTutorials for DRD6

This repository hosts tutorials for using the *Gaudi* software as part of the larger *key4hep* ecosystem.

It contains hands-on exercises to get familiar with Gaudi steering files and algorithms.
To experiment with the tutorial, you can follow this presentation at the 4th DRD-Calo Collaboration Meeting, which covers the *EventStats*, *RandomNoiseDigitizer*, and *MoliereRadius* exercises.

This README contains a short description for each of the hosted exercises.
The exercises run on data that has been created with with the *simplecalo* calorimeter from the **DD4hepTutorials** exercises.
An example data file will be downloaded automatically when compiling the repository.

## EventStats

The goal of this exercise is to become familiar with the Gaudi steering file. 
For this purpose, an EventStats algorithm is provided, which saves the energy barycentre and total energy for each event using the `podio::UserDataCollection`.

You should adapt the steering file `runEventStats.py` in the `EventStats/options' folder such that this algorithm is executed on the data.
A solution file is provided.

## RandomNoiseDigitizer

The goal of this exercise is to complete a simple digitising algorithm from a skeleton file.

## MoliereRadius

The goal of this exercise is to complete a Gaudi algorithm to compute a physics value from the data, and to revise adding algorithms to the steering file.
