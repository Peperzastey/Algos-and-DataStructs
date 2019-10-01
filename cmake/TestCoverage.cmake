#TODO
# find_program lcov, genhtml, (gcov)

#TODO
# https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-coverage-step

#string(JOIN " " COVERAGE_EXCLUDE "\"/usr/*\"" "\"*test*.cpp\"") #since CMake version 3.12
#set(COVERAGE_EXCLUDE "\"/usr/*\" \"*test*.cpp\"") #the space is escaped (when is sh), I don't know why
# must be specified as a single string to not cause inserting of ';' between list elements
# quotes must be escaped to survive into lcov call by sh

# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
add_custom_target(coverage
    # clean after previous coverage
    COMMAND lcov --zerocounters --directory . --quiet
    # Run tests
    #COMMAND ${Coverage_EXECUTABLE} ${Coverage_EXECUTABLE_ARGS}
    COMMAND ctest --output-on-failure    
    # Capturing lcov counters and generating report
    #COMMAND ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_PATH} --directory . --capture --output-file coverage.info
    COMMAND lcov --capture --directory . --base-directory . --rc lcov_branch_coverage=1 --output-file coverage.info.total --quiet
    #TODO add --quiet
    #TODO add explicit --gcov-tool ${GCOV}
    #TODO lcovrc config file instead of --rc
    #--directory ${CMAKE_BINARY_DIR} / CURRENT
    COMMAND lcov --remove coverage.info.total "\"/usr/*\"" "\"*test*.cpp\"" --rc lcov_branch_coverage=1 --output-file coverage.info --quiet #TODO ${COVERAGE_EXCLUDE}
    #TODO COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_PATH} --remove ${Coverage_NAME}.total ${COVERAGE_LCOV_EXCLUDES} --output-file ${PROJECT_BINARY_DIR}/${Coverage_NAME}.info.cleaned
    
    #COMMAND ${GENHTML_PATH} ${Coverage_GENHTML_ARGS} -o ${Coverage_NAME} ${PROJECT_BINARY_DIR}/${Coverage_NAME}.info.cleaned
    COMMAND genhtml --legend --branch-coverage --rc lcov_branch_coverage=1 coverage.info --output-directory coverage-html --quiet
    #TODO --demangle-cpp <-- TODO find_program(c++filt) (required for this option)

    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    #DEPENDS ${Coverage_DEPENDENCIES} #TODO tests targets (for ctest)
    COMMENT "Processing test coverage and generating report"
)
