#ifndef _RRT_CPP_ 
#define _RRT_CPP_ 
 
#include <iostream> 
#include <stdlib.h> 
#include <time.h> 
#include <cmath> 
#include <list> 
 
#include "rrt.h" 
 
using namespace std; 
 

/****************************************************************************************** 
 Pathplan Interface 
 ******************************************************************************************/ 
 
void Rrt::run() 
{
	clockBase = clock();
	
	pathCells.clear();
	path.clear();
	fullPath.clear();
	status = NOTHING;
	
 	initial = initialpos; 
	goal = finalpos; 
	
	tree = rrtPlan(); 

    this->fullPath = tree->treeToVector(); 

	if(status != ERROR_TIMELIMIT) {
		this->pathCells = findSolution();
		
		// convert public Path to MM
		for(unsigned int i=0; i<pathCells.size(); i++) {
			path.push_back( Point(CELLS_TO_MM_X(pathCells[i].getX()),
								CELLS_TO_MM_Y(pathCells[i].getY())) );
		}
		
	}

	// convert public Full Path to MM
	for(unsigned int i=0; i<fullPath.size(); i++) {
		fullPath[i].setXY( CELLS_TO_MM_X(fullPath[i].getX()),
							CELLS_TO_MM_Y(fullPath[i].getY()));
	}

	if(status == SUCCESS)
		elapsedTime = (clock() - clockBase)/(float)CLOCKS_PER_SEC;

//	printPathplan();
}

bool Rrt::validatePath(Point newGoal, int maxvar)
{
	if(getFinalPos().getDistance(newGoal) > maxvar)
		return false;
	else {
		for(unsigned int i=0; i<pathCells.size()-1; i++)
			if( isLineBlocked( pathCells[i], pathCells[i+1]) )
				return false;
	}
	return true;
}
 
/****************************************************************************************** 
 Código baseado no ETDP dos CMDragons de 2009 
 ******************************************************************************************/ 
 
RRTTree* Rrt::rrtPlan() { 
	srand(time(NULL)); //for Extend 

	RRTTree *nearest; 
	Point extended, target; 
 
	RRTTree *nodoInicial;
	nodoInicial = new RRTTree; 
	*nodoInicial = initial; 

	nearest = nodoInicial; 
	tree = nodoInicial; 

	while( distance(nearest->nodo, goal) > 1 ) 
	{
		if( ( (clock() - clockBase)/(float)CLOCKS_PER_SEC ) > timeLimit ) {
				status = ERROR_TIMELIMIT;
				return tree;
		}
		else {
				target = chooseTarget(); 
				nearest = findNearest(target); 
				extended = extend(nearest->nodo, target); 

				if (extended != EMPTY_STATE) 
						addPoint(nearest, extended); 
		}
	} 
 
	//addPoint(nearest, goal); //we add the final poin to the path to help finding the final path on findSolution()
	lastTreePoint = nearest;
 
	return tree; 
} 
 
Point Rrt::chooseTarget() { 
	float p; 
	p = (rand() % 100 + 1) / 100.; 
 
	if (p <= goalProb)  // 0 <= p <= goalProb 
		return goal; 
	else 				 // goalProb < p <= 1 
		return randomState(); 
} 
 
RRTTree* Rrt::findNearest(Point target) { 
	RRTTree *nearest = tree; 
 
    nearestState(tree,target,&nearest); //calcula nodo mais próximo de target 
 
	return nearest; 
} 
 

/****************************************************************************************** 
 Código deduzido do ETDP dos CMDragons de 2009 
 ******************************************************************************************/ 
 
void Rrt::nearestState(RRTTree *tree,Point target,RRTTree **nearest) { 
 
    if (tree->nodo != EMPTY_STATE){ 
 
       Point actual = tree->nodo; 
 
       if (distance(actual,target) < distance((*nearest)->nodo,target)) 
           *nearest = tree; 
 
       for(list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i) 
           nearestState(&(*i),target,nearest); 
    } 
} 
 
float Rrt::distance(Point a, Point b) { 
	return fabs( sqrt(  (float)(  SQR(a.getX() - b.getX()) + SQR(a.getY() - b.getY())  )  )); 
} 
 
Point Rrt::extend(Point nearest, Point target) { 
 
    int step = rand()%stepsize + 1;
 
    int directions[8][2] = { {-step, -step}, {-step, 0},
							 {-step, step}, {0, step},
							 {step, step}, {step, 0},
							 {step, -step}, {0, -step}}; 
    int res = rand() % directionsToLook, i, resIndex[8], tmp, j, min; 
    float distances[8], temp; 
    Point extended; 
 
    for(i = 0; i < 8; i++) { 
        distances[i] = distance(  Point (nearest.getX() + directions[i][0], 
                                         nearest.getY() + directions[i][1]), 
                                target); 
        resIndex[i] = i; 
    } 
 
    //selection sort 
    for(i = 0; i < 8; i++) { 
        min = i; 
        for(j = i + 1; j < 8; j++) 
            if(distances[j] < distances[min]) 
                min = j; 
        if(min != i) { 
            temp = distances[min]; 
            distances[min] = distances[i]; 
            distances[i] = temp; 
 
            tmp = resIndex[min]; 
            resIndex[min] = resIndex[i]; 
            resIndex[i] = tmp; 
        } 
    } 
 
    extended = Point(nearest.getX() + directions[resIndex[res]][0], 
               nearest.getY() + directions[resIndex[res]][1]); 
 
 
 
    if(!collision(nearest, extended)) 
        return extended; 
    else return EMPTY_STATE; 
} 
 
Point Rrt::randomState() { 
    Point randomState; 
 
    randomState.setX( rand() % envMatrixX ); 
    randomState.setY( rand() % envMatrixY ); 
 
	return randomState; 
}

int Rrt::collision(Point nearest, Point extended) { 
    if(extended.getX() >= 0 && extended.getX() < envMatrixX && 
       extended.getY() >= 0 && extended.getY() < envMatrixY) 
 
        return isLineBlocked(nearest, extended); 
        //return env[extended.getX()][extended.getY()] == OBSTACULO; //for stepsize=1
    else 
        return 1; 
} 
 
 
void Rrt::addPoint(RRTTree *nearest, Point extended) { 
    //cout << "AddPoint " << extended << "at " << nearest->nodo << endl; 
 
    RRTTree *extended_Point; 
    extended_Point = new RRTTree; 
    *extended_Point = extended; 
 
    extended_Point->pai = nearest; 
    nearest->filhos.push_back(*extended_Point); //insere extended como filho de nearest 
} 
 
 
void Rrt::findEnding(RRTTree *tree,Point goal,RRTTree **fim) 
{ 
    if (tree->nodo != EMPTY_STATE){ 
        //cout << tree->nodo << " == " << goal << " = " << (tree->nodo == goal) << endl; 
 
        if(tree->nodo == goal) 
            *fim = tree; 
        else 
            for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i) 
                findEnding(&(*i),goal,fim); 
    } 
} 
 
std::vector<Point> Rrt::findSolution() { 
    
    // First we find the last node of the tree, i.e. the goal.
    RRTTree *aux = lastTreePoint; 
    //findEnding(tree,goal,&aux);
    
    // With aux pointing to the last node of the tree, we reconstruct the solution tree by navigating upwards.
    while( aux != NULL ){ 
        pathCells.push_back(aux->nodo); 
        aux = aux->pai; //"Who's your daddy?" - Darth Vader
    } 
	
	if(pathCells.size() > 0)
		status = SUCCESS;
	// If no path was built then the goal wasn't in the tree, which means it wasn't reached at all.
	else 
		status = ERROR_UNKNOWN;
		
    return pathCells; 
} 
 
void RRTTree::treeToVector_recursive(RRTTree *tree,vector<Point>*caminho) 
{ 
    if( tree->nodo != EMPTY_STATE ){ 
        caminho->push_back(tree->nodo); 
 
        for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i) 
			treeToVector_recursive(&(*i),caminho); 
    } 
} 
 
vector<Point> RRTTree::treeToVector() 
{ 
	vector<Point> caminho; 
 
	treeToVector_recursive(this,&caminho); 
 
	return caminho; 
} 
 
 
#endif
