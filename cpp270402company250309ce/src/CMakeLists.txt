cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               ${INCLUDE_DIR}/staff.h staff.cpp
               ${INCLUDE_DIR}/ceo.h ceo.cpp
               ${INCLUDE_DIR}/teamlead.h teamlead.cpp
               ${INCLUDE_DIR}/employee.h employee.cpp 
               ${INCLUDE_DIR}/team.h team.cpp                         
               ${INCLUDE_DIR}/cci.h cci.cpp               
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

