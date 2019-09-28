add_executable(main
    main.cpp
    minWindowSubstr.hpp
)

add_executable(minWindowSubstrTests
    tests.cpp
    minWindowSubstr.hpp
)
target_link_libraries(minWindowSubstrTests
    PRIVATE
        gtest # what's the proper order for linking?
        gtest_main #gmock_main
        pthread
)
