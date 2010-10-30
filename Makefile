all:
	@cd lib && $(MAKE)
	@echo "Compiled robopet lib."
	@cd communication && $(MAKE)
	@echo "Compiled Communication."
	@cd ai && $(MAKE)
	@echo "Compiled AI."
	@cd radio && $(MAKE)
	@echo "Compiled Radio."
	@cd simulation && $(MAKE)
	@echo "Compiled Simulator."
	@cd tracker && $(MAKE)
	@echo "Compiled Tracker."
	@cd gui && $(MAKE)
	@echo "Compiled GUI."
lua:
	./get_lua.sh
