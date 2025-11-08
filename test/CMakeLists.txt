# Collect all .c, .cpp, .h, .tpp files from src/ & include/
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp *.c *.tpp)

# Create the executable
add_executable(ogga_tests ${TEST_SOURCES})
target_link_libraries(ogga_tests PRIVATE ogga)
target_compile_definitions(ogga_tests PRIVATE OGGA_DEV=1)