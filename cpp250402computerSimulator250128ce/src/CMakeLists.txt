cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} main.cpp kbd.cpp ${INCLUDE_DIR}/kbd.h
               ram.cpp ${INCLUDE_DIR}/ram.h
               gpu.cpp ${INCLUDE_DIR}/gpu.h
               cpu.cpp ${INCLUDE_DIR}/cpu.h
               disk.cpp ${INCLUDE_DIR}/disk.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})