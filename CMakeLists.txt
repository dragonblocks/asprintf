cmake_minimum_required(VERSION 3.14)
project(Asprintf C)

add_compile_options(
	-Wall
	-Wextra
)

add_library(asprintf
	asprintf.c
)

target_include_directories(asprintf
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
