OBJECTS = referee vector point line movingObject player physicsRobot
XML = $(OBJECTS:=.xml)
HEADERS = $(OBJECTS:=_userdata.h)
CPPS = $(OBJECTS:=_userdata.cpp)

all: $(XML) $(HEADERS) $(CPPS)

doc:
	doxygen .

%.xml: ../%.cpp
	gccxml $< -fxml=$@

%_userdata.cpp: %.xml %_userdata.h
	../moonbind $< > $@

%_userdata.h: %.xml
	../moonbind $< header > $@

clean:
	rm *.xml
	rm *_userdata.*
