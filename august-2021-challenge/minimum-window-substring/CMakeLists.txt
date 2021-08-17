add_executable(minimum-window-substring
    main.cpp)
target_link_libraries(minimum-window-substring
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)