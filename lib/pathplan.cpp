#include<iostream>

#include "pathplan.h"


using namespace std;

Pathplan::Pathplan()
{
	
}


Pathplan::Pathplan(Point initialpos, Point finalpos)
{
	this->initialpos = initialpos;
	this->finalpos = finalpos;
}

Pathplan::~Pathplan() {};


void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{	
	const int lado = MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;


	for(int i=0; i<lado; i++)
        for(int k=0; k<lado; k++)
            env [x+i - lado/2][y+k - lado/2] = OBSTACULO;

}


void Pathplan::fillEnv(vector<Point> playersPositions)
{
	int centerx, centery;
	int nSafetyCells = 4;

	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
			env[i][j] = LIVRE;

	vector<Point>::iterator it;
	for(it=playersPositions.begin(); it<playersPositions.end(); it++)
	{
		centerx = (int)MM_TO_CELLS((*it).getX());
		centery = (int)MM_TO_CELLS((*it).getY());
		fillEnv_playerBox(centerx,centery,nSafetyCells);
	}

}


Point Pathplan::getPathNode(int nodeIndex)
{
	list<state>::iterator it;
	for( it=pathFinal.begin(); nodeIndex>0; it++ )
		nodeIndex--;
	
	return *it;
}


void Pathplan::runRRT()
{
	#if 0
	//this is the interface for Cristiano's RRT implementation
	
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;
	
    RRTTree *solutionTree;
	solutionTree = RRTPlan(env,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);

	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
	#endif
}


void Pathplan::runPathplan( int pathplanIndex )
{
	switch(pathplanIndex)
	{
		case PATHPLAN_RRT:
			runRRT();
			break;

		case PATHPLAN_ASTAR:
			break;
	}
}

bool Pathplan::aStar(RP::Point start, RP::Point goal)
{

#if 0
	using RP::Point;

	//'Close' and 'Open' are ASet objects. Each of its terms has a point and a double variable
	Closed.clear(); 
	Open.clear();
	Open.insert( make_pair(start,0) );

    //an obstacle has the value 1000. E.g. cost[x][y] = 1000; 

	//h_score: heuristics (a guess about the distance from a square to the goal) - this heuristics calculates the distance between two squares (points) on the environment matrix using euclidean distance [sqrt((x-x0)²+(y-y0)²)]
	//g_score: cost to go from a parent square to a son square	
	//f_score: h_score + g_score

	int x = start.getX();
	int y = start.getY();
	g_score[x][y] = 0;
	h_score[x][y] = start.getDistance(goal); 
	f_score[x][y] = g_score[x][y] + h_score[x][y]; 
	
	//Sets the distance from each square of environment matriz to the goal square 
	for(int i = 0; i < MAX_X; i++)
		for(int j = 0; j < MAX_Y; j++)
		{
			Point aux(i,j);	
			h_score[i][j] = aux.getDistance(goal); 
		}

	//RIGHT, LEFT, DOWN, UP, RIGHT_DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN
	Point corners[] = { Point(1,0), Point(-1,0), Point(0,1), 
						Point(0,-1), Point(1,1), Point(-1,-1),
						Point(1,-1), Point(-1,1) };

	while(!Open.empty())
	{
        ASet::iterator a = Open.begin(); //the iterator points to the first item in the set 'Open'
		Point p = a->first; //the point p now has the first element of the pair pointed by the a iterator
		
		if( p == goal)
		     return true; //the goal has been reached, finishes AStar algorithm
		
		//we analized the point p. It has to be set as closed, should be placed in the 'Closed' set and erased from the 'Open' one
		env[(int)p.getX()][(int)p.getY()].setClosed();
		Closed.insert(*a); 
		Open.erase(*a); 

		for(int i = 0; i < 8; i++) //8 == number of neighbors
		{
			Point neighbor = p + corners[i];
		   
		    /*---- Test the validity of the neighbors here!! ----*/
		   
		   	if(env[(int)neighbor.getX()][(int)neighbor.getY()].isClosed())
		      	continue; //goes to another iteration in the loop 'for'

		   	bool podePassar = true;
           	if(i >= 4) //4 because only RIGHT, LEFT, UP and DOWN are tested. The diagonals aren't because the robots won't move in this ways
               	for(int j = 0; j < 4; j++)
                   	if(cost[element + corners[j]] == 1000) 
                   	{ //se o vizinho (element+corners[j]) tiver um obstáculo, não pode passar
                    	podePassar = false;
                       	break;
                   	}

           	if(!podePassar)
              	continue; //termina a iteração vigente do for e começa outra  

		   	double tentative_g_score = g_score[(int)p.getX()][(int)p.getY()] + p.getDistance(neighbor);
		   	bool tentative_is_better = false;

		   	if(env[(int)neighbor.getX()][(int)neighbor.getY()].isNew())
		   	{
		       env[(int)neighbor.getX()][(int)neighbor.getY()].setOpen(); 
		       tentative_is_better = true; 
		   	}
		   	else if(tentative_g_score < g_score[(int)neighbor.getX()][(int)neighbor.getY()]) 
		       tentative_is_better = true;

		   	if(tentative_is_better) //se a posição for a melhor, então ela é armazenada
		   	{   					   //no vetor backpointer
		       setBackpointer(neighbor, element); //neighbor é o índice de uma posição do campo no 	vetor backpointer
			   int x = neighbor.getX();
			   int y = neighbor.getY();
		       g_score[x][y] = tentative_g_score;
		       f_score[x][y] = g_score[x][y] + h_score[x][y] + cost[x][y];
		       Open.insert(Par(neighbor, f_score[neighbor]));
		   	}
		}
	}
#endif
	return false;
}

