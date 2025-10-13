cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp
               track.cpp ${INCLUDE_DIR}/track.h
               player.cpp ${INCLUDE_DIR}/player.h
               cci.cpp ${INCLUDE_DIR}/cci.h
               )
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
