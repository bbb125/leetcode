add_executable(patching-array
    main.cpp)
target_link_libraries(patching-array
    PRIVATE
        GTest::gtest GTest::gmock GTest::Main)