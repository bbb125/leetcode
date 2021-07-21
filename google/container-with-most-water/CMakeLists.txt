add_executable(container-with-most-water
        main.cpp)
target_link_libraries(container-with-most-water
        PRIVATE
        GTest::gtest GTest::Main)