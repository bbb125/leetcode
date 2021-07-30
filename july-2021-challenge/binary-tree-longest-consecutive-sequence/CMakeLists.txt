add_executable(binary-tree-longest-consecutive-sequence
        main.cpp)
target_link_libraries(binary-tree-longest-consecutive-sequence
        PRIVATE
        GTest::gtest GTest::Main)