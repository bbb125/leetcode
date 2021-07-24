add_executable(multiply-strings
        main.cpp)
target_link_libraries(multiply-strings
        PRIVATE
        GTest::gtest GTest::Main)