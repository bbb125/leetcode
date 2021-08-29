add_executable(max-profit-in-job-scheduling
    main.cpp)
target_link_libraries(max-profit-in-job-scheduling
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)