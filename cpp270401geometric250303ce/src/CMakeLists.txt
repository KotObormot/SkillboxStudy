cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/shape.h shape.cpp 
               ${INCLUDE_DIR}/circle.h circle.cpp
               ${INCLUDE_DIR}/rectangle.h rectangle.cpp
               ${INCLUDE_DIR}/square.h square.cpp
               ${INCLUDE_DIR}/triangle.h triangle.cpp                          
               ${INCLUDE_DIR}/cci.h cci.cpp               
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

