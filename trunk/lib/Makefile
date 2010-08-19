
CC = g++
CFLAGS = -Wall

AA = ar
AFLAGS = rsv

OBJECTS= movingObject.o player.o point.o vector.o line.o rrt.o astar.o fieldInfo.o physicsRobot.o pathplan.o

PKG= vector_pkg.o#$(OBJECTS:.o=_pkg.o)

all: robopet.a astar_pet

astar_pet: main.cpp $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

tolua_include:
	./generate_includes

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

astar.o: astar.cpp astar.h point.o
	$(CC) -c -o $@ $< $(FLAGS)

fieldInfo.o: fieldInfo.cpp fieldInfo.h
	$(CC) -c -o $@ $< $(CFLAGS)

physicsRobot.o: physicsRobot.cpp physicsRobot.h
	$(CC) -c -o $@ $< $(CFLAGS)

pathplan.o: pathplan.cpp pathplan.h
	$(CC) -c -o $@ $< $(CFLAGS)



#%_pkg.o: %_pkg.cpp
#	$(CC) -c -o $@ $<

#%_pkg.cpp: %.pkg
#	tolua -H $*_pkg.h $< > $@


#rrt.o
robopet.a: $(OBJECTS)
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
	rm *.a
