cmake_minimum_required(VERSION 3.17)

project(QtDesigner VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Включаем автоматическую обработку файлов Qt (MOC, UIC, RCC)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь, чтобы CMake мог найти заголовочные файлы
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
#add_subdirectory(src)

# Находим пакет Qt 5 с нужными компонентами (например, Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets WaylandClient)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}
                main.cpp
                )

# Связываем исполняемый файл с модулями Qt 5
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::WaylandClient
)

# Определяем макрос PROJECT_ROOT, передавая в него путь к исходникам проекта.
# CMake_SOURCE_DIR будет заменен на абсолютный путь при конфигурировании проекта.
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

#install(TARGETS ${PROJECT_NAME}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
