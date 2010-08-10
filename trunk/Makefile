all:
	@cd lib && $(MAKE)
	@echo "Compilou robopet lib."
	@cd robopet-communication && $(MAKE)
	@echo "Compilou Communication."
	@cd robopet-ai && $(MAKE)
	@echo "Compilou IA."
	@cd robopet-radio && $(MAKE)
	@echo "Compilou Radio."
	@cd robopet-simulation && $(MAKE)
	@echo "Compilou Simulador."
	@cd robopet-tracker && $(MAKE)
	@echo "Compilou Tracker."
	@cd robopet-gui/nbproject make -f nbproject/Makefile-Release.mk ../GUI
	@echo "Compilou GUI."
lua:
	./get_lua.sh
