#TODO
# find_program lcov, genhtml, (gcov)

#TODO
# https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-coverage-step

# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
add_custom_target(coverage
    # Run tests
    #COMMAND ${Coverage_EXECUTABLE} ${Coverage_EXECUTABLE_ARGS}
    COMMAND ctest -VV
    # Capturing lcov counters and generating report
    #COMMAND ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_PATH} --directory . --capture --output-file coverage.info
    COMMAND lcov --capture --directory . --output-file coverage.info --no-external
    #--directory ${CMAKE_BINARY_DIR} / CURRENT
    
    #TODO COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_PATH} --remove ${Coverage_NAME}.total ${COVERAGE_LCOV_EXCLUDES} --output-file ${PROJECT_BINARY_DIR}/${Coverage_NAME}.info.cleaned
    # instead of --no-external + (CMAKE_)RUNTIME_OUTPUT_DIRECTORY
    
    #COMMAND ${GENHTML_PATH} ${Coverage_GENHTML_ARGS} -o ${Coverage_NAME} ${PROJECT_BINARY_DIR}/${Coverage_NAME}.info.cleaned
    COMMAND genhtml coverage.info --output-directory coverage-html

    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    #DEPENDS ${Coverage_DEPENDENCIES} #TODO tests targets (for ctest)
    COMMENT "Processing test coverage and generating report."
)
