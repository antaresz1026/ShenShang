# tests/CMakeLists.txt

file(GLOB TEST_SOURCES *.cpp)
add_executable(ShenShang_TEST ${TEST_SOURCES})

# GoogleTest assumed to be added via FetchContent or submodule
# Example: FetchContent_MakeAvailable(gtest)
find_package(GTest REQUIRED)

target_link_libraries(ShenShang_TEST PRIVATE GTest::gtest_main)
add_test(NAME AllTests COMMAND ShenShang_TEST)
