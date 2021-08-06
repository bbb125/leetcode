add_executable(n-ary-tree-order-traversal
    main.cpp)
target_link_libraries(n-ary-tree-order-traversal
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)