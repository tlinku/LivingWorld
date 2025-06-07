cmake_minimum_required(VERSION 3.16)
project(LivingWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "LivingWorld.cpp")

add_executable(LivingWorld ${SOURCES})

target_include_directories(LivingWorld PRIVATE src)