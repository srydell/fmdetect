# get_special_filetype - A `constexpr` file type matcher #

`get_special_filetype` is a **very** fast way of matching contents of a file to a string. It can for example be used to identify usage of a library in a file to set specific options in an editor (example for vim below).

## Installation ##

There are pre built binaries in the `bin` directory. Copy the one built for your OS to where you keep user binaries.

If your OS is not in there, you can easily build it for your platform by following [the build from source section.](#Build-from-source)

## Usage ##

`get_special_filetype` is meant to be used from a script but can be used from the command line as well:

```shell
# Found usage of the catch2 library
$ get_special_filetype --path test/testfiles/catch2/010-TestCase.cpp --filetype cpp
catch2

# No output since there is nothing in README.md that matches any of the cpp regex values
$ get_special_filetype --path README.md --filetype cpp
```

You can always check the help output.

```shell
$ get_special_filetype --help
usage:
  get_special_filetype  options

where options are:
  -?, -h, --help               display usage information
  -f, --filetype <filetype>    What is the current filetype? E.g. cpp
  -p, --path <path>            Path to the file being examined.
```

## Build from source ##

### Prerequisites ###

* [`cmake`](https://cmake.org/download/)
* [`conan`](https://docs.conan.io/en/latest/installation.html)
* A recent version of `gcc` or `clang`

### Building ###

```shell
$ git clone https://github.com/srydell/get_special_filetype.git && cd get_special_filetype
$ mkdir build
$ cmake -S . -B build -D CMAKE_CXX_COMPILER=$(command -v clang++)
$ cmake --build build
$ cp build/bin/get_special_filetype <wherever you have binaries>
```

## Contributing ##
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License ##
[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
