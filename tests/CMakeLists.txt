# 收集除 test_test.cpp 之外的所有测试源文件
file(GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
list(REMOVE_ITEM TEST_SOURCES test_test.cpp)
find_package(GTest REQUIRED)
# 正常注册其他测试
foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name}
        PRIVATE
        ShenShangCore
        Drogon::Drogon
        GTest::gtest_main
        jsoncpp
        pthread
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# ✅ 单独添加 test_test.cpp，只链接 GTest
add_executable(test_test test_test.cpp)
target_link_libraries(test_test PRIVATE GTest::gtest_main)
add_test(NAME test_test COMMAND test_test)
