CC = g++
CFLAGS = -Wall
CC2L = ./cpptolua

AA = ar
AFLAGS = rsv

OBJECTS= 	movingObject.o \
			player.o \
			point.o  \
			vector.o \
			line.o \
			rrt.o \
			astar.o \
			fieldInfo.o \
			physicsRobot.o \
			pathplan.o

#USERDATA_OBJECTS= $(addprefix userdata/, $(OBJECTS))

CPPTOLUA_FOLDER = CppToLua_0.1

#all: robopet.a $(USERDATA_OBJECTS)
all: robopet.a $(OBJECTS)

cpptolua:
	wget http://github.com/downloads/kssilveira/CppToLua/$(CPPTOLUA_FOLDER).zip
	unzip $(CPPTOLUA_FOLDER).zip
	cd $(CPPTOLUA_FOLDER); make
	cp $(CPPTOLUA_FOLDER)/cpptolua .

#userdata/%.o: %_userdata.cpp
	#$(CC) -c -o $@ $^ $(LUA)

#userdata/%.cpp: userdata/%.h
#	$(CC2L) -i $< -o $@ -n $*.h

#userdata/%.h: %.h
#	$(CC2L) -i $< -o $@ -H -N ../$*.h

%.o: %.cpp %.h
	$(CC) -c $< -o  $@ $(CFLAGS)

robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
	rm *.a
