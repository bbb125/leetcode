add_executable(group-anagrams
    main.cpp)
target_link_libraries(group-anagrams
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)