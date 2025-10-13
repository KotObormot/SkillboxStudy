cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/swimmer.h swimmer.cpp 
#               ${INCLUDE_DIR}/forest.h forest.cpp 
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})