cmake_minimum_required(VERSION 3.27)
project(ogga LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Define executable path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find threads
find_package(Threads REQUIRED)

# Collect all .c, .cpp, .h, .tpp files from src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.hpp src/*.h src/*.cpp src/*.c src/*.tpp)

add_library(ogga STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ogga PUBLIC Threads::Threads)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp test/*.c test/*.tpp test.cpp)

add_executable(ogga_tests ${TEST_SOURCES})
target_link_libraries(ogga_tests PRIVATE ogga)
target_include_directories(ogga_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

option(OGGA_DEV "Enable development-only tests" OFF)

if (OGGA_DEV)
	message(STATUS "Building with OGGA_DEV enabled")
	target_compile_definitions(ogga_tests PRIVATE OGGA_DEV=1)
else ()
	set_target_properties(ogga_tests PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif ()