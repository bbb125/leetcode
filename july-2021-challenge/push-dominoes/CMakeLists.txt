add_executable(push-dominoes
        main.cpp)
target_link_libraries(push-dominoes
        PRIVATE
        GTest::gtest GTest::Main)