cmake_minimum_required(VERSION 3.17)

project(requests VERSION 1.0)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_CPR_TESTS OFF)

set(CMAKE_USE_OPENSSL OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG bb01c8db702fb41e5497aee9c0559ddf4bf13749)          # from Artyom Lyakhovsky
    #                        GIT_TAG da40186618909b1a7363d4e4495aa899c6e0eb) 
# Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
# namely from here: https://github.com/libcpr/cpr/pull/1154/commits/504779cb9af537c4207c4ee441afffbe9d05d60e
#                          GIT_TAG 504779cb9af537c4207c4ee441afffbe9d05d60e)
FetchContent_MakeAvailable(cpr)

#add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
