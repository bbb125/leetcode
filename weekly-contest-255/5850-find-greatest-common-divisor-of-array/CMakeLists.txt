add_executable(5850-find-greatest-common-divisor-of-array
    main.cpp)
target_link_libraries(5850-find-greatest-common-divisor-of-array
    PRIVATE
        GTest::gtest  GTest::gmock GTest::Main)