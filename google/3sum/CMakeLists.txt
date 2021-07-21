add_executable(3sum
        main.cpp)
target_link_libraries(3sum
        PRIVATE
        GTest::gtest GTest::Main)