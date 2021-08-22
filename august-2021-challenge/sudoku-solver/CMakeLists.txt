add_executable(sudoku-solver
    main.cpp)
target_link_libraries(sudoku-solver
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)