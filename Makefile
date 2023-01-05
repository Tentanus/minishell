# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/01/05 17:53:29 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	marshell
EXE			:=	marsh

OBJ_DIR		:=	OBJ
SRC_DIR		:=	src
INC_DIR		:=	include
LIB_DIR		:=	lib

SRC			:=	main.c
				

OBJ			:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC))

DEP			:=	$(OBJ:.o=.d)

BREW_DIR	:=	$(shell brew --prefix)


#============== LIBRARIES ===============#

LIBFT		:=	libft
LIB_LIBFT	:=	$(LIB_DIR)/$(LIBFT)
LIB_LIB_ARC	:=	$(LIB_LIBFT)/$(LIBFT).a

LIB_READLINE:=	$(BREW_DIR)/opt/readline/lib

LIB_COLLECT	:=	$(LIB_LIBFT) \
				$(LIB_READLINE)

LIB_LIST	:=	$(addprefix -L,$(LIB_COLLECT))

#=============== COLOURS ================#

BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
CYAN	:= \033[36;1m
RESET	:= \033[0m

#============= COMPILATION ==============#

INCLUDE		:=	-I $(INC_DIR) \
				-I $(LIB_LIBFT)/include \
				-I $(LIB_READLINE)/opt/readline/include

CC			:=	gcc
ifdef DEBUG
	CFL		:=	-Wall -Werror -Wextra -g -fsanitize=address
else
	CFL		:=	-Wall -Werror -Wextra
endif

COMPILE		:=	$(CC) $(CFL)

#============ MAKE INCLUDES =============#

-include makerc/colours.mk
-include makerc/config.mk
# research colours.mk/config.mk
# not functioning
-include $(DEP)

echo: 
	@echo "$(RED)HEYA$(RESET)"
#FOR TESTING PURPOSES

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(OBJ) -o $(EXE) $(LIB_LIST)
	@echo "$(CYAN)$(BOLD)COMPILING COMPLETE$(RESET)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/*/%.c | $(OBJ_DIR)
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING: $(notdir $<)$(if $(findstring -g,$(CFL)), debug) \
		$(RESET)"

debug:
	@$(MAKE) DEBUG=1

rebug: fclean debug

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(EXE)

lclean:
	@make -C $(LIB_LIBFT) clean
	@$(RM) $(LIB_LIB_ARC)

flclean: lclean fclean

re: fclean all

#========================================#
#============== LIBRARIES ===============#
#========================================#

LIB: $(LIB_LIB_ARC)

$(LIB_LIB_ARC):
	@make -C $(LIB_LIBFT)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean tclean re test

.DEFAULT_GOAL := all
