# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/01/19 12:01:54 by mverbrug      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===========  MAKE INCULDES  ============#

-include include/config.mk

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	marshell

SRC			:=	marshell/main.c \
#				lexer/lexer.c

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJ			:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
DEP			:=	$(OBJ:.o=.d)
-include $(DEP)

#============== LIBRARIES ===============#

LIBFT		:=	libft
DIR_LIBFT	:=	$(LIB_DIR)/$(LIBFT)
LIB_LIBFT	:=	$(DIR_LIBFT)/$(LIBFT).a

LIB_READLINE:=	$(BREW_DIR)/opt/readline/lib

LIB_LIST	:=	$(addprefix -L,$(LIB_READLINE)) \
				$(LIB_LIBFT)

#=========== FLAGS & INCLUDES ===========#

INCLUDE		:=	-I$(INC_DIR) \
				-I$(DIR_LIBFT)/include \
				-I$(BREW_DIR)/opt/readline/include

FLAG		:=	-lreadline

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(FLAG) $(LIB_LIST) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)========= $(NAME) COMPILED =========$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c | $(OBJ_DIR)
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING: $(notdir $<)$(if $(findstring -g,$(CFL)), debug)\
		$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(EXE)

lclean:
	@make -C $(DIR_LIBFT) fclean

flclean: lclean fclean

re: fclean all

debug:
	@$(MAKE) DEBUG=1

rebug: fclean debug

#========================================#
#============== LIBRARIES ===============#
#========================================#

LIB: $(LIB_LIBFT)

$(LIB_LIBFT):
	@make -C $(DIR_LIBFT)

