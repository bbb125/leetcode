add_executable(paint-fence
    main.cpp)
target_link_libraries(paint-fence
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)