
cmake_minimum_required (VERSION 2.8.11)
set(project_name matrix_multiply)
project(${project_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

set(HEADER_FILES matrix_multiply.h)
set(SOURCES matrix_multiply.cpp main.cpp matrix_multiply.h)

add_executable(${project_name} ${SOURCES})

target_link_libraries(${project_name} ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(${project_name} PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(${project_name} PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
