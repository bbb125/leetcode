add_executable(shuffle-array
        main.cpp)
target_link_libraries(shuffle-array
        PRIVATE
        GTest::gtest GTest::Main)