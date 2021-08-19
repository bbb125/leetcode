add_executable(max-product-of-splitted-binary-tree
    main.cpp)
target_link_libraries(max-product-of-splitted-binary-tree
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)