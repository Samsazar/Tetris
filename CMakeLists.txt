cmake_minimum_required(VERSION 3.17)
project(.)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(. main.cpp)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

target_link_libraries(. sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)