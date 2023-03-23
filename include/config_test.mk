VOBJ		:=	$(VER_SRC:%.c=$(OBJ_DIR)/%.o)
WOBJ		:=	$(WEV_SRC:%.c=$(OBJ_DIR)/%.o)

ODIR		:=	$(OBJ) \
				$(VOBJ) \
				$(WOBJ)

V: LIB $(VOBJ)
	@$(COMPILE) -g3 $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(VOBJ) -o martest
	@echo "$(GREEN)$(BOLD)  | MARES TEST COMPILED |$(RESET)"
	# ./martest

W: LIB $(WOBJ)
	@$(COMPILE) $(INCLUDE) $(READLINE_LINK) $(WOBJ) $(LIB_LIST) -o martest
	@echo "$(GREEN)$(BOLD)  | MARTIJN TEST COMPILED |$(RESET)"

Vebug: clean
	@$(MAKE) V DEBUG=1

Webug: clean
	@$(MAKE) W DEBUG=1

tclean:
	@rm -rf martest
