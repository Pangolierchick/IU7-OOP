cmake_minimum_required(VERSION 3.5)

project(lab_02 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR src)
set(MATRIX_DIR ${SOURCE_DIR}/matrix)
set(ITERATOR_DIR ${SOURCE_DIR}/iterator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${MATRIX_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${ITERATOR_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR})

add_definitions(-Wall -Wextra)

find_package(OpenMP REQUIRED)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/main.cpp

    ${MATRIX_DIR}/base_matrix.h
    ${MATRIX_DIR}/matrix_exceptions.h
    ${MATRIX_DIR}/matrix_implementation.hpp
    ${MATRIX_DIR}/matrix.h

    ${ITERATOR_DIR}/const_iterator.h
    ${ITERATOR_DIR}/const_iterator_imp.hpp
    
    ${ITERATOR_DIR}/iterator.h
    ${ITERATOR_DIR}/iterator_imp.hpp
    
    ${ITERATOR_DIR}/iterator_exception.h
)

set_property(SOURCE ${PROJECT_SOURCES} PROPERTY CXX_STANDARD 11)

add_executable(lab_02.out ${PROJECT_SOURCES})

target_link_libraries(lab_02.out PRIVATE OpenMP::OpenMP_CXX)
