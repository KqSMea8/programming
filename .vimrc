syntax on
set nocompatible
set nu
set autoindent
set cindent
set smartindent
set tabstop=4
set shiftwidth=4
set expandtab
set encoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,gbk,gb2312
set termencoding=utf-8
set ignorecase
set background=dark
colorscheme desert
au BufReadPost * if line("'\"") > 0|if line("'\"") <= line("$")|exe("norm '\"")|else|exe "norm $"|endif|endif
