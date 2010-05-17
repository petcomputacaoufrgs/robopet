
CC = g++
CFLAGS = -Wall

AA = ar
AFLAGS = rsv

all: movingObject.o player.o point.o vector.o line.o rrt.o fieldInfo.o physicsRobot.o pathplan.o constants.o robopet.a

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

#rrt.o: rrt.cpp rrt.h point.o
#	$(CC) -c -o $@ $< $(FLAGS)

fieldInfo.o: fieldInfo.cpp fieldInfo.h
	$(CC) -c -o $@ $< $(FLAGS)

physicsRobot.o: physicsRobot.cpp physicsRobot.h
	$(CC) -c -o $@ $< $(FLAGS)

pathplan.o: pathplan.cpp pathplan.h
	$(CC) -c -o $@ $< $(FLAGS)

constants.o: constants.h
	$(CC) -c -o $@ $< $(FLAGS)


robopet.a: movingObject.o player.o point.o vector.o line.o  fieldInfo.o physicsRobot.o pathplan.o constants.o
#rrt.o
	$(AA) $(AFLAGS) $@ $^

clean:
	rm *.o
