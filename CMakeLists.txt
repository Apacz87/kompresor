cmake_minimum_required(VERSION 3.1...3.28)

project(
	kompresor
	VERSION 0.1
	LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

file(GLOB SOURCES "src/*.cpp")

add_executable(exec ${SOURCES})

add_custom_target(clang-format
	COMMAND clang-format -style=file -i ${SOURCES}
	COMMENT "Formatting code with Clang-Format"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	USES_TERMINAL
)

add_custom_target(clang-format-check
	COMMAND clang-format -style=file --dry-run --Werror ${SOURCES}
	COMMENT "Checking code with Clang-Format"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	USES_TERMINAL
)

