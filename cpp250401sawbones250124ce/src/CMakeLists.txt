cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp double_input.cpp ${INCLUDE_DIR}/double_input.h operations.cpp 
               ${INCLUDE_DIR}/operations.h coordinate.cpp ${INCLUDE_DIR}/coordinate.h )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})