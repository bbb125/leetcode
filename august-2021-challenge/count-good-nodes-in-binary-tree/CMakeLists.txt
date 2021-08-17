add_executable(count-good-nodes-in-binary-tree
    main.cpp)
target_link_libraries(count-good-nodes-in-binary-tree
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)