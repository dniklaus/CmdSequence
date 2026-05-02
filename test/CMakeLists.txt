include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(TEST ${PROJECT})
set(TEST_EXEC ${TEST}_test)

add_executable(${TEST_EXEC}
    test_main.cpp
    TestCmdSeqTimer.cpp
)

target_link_libraries(${TEST_EXEC}
    PRIVATE
        ${PROJECT}
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_EXEC})