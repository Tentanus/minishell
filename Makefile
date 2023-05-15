# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/05/15 18:49:55 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===========  MAKE INCULDES  ============#

-include include/config_std.mk

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	minishell

SRC			:=	\
				builtin/builtin.c					\
				builtin/cd.c						\
				builtin/echo.c						\
				builtin/env.c						\
				builtin/exit.c						\
				builtin/export.c					\
				builtin/pwd.c						\
				builtin/unset.c						\
				complexer/complexer.c				\
				complexer/lexer.c					\
				complexer/lexer_jmptbl_func.c		\
				complexer/syntax.c					\
				complexer/syntax_jmptbl_func.c		\
				complexer/expander.c				\
				complexer/expander_utils.c			\
				complexer/appender.c				\
				complexer/parser.c					\
				complexer/parser_jmptbl_func.c		\
				executor/executor.c					\
				executor/execute_multiple_cmds.c	\
				executor/execute_single_cmd.c		\
				executor/execute_non_builtin.c		\
				executor/here_doc.c					\
				executor/here_doc_expand.c			\
				executor/redir.c					\
				executor/signals.c					\
				env_var_init_shell/env_var.c		\
				env_var_init_shell/env_var_list.c	\
				env_var_init_shell/env_var_node.c	\
				env_var_init_shell/init_shell.c		\
				utils/list_cmd_utils.c				\
				utils/list_redir_utils.c			\
				utils/list_token_utils.c			\
				utils/list_token_free_utils.c		\
				utils/minishell_error.c				\
				utils/minishell_error_custom.c		\
				utils/status.c						\
				main.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:=	$(OBJ:%.o=%.d)

-include $(DEP)
-include include/config_test.mk

ODIR			:=	$(sort $(dir $(ODIR)))
READLINE_PATH	:=	lib/readline
READLINE_LINK	?=	-Llib/readline/lib -lreadline -lncurses

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

$(NAME): $(ODIR) LIB $(OBJ)
	@$(COMPILE) $(INCLUDE) $(OBJ) $(LIB_LIBFT) $(READLINE_LINK) -o $(NAME)
	@echo "$(GREEN)$(BOLD)========= $(NAME) COMPILED =========$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING:\t$(if $(findstring -g,$(CFLAGS)), debug (-g))\t$(notdir $<)\
	$(RESET)"

$(ODIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)\tCLEANING $(NAME)$(RESET)"

fclean: clean lclean
	@rm -f $(NAME)

gclean: lclean fclean
	@echo "$(RED)$(BOLD)\n\t-=- READY FOR GIT -=-$(RESET)"

re: fclean
	@$(MAKE)

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
