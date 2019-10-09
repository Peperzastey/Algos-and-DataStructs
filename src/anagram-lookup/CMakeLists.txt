#TODO create single executable with all tests
if(BUILD_TESTING)
    add_executable(anagramDictTests
        tests.cpp
        AnagramDict.hpp
    )
    target_link_libraries(anagramDictTests
        PRIVATE
            gtest
            gtest_main
            Threads::Threads
    )

    add_test( #TODO gtest module's add_test
        NAME AnagramDictTests
        COMMAND anagramDictTests
    )
endif()
