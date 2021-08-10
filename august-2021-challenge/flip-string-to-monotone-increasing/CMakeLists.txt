add_executable(flip-string-to-monotone-increasing
    main.cpp)
target_link_libraries(flip-string-to-monotone-increasing
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)