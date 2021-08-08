add_executable(find-longest-valid-obstacle-course
    main.cpp)
target_link_libraries(find-longest-valid-obstacle-course
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)