cmake_minimum_required(VERSION 3.17)
project(enterprise VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/enterprise.pb.cc)

target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${Protobuf_INCLUDE_DIRS} include)

