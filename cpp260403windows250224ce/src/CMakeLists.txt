cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               monitor.cpp ${INCLUDE_DIR}/monitor.h
               window.cpp ${INCLUDE_DIR}/window.h               
               cci.cpp ${INCLUDE_DIR}/cci.h               
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

