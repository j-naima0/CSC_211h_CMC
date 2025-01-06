# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/College_Mental_Health__autogen.dir/AutogenUsed.txt"
  "CMakeFiles/College_Mental_Health__autogen.dir/ParseCache.txt"
  "College_Mental_Health__autogen"
  )
endif()
