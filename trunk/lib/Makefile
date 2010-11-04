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
			fieldInfo.o \
			physicsRobot.o \
			pathplan.o

#USERDATA_OBJECTS= $(addprefix userdata/, $(OBJECTS))

CPPTOLUA_FOLDER = CppToLua_0.1

all: robopet.a $(USERDATA_OBJECTS)

cpptolua:
	wget http://github.com/downloads/kssilveira/CppToLua/$(CPPTOLUA_FOLDER).zip
	unzip $(CPPTOLUA_FOLDER).zip
	cd $(CPPTOLUA_FOLDER); make
	cp $(CPPTOLUA_FOLDER)/cpptolua .

#userdata/%.o: %_userdata.cpp
#	$(CC) -c -o $@ $^ $(LUA)

#userdata/%.cpp: userdata/%.h
#	$(CC2L) -i $< -o $@ -n $*.h

#userdata/%.h: %.h
#	$(CC2L) -i $< -o $@ -H -N ../$*.h

movingObject.o: movingObject.h movingObject.cpp
	$(CC) -c -o $@ movingObject.cpp $(CFLAGS)

player.o: movingObject.o player.h player.cpp
	$(CC) -c -o $@ player.cpp $(CFLAGS)

point.o: point.h point.cpp
	$(CC) -c -o $@ point.cpp $(CFLAGS)

vector.o: point.o vector.cpp vector.h
	$(CC) -c -o $@ -c vector.cpp $(CFLAGS)

line.o: vector.o line.cpp line.h
	$(CC) -c -o $@ -c line.cpp $(CFLAGS)

rrt.o: rrt.cpp rrt.h point.o
	$(CC) -c -o $@ $< $(FLAGS)

fieldInfo.o: fieldInfo.cpp fieldInfo.h
	$(CC) -c -o $@ $< $(CFLAGS)

physicsRobot.o: physicsRobot.cpp physicsRobot.h
	$(CC) -c -o $@ $< $(CFLAGS)

pathplan.o: pathplan.cpp pathplan.h
	$(CC) -c -o $@ $< $(CFLAGS)

#rrt.o
robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
	rm *.a
