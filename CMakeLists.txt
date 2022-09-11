cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(ERBuildOptimizerModule)

include_directories("${CMAKE_SOURCE_DIR}/cpp/include")
include_directories("${CMAKE_SOURCE_DIR}/pybind11")

file (GLOB SOURCE_FILES "cpp/*.cpp")
file (GLOB HEADER_FILES "cpp/include/*.h")

add_subdirectory("pybind11")

#add_subdirectory(pybind11)
pybind11_add_module(ERBuildOptimizerModule
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(ERBuildOptimizerModule PUBLIC)

install(TARGETS ERBuildOptimizerModule
        COMPONENT python
        LIBRARY DESTINATION "/home/tarnished/PycharmProjects/ER-Build-Optimizer/venv/lib/python3.10/site-packages"
)