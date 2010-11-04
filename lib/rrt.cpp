#ifndef _RRT_CPP_
#define _RRT_CPP_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include <list>

//#include "matrix/matrix.h"
//#include "point.h"
#include "rrt.h"

using namespace std;


//std::ostream& operator<<(std::ostream &stream,Point param) {
//     return stream << "[" << param.getX() << "," << param.getY() << "] ";
//}

/******************************************************************************************
 Pathplan Interface
 ******************************************************************************************/

void Rrt::run()
{
	Point initial = Point( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	Point goal = Point( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;

    RRTTree *solutionTree;
	solutionTree = RRTPlan(env,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);
	
	//print(solutionTree,initial,goal,pathFinal,env); //print result in console
}

/******************************************************************************************
 Código do ETDP dos CMDragons de 2009
 ******************************************************************************************/

RRTTree* RRTPlan(envType env[][MAX_Y], Point initial, Point goal) {
    int printCont=0;
	RRTTree *nearest;
	Point extended,target;
	RRTTree *tree;

    // dá pra fazer melhor
	RRTTree *nodoInicial; //aloca raiz
	nodoInicial = new RRTTree;
	*nodoInicial = initial;


	srand(time(NULL)); //for Extend


	nearest = nodoInicial;
	tree = nodoInicial;

	while( Distance(nearest->nodo, goal) > THRESHOLD ){

        if(STEP_BY_STEP){ //impressão passo a passo p/ debug
            if(printCont==STEPS_DELAY){
               list<Point> null;
               print(tree,initial,goal,null,env);
               printCont=0;
               //getchar();
            }
            else
                printCont++;
        }


		target = ChooseTarget(goal);
		nearest = Nearest(tree, target);
		extended = Extend(env, nearest->nodo, target);

		if (extended != EMPTY_STATE)
			AddNode(nearest, extended);
	}

	AddNode(nearest, goal);


	return tree;
}

Point ChooseTarget(Point goal) {
	float p;
	p = (rand() % 100 + 1) / 100.0;

	if (p <= GOAL_PROB)  // 0 <= p <= goalProb
		return goal;
	else 				 // goalProb < p <= 1
		return RandomState();
}

RRTTree* Nearest(RRTTree *tree, Point target) {
	RRTTree *nearest = tree;

    nearestState(tree,target,&nearest); //calcula nodo mais próximo de target

	return nearest;
}

/******************************************************************************************
 Código deduzido do ETDP dos CMDragons de 2009
 ******************************************************************************************/

void nearestState(RRTTree *tree,Point target,RRTTree **nearest) {

    if (tree->nodo != EMPTY_STATE){

       Point actual = tree->nodo;

       //cout << "actual:" << actual << endl;
       //cout << "nearest->nodo:" << nearest->nodo << endl;
       //cout << Distance(actual,target) << " < " << Distance(nearest->nodo,target) << endl;

       if (Distance(actual,target) < Distance((*nearest)->nodo,target))
           *nearest = tree;

       for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i)
           nearestState(&(*i),target,nearest);
    }
}

float Distance(Point a, Point b) {
	return fabs( sqrt(  (float)(  SQR(a.getX() - b.getX()) + SQR(a.getY() - b.getY())  )  ));
}

Point Extend(envType env[][MAX_Y], Point nearest, Point target) {

    int step = rand()%MAX_STEPSIZE + 1;

    int directions[8][2] = {{-step, -step}, {-step, 0}, {-step, step}, {0, -step}, {0, 0}, {step, -step}, {step, 0}, {step, step}};
    int res = rand() % DIRECTIONS_TO_LOOK, i, resIndex[8], tmp, j, min;
    float distances[8], temp;
    Point extended;

    for(i = 0; i < 8; i++) {
        distances[i] = Distance(  Point (nearest.getX() + directions[i][0],
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

    extended =    Point(nearest.getX() + directions[resIndex[res]][0],
                        nearest.getY() + directions[resIndex[res]][1]);



    if(!Collision(env, nearest, extended))
        return extended;
    else return EMPTY_STATE;
}

Point RandomState() {
    Point randomState;

    randomState.setX( rand() % MAX_X );
    randomState.setY( rand() % MAX_Y );

	return randomState;
}


 int bresenham(envType env[][MAX_Y], Point stat1, Point stat2){ //retorna 0 se consegue traçar linha entre os dois pontos
       int x1 = stat1.getX();
       int x2 = stat2.getX();
       int y1 = stat1.getY();
       int y2 = stat2.getY();

       int slope;
       int dx, dy, incE, incNE, d, x, y;
       // Onde inverte a linha x1 > x2
       if (x1 > x2){
           return bresenham(env, stat2, stat1);
       }

       if(x1 == x2){ //reta é paralela com eixo y
            if(y1 < y2)
                for(y = y1; y <= y2; y++)
                    if (env[x1][y] == OBSTACLE) //(x,y) é um ponto da linha ajustado à matriz
                        return 1;
            else
                for(y = y2; y <= y1; y++)
                    if (env[x1][y] == OBSTACLE) //(x,y) é um ponto da linha ajustado à matriz
                        return 1;
            return 0;
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
 }
int Collision(envType env[][MAX_Y], Point nearest, Point extended) {
    if(extended.getX() >= 0 && extended.getX() < MAX_X &&
       extended.getY() >= 0 && extended.getY() < MAX_Y)

        return bresenham(env, nearest, extended);
        //return env[extended.getX()][extended.getY()] == OBSTACULO;
    else
        return 1;
}


void AddNode(RRTTree *nearest, Point extended) {

    //cout << "AddNode " << extended << "at " << nearest->nodo << endl;

    RRTTree *extended_node;
    extended_node = new RRTTree;
    *extended_node = extended;

    extended_node->pai = nearest;
    nearest->filhos.push_back(*extended_node); //insere extended como filho de nearest
}




void encontraFim(RRTTree *tree,Point goal,RRTTree **fim)
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

std::list<Point> RRTTree::findSolucao(Point goal) {
    std::list<Point> caminho;

    RRTTree *aux;
    encontraFim(this,goal,&aux);

    while( aux != NULL ){
        caminho.push_back(aux->nodo);
        aux = aux->pai;
    }

    return caminho;
}

void RRTTree::treeToList_recursive(RRTTree *tree,list<Point>*caminho)
{
    if (tree->nodo != EMPTY_STATE){

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




/******************************************************************************************
 Código para testes
 ******************************************************************************************/

void printVarreTree(RRTTree *tree,int matrizPrint[][MAX_Y])
{
    if (tree->nodo != EMPTY_STATE){

        matrizPrint[(int)tree->nodo.getX()][(int)tree->nodo.getY()] = NODE;

        for(std::list<RRTTree>::iterator i=tree->filhos.begin(); i != tree->filhos.end(); ++i)
            printVarreTree(&(*i),matrizPrint);
    }
}
void print(RRTTree *tree,Point initial,Point goal,list<Point> caminho,envType env[][MAX_Y])
{
    system("cls");

    int matrizPrint[MAX_X][MAX_Y];

    //copia environment para matriz temporária de impressão
    for(int i=0;i<MAX_X;i++)
        for(int j=0;j<MAX_Y;j++)
            matrizPrint[i][j] = env[i][j];

    //preenche matriz com nodos da árvore
    printVarreTree(tree,matrizPrint);

    //marca caminho-solução
    for(std::list<Point>::iterator i=caminho.begin(); i != caminho.end(); ++i)
        matrizPrint[(int)i->getX()][(int)i->getY()] = PATH;

    //marcadores de ponto inicial e ponto final
    matrizPrint[(int)initial.getX()][(int)initial.getY()] = MARKER;
    matrizPrint[(int)goal.getX()][(int)goal.getY()] = MARKER;

    //imprime!
    for(int i=MAX_Y-1;i>=0;i--){
        for(int k=0;k<MAX_X;k++)
            switch (matrizPrint[k][i]){
                case FREE:
                    cout << " ";
                    break;
                case MARKER:
                    cout << "X";
                    break;
                case OBSTACLE:
                    cout << "#";
                    break;
                case NODE:
                    cout << ".";
                    break;
                case PATH:
                    cout << "o";
                    break;
            }
        cout << endl;
    }
}


#endif

