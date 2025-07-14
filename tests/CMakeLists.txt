file(GLOB TEST_SOURCES *.cpp)

find_package(GTest REQUIRED)

foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name}
        PRIVATE
        ShenShangCore         # ✅ 这里是关键
        Drogon::Drogon
        GTest::gtest_main
        jsoncpp
        pthread
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()