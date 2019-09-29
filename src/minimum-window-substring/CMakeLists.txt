add_executable(main
    main.cpp
    minWindowSubstr.hpp
)

if(BUILD_TESTING)
    add_executable(minWindowSubstrTests
        tests.cpp
        minWindowSubstr.hpp
    )
    target_link_libraries(minWindowSubstrTests
        PRIVATE
            gtest # what's the proper order for linking?
            gtest_main #gmock_main
            Threads::Threads
    )

    add_test( #TODO gtest module's add_test
        NAME MinWindowSubstrTests
        COMMAND minWindowSubstrTests
    )
endif()
