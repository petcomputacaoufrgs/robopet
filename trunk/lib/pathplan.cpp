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

/*
void Pathplan::runRRT()
{
	//this is the interface for Cristiano's RRT implementation
	
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;
	
    RRTTree *solutionTree;
	solutionTree = RRTPlan(env,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);

	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
}
*/

void Pathplan::runPathplan( int pathplanIndex )
{
	switch(pathplanIndex){

		case PATHPLAN_RRT:
			runRRT();
			break;


		case PATHPLAN_ASTAR:
			break;
	}
}

bool Pathplan::aStar(RP::Point start, RP::Point goal)
{
	using RP::Point;

	Closed.clear();
	Open.clear();
	Open.insert( make_pair(start,0) );

    //cost[INDEX(6,6)] = 1000; //valor 1000 é um obstáculo

	//cada um desses vetores tem o tamanho igual ao número de posições da matriz, ou seja, MAX_Y * MAX_X

	int x = start.getX(), y = start.getY();
	g_score[x][y] = 0;
	h_score[x][y] = start.getDistance(goal); //h_score: heurística (aproximação)
											//DISTANCE: retorna a distância entre os dois pontos;
											//utiliza a equação de distância entre dois pontos
											//dist = ((x-x0)²+(y-y0)²)^(1/2)
	f_score[x][y] = h_score[x][y]; //f_score: soma de g_score com h_score

	
	for(int i = 0; i < MAX_X; i++)
		for(int j = 0; j < MAX_Y; j++)
		{
			Point aux(i,j);	
			h_score[i][j] = aux.getDistance(goal); //calcula a distância de todas as posições da matriz até o destino (goal)
		}

	while(!Open.empty())
	{
        ASet::iterator a = Open.begin(); //begin() retorna 
		Point p = a->first;
		
		if( p == goal)
		     return true;
		
		int i = p.getX(),j = p.getY();
		
        //já olhamos o ponto element, logo ele é fechado
		env[i][j].setClosed();
									
		Closed.insert(*a); //insere a coordenada de início do caminho até o destino
		Open.erase(*a); //essa coordenada agora não está mais aberta, pois foi analisada

		
		//RIGHT, LEFT, DOWN, UP, RIGHT_DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN
		Point corners[] = { Point(1,0), Point(-1,0), Point(0,1), 
							Point(0,-1), Point(1,1), Point(-1,-1),
							Point(1,-1), Point(-1,1) 				}

		for (int i = 0; i < NUM_NEIGHBORS; i++) //i=0; i < 8; i++
		{
           //use env[x][y]
           //int neighbor = element + corners[i]; //vizinho da posição 'element'
		   Point neighbor = p + corners[i];
		   
		   //testa se o vizinho está dentro da grid ainda, pois ele pode estar fora. No caso de estar fora da 
		   //grid esse vizinho é uma posição inválida	
		   //teste aqui
		   
		   bool podePassar = true;
           if(i >= RIGHT_DOWN) //i>=4
               for(int j = RIGHT; j < RIGHT_DOWN; j++) //j=0; j<4; j++
                   if(cost[element + corners[j]] == 1000) 
                   { //se o vizinho (element+corners[j]) tiver um obstáculo, não pode passar
                       podePassar = false;
                       break;
                   }

           if(!podePassar)
              continue; //termina a iteração vigente do for e começa outra

		   if( env[neighbor.getX()][neighbor.getY()].isClosed() )
		      continue; //se o vizinho está fechado, ou seja, já foi visitado e colocado no PAR, 
						//então não pode continuar e termina a execução da atual iteração do for, começando uma nova

		   double tentative_g_score = g_score[p.getX()][p.getY()] + p.getDistance(neighbor);
		   
		   bool tentative_is_better = false;

		   if(env[neighbor.getX()][neighbor.getY()].isNew())
		   {
		       env[neighbor.getX()][neighbor.getY()].setOpen(); 
										  //se o vizinho for novo, então deixa ele disponível para ser analisado, 
										  //como a operação membro 'setOpen()'
		       tentative_is_better = true; 
		   }
		   else if(tentative_g_score < g_score[neighbor.getX()][neighbor.getY()]) 
		       tentative_is_better = true;

		   if(tentative_is_better) //se a posição for a melhor, então ela é armazenada
		   {   					   //no vetor backpointer
		       setBackpointer(neighbor, element); //neighbor é o índice de uma posição do campo no vetor backpointer
		       g_score[neighbor.getX()][neighbor.getY()] = tentative_g_score;
		       f_score[neighbor.getX()][neighbor.getY()] = g_score[neighbor.getX()][neighbor.getY()] + 
														   h_score[neighbor.getX()][neighbor.getY()] + 
														   cost[neighbor.getX()][neighbor.getY()];
		       Open.insert(Par(neighbor, f_score[neighbor]));
		   }
		}
	}
	return false;
}

