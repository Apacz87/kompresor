cmake_minimum_required(VERSION 3.1...3.28)

project(
	kompresor
	VERSION "0.0.0.2"
	LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# generate version.h replacing all @VARIABLE@ 
configure_file (version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/generated/version.h @ONLY)

include_directories(
	"include/generated"
	"external/clipp/include")

file(GLOB SOURCES "src/*.cpp")

add_executable(exec ${SOURCES})

message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

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

