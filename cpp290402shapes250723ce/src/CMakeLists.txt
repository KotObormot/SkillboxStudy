cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/common.h
               ${INCLUDE_DIR}/shape.h shape.cpp 
               ${INCLUDE_DIR}/trianlge.h trianlge.cpp
               ${INCLUDE_DIR}/circle.h circle.cpp
#               ${INCLUDE_DIR}/square.h square.cpp
               ${INCLUDE_DIR}/rectangle.h rectangle.cpp
               ${INCLUDE_DIR}/loclib.h loclib.cpp
               )

set_target_properties(
                ${PROJECT_NAME} PROPERTIES
                CXX_STANDART 17
                CXX_STANDART_REQUIRED ON
)              

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
