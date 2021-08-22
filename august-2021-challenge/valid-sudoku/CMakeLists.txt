add_executable(valid-sudoku
    main.cpp)
target_link_libraries(valid-sudoku
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)