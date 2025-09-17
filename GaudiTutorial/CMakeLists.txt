#[[
Copyright (c) 2020-2024 Key4hep-Project.

This file is part of Key4hep.
See https://key4hep.github.io/key4hep-doc/ for further info.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
]]
add_subdirectory(EventStats)
add_subdirectory(MoliereRadiusFunctional)
add_subdirectory(RandomNoiseDigitizer)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory
    ${PROJECT_SOURCE_DIR}/GaudiTutorial/data)

set(SIM_FILE ${PROJECT_SOURCE_DIR}/GaudiTutorial/data/simpleCalo_simulation.root)

if(NOT EXISTS ${SIM_FILE})
    message(STATUS "Downloading simpleCalo_simulation.root ...")
    execute_process(
        COMMAND wget -O ${SIM_FILE} https://fccsw.web.cern.ch/fccsw/tutorials/DRD6_2025_Ancona/simpleCalo_simulation.root
    )
else()
    message(STATUS "File already exists: ${SIM_FILE}, skipping download.")
endif()
