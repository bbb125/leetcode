add_executable(three-equal-parts
        main.cpp)
    target_link_libraries(three-equal-parts
            PRIVATE
                GTest::gtest GTest::Main)