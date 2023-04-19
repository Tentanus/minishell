# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/04/19 18:28:10 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===========  MAKE INCULDES  ============#

-include include/config_std.mk

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	marshell

SRC			:=	\
				builtin/builtin.c					\
				builtin/cd.c						\
				builtin/echo.c						\
				builtin/env.c						\
				builtin/exit.c						\
				builtin/export.c					\
				builtin/pwd.c						\
				builtin/unset.c						\
				complexer/appender.c				\
				complexer/complexer.c				\
				complexer/expander.c				\
				complexer/lexer.c					\
				complexer/lexer_jmptbl_func.c		\
				complexer/parser.c					\
				complexer/parser_jmptbl_func.c		\
				complexer/syntax.c					\
				complexer/syntax_jmptbl_func.c		\
				executor/executor.c					\
				executor/execute_multiple_cmds.c	\
				executor/execute_single_cmd.c		\
				executor/execute_non_builtin.c		\
				executor/here_doc.c					\
				executor/redir.c					\
				env_var_init_shell/env_var.c		\
				env_var_init_shell/env_var_list.c	\
				env_var_init_shell/init_shell.c		\
				utils/list_cmd_utils.c				\
				utils/list_redir_utils.c			\
				utils/list_token_utils.c			\
				utils/minishell_error.c				\
				utils/print_utils.c					\

VER_SRC		:=	$(SRC) \
				tmp_mares/parse_utils.c				\
				test/ver_main.c

WEV_SRC		:=	$(SRC) \
				tmp_mares/parse_utils.c				\
				tmp_martijn/wev_main.c

SRC			+=	main.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:=	$(OBJ:%.o=%.d)

-include $(DEP)
-include include/config_test.mk

ODIR			:=	$(sort $(dir $(ODIR)))
READLINE_PATH	:=	lib/readline
READLINE_LINK	:=	-Llib/readline/lib -lreadline -lncurses

#============== LIBRARIES ===============#

LIBFT			:=	libft
DIR_LIBFT		:=	$(LIB_DIR)/$(LIBFT)
LIB_LIBFT		:=	$(DIR_LIBFT)/$(LIBFT).a

LIB_LIST		:=	$(READLINE_LINK)	\
					$(LIB_LIBFT)

#=========== FLAGS & INCLUDES ===========#

INCLUDE			:=	-I$(INC_DIR) \
					-I$(DIR_LIBFT)/include \
					-I$(READLINE_PATH)/include

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(OBJ) $(LIB_LIST) -o $(NAME)
	@echo "$(GREEN)$(BOLD)========= $(NAME) COMPILED =========$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(ODIR)
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING:\t$(if $(findstring -g,$(CFLAGS)), debug (-g))\t$(notdir $<)\
	$(RESET)"

$(ODIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)\tCLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

gclean: lclean tclean fclean
	@echo "$(RED)$(BOLD)\n\t-=- READY FOR GIT -=-$(RESET)"

re: fclean all

debug:
	@$(MAKE) DEBUG=1

rebug: fclean debug

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
