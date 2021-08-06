add_executable(stone-game
    main.cpp)
target_link_libraries(stone-game
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)