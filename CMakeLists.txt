cmake_minimum_required(VERSION 3.15)
project(SortsAnalyzer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3")

add_subdirectory(GUI/constants)
add_subdirectory(GUI/controls)
add_subdirectory(GUI/custom_controls)
add_subdirectory(GUI/events)
add_subdirectory(GUI/plot)
add_subdirectory(GUI/clickable)
add_subdirectory(benchmark/benchmark)
add_subdirectory(benchmark/sorts)

add_executable(Main main.cpp)

target_include_directories(Main 
                          PUBLIC "${PROJECT_BINARY_DIR}"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/controls"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/constants"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/events"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/plot"
                          PUBLIC "${PROJECT_SOURCE_DIR}/benchmark/sorts"
                          PUBLIC "${PROJECT_SOURCE_DIR}/benchmark/benchmark"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/custom_controls"
                          PUBLIC "${PROJECT_SOURCE_DIR}/GUI/clickable")


#look for SFML and add it
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_package (SFML REQUIRED system window graphics network audio)


#we add the executable of the program
target_link_libraries(Main PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio Benchmark Sorts Controls CustomControls Constants Events Plot Clickable)
