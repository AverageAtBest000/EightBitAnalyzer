cmake_minimum_required(VERSION 3.13)

# Let clangd use the same Pico SDK headers, defines, and target as the build.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)
project(logic_analyzer C CXX ASM)
pico_sdk_init()

add_executable(logic_analyzer blink.cpp)
target_link_libraries(logic_analyzer pico_stdlib)

pico_enable_stdio_usb(logic_analyzer 1)
pico_enable_stdio_uart(logic_analyzer 0)
pico_add_extra_outputs(logic_analyzer)
