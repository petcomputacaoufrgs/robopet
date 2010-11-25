#include "astar.h"

AStar::AStar() {
	initialize();
}

AStar::AStar(node start, node goal) : Pathplan(start, goal){
	initialize();
}

void AStar::initialize() {
	//itializing came_from matrix
	for(int i=0; i<MAX_X; i++) {
		for(int j=0; j<MAX_Y; j++) {
			came_from[i][j].setX(-1);
			came_from[i][j].setY(-1);
		}
	}
}

AStar::~AStar() {
}

//int AStar::grid [MAX_X][MAX_Y] = {	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, O, O, O, O, O, O, O, O,
//									1, 1, O, 1, O, 1, 1, 1, 1, 1,
//									1, 1, O, O, O, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//									1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

bool AStar::inLimits(node y) {

	if(	(y.getX() >=0 && y.getY() >= 0) &&
		(y.getX() < MAX_X && y.getY() < MAX_Y)) {

		return true;
	} else {
		return false;
	}
}

bool AStar::validPosition(node n) {

	return (!(n.getX() == 0 && n.getY() ==0) 	&& //if it's a neighbor
			inLimits(n) 		&&
			env[(int)n.getX()][(int)n.getY()] != OBSTACLE
			);
}


float AStar::distance(node a, node b) {

	return sqrt(pow(a.getX() - b.getX(),2) + pow(a.getY() - b.getY(),2));
}


float AStar::calcG(node x) {

	node current = x;
	float g = 0;

	while(current != initialpos) {
		//our cost to go from one node to another is always 1
		//here we're doing a generic implementation of the algorithm
		//maybe can be optimized later

		//env[(int)current.getX()][(int)current.getY()];
		g++;
		current = came_from[(int)current.getX()][(int)current.getY()];
	}
	return g;
}

float AStar::calcH(node x) {

	return distance(x, finalpos);
}

float AStar::calcF(node x) {

	return calcG(x) + calcH(x);
}

node AStar::lowestF() {

	float lowest_F_value = calcF(*(open_set.begin()));
	node lowest_F_node = *(open_set.begin());

	set<node>::iterator current = open_set.begin();
	current++;	//start iterating from second element of open_set

	float current_f_value = 0;

	while(current != open_set.end()) {
		current_f_value = calcF(*current);
		if (current_f_value < lowest_F_value) {
			lowest_F_value = current_f_value;
			lowest_F_node = *current;
		}
		current++;
	}
	return lowest_F_node;
}

node AStar::neighbor(node x, int i, int j) {

	return Point( (x.getX())+i, (x.getY())+j );
}

//given a source and a goal node, runs A* algorithm
void AStar::run() {

	bool tentative_is_better;
	float tentative_g;

	//INITIALIZE WITH THE INITIAL NODE
	open_set.insert(initialpos);

	//the distance from the current node to the start node is 0
	g[(int)initialpos.getX()][(int)initialpos.getY()] = 0;
	h[(int)initialpos.getX()][(int)initialpos.getY()] = calcH(initialpos);
	f[(int)initialpos.getX()][(int)initialpos.getY()] =
			g[(int)initialpos.getX()][(int)initialpos.getY()] +
			h[(int)initialpos.getX()][(int)initialpos.getY()];

	while(!(open_set.empty())) {

		//x = the node in openset having the lowest f value
		node x = lowestF();

		//if x is the goal node
		if(x == finalpos) {
			printf("ending AStar\n");
			reconstructPath();
		}

		open_set.erase(x);
		closed_set.insert(x);

		//foreach neighbor of the node x
		for(short int i=-1; i<=1; i++) {
			for(short int j=-1; j<=1; j++) {

				node y = neighbor(x,i,j);

				if(validPosition(y)) {

					//if y belongs to closed_set
					if (closed_set.find(y) != closed_set.end()) {
						continue;
					}

					tentative_g = calcG(x) + distance(x, y);

					//if y doesn't belongs to open_set
					if(open_set.find(y) == open_set.end()) {
						open_set.insert(y);
						tentative_is_better = true;
					} else if(tentative_g < calcG(y)) {
						tentative_is_better = true;
					} else {
						tentative_is_better = false;
					}

					if (tentative_is_better) {
						came_from[(int)y.getX()][(int)y.getY()] = x;
						g[(int)y.getX()][(int)y.getY()] 		= tentative_g;
						h[(int)y.getX()][(int)y.getY()] 		= distance(y, finalpos);
						f[(int)y.getX()][(int)y.getY()] 		=
									g[(int)y.getX()][(int)y.getY()] +
									h[(int)y.getX()][(int)y.getY()];
					}
				}
			}
		}
	}
}

void AStar::reconstructPath() {

	node current = finalpos;

	while(current != initialpos) {
		pathFinal.push_front(current);
		//goto previous node
		current = came_from[(int)current.getX()][(int)current.getY()];
	}
	pathFinal.push_front(initialpos);
}
