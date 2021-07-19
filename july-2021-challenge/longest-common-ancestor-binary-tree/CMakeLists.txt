add_executable(longest-common-ancestor-binary-tree
    main.cpp)
    target_link_libraries(longest-common-ancestor-binary-tree
        PRIVATE
            GTest::gtest GTest::Main)