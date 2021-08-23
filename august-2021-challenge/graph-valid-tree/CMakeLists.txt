add_executable(graph-valid-tree
    main.cpp)
target_link_libraries(graph-valid-tree
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)