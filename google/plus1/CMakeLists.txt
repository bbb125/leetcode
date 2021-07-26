add_executable(plus1
    main.cpp)
target_link_libraries(plus1
    PRIVATE
        GTest::gtest GTest::Main)