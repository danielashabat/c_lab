cmake_minimum_required(VERSION 3.17)
project(ex2)

set(CMAKE_CXX_STANDARD 14)
# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.c analyze_and_print.h analyze_and_print.c line_check.c import_data.c line_check.h import_data.h handle_arguments.c handle_arguments.h IO.c IO.h output.c output.h)
add_executable(ex2  ${SOURCE_FILES})