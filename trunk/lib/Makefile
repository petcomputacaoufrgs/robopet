CC = g++
CFLAGS = -Wall

AA = ar
AFLAGS = rsv

LUA = -llua -ldl -lm

OBJ_NAMES= 	movingObject \
			player \
			point  \
			vector \
			line \
			rrt \
			physicsRobot \
			pathplan \
			discretePathplan \
			referee \
			pathplan_player \
			utils \
			gstar \
			astar

OBJDIR = obj
OBJ_FILES = $(addsuffix .o,$(OBJ_NAMES))
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJ_FILES))


.PHONY : all doc

all: robopet.a robopet_lua.o lua_runtime.h

doc:
	doxygen robopet.doc

lua_runtime.h: robopet_lua.o
	swig -lua -external-runtime lua_runtime.h

robopet_lua.o:
	cd userdata ; make
	$(CC) -I./ -c userdata/robopet_lua.cpp -o $@ $(CFLAGS) -llua -ldl

$(OBJDIR)/%.o: %.cpp %.h | $(OBJDIR)
	$(CC) -c $< -o  $@ $(CFLAGS)

$(OBJDIR):
	@mkdir $(OBJDIR) -p

repl: userdata/interpreter.cpp userdata/robopet_lua.o robopet.a
	$(CC) -I. -o $@ $^ $(LUA)

robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
	rm *.a
