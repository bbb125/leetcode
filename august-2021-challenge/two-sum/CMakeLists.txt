add_executable(two-sum
    main.cpp)
target_link_libraries(two-sum
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)