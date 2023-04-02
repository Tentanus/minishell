" STANDARD
set number
set ruler
syntax on
set mouse=a
set nowrap
set nofixendofline
set rnu
set scrolloff=10

" INDENTAION
set cindent

" Lay-out 
set list
set listchars=tab:▸·
let &colorcolumn=join(range(81,999),",")
highlight ColorColumn ctermbg=235

"Enviroment Variables

let g:user42 = 'mweverli'
let g:mail42 = 'mweverli@student.codam.nl'
