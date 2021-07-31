add_executable(trapping-rain-water
    main.cpp)
target_link_libraries(trapping-rain-water
    PRIVATE
        GTest::gtest GTest::Main)