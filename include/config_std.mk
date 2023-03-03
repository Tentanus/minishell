#========================================#
#============= MAKE CONFIG ==============#
#========================================#

#========== STANDARD VARIABLES ==========#

OBJ_DIR		:=	OBJ
SRC_DIR		:=	src
INC_DIR		:=	include
LIB_DIR		:=	lib
# BREW_DIR	:=	$(shell brew --prefix)

#============= COMPILATION ==============#

# CC			:=	gcc

ifdef DEBUG
	CFLAGS		?=	-Wall -Werror -Wextra -g -fsanitize=address
else
	CFLAGS		?=	-Wall -Werror -Wextra
endif

COMPILE		:=	$(CC) $(CFLAGS)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean lclean flclean re

.DEFAULT_GOAL := all

#=============== COLOURS ================#

BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
CYAN	:= \033[36;1m
RESET	:= \033[0m

