CC = g++
CFLAGS = -Wall

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
			pathplan_player.o \
			utils.o

.PHONY : all doc

all: robopet.a

doc:
	doxygen robopet.doc

robopet_lua.o:
	cd userdata ; make
	$(CC) -I./ -c userdata/robopet_lua.cpp -o $@ $(CFLAGS) -llua -ldl

%.o: %.cpp %.h
	$(CC) -c $< -o  $@ $(CFLAGS)

repl: userdata/interpreter.cpp userdata/robopet_lua.o robopet.a
	$(CC) -I. -o $@ $^ $(LUA)

robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
	rm *.a
