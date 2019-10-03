# Algorithms and Data Structures

## Build instructions

Execute in project's root directory:
```
> mkdir build
> cd build
> cmake ..
> make
```

### Run tests

Execute in build directory:
```
> ctest [options]
```
`options` are optional.  
You can type `-VV` for detailed output -- ctest will then print the output of gtest.  
For more options refer to ctest manual.

You can also run test executables separately by hand.

### Generate docs

Execute in project's root directory:
```
> doxygen docs/Doxyfile 1>/dev/null
```
Generated docs are written to `build/docs` directory.

- HTML output to `html` subdirectory
- Latex output to `latex` subdirectory


### Generate coverage report (HTML)

First you must build the project using `Coverage` build type (configuration):
```
> mkdir build-coverage
> cd build-coverage
> cmake .. -DCMAKE_BUILD_TYPE=Coverage
> make
```
Then execute:
```
> make coverage
```

HTML output is written to `coverage-html` subdirectory of the build directory (in example above: `build-coverage/coverage-html`).

You can now open the index page in your web browser.  
For example, for firefox execute:
```
> firefox coverage-html/index.html
```

## Project dependencies

You will need:
- CMake [version >=3.10]
- C++17 compiler
- Google Test library and headers
- _optional:_ doxygen (for generating docs)
- _optional:_ lcov, genhtml (for measuring coverage and generating report)
