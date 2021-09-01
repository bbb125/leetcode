add_executable(find-minimum-in-rotated-sorted-array
    main.cpp)
target_link_libraries(find-minimum-in-rotated-sorted-array
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)