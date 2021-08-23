add_executable(rectangle-area-ii
    main.cpp)
target_link_libraries(rectangle-area-ii
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)