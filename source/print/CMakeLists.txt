cmake_minimum_required(VERSION 3.27)
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJ_NAME} LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all .c, .cpp, .h, .tpp files from src/ & include/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.c src/*.tpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.cpp include/*.c include/*.tpp include/*.hpp include/*.h)

# Define executable path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Create the executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} PRIVATE ${HEADERS})

# Include headers from include/
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)


if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 wsock32)
elseif (UNIX)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# Set C++ standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)