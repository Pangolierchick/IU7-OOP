cmake_minimum_required(VERSION 3.5)

project(lab_04 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR})

add_definitions(-Wall -Wextra)

set(PROJECT_SOURCES
        ${INCLUDE_DIR}/mainwindow.h

        ${INCLUDE_DIR}/lift.h
        ${INCLUDE_DIR}/lift_cabin.h
        ${INCLUDE_DIR}/lift_controller.h
        ${INCLUDE_DIR}/lift_doors.h

        ${SOURCE_DIR}/mainwindow.ui

        ${SOURCE_DIR}/lift.cpp
        ${SOURCE_DIR}/lift_cabin.cpp
        ${SOURCE_DIR}/lift_controller.cpp
        ${SOURCE_DIR}/lift_doors.cpp

        ${SOURCE_DIR}/mainwindow.cpp
        ${SOURCE_DIR}/main.cpp
)

add_executable(main ${PROJECT_SOURCES})

target_link_libraries(main Qt5::Widgets)
