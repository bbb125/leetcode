add_executable(sum-of-square-numbers
    main.cpp)
target_link_libraries(sum-of-square-numbers
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)