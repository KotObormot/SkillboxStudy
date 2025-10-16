cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/common.h
               ${INCLUDE_DIR}/dog.h dog.cpp 
               ${INCLUDE_DIR}/talent.h talent.cpp
               ${INCLUDE_DIR}/loclib.h loclib.cpp
               )

set_target_properties(
                ${PROJECT_NAME} PROPERTIES
                CXX_STANDART 17
                CXX_STANDART_REQUIRED ON
)              

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
