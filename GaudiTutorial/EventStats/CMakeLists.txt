file(GLOB _plugin_sources src/components/*.cpp)
gaudi_add_module(EventStatsPlugins
                 SOURCES ${_plugin_sources}
                 LINK Gaudi::GaudiKernel
                      k4FWCore::k4FWCore
                      EDM4HEP::edm4hep
                      )

install(TARGETS EventStatsPlugins
  EXPORT ${CMAKE_PROJECT_NAME}Targets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}"
  COMPONENT dev)

execute_process(COMMAND mkdir ${PROJECT_SOURCE_DIR}/GaudiTutorial/data)
execute_process(COMMAND wget -O ${PROJECT_SOURCE_DIR}/GaudiTutorial/data/simpleCalo_simulation.root https://fccsw.web.cern.ch/fccsw/tutorials/DRD6_2025_Ancona/simpleCalo_simulation.root)
