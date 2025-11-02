cmake_minimum_required(VERSION 3.17)

project(cpp340401qt251029sb VERSION 1.0 LANGUAGES CXX)

# Включаем автоматическую обработку файлов Qt (MOC, UIC, RCC)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь, чтобы CMake мог найти заголовочные файлы
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Находим пакет Qt 5 с нужными компонентами (например, Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

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
)

#install(TARGETS ${PROJECT_NAME}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
