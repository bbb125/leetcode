add_executable(rank-transform-of-matrix
    main.cpp)
target_link_libraries(rank-transform-of-matrix
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)