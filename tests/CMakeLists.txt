cmake_minimum_required(VERSION 3.16)
add_executable(Test mainTest.cpp WonderfulTrianglePoints.cpp)

target_link_libraries(Test
    PUBLIC
    tcpstream
    GTest::gtest_main
    GTest::gtest
    GTest::gmock         
)

add_test(NAME Test COMMAND Test)

