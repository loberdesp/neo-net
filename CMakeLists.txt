cmake_minimum_required(VERSION 3.26)
project(neural_net)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/SDL2-2.30.2/x86_64-w64-mingw32")
set(SDL2TTF_PATH "C:/SDL2-2.30.2/x86_64-w64-mingw32")

find_package(
        SDL2 REQUIRED
        SDL2TTF REQUIRED
)


if(SDL2_FOUND)
    message(STATUS "SDL2 found!")
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2TFF_INCLUDE_DIR}
)


add_executable(neural_net main.cpp
        cpp/neuron.cpp
        header/neuron.h
        include.h
        cpp/net.cpp
        header/net.h
        header/display.h
        cpp/display.cpp
)

#THOSE 4 LINES TOOK ME 4 HOURS TO FIND BECAUSE PROGRAM WOULDN'T WORK WITHOUT THEM -lwinmm -limm32 -lsetupapi -lversion

target_link_libraries(neural_net ${SDL2_LIBRARY} ${SDL2TFF_LIBRARY} -lwinmm -limm32 -lsetupapi -lversion)