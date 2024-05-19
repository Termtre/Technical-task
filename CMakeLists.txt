cmake_minimum_required(VERSION 3.2)
project(Tecnical-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB hdrs "*.h*" "include/*.h")
file(GLOB srcs "*.cpp" "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../testExample)

add_executable(task sample/main.cpp ${srcs} ${hdrs})

