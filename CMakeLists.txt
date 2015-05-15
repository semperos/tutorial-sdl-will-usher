cmake_minimum_required(VERSION 3.2)
project(SdlTutorial)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(SdlTutorial ${SOURCE_FILES} include/res_path.h include/cleanup.h)

include(FindPkgConfig)
pkg_search_module(SDL2 required sdl2)
include_directories(include ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

