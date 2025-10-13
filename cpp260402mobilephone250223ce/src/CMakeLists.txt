cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               address.cpp ${INCLUDE_DIR}/address.h
               cci.cpp ${INCLUDE_DIR}/cci.h
               phone.cpp ${INCLUDE_DIR}/phone.h
               timer.cpp ${INCLUDE_DIR}/timer.h
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
