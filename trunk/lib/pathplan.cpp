#include<iostream>

#include "pathplan.h"


using namespace std;

double DISTANCE(int num1, int num2)
{
    int num1x = REVERSE_INDEX_X(num1), num1y = REVERSE_INDEX_Y(num1); 
    int num2x = REVERSE_INDEX_X(num2), num2y = REVERSE_INDEX_Y(num2);

    return (double) sqrt(((num1x - num2x) * (num1x - num2x)) + ((num1y - num2y) * (num1y - num2y)));
}

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
	//this is the interface for Cristiano's RRT implementation
	
	
	
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;
	
    RRTTree *solutionTree;
	solutionTree = RRTPlan(env,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);


	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
}



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

bool Pathplan::aStar(int start, int goal)
{
	//conferir A* na wikipedia
	
	Closed.clear();
	Open.clear();
	Open.insert(start);

    //cost[INDEX(6,6)] = 1000; //valor 1000 é um obstáculo

	//cada um desses vetores tem o tamanho igual ao número de posições da matriz, ou seja, MAX_Y * MAX_X
	g_score[start] = 0;
	h_score[start] = DISTANCE(start, goal); //h_score: heurística (aproximação)
											//DISTANCE: retorna a distância entre os dois pontos;
											//utiliza a equação de distância entre dois pontos
											//dist = ((x-x0)²+(y-y0)²)^(1/2)
	f_score[start] = h_score[start]; //f_score: soma de g_score com h_score

	for(int i=0; i<MAX_X * MAX_Y; i++)
	    h_score[i] = DISTANCE(i, goal); //calcula a distância de todas as posições da matriz até o destino (goal)

	while(!Open.empty())
	{
        ASet::iterator a = Open.begin(); //begin() retorna 
		if( *a/*a->getElement()*/ == goal)
		     return true;

        int element = *a;//a->getElement();  //element é o elemento do início do iterador 'a'
		//use env[x][y]
		//field[element].setClosed(); //field[element] fica fechado pois é o início do caminho até o destino, 
									//logo ele vai fazer parte do caminho final 
		Closed.insert(*a); //insere a coordenada de início do caminho até o destino
		Open.erase(*a); //essa coordenada agora não está mais aberta, pois foi analisada

		for(int i = RIGHT; i < NUM_NEIGHBORS; i++) //i=0; i < 8; i++
		{
           //use env[x][y]
           //int neighbor = element + corners[i]; //vizinho da posição 'element'

		   //testa se o vizinho está dentro da grid ainda, pois ele pode estar fora. No caso de estar fora da 
		   //grid esse vizinho é uma posição inválida	
		   if( (IS_BOTTOM_BORDER(element) && (i == DOWN || i == LEFT_DOWN || i == RIGHT_DOWN)) ||
		       (IS_UPPER_BORDER(element) && (i == UP || i == LEFT_UP || i == RIGHT_UP)) ||
		       (IS_RIGHT_BORDER(element) && (i == RIGHT || i == RIGHT_UP || i == RIGHT_DOWN)) ||
		       (IS_LEFT_BORDER(element) && (i == LEFT || i == LEFT_UP || i == LEFT_DOWN)) )
		      continue;

		   bool podePassar = true;
           if(i>=RIGHT_DOWN) //i>=4
               for(int j=RIGHT; j<RIGHT_DOWN; j++) //j=0; j<4; j++
                   if(cost[element + corners[j]] == 1000) 
                   { //se o vizinho (element+corners[j]) tiver um obstáculo, não pode passar
                       podePassar = false;
                       break;
                   }

           if(!podePassar)
              continue; //termina a iteração vigente do for e começa outra

		   if(field[neighbor].isClosed())
		      continue; //se o vizinho está fechado, ou seja, já foi visitado e colocado no PAR, 
						//então não pode continuar e termina a execução da atual iteração do for, começando uma nova

		   double tentative_g_score = g_score[element] + DISTANCE(element, neighbor);
		   //cout << "g_score[element] = " << g_score[element] << endl;
		   //cout << "i = " << i << ", tentative_g_score = " << tentative_g_score << "\n";
		   //getchar();
		   
		   bool tentative_is_better = false;

		   if(field[neighbor].isNew())
		   {
		       field[neighbor].setOpen(); //se o vizinho for novo, então deixa ele disponível para ser analisado, 
										  //como a operação membro 'setOpen()'
		       tentative_is_better = true; 
		   }
		   else if(tentative_g_score < g_score[neighbor]) 
		       tentative_is_better = true;

		   if(tentative_is_better) //se a posição for a melhor, então ela é armazenada
								   //no vetor backpointer
		   {
		       setBackpointer(neighbor, element); //neighbor é o índice de uma posição do campo no vetor backpointer
		       g_score[neighbor] = tentative_g_score;
		       f_score[neighbor] = g_score[neighbor] + h_score[neighbor] + cost[neighbor];
		       Open.insert(Par(neighbor, f_score[neighbor]));
		   }
		}
	}
	return false;
}

