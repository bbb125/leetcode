add_executable(two-sum-input-bst
    main.cpp)
target_link_libraries(two-sum-input-bst
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)