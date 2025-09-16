cmake_minimum_required(VERSION 4.0)
project(oW)

set(CMAKE_CXX_STANDARD 20)

add_executable(oW main.cpp
        includes/sceneHandler.h
        src/sceneHandler.cpp
        includes/UIelements/UIelement.h
        includes/openWindow.h
        includes/eventListener.h
        src/eventListener.cpp)

target_link_libraries(oW PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
)