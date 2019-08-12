# fmdetect - A `constexpr` framework detector #

`fmdetect` is a dead simple and **very** fast way of matching contents of a file to a string, specifically meant for framework detection. It can for example be used to identify usage of a library in a file to set specific options in an editor (example with vim below).

## Installation ##

There are pre built binaries in the `bin` directory. Copy the one built for your OS to where you keep user binaries.

If your OS is not in there, you can easily build it for your platform by following [the build from source section.](#Build-from-source)

## Usage ##

For usage from an editor, please see [vim_examples.md](vim_examples.md).

`fmdetect` is meant to be used from a script but can be used from the command line as well:

```shell
# Found usage of the catch2 test library
$ fmdetect --paths test/testfiles/catch2/010-TestCase.cpp --filetype cpp
catch2

# No output since there is nothing in README.md that matches any of the cpp regex values
$ fmdetect --paths README.md --filetype cpp
```

The general usage can be seen with the `--help` flag.

```shell
$ fmdetect --help
usage:
  fmdetect  options

where options are:
  -?, -h, --help               display usage information
  -f, --filetype <filetype>    What is the current filetype? E.g. cpp
  -p, --paths <paths>          Path(s) to the file(s) being examined. May be
                               multiple separated by a comma (,).
```

## Supported frameworks ##

This section is ordered as

```yaml
- The input of `--filetype`
    - The detected framework and the output on such detection
```

---

```yaml
- cpp
    - [catch2](https://github.com/catchorg/Catch2)
    - [gtest](https://github.com/google/googletest)
    - [benchmark](https://github.com/google/benchmark)
- python
    - [unittest](https://docs.python.org/3/library/unittest.html)
    - [pytest](https://docs.pytest.org/en/latest/)
```

## Build from source ##

### Prerequisites ###

* [`cmake`](https://cmake.org/download/)
* [`conan`](https://docs.conan.io/en/latest/installation.html)
* A recent version of `gcc` or `clang` that support `C++17`

### Building ###

```shell
$ git clone https://github.com/srydell/fmdetect.git && cd fmdetect
$ mkdir build
$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_COMPILER=$(command -v clang++)
$ cmake --build build
$ cp build/bin/fmdetect <wherever you have binaries>
```

## Contributing ##

Pull requests are welcome.

If you would like another framework to be added, you can open an issue with one (or more) of the following:

* A description of how to include the framework. E.g. for `python` with `unittest`: `import unittest`
* A suitable `regex` matching an identifier for that framework. Note that the matching is done line wise.

Please make sure to update tests as appropriate.

## License ##

[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)

**NOTE:** The license excludes the files in `tests/testfiles/*` since they are from third party code.
