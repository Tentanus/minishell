# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/03/09 21:03:24 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===========  MAKE INCULDES  ============#

-include include/config_std.mk

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	marshell

SRC			:=	\
				parser/lexer.c						\
				parser/lexer_jmptbl_func.c			\
				utils/list_token_utils.c			\
				utils/minishell_error.c

VER_SRC		:=	$(SRC) \
				tmp_mares/mini_parse.c		\
				tmp_mares/parse_utils.c		\
				builtin/builtin.c			\
				builtin/cd.c				\
				builtin/echo.c				\
				builtin/env.c				\
				builtin/exit.c				\
				builtin/export.c			\
				builtin/pwd.c				\
				builtin/unset.c				\
				executor/env_var_list.c		\
				executor/env_var.c			\
				executor/init_shell.c		\
				test/ver_main.c

WEV_SRC		:=	$(SRC) \
				parser/parser.c						\
				parser/syntax_jmptbl_func.c			\
				parser/syntax.c						\
				parser/expander.c					\
				tmp_martijn/print_utils.c			\
				tmp_martijn/wev_main.c

SRC			+=	main.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:=	$(OBJ:%.o=%.d)

-include $(DEP)
-include include/config_test.mk

ODIR		:=	$(sort $(dir $(ODIR)))
READLINE_PATH	:=	lib/readline
READLINE_LINK	?=	-Llib/readline/lib -lreadline -lncurses

#============== LIBRARIES ===============#

LIBFT		:=	libft
DIR_LIBFT	:=	$(LIB_DIR)/$(LIBFT)
LIB_LIBFT	:=	$(DIR_LIBFT)/$(LIBFT).a

LIB_LIST	:=	$(READLINE_LINK) \
				$(LIB_LIBFT)

#=========== FLAGS & INCLUDES ===========#

INCLUDE		:=	-I$(INC_DIR) \
				-I$(DIR_LIBFT)/include \
				-I$(READLINE_PATH)/include

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(LIB_LIST) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)========= $(NAME) COMPILED =========$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(ODIR)
	@$(COMPILE) $(INCLUDE) -g -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING:\t$(if $(findstring -g,$(CFL)), debug (-g))\t$(notdir $<)\
	$(RESET)"

$(ODIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

gclean: lclean tclean fclean
	@echo "$(RED)$(BOLD)\n\t-=- READY FOR GIT -=-$(RESET)"

re: fclean all

debug:
	@$(MAKE) DEBUG=1

rebug: fclean debug

#=========== TESTING RECIPIES ===========#

info: 
	$(info $(ODIR))

#========================================#
#============== LIBRARIES ===============#
#========================================#

LIB: $(READLINE_PATH) $(LIB_LIBFT)

$(LIB_LIBFT):
	@make -C $(DIR_LIBFT)

$(READLINE_PATH):
	sh ./install_readline.sh

lclean:
	@make -C $(DIR_LIBFT) fclean
