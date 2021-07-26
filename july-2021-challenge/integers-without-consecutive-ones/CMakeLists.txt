add_executable(integers-without-consecutive-ones
    main.cpp)
target_link_libraries(integers-without-consecutive-ones
    PRIVATE
        GTest::gtest GTest::Main)