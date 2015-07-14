# Cmake file to build the application

cmake_minimum_required (VERSION 2.6)
project (SuperMarioWorld)

# I guess you have not released the project yet :p
set (SuperMarioWorld_VERSION_MAJOR 0)
set (SuperMarioWorld_VERSION_MINOR 1)
set (SuperMarioWorld_VERSION_PATCH 0)

set (EXECUTABLE_NAME "SuperMarioWorld")

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 ")

file( GLOB_RECURSE SRC_CPP src/*.cpp )
add_executable(${EXECUTABLE_NAME} ${SRC_CPP})

# Install SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
