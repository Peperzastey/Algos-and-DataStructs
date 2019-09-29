#TODO create single executable with all tests
if(BUILD_TESTING)
    add_executable(minGreaterSeqTests
        tests.cpp
        minGreaterSeq.hpp
    )
    target_link_libraries(minGreaterSeqTests
        PRIVATE
            gtest
            gtest_main
            Threads::Threads
    )

    add_test( #TODO gtest module's add_test
        NAME MinGreaterSeqTests
        COMMAND minGreaterSeqTests
    )
endif()
