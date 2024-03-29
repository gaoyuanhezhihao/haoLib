CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
PROJECT(cpp)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost COMPONENTS filesystem regex)

add_subdirectory(tree_timer)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(runner src/main.cpp)
target_link_libraries(runner ${Boost_LIBRARIES} tree_timer)

add_executable(time_of_file src/time_of_file)
target_link_libraries(time_of_file ${Boost_LIBRARIES} )
