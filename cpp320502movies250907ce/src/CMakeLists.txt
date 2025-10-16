cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/common.h
               ${INCLUDE_DIR}/movie.h movie.cpp 
               ${INCLUDE_DIR}/movies.h movies.cpp
               )

set_target_properties(
                ${PROJECT_NAME} PROPERTIES
                CXX_STANDART 17
                CXX_STANDART_REQUIRED ON
)              

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
