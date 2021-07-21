add_executable(range-addition
        main.cpp)
target_link_libraries(range-addition
        PRIVATE
        GTest::gtest GTest::Main)