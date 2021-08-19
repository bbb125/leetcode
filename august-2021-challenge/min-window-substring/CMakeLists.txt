add_executable(min-window-substring
    main.cpp)
target_link_libraries(min-window-substring
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)