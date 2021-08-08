add_executable(check-if-string-is-a-prefix-of-array
        main.cpp)
target_link_libraries(check-if-string-is-a-prefix-of-array
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)