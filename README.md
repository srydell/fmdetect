# ftdetect - A `constexpr` filetype matcher #

`ftdetect` is a dead simple and **very** fast way of matching contents of a file to a string, specifically meant for filetype detection. It can for example be used to identify usage of a library in a file to set specific options in an editor (example with vim below).

## Installation ##

There are pre built binaries in the `bin` directory. Copy the one built for your OS to where you keep user binaries.

If your OS is not in there, you can easily build it for your platform by following [the build from source section.](#Build-from-source)

## Usage ##

`ftdetect` is meant to be used from a script but can be used from the command line as well:

```shell
# Found usage of the catch2 library
$ ftdetect --path test/testfiles/catch2/010-TestCase.cpp --filetype cpp
catch2

# No output since there is nothing in README.md that matches any of the cpp regex values
$ ftdetect --path README.md --filetype cpp
```

This can be called from a `vimscript`

```vim
function! set_special_filetype() abort
  let ft_binary = expand('~/bin/ftdetect')
  if executable(ft_binary)
    " Search the current file for extra filetypes
    let extra_ft = system(ft_binary . ' --path ' . expand('%:p') . ' --filetype ' . &filetype)
    if len(extra_ft) != 0
      " Set the filetype
      execute('setlocal filetype+=.' . extra_ft)
    endif
  endif
endfunction


augroup extra_filetypes
  autocmd!
  " Look for and set extra filetypes.
  " Ex: Filetype = cpp
  "     This might set the filetype as 'cpp.catch2'
  autocmd Filetype cpp call set_special_filetype()
augroup END

```


You can always check the help output.

```shell
$ ftdetect --help
usage:
  ftdetect  options

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
$ git clone https://github.com/srydell/ftdetect.git && cd ftdetect
$ mkdir build
$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_COMPILER=$(command -v clang++)
$ cmake --build build
$ cp build/bin/ftdetect <wherever you have binaries>
```

## Contributing ##
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License ##
[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
