VOBJ		:=	$(VER_SRC:%.c=$(OBJ_DIR)/%.o)
WOBJ		:=	$(WEV_SRC:%.c=$(OBJ_DIR)/%.o)

ODIR		:=	$(OBJ) \
				$(VOBJ) \
				$(WOBJ)

V: LIB $(VOBJ)
	@$(COMPILE) $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(VOBJ) -o martest
	@echo "$(GREEN)$(BOLD)  | MARES TEST COMPILED |$(RESET)"
	./martest

W: LIB $(WOBJ)
	@$(COMPILE) $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(WOBJ) -o martest
	@echo "$(GREEN)$(BOLD)  | MARTIJN TEST COMPILED |$(RESET)"

Vebug: clean
	@$(MAKE) V DEBUG=1

Webug: clean
	@$(MAKE) W DEBUG=1

tclean:
	@rm -rf martest
