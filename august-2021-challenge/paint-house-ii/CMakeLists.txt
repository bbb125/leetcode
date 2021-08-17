add_executable(paint-house-ii
    main.cpp)
target_link_libraries(paint-house-ii
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)