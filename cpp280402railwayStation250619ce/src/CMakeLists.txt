cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/initial_conditions.h
               ${INCLUDE_DIR}/train.h train.cpp 
               ${INCLUDE_DIR}/cci.h cci.cpp
               )

set_target_properties(
                ${PROJECT_NAME} PROPERTIES
                CXX_STANDART 14
                CXX_STANDART_REQUIRED ON
)              

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
