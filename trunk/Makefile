all:
	cd robopet-communication && $(MAKE)
	echo "Compilou Communication!"
	cd robopet-ai && $(MAKE)
	echo "Compilou IA!"
	cd robopet-radio && $(MAKE)
	echo "Compilou Radio!"
	cd robopet-simulation && $(MAKE)
	echo "Compilou Simulador!"
	cd robopet-tracker && $(MAKE)
	echo "Compilou Tracker!"
	cd robopet-gui/nbproject && $(MAKE) -f nbproject/Makefile-Release.mk SUBPROJECTS= .build-conf
	echo "Compilou GUI!"
lua:
	./get_lua.sh
