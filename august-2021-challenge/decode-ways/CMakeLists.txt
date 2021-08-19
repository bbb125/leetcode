add_executable(decode-ways
    main.cpp)
target_link_libraries(decode-ways
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)