# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/01/24 12:27:50 by mverbrug      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===========  MAKE INCULDES  ============#

-include include/config_std.mk

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	marshell

SRC			:=	builtin/builtin.c		\
				builtin/echo.c			\
				builtin/pwd.c			\
				utils/utils.c

VER_SRC		:=	$(SRC) \
				tmp_mares/mini_parse.c \
				test/ver_main.c
WEV_SRC		:=	$(SRC) \
				test/wev_main.c
SRC			+=	main.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:=	$(OBJ:%.o=%.d)

-include $(DEP)
-include include/config_test.mk

ODIR		:=	$(sort $(dir $(ODIR)))

READLINE_PATH	:=	lib/readline
READLINE_LINK	:=	-Llib/readline/lib -lreadline -lncurses

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
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING:\t$(if $(findstring -g,$(CFL)), debug (-g))\t$(notdir $<)\
	$(RESET)"

$(ODIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

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

flclean: lclean fclean

