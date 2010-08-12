all:
	@cd lib && $(MAKE)
	@echo "Compiled robopet lib."
	@cd robopet-communication && $(MAKE)
	@echo "Compiled Communication."
	@cd robopet-ai && $(MAKE)
	@echo "Compiled AI."
	@cd robopet-radio && $(MAKE)
	@echo "Compiled Radio."
	@cd robopet-simulation && $(MAKE)
	@echo "Compiled Simulator."
	@cd robopet-tracker && $(MAKE)
	@echo "Compiled Tracker."
	@cd robopet-gui/nbproject && make -f nbproject/Makefile-Release.mk ../GUI
	@echo "Compiled GUI."
lua:
	./get_lua.sh
