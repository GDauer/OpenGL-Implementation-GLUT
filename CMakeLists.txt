cmake_minimum_required(VERSION 3.16)
project(openGL)

set(CMAKE_CXX_STANDARD 17)
set(OpenGlLinkers -lncurses -lSDL2 -lglut -lGLU -lGL -lglfw -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11)

add_executable(openGL main.cpp)

target_link_libraries(openGL ${OpenGlLinkers})