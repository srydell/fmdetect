# Vim examples #

To not make this document a thousand lines long I will assume some knowledge about how config files are read in vim and how functions are called. The vim documentation is excellent and if something is unclear you should try to read `:help <something>`.

A more complex, but perhaps more realistic version of running `ftdetector` from vim would be to create a function that takes into account multiple input files and a variable initial filetype:

```vim
" In file ~/.vim/autoload/ftdetector.vim

function! ftdetector#runftdetector(path, initialFiletype) abort
  let ft_binary = g:integrations_dir . '/bin/ftdetector'
  " Allow multiple files to be read in one system call
  let parsed_paths = type(a:path) == type([]) ? join(a:path, ',') : a:path
  if executable(ft_binary)
    return system(ft_binary . ' --paths ' . parsed_paths . ' --filetype ' . a:initialFiletype)
  endif
  return ''
endfunction
```

This gives us a good ground to stand on. Onto the examples!

## Finding the test framework for a new file ##

I use different test frameworks at work and at home, leading to some differences in preferred configurations. If we could detect which framework is used, we could set a filetype based on that. We could then use the corresponding `ftplugin` to build separate configs while retaining the original filetype (say `cpp` or `python`). So, in `~/.vim/ftdetect/new_cpp.vim`:


```vim
" In file ~/.vim/ftdetect/new_cpp.vim

function! s:try_set_detected_ft(filepath) abort
  if len(a:filepath) == 0
    return
  endif

  let extra_ft = ftdetector#runftdetector(a:filepath, 'cpp')
  if len(extra_ft) != 0
    execute('setlocal filetype+=.' . extra_ft)
  endif
endfunction

function! s:check_for_similar_files() abort
  " All cpp files in the opened directory
  let cpp_files = split(globpath(expand('%:h'), '*.{cpp,cxx,cc}'), '\n')
  call s:try_set_detected_ft(cpp_files)
endfunction

" Check if any of the files in the same directory
" can give us info about the new file
autocmd BufNewFile *.{cpp,cxx,cc} call s:check_for_similar_files()
```

Now, whenever a new `cpp` file is created, it will check the files in the same directory for special filetypes and assume that the new file is of the same breed.

