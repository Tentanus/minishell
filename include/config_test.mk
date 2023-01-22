$(VOBJ)		:=	$(VER_SRC:$(SRC_DIR)/%.C=$(OBJ_DIR)/%.o)
$(WOBJ)		:=	$(WEV_SRC:$(SRC_DIR)/%.C=$(OBJ_DIR)/%.o)

W: LIB $(WOBJ)
	@$(COMPILE) $(INCLUDE) $(LIB_LIST) $(READLINE_LINK) $(WOBJ) -o W
	@echo "$(GREEN)$(BOLD)\t| W_TEST COMPILED |$(RESET)"


