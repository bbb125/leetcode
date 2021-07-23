add_executable(alien-dictionary
        main.cpp)
target_link_libraries(alien-dictionary
        PRIVATE
        GTest::gtest GTest::Main)