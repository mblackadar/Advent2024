# CMakeList.txt : CMake project for Advent2024, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Advent2024")

# Add source to this project's executable.
add_executable (Advent2024 "source/Advent2024.cpp" "source/Advent2024.h"  "source/day1.cpp" "source/day2.cpp" "source/day3.cpp" "source/day4.cpp"  "source/Grid.h" "source/day5.cpp" "source/day6.cpp" "source/day7.cpp" "source/day8.cpp" "source/day9.cpp" "source/day10.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Advent2024 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
