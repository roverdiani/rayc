cmake_minimum_required(VERSION 3.20)
project(rayc)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "D:\\C\\SFML\\SFML-2.5.1\\lib\\cmake\\SFML")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(rayc main.cpp Raycaster.cpp Raycaster.h Map.cpp Map.h Player.cpp Player.h Utils.cpp Utils.h Ray.cpp Ray.h Fps.cpp Fps.h)
target_link_libraries(rayc sfml-graphics)
