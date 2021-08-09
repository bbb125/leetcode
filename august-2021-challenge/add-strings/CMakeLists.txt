add_executable(add-strings
    main.cpp)
target_link_libraries(add-strings
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)