CC = gcc
OBJECTS = referee point vector line movingObject player physicsRobot
XML = $(OBJECTS:=.xml)
SWIGS = $(OBJECTS:=.i)

all: robopet_lua.o

%.xml: ../%.cpp
	gccxml $< -fxml=$@

%.i: %.xml
	../swigbind $< >> robopet_temp.i

robopet.i: $(XML) $(SWIGS)
	cat header robopet_temp.i > robopet.i
	rm robopet_temp.i

robopet_lua.cpp: robopet.i
	swig -c++ -lua -o $@ $<

robopet_lua.o: robopet_lua.cpp
	$(CC) -I../ -c $< -o  $@ $(CFLAGS) -llua -ldl

clean:
	rm *.xml
	rm robopet_lua.cpp
	rm *.i
