VOBJ		:=	$(VER_SRC:%.c=$(OBJ_DIR)/%.o)
WOBJ		:=	$(WEV_SRC:%.c=$(OBJ_DIR)/%.o)

ODIR		:=	$(OBJ) \
				$(VOBJ) \
				$(WOBJ)

OS			:=	$(shell uname)

V: LIB $(VOBJ)
	@$(COMPILE) -g3 $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(VOBJ) -o martest
	@echo "$(GREEN)$(BOLD)  | MARES TEST COMPILED |$(RESET)"
	./martest

W: LIB $(WOBJ)
	@$(COMPILE) $(INCLUDE) $(WOBJ) $(LIB_LIBFT) $(READLINE_LINK) -o martest
	@echo "$(GREEN)$(BOLD)  | MARTIJN TEST COMPILED |$(RESET)"

Vebug: clean
	@$(MAKE) V DEBUG=1

Webug: clean
	@$(MAKE) W DEBUG=1

tclean:
	@rm -rf martest
