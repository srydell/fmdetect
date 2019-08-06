# ftdetector - A `constexpr` filetype matcher #

`ftdetector` is a dead simple and **very** fast way of matching contents of a file to a string, specifically meant for filetype detection. It can for example be used to identify usage of a library in a file to set specific options in an editor (example with vim below).

## Installation ##

There are pre built binaries in the `bin` directory. Copy the one built for your OS to where you keep user binaries.

If your OS is not in there, you can easily build it for your platform by following [the build from source section.](#Build-from-source)

## Usage ##

`ftdetector` is meant to be used from a script but can be used from the command line as well:

```shell
# Found usage of the catch2 library
$ ftdetector --paths test/testfiles/catch2/010-TestCase.cpp --filetype cpp
catch2

# No output since there is nothing in README.md that matches any of the cpp regex values
$ ftdetector --paths README.md --filetype cpp
```

This can be called from a `vimscript`

```vim
function! s:set_special_filetype() abort
  let ft_binary = expand('~/bin/ftdetector')
  if executable(ft_binary)
    " Search the current file for extra filetypes
    let extra_ft = system(ft_binary . ' --paths ' . expand('%:p') . ' --filetype ' . &filetype)
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
  autocmd Filetype cpp call s:set_special_filetype()
augroup END

```

For a more complete vim example, please see [vim_examples.md](vim_examples.md).

The general usage can be seen with the `--help` flag.

```shell
$ ftdetector --help
usage:
  ftdetector  options

where options are:
  -?, -h, --help               display usage information
  -f, --filetype <filetype>    What is the current filetype? E.g. cpp
  -p, --paths <paths>          Path(s) to the file(s) being examined. May be
                               multiple separated by a comma (,).
```

## Supported filetypes ##

This section is ordered as

```yaml
- The input of `--filetype`
    - The detected filetype and the output on such detection
```

---

```yaml
- cpp
    - catch2
    - gtest
    - benchmark
- python
    - unittest
    - pytest
```



## Build from source ##

### Prerequisites ###

* [`cmake`](https://cmake.org/download/)
* [`conan`](https://docs.conan.io/en/latest/installation.html)
* A recent version of `gcc` or `clang`

### Building ###

```shell
$ git clone https://github.com/srydell/ftdetector.git && cd ftdetector
$ mkdir build
$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_COMPILER=$(command -v clang++)
$ cmake --build build
$ cp build/bin/ftdetector <wherever you have binaries>
```

## Contributing ##
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License ##
[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
