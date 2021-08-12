add_executable(array-of-doubled-pairs
    main.cpp)
target_link_libraries(array-of-doubled-pairs
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)