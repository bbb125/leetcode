add_executable(equal-tree-partition
    main.cpp)
target_link_libraries(equal-tree-partition
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)