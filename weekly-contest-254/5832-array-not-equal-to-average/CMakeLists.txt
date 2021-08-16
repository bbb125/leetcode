add_executable(5832-array-not-equal-to-average
    main.cpp)
target_link_libraries(5832-array-not-equal-to-average
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)