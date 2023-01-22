# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/01/20 19:23:55 by mweverli      ########   odam.nl          #
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
				utils/utils.c

VER_SRC		+=	$(SRC) \
				tmp_mares/mini_parse.c \
				test/mver_main.c
WEV_SRC		+=	$(SRC) \
				test/mwev_main.c
SRC			+=	$(SRC) \
				main.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:=	$(OBJ:%.o=%.d)

-include $(DEP)
-include include/config_test.mk

READLINE_PATH = vendor/readline
READLINE_LINK = -L vendor/readline/lib -l readline -l ncurses

#============== LIBRARIES ===============#

LIBFT		:=	libft
DIR_LIBFT	:=	$(LIB_DIR)/$(LIBFT)
LIB_LIBFT	:=	$(DIR_LIBFT)/$(LIBFT).a

LIB_LIST	:=	$(addprefix -L,$(LIB_READLINE)) \
				$(LIB_LIBFT)

#=========== FLAGS & INCLUDES ===========#

INCLUDE		:=	-I$(INC_DIR) \
				-I$(DIR_LIBFT)/include \
				-I$(READLINE_PATH)/include

#=========== TESTING RECIPIES ===========#

echo: 
	@echo "$(SRC)"
	@echo "$(OBJ)"

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)========= $(NAME) COMPILED =========$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
	@echo "$(CYAN)COMPILING:\t$(if $(findstring -g,$(CFL)), debug (-g))\t$(notdir $<)\
		$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

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

LIB: readline $(LIB_LIBFT)

$(LIB_LIBFT):
	@make -C $(DIR_LIBFT)

readline: $(READLINE_PATH)

$(READLINE_PATH):
	@mkdir -p vendor
	sh ./install_readline.sh

