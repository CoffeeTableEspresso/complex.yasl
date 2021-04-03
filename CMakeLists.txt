cmake_minimum_required(VERSION 3.5.0)
project(complex)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 99)

if (NOT "${CMAKE_C_COMPILER_ID}" MATCHES ".*MSVC.*")
    set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-vla -Wno-logical-op-parentheses -Wno-parentheses")
endif()

include_directories(.)

add_library(complex SHARED
        complex.c)

set_property(TARGET complex PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(complex yaslapi)
