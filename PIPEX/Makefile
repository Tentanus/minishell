# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mverbrug <mverbrug@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/11 16:33:30 by mverbrug      #+#    #+#                  #
#    Updated: 2023/01/16 10:07:06 by mverbrug      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex # NAME = name of executable
HEADER 	=	pipex.h
LIBFT 	=	libft/libft.a
FLAGS 	=	-Wall -Wextra -Werror -g
CC		= 	gcc  # CC = compliler to be used
RM		=	rm -f # RM = the program to delete files

# SRC = .c files
VPATH	=	./src
SRC		=	pipex.c 		\
			parse_input.c 	\
			find_paths.c	\
			utils.c			\
			builtin.c		\
			errors.c

# OBJ = .o files
OBJ_DIR		=	./obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Colors
P 		= 	\x1b[35m
B 		= 	\x1b[34m
Y 		= 	\x1b[33m
G 		= 	\x1b[32m
R 		= 	\x1b[31m
W 		= 	\x1b[0m

# "all" builds executable, should recompile only the updated source files
all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT) $(HEADER)
			@$(CC) $(OBJ) -I $(HEADER) $(LIBFT) -o $@
			@echo "$(Y)Made $(W)$@"
			@echo "$(Y)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n$(W)"

$(LIBFT):
			@echo "$(G)Created $(W)libft"
			@$(MAKE) -C libft

$(OBJ_DIR)/%.o:		%.c
			@mkdir -p $(OBJ_DIR)
			@echo "$(B)Compiling$(W) $< to $@"
			@$(CC) -c $(FLAGS) $< -o $@

# clean deletes temporary/object files
clean:
			@echo "\n$(R)$@ $(W)object files and obj directory"
			@${RM} -r $(OBJ_DIR)

# fclean deletes temporary/object files and executable
fclean: 	clean
			@$(MAKE) fclean -C libft
			@echo "$(P)$@ $(W)object files, obj directory, .a and executable"
			@$(RM) $(NAME)

# re forces recompilation of all source files
re: 		fclean all
			@echo "\n\n$(W)	   	      Restarted"
			@echo "	      	        $(Y)P$(G)I$(B)P$(P)E$(R)X\n"
			@echo "\n\n$(Y)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(W)\n"

# fsanitize to check for leaks
fsani:		$(OBJ) $(LIBFT) $(HEADER)
			@$(CC) -g -fsanitize=address $(OBJ) -I $(HEADER) $(LIBFT) -o $(NAME)
			@echo "$(Y)Made $(W)$(NAME)with $(R)* ! ! ! fsanitize ! ! ! *"
			@echo "$(Y)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n$(W)"

test:		fsani
			./pipex infile "ls -l" "wc -l" myoutfile

.PHONY:		all clean fclean re

subj:		fclean fsani # subject example
			./pipex infile "grep a1" "wc -w" myoutfile
			< infile grep a1 | wc -w > outfile
			make diff_out

0:	fclean fsani # cmd1 valid & cmd2 valid
	./pipex infile ls wc myoutfile
	< infile ls | wc > outfile
	make diff_out

1: fclean fsani # cmd1 valid & cmd2 valid
	./pipex infile "ls -l" "wc -l" myoutfile
	< infile ls -l | wc -l > outfile
	make diff_out

2: fclean fsani # cmd1 valid & cmd2 valid => potential leaks
	./pipex infile "ls -l" "sed 's/hello/world/'" myoutfile
	< infile ls -l | sed 's/hello/world/' > outfile
	make diff_out

3:	fclean fsani # not existing cmd1
	./pipex infile "mafkees" "wc" myoutfile
	< infile "mafkees" | "wc" > outfile
	make diff_out

4:	fclean fsani # not existing cmd2
	./pipex infile "ls" "ikbestaniet" myoutfile
	< infile "ls" | "ikbestaniet" > outfile

5: fclean fsani # cmd1 invalid param & cmd2 valid
	./pipex Makefile "grep a1" "wc -w" myoutfile
	< Makefile grep a1 | wc -w > outfile
	make diff_out

6: fclean fsani # cmd1 valid & cmd2 valid
	./pipex infile "/bin/ls" "wc -w" myoutfile
	< infile /bin/ls | wc -w > outfile
	make diff_out

7: fclean fsani # cmd1 valid & cmd2 valid
	./pipex infile "/bin/ls -l" "wc -w" myoutfile
	< infile /bin/ls -l | wc -w > outfile
	make diff_out

8: fclean fsani # cmd1 arg invalid & cmd2 path invalid
	./pipex infile "grep codam" "/bin/wc -l" myoutfile
	< infile grep codam | /bin/wc -l > outfile

9: fclean fsani # cmd1 valid & cmd2 valid
	./pipex infile      "ls"          "wc"    myoutfile
	< infile      ls |         wc   > outfile
	make diff_out

10: fclean fsani # invalid infile
	./pipex minfile ls wc myoutfile
	< minfile ls | wc > outfile
	make diff_out

11: fclean fsani # cmd1 valid & cmd2 path invalid
	./pipex infile ls /usr/wc myoutfile
	< infile ls | /usr/wc > outfile

12: fclean fsani # invalid outfile
	./pipex infile ls wc youtfile
	< infile ls | wc > utfile
	diff -y youtfile utfile

13: fclean fsani # invalid relative path cmd1 - Test 22
	./pipex infile "../../../../usr/bin/grep codam" "wc -l" myoutfile
	< infile ../../../../usr/bin/grep codam | wc -l > outfile
	make diff_out

14: fclean fsani # valid relative path cmd1 - Test 23
	./pipex infile "../../../../../usr/bin/grep codam" "wc -l" "myoutfile"
	< infile ../../../../../usr/bin/grep codam | wc -l > outfile
	make diff_out

15: fclean fsani # invalid relative path cmd2 - Test 24
	./pipex infile "grep codam" "../../../../usr/bin/wc -l" "myoutfile"
	< infile grep codam | ../../../../usr/bin/wc -l > outfile
	make diff_out

16: fclean fsani # valid relative path cmd2 - Test 25
	./pipex infile "grep codam" "../../../../../usr/bin/wc -l" myoutfile
	< infile grep codam | ../../../../../usr/bin/wc -l > outfile
	make diff_out

17:	fclean fsani
	./pipex infile "cat" "grep codam" myoutfile
	< infile cat | grep codam > outfile
	make diff_out

18: fclean fsani # empty cmd2
	./pipex infile "ls -la" "" myoutfile
	< infile ls -la | "" > outfile

19: fclean fsani # invalid cmd2
	./pipex infile "grep codam" "/bin/wc -l" myoutfile
	< infile grep codam | "/bin/wc -l" > outfile

sed:	fclean fsani # extra test for sed
		./pipex infile "ls" "sed 's/obj/BLAAAA/'" myoutfile
		< infile ls | sed 's/obj/BLAAAA/' > outfile
		make diff_out

diff_out:
	diff -y myoutfile outfile

norm:	del
		norminette

git: del
	git add *
	git commit -m "Commit through make"
	git push origin master

del: fclean
	$(RM) *.DS_Store .DS_Store ./.DS_Store
	$(RM) ./libft/.DS_Store ./libft/libft_src/.DS_Store
	$(RM) ./README.md *.out ./libft/libft.a.5OzDFi
	$(RM) outfile myoutfile pipex utfile youtfile
	rm -rf *.dSYM
