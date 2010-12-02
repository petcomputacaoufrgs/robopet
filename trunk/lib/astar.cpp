#include "astar.h"

AStar::AStar() {
	initialize();
}

AStar::AStar(Node start, Node goal) : Pathplan(start, goal){
	initialize();
}

void AStar::initialize() {
//	initializing came_from matrix
	for(int i=0; i<MAX_X; i++) {
		for(int j=0; j<MAX_Y; j++) {
			open[i][j] = false;
			closed[i][j] = false;
		}
	}
}

AStar::~AStar() {
}

bool AStar::inLimits(Node y) {

	if(	(y.x >=0 && y.y >= 0) &&
		(y.x < MAX_X && y.y < MAX_Y)) {

		return true;
	} else {
		return false;
	}
}

bool AStar::validPosition(Node n) {

	return (!(n.x == 0 && n.y ==0) 	&& //if it's a neighbor
			inLimits(n) 		&&
			env[n.x][n.y] != OBSTACLE
			);
}


float AStar::distance(Node a, Node b) {

	//return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
	float d = sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
	
	// diagonals are expensive!
	return d; //* (a.x != b.x && b.y != a.y) ? 1.5 : 1; 
	//return (a.x )
}


float AStar::calcG(const Node &current) {

	Node from = came_from[current.x][current.y];
	
	float g_value = g[from.x][from.y];

//	while(current != initialpos) {
//		//our cost to go from one Node to another is always 1
//		//here we're doing a generic implementation of the algorithm
//		//maybe can be optimized later

//		//env[current.x][current.y];
//		g++;
//		current = came_from[current.x][current.y];
//	}
	return g_value;
}

float AStar::calcH(Node x) {

	return distance(x, finalpos);
}

float AStar::calcF(Node x) {

	return calcG(x) + calcH(x);
}

Node AStar::lowestF() {

	
	Node lowest_F_node = *(open_set.begin());
	float lowest_F_value = calcF(lowest_F_node);
	
	NodeList::iterator current = open_set.begin();
	current++;	//start iterating from second element of open_set

	float current_f_value = 0;

	while(current != open_set.end()) {
		printf("oh yah\n");
		current_f_value = calcF(*current);
		if (current_f_value < lowest_F_value) {
			lowest_F_value = current_f_value;
			lowest_F_node = *current;
		}
	}
	
	return lowest_F_node;
}

Node AStar::neighbor(Node x, int i, int j) {

	return Node( (x.x)+i, (x.y)+j );
}

//given a source and a goal node, runs A* algorithm
void AStar::run() {

	bool tentative_is_better;
	float tentative_g;

	//INITIALIZE WITH THE INITIAL NODE
	open_set.insert(initialpos);
	closed[initialpos.x][initialpos.y] = true;
	
	//the distance from the current Node to the start Node is 0
	g[initialpos.x][initialpos.y] = 0;
	h[initialpos.x][initialpos.y] = calcH(initialpos);
	f[initialpos.x][initialpos.y] =
			g[initialpos.x][initialpos.y] +
			h[initialpos.x][initialpos.y];

	while(!(open_set.empty())) {

		//x = the Node in openset having the lowest f value
		Node x = lowestF();

		//if x is the goal node
		if(x == finalpos) {
			printf("ending AStar\n");
			reconstructPath();
		}

		open_set.erase(x);
		open[x.x][x.y] = false;
		
		closed_set.insert(x);
		closed[x.x][x.y] = true;
		
		//foreach neighbor of the Node x
		for(short int i=-1; i<=1; i++) {
			for(short int j=-1; j<=1; j++) {

				Node y = neighbor(x,i,j);

				if(validPosition(y)) {

					//if y belongs to closed_set
					//if (closed_set.find(y) != closed_set.end()) {
					if (closed[y.x][y.y]) {
						continue;
					}

					tentative_g = calcG(x) + distance(x, y);

					//if y doesn't belongs to open_set
					//if(open_set.find(y) == open_set.end()) {
					if (!open[y.x][y.y]) {
						open_set.insert(y);
						open[y.x][y.y] = true;
						
						tentative_is_better = true;
					} else if(tentative_g < calcG(y)) {
						tentative_is_better = true;
					} else {
						tentative_is_better = false;
					}

					if (tentative_is_better) {
						came_from[y.x][y.y] = x;
						g[y.x][y.y] 		= tentative_g;
						h[y.x][y.y] 		= distance(y, finalpos);
						f[y.x][y.y] 		=
									g[y.x][y.y] +
									h[y.x][y.y];
					}
				}
			}
		}
	}
}

void AStar::reconstructPath() {

	Node current = finalpos;

	while(current != initialpos) {
		pathFinal.push_front(current);
		//goto previous node
		current = came_from[current.x][current.y];
	}
	pathFinal.push_front(initialpos);
}
