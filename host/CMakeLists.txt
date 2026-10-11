cmake_minimum_required(VERSION 3.13)

project(data_collector LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(data_collector data_collector.cpp reader.cpp writer.cpp )
target_include_directories( data_collector PRIVATE ../include)
