cmake_minimum_required(VERSION 3.10)  # CMake version check
project(File_Protector)               # Create project "File_Protector"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_CXX_FLAGS_RELEASE "-O0")    # Sets Optimization
set(SOURCE_FILES main.cpp uint_bit_types.h calculations.h helper_functions.h helper_functions.cpp)

#

add_compile_options(-pthread -lbenchmark -isystem vendor/google/benchmark/include -Lbenchmark/build/src)

include(GoogleTest)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(vendor/google/benchmark)

find_package(Boost 1.36.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(File_Protector ${SOURCE_FILES})
endif()

target_link_libraries("${PROJECT_NAME}" benchmark)