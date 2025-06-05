cmake_minimum_required(VERSION 3.31)
project(charge_system)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.h)

set(CMAKE_CXX_STANDARD 20)

add_executable(charge_system ${SOURCE_FILES}
        src/entity/Vehicle.cpp
        include/entity/Vehicle.h
        src/entity/ChargingPile.cpp
        include/entity/ChargingPile.h)

target_include_directories(charge_system PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(charge_system PRIVATE)
