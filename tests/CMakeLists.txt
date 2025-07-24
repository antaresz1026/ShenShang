add_executable(GoogleTestTest test_test.cpp)
target_link_libraries(GoogleTestTest PRIVATE GTest::gtest_main)
add_test(NAME GoogleTestTest COMMAND GoogleTestTest)

add_executable(ConfigLoaderTest config_loader_test.cpp)
target_link_libraries(ConfigLoaderTest PRIVATE GTest::gtest_main Utils)
add_test(NAME ConfigLoaderTest COMMAND ConfigLoaderTest)

add_executable(LoggerExcetionTest logger_exception_test.cpp)
target_link_libraries(LoggerExcetionTest PRIVATE GTest::gtest_main Utils)
add_test(NAME LoggerExcetionTest COMMAND LoggerExcetionTest)

add_executable(SQLConnectionTest sqlconnection_test.cpp)
target_link_libraries(SQLConnectionTest PRIVATE GTest::gtest_main Basic_layer)
add_test(NAME SQLConnectionTest COMMAND SQLConnectionTest)