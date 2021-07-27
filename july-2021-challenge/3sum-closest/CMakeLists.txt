add_executable(3sum-closest
    main.cpp)
target_link_libraries(3sum-closest
    PRIVATE
        GTest::gtest GTest::Main)