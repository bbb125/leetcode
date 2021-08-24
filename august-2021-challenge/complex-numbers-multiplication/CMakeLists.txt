add_executable(complex-numbers-multiplication
    main.cpp)
target_link_libraries(complex-numbers-multiplication
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)