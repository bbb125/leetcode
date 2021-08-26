add_executable(verify-preordered-serialization-of-binary-tree
    main.cpp)
target_link_libraries(verify-preordered-serialization-of-binary-tree
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)