# Vim examples #

Lets start by defining a help function that will give us a nice interface to run `fmdetect` from. Here is a function that takes into account multiple input files and a variable initial filetype:

```vim
" In file ~/.vim/autoload/fmdetect.vim

function! fmdetect#run_fmdetect(paths, initialFiletype) abort
  let fmdetect_binary = '/path/to/fmdetect'
  " Allow multiple files to be read in one system call
  let parsed_paths = type(a:paths) == type([]) ? join(a:paths, ',') : a:paths
  if executable(fmdetect_binary)
    return system(fmdetect_binary . ' --paths ' . parsed_paths . ' --filetype ' . a:initialFiletype)
  endif
  return ''
endfunction
```

This gives us a good ground to stand on. Onto the examples!

## Setting an extra filetype based on the framework ##

This can be called from a `vimscript`

```vim
function! s:set_framework_filetype() abort
  " Search the current file for extra filetypes
  let extra_ft = fmdetect#run_fmdetect(expand('%:p'), &filetype)
  if len(extra_ft) != 0
    " Set the filetype
    execute('setlocal filetype+=.' . extra_ft)
  endif
endfunction


augroup extra_framework_filetypes
  autocmd!
  " Look for and set extra filetypes based on what framework is used in the file.
  " Ex: Current filetype = cpp
  "     This might set the filetype to 'cpp.catch2'
autocmd BufRead *.cpp,*.cc,*.cxx s:set_framework_filetype()
augroup END

```

Now whenever a `cpp` file is opened, `fmdetect` will check if the file uses any known frameworks. If `fmdetect` returns a non empty string, such as `catch2`, it will set the filetype to `cpp.catch2` allowing you to set filetype specific options for `catch2` in your configs. This is especially useful for framework specific snippets!

## Finding the test framework for a new file ##

I use different test frameworks at work and at home, leading to some differences in preferred configurations. If we could detect which framework is used by reading the files in the same directory as the new file, we could set a filetype based on that. We could then use the corresponding `ftplugin` or `snippets` file to build separate configs while retaining the original filetype (say `cpp` or `python`). So, in `~/.vim/ftdetect/new_cpp.vim`:


```vim
" In file ~/.vim/ftdetect/new_cpp.vim

function! s:try_set_detected_fm_as_ft(filepath) abort
  if len(a:filepath) == 0
    return
  endif

  let extra_ft = fmdetect#run_fmdetect(a:filepath, 'cpp')
  if len(extra_ft) != 0
    execute('setlocal filetype+=.' . extra_ft)
  endif
endfunction

function! s:check_for_similar_files() abort
  " All cpp files in the opened directory
  let cpp_files = split(globpath(expand('%:h'), '*.{cpp,cxx,cc}'), '\n')
  call s:try_set_detected_fm_as_ft(cpp_files)
endfunction

" Check if any of the files in the same directory
" can give us info about the new file
autocmd BufNewFile *.{cpp,cxx,cc} call s:check_for_similar_files()
```

Now, whenever a new `cpp` file is created, it will check the files in the same directory for special filetypes and assume that the new file is of the same breed.

If you're using the [`vim-template` plugin](https://github.com/srydell/vim-template), this can be used to fill the new file with a dynamic skeleton for the detected framework:

![vim-template](https://media.giphy.com/media/hStxOlws6zdjXFd3wQ/giphy.gif "vim-template")

As you might be able to see, `fmdetect` found files using the `catch2` library in the same directory, and therefore the template associated with `catch2` was expanded.
