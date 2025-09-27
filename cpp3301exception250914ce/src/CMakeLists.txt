cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/common.h
               ${INCLUDE_DIR}/basket.h basket.cpp 
               ${INCLUDE_DIR}/store.h store.cpp
               ${INCLUDE_DIR}/loclib.h loclib.cpp
               )

set_target_properties(
                ${PROJECT_NAME} PROPERTIES
                CXX_STANDART 23
                CXX_STANDART_REQUIRED ON
)              

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
