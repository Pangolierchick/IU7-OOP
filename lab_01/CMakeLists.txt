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

add_definitions(-Wall -Wextra -O2 -I ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

set(PROJECT_SOURCES
        ${SOURCE_DIR}/main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${SOURCE_DIR}/edge.cpp
        ${SOURCE_DIR}/dot.cpp
        ${SOURCE_DIR}/model.cpp
        ${INCLUDE_DIR}/edge.hpp
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

)


add_executable(lab_01 ${PROJECT_SOURCES})

target_link_libraries(lab_01 Qt5::Widgets)
