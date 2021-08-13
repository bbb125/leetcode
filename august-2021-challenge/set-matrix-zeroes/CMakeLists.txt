add_executable(set-matrix-zeroes
    main.cpp)
target_link_libraries(set-matrix-zeroes
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)