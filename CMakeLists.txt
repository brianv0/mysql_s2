cmake_minimum_required (VERSION 3.6)
project (MYSQLS2)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory (src)
