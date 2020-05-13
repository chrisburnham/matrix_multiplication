
cmake_minimum_required (VERSION 2.8.11)
set(project_name matrix_multiply)

project(${project_name})

set(HEADER_FILES matrix_multiply.h)
set(SOURCES matrix_multiply.cpp main.cpp matrix_multiply.h)

add_executable(${project_name} ${SOURCES})