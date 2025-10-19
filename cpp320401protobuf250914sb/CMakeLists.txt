cmake_minimum_required(VERSION 3.10)
project(MyProtoProject)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

# Добавляем исходники
add_executable(my_app src/main.cpp src/enterprise.pb.cc)

# Подключаем библиотеку protobuf
target_link_libraries(my_app ${Protobuf_LIBRARIES})

# Указываем пути к заголовкам
target_include_directories(my_app PUBLIC ${Protobuf_INCLUDE_DIRS} include)

