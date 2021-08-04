add_executable(subsets-ii
    main.cpp)
target_link_libraries(subsets-ii
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)