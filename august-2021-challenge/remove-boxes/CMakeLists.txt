add_executable(remove-boxes
    main.cpp)
target_link_libraries(remove-boxes
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)