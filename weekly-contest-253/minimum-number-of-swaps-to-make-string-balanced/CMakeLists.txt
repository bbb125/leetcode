add_executable(minimum-number-of-swaps-to-make-string-balanced
        main.cpp)
target_link_libraries(minimum-number-of-swaps-to-make-string-balanced
        PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)