cmake_minimum_required(VERSION 3.20)
project(shortest_path)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)

find_package(Catch2 CONFIG REQUIRED)

if(${benchmark_FOUND})
	message(STATUS "Found benchmark.")
else(${benchmark_FOUND})
	message(STATUS "Could not locate benchmark.")
endif (${benchmark_FOUND})

if(${Catch2_FOUND})
	message(STATUS "Found Catch2.")
	find_path(CATCH_INCLUDE_DIR NAMES catch.hpp PATH_SUFFIXES catch2)
	include_directories(${CATCH_INCLUDE_DIR})
else(${Catch2_FOUND})
	message(STATUS "Could not locate Catch2.")
endif (${Catch2_FOUND})

include_directories(include)
include_directories(src)

if(UNIX AND STRICT)
	message("-- Enabling strict compilation mode")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

add_executable(benchmarks 
	benchmark/benchmarks.cpp
	include/shortest_path.hpp src/shortest_path.cpp
)
	
add_executable(test_shortest_path
	test/test_shortest_path.cpp
	include/shortest_path.hpp src/shortest_path.cpp
	${CATCH_INCLUDE_DIR}
)

add_executable(main
	src/main.cpp
	include/shortest_path.hpp src/shortest_path.cpp
)

target_link_libraries(benchmarks benchmark::benchmark benchmark::benchmark_main)
	
enable_testing()
add_test(test_shortest_path test_shortest_path)

if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND COVERAGE)
	message("Enabling Test Coverage")
	SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

	set_target_properties(test_shortest_path PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
	target_link_libraries(test_shortest_path gcov)
	add_custom_target(coverage COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/scripts/coverage.sh)
endif()

find_package(Doxygen)
if (${Doxygen_FOUND})
	message(STATUS "Doxygen found.")
else (${Doxygen_FOUND})
	message(STATUS "Doxygen not found.")
endif (${Doxygen_FOUND})