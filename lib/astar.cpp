#include "astar.h"

AStar::AStar() {
	//initialize();
}

AStar::AStar(Node start, Node goal) : Pathplan(start, goal){
	//initialize();
}

void AStar::initialize() {
	//itializing came_from matrix
//	for(int i=0; i<MAX_X; i++) {
//		for(int j=0; j<MAX_Y; j++) {
//			came_from[i][j].setX(-1);
//			came_from[i][j].setY(-1);
//		}
//	}
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

	float delta_x = a.x - b.x;
	float delta_y = a.y - b.y;

	//if the nodes are in the same column
	if (delta_x == 0)
		return delta_y;
	//else, if the nodes are in the same row
	else if (delta_y == 0)
		return delta_x;
	//otherwise
	else
		return sqrt(delta_x*delta_x + delta_y*delta_y);

	//return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
    //float d = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) ;

    // diagonals are expensive!
    // but this doesnt make much sense
    //return d* (a.x != b.x && b.y != a.y) ? 1.4 : 1;

}


float AStar::calcG(Node n) {

	Node from = came_from[n.x][n.y];

	return g[from.x][from.y];

//	while(current != initialpos) {
//		//our cost to go from one Node to another is always 1
//		//here we're doing a generic implementation of the algorithm
//		//maybe can be optimized later

//		//env[current.x][current.y];
//		g++;
//		current = came_from[current.x][current.y];
//	}
//	return g_value;
}

float AStar::calcH(Node x) {

	return distance(x, finalpos);
}

float AStar::calcF(Node x) {

	return calcG(x) + calcH(x);
}

Node AStar::lowestF() {

	float lowest_F_value = calcF(*(open_set.begin()));
	Node lowest_F_node = *(open_set.begin());

	set<Node>::iterator current = open_set.begin();
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

Node AStar::neighbor(Node n, int i, int j) {

	return Node( (n.x)+i, (n.y)+j );
}

//given a source and a goal node, runs A* algorithm
void AStar::run() {

	bool tentative_is_better;
	float tentative_g;

	//INITIALIZE WITH THE INITIAL NODE
	open_set.insert(initialpos);

	//the distance from the current Node to the start Node is 0
	g[initialpos.x][initialpos.y] = 0;
	h[initialpos.x][initialpos.y] = calcH(initialpos);
	f[initialpos.x][initialpos.y] =
			g[initialpos.x][initialpos.y] +
			h[initialpos.x][initialpos.y];

	while(!(open_set.empty())) {

		//current_node = the Node in openset having the lowest f value
		Node current_node = lowestF();

		//if current_node is the goal node
		if(current_node == finalpos) {
			printf("ending AStar\n");
			reconstructPath();
		}

		open_set.erase(current_node);
		closed_set.insert(current_node);

		//foreach neighbor of the Node current_node
		for(short int i=-1; i<=1; i++) {
			for(short int j=-1; j<=1; j++) {

				Node current_neighbor = neighbor(current_node,i,j);

				if(validPosition(current_neighbor)) {

					//if current_neighbor belongs to closed_set
					if (closed_set.find(current_neighbor) != closed_set.end()) {
						continue;
					}

					tentative_g = calcG(current_node) +
								//if the nodes are in diagonal, we sum 1.4. Otherwise, 1.
								(	current_node.x == current_neighbor.x ||
									current_node.y == current_neighbor.y) ? 1 : 1.4;

					//if current_neighbor doesn't belongs to open_set
					if(open_set.find(current_neighbor) == open_set.end()) {
						open_set.insert(current_neighbor);
						tentative_is_better = true;
					} else if(tentative_g < calcG(current_neighbor)) {
						tentative_is_better = true;
					} else {
						tentative_is_better = false;
					}

					if (tentative_is_better) {
						came_from[current_neighbor.x][current_neighbor.y] 	= current_node;
						g[current_neighbor.x][current_neighbor.y]			= tentative_g;
						h[current_neighbor.x][current_neighbor.y] 			= distance(current_neighbor, finalpos);
						f[current_neighbor.x][current_neighbor.y] 			=
																		g[current_neighbor.x][current_neighbor.y] +
																		h[current_neighbor.x][current_neighbor.y];
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
