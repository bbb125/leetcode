add_executable(remove-stones-to-minimize-total
        main.cpp)
target_link_libraries(remove-stones-to-minimize-total
        PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)