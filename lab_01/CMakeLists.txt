cmake_minimum_required(VERSION 3.5)

project(lab_01 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(GRAPHICS_DIR graphics)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/${GRAPHICS_DIR})

add_definitions(-Wall -Wextra -O2)

set(PROJECT_SOURCES
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/${GRAPHICS_DIR}/mainwindow.cpp
        ${SOURCE_DIR}/${GRAPHICS_DIR}/mainwindow.h
        ${SOURCE_DIR}/${GRAPHICS_DIR}/mainwindow.ui
        ${SOURCE_DIR}/edge.cpp
        ${SOURCE_DIR}/dot.cpp
        ${SOURCE_DIR}/model.cpp
        ${INCLUDE_DIR}/edge.hpp
        ${INCLUDE_DIR}/error.hpp
        ${SOURCE_DIR}/error.cpp
        ${INCLUDE_DIR}/dot.hpp
        ${INCLUDE_DIR}/model.hpp
        ${INCLUDE_DIR}/main.hpp
        ${INCLUDE_DIR}/dots_arr.hpp
        ${INCLUDE_DIR}/dot_io.hpp
        ${SOURCE_DIR}/dots_arr.cpp
        ${SOURCE_DIR}/dot_io.cpp
        ${SOURCE_DIR}/edges_arr.cpp
        ${INCLUDE_DIR}/edges_arr.hpp
        ${SOURCE_DIR}/edges_io.cpp
        ${INCLUDE_DIR}/edges_io.hpp
        ${SOURCE_DIR}/model_io.cpp
        ${INCLUDE_DIR}/model_io.hpp
        ${SOURCE_DIR}/dots_transform.cpp
        ${INCLUDE_DIR}/dots_transform.hpp
        ${SOURCE_DIR}/model_transform.cpp
        ${INCLUDE_DIR}/model_transform.hpp
        ${SOURCE_DIR}/manager.cpp
        ${INCLUDE_DIR}/manager.hpp
        ${INCLUDE_DIR}/commands.hpp
        ${SOURCE_DIR}/${GRAPHICS_DIR}/draw.cpp
        ${SOURCE_DIR}/${GRAPHICS_DIR}/draw.hpp
        ${INCLUDE_DIR}/logger.h
)

add_executable(lab_01 ${PROJECT_SOURCES})

target_link_libraries(lab_01 Qt5::Widgets)
