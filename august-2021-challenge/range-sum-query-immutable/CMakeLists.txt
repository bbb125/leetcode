add_executable(range-sum-query-immutable
    main.cpp)
target_link_libraries(range-sum-query-immutable
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)