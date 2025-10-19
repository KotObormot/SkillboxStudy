cmake_minimum_required(VERSION 3.17)

project(nlohmann-json VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

#set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(nlohmann_json)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
