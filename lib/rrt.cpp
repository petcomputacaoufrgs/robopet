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
 
	initial = initialpos; 
	goal = finalpos; 
	
	tree = rrtPlan(); 
 
    this->pathFull = tree->treeToList(); 
	this->pathFinal = findSolution(); 
 
//	printPathplan();
} 
 
/****************************************************************************************** 
 Código do ETDP dos CMDragons de 2009 
 ******************************************************************************************/ 
 
RRTTree* Rrt::rrtPlan() { 
	srand(time(NULL)); //for Extend 

	time_t _timeStarted = time(0);

	RRTTree *nearest; 
	Point extended, target; 
 
	RRTTree *nodoInicial;
	nodoInicial = new RRTTree; 
	*nodoInicial = initial; 

	nearest = nodoInicial; 
	tree = nodoInicial; 
 
	while( distance(nearest->nodo, goal) > stepsize ) 
	{
			if( ( time(0) - _timeStarted ) > timeLimit ) {
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
 
	//We add the final poin to the path to help finding the final path on findSolution()
	addPoint(nearest, goal); 
 
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
 
    int directions[8][2] = {{-step, -step}, {-step, 0}, {-step, step}, {0, -step}, {0, 0}, {step, -step}, {step, 0}, {step, step}}; 
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
 
 
int Rrt::bresenham(Point stat1, Point stat2)
// retorna 0 se consegue traçar linha entre os dois pontos 
// útil para fazer um passo maior que uma unidade de celula.
{      
		int x1 = stat1.getX(); 
		int x2 = stat2.getX(); 
		int y1 = stat1.getY(); 
		int y2 = stat2.getY(); 

		int slope; 
		int dx, dy, incE, incNE, d, x, y; 
		// Onde inverte a linha x1 > x2 
		if (x1 > x2){ 
				return bresenham(stat2, stat1); 
		} 
 
       if(x1 == x2){ //reta é paralela com eixo y 
            if(y1 < y2) { 
                for(y = y1; y <= y2; y++) 
                    if (env[x1][y] == OBSTACLE) //(x,y) é um ponto da linha ajustado à matriz 
                        return 1;
			} 
            else 
                for(y = y2; y <= y1; y++) 
                    if (env[x1][y] == OBSTACLE) //(x,y) é um ponto da linha ajustado à matriz 
                        return 1; 
       } 
       else{ 
               dx = x2 - x1; 
               dy = y2 - y1; 
 
               if (dy < 0){ 
                   slope = -1; 
                   dy = -dy; 
               } 
               else{ 
                  slope = 1; 
               } 
               // Constante de Bresenham 
               incE = 2 * dy; 
               incNE = 2 * dy - 2 * dx; 
               d = 2 * dy - dx; 
               y = y1; 
               for (x = x1; x <= x2; x++){ 
                   if (env[x][y] == OBSTACLE) //(x,y) é um ponto da linha ajustado à matriz 
                      return 1; 
 
                   if (d <= 0){ 
                     d += incE; 
                   } 
                   else{ 
                     d += incNE; 
                     y += slope; 
                   } 
               } 
 
               return 0; 
       } 
       
       return 0;
 } 

int Rrt::collision(Point nearest, Point extended) { 
    if(extended.getX() >= 0 && extended.getX() < envMatrixX && 
       extended.getY() >= 0 && extended.getY() < envMatrixY) 
 
        return bresenham(nearest, extended); 
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
 
 
void Rrt::encontraFim(RRTTree *tree,Point goal,RRTTree **fim) 
{ 
    if (tree->nodo != EMPTY_STATE){ 
        //cout << tree->nodo << " == " << goal << " = " << (tree->nodo == goal) << endl; 
 
        if(tree->nodo == goal) 
            *fim = tree; 
        else 
            for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i) 
                encontraFim(&(*i),goal,fim); 
    } 
} 
 
std::list<Point> Rrt::findSolution() { 
    std::list<Point> caminho; 
 
    RRTTree *aux = NULL; 
    encontraFim(tree,goal,&aux); 
 
    while( aux != NULL ){ 
        caminho.push_back(aux->nodo); 
        aux = aux->pai; 
    } 
 
	if(caminho.size() > 0)
		status = SUCCESS;
	else
		status = ERROR_UNKNOWN;
    return caminho; 
} 
 
void RRTTree::treeToList_recursive(RRTTree *tree,list<Point>*caminho) 
{ 
    if( tree->nodo != EMPTY_STATE ){ 
        caminho->push_back(tree->nodo); 
 
        for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i) 
			treeToList_recursive(&(*i),caminho); 
    } 
} 
 
list<Point> RRTTree::treeToList() 
{ 
	std::list<Point> caminho; 
 
	treeToList_recursive(this,&caminho); 
 
	return caminho; 
} 
 
 
#endif
