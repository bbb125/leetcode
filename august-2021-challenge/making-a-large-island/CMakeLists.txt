add_executable(making-a-large-island
    main.cpp)
target_link_libraries(making-a-large-island
    PRIVATE
        GTest::gtest GTest::Main)