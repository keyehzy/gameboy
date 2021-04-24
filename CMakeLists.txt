cmake_minimum_required(VERSION 3.18)

project(gameboy C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -fcolor-diagnostics")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(src)
add_subdirectory(vendor)

include(CTest)
if (BUILD_TESTING)
  add_subdirectory(test)
endif ()

file(GLOB ROMS roms/*)
