# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "debug")
  file(REMOVE_RECURSE
  "debug\\lpi2c_polling_b2b_slave.bin"
  "output.map"
  )
endif()
