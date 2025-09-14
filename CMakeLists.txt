cmake_minimum_required(VERSION 4.0.2)

project(LAD_APP)


add_subdirectory(googletest)
enable_testing()


add_executable(
    LAD_APP
    Commands.cpp
    Helpers.cpp
    Interpretator.cpp
    "LAD_AP v.2.0.0.cpp"
    Reciever.cpp
)


add_executable(
    TEST_APP
    tests/test_token_converter.cpp
)

target_link_libraries(
    TEST_APP
    gtest_main
    gmock_main
)

add_test(
    NAME AllTest
    COMMAND TEST_APP
)