add_executable(palindrome-partitioning-ii
        main.cpp)
target_link_libraries(palindrome-partitioning-ii
        PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)