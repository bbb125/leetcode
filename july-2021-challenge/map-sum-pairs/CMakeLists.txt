add_executable(map-sum-pairs
    main.cpp)
target_link_libraries(map-sum-pairs
    PRIVATE
        GTest::gtest GTest::Main)