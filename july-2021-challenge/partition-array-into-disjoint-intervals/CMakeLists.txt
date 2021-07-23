add_executable(partition-array-into-disjoint-intervals
        main.cpp)
target_link_libraries(partition-array-into-disjoint-intervals
        PRIVATE
        GTest::gtest GTest::Main)