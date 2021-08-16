add_executable(5843-number-of-strings
    main.cpp)
target_link_libraries(5843-number-of-strings
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)