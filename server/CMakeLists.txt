cmake_minimum_required(VERSION 3.31)
project(charge_system)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

set(CMAKE_CXX_STANDARD 20)

add_executable(charge_system ${SOURCE_FILES})

target_include_directories(charge_system PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    # Windows系统需要链接ws2_32库
    target_link_libraries(charge_system ws2_32)
endif ()