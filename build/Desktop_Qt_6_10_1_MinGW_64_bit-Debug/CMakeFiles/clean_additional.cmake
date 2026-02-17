# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\emp_vehic_zones_poubelle_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\emp_vehic_zones_poubelle_autogen.dir\\ParseCache.txt"
  "emp_vehic_zones_poubelle_autogen"
  )
endif()
