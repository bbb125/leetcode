add_executable(01-matrix
    main.cpp)
target_link_libraries(01-matrix
    PRIVATE
        GTest::gtest GTest::Main)