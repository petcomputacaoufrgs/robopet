CC = g++
CFLAGS = -Wall -pg

AA = ar
AFLAGS = rsv

LUA = -llua -ldl -lm

OBJECTS= 	movingObject.o \
			player.o \
			point.o  \
			vector.o \
			line.o \
			rrt.o \
			astar.o \
			fieldInfo.o \
			physicsRobot.o \
			pathplan.o \
			referee.o \
			pathplan_player.o

USERDATA_OBJECTS = movingObject_userdata.o \
			player_userdata.o \
			point_userdata.o  \
			vector_userdata.o \
			line_userdata.o \
			physicsRobot_userdata.o \
			referee_userdata.o

.PHONY : all doc make_userdata

all: robopet.a robopet_lua.a

doc:
	doxygen robopet.doc

make_userdata:
	cd userdata ; make

%_userdata.o: userdata/%_userdata.cpp %.o
	$(CC) -I. -c -o $@ $^ $(LUA)

%.o: %.cpp %.h
	$(CC) -c $< -o  $@ $(CFLAGS)

repl: userdata/interpreter.cpp robopet.a robopet_lua.a
	$(CC) -I. -o $@ $^ $(LUA)

robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

robopet_lua.a: $(OBJECTS) make_userdata $(USERDATA_OBJECTS)
	$(AA) $(AFLAGS) $@ $(OBJECTS) $(USERDATA_OBJECTS)

clean:
	rm *.o
	rm *.a
