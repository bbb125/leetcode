add_executable(longest-substring-without-repetition
        main.cpp)
target_link_libraries(longest-substring-without-repetition
        PRIVATE
        GTest::gtest GTest::Main)