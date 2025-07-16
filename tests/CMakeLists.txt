add_executable(GoogleTestTest test_test.cpp)
target_link_libraries(GoogleTestTest PRIVATE GTest::gtest_main)
add_test(NAME GoogleTestTest COMMAND GoogleTestTest)

add_executable(ConfigLoaderTest config_loader_test.cpp)
target_link_libraries(ConfigLoaderTest PRIVATE GTest::gtest_main Basic_layer)
add_test(NAME ConfigLoaderTest COMMAND ConfigLoaderTest)

add_executable(APIControllerTest apicontroller_test.cpp)
target_link_libraries(APIControllerTest PRIVATE GTest::gtest_main Logic_layer)
add_test(NAME APIControllerTest COMMAND APIControllerTest)

add_executable(LoggerExcetionTest logger_exception_test.cpp)
target_link_libraries(LoggerExcetionTest PRIVATE GTest::gtest_main Basic_layer)
add_test(NAME LoggerExcetionTest COMMAND LoggerExcetionTest)