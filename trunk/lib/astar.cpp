#include "astar.h"
#include "utils.h"

AStar::AStar() {
			
	
	nodeinitialpos.setX(initialpos.getX());
	nodeinitialpos.setY(initialpos.getY());
	
	nodefinalpos.setX(finalpos.getX());
	nodefinalpos.setY(finalpos.getY());
	
	initialize();
}
/*
AStar::AStar(Node start, Node goal) : DiscretePathplan(Point(start.x,start.y), Point(goal.x,goal.y)){
	initialize();
}*/

void AStar::initialize() {
	
	came_from = (Node**) allocMatrix( envMatrixX,envMatrixY,sizeof(Node) );
	closed = (bool**) allocMatrix( envMatrixX,envMatrixY,sizeof(bool) );
	open = (bool**) allocMatrix( envMatrixX,envMatrixY,sizeof(bool) );
	g = (float**) allocMatrix( envMatrixX,envMatrixY,sizeof(float) );
	h = (float**) allocMatrix( envMatrixX,envMatrixY,sizeof(float) );
	f = (float**) allocMatrix( envMatrixX,envMatrixY,sizeof(float) );
}

AStar::~AStar() {
}

bool AStar::inLimits(Node y) {

	if(	(y.x >=0 && y.y >= 0) &&
		(y.x < envMatrixX && y.y < envMatrixY)) {

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
	return distance(x, nodefinalpos); //?
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
	open_set.insert(nodeinitialpos);

	//the distance from the current Node to the start Node is 0
	g[nodeinitialpos.x][nodeinitialpos.y] = 0;
	h[nodeinitialpos.x][nodeinitialpos.y] = calcH(nodeinitialpos);
	f[nodeinitialpos.x][nodeinitialpos.y] =
			g[nodeinitialpos.x][nodeinitialpos.y] +
			h[nodeinitialpos.x][nodeinitialpos.y];

	while(!(open_set.empty())) {

		//current_node = the Node in openset having the lowest f value
		Node current_node = lowestF();

		//if current_node is the goal node
		if(current_node == nodefinalpos) {
			//printf("ending AStar\n");
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
						h[current_neighbor.x][current_neighbor.y] 			= distance(current_neighbor, nodefinalpos);
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

	Node current = nodefinalpos;
	Point a;
	
	a.setXY(current.getX(), current.getY());
	
	while(current != nodeinitialpos) {
		path.push_back(a);
		//goto previous node
		current = came_from[current.x][current.y];
		a.setXY(current.getX(), current.getY());
	}
	path.push_back(a);
	
	for (int i=0 ; i < path.size()/2 ; i++)
	{
		a=path[i];
		path[i] = path[path.size()-i];
		path[path.size()-i] = a;
	}
	
}
