## Reddit Code Formatter
Reformats input data so that it's suitable for *Reddit* code formatted posts or comments.

### Usage

Directly from your terminal's STDIN...

    $ reddit-code-formatter <<EOF
    > function print(data) {
    >     console.log(data);
    > }
    > EOF

Contents of a file...

    $ cat ./my-code-file.cpp | reddit-code-formatter

Output to clipboard in Linux (requires `xclip`)...

    $ cat ./my-code-file.cpp | reddit-code-formatter | xclip -selection clipboard

Output to clipboard in MacOS...

    $ cat ./my-code-file.cpp | reddit-code-formatter | pbcopy

### Building
Requirements:
- A C++17 compiler (GCC or Clang)
- [CMake](https://cmake.org/download/) version >= 3.10

Steps:

    $ mkdir build && cd build
    $ cmake ..
    $ cmake --build .

### Installing

    $ cmake --build . --target install

### Running the tests

    $ cmake -DCMAKE_BUILD_TYPE=Debug -DREDDIT_CODE_FORMATTER_ENABLE_TESTS=ON ..
    $ cmake --build . --clean-first
    $ ctest . --output-on-failure
