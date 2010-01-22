all:
	cd robopet-ai && $(MAKE)
	cd robopet-communication && $(MAKE)
	cd robopet-gui && $(MAKE)
	cd robopet-radio && $(MAKE)
	cd robopet-simulation && $(MAKE)
	cd robopet-tracker && $(MAKE)
