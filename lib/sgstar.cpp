#include "sgstar.h"

SGStar::SGStar() {}

SGStar::~SGStar() {}

void SGStar::run()
{	
	clockBase = clock();
	//cout << "SUPER G*" << endl;
	
	//insere initialpos no vetor
	Vertex init;
	init.dist = 0;
	init.previous = 0;
	init.point = initialpos;
	vetVertexs.push_back(init);
	
	//inicializa vetor de vertices
	initVertexs();
	
	numFinals = 0;
	
	if (isBlocked(finalpos))
	{
		aprocimateFinals();
	}
	else {
		Vertex fim; //insere finalpos no vetor
		fim.dist = INFINITY;
		fim.previous = -1;
		fim.point = finalpos;
		vetVertexs.push_back(fim);
		
		numFinals = 1;
	}
	
	//cria lista de adjacentes
	createAdjList();
		
	int v = 0; //vertice
	double distAux = 0;
	multimap<double, int> prioriQ;
	multimap<double, int>::iterator it;
		
	do //Dijkstra
	{		
		for (it=vetVertexs[v].vertsAdj.begin(); it!=vetVertexs[v].vertsAdj.end(); it++) {

			distAux = vetVertexs[v].dist + it->first;
			
			if (distAux < vetVertexs[it->second].dist) {
				vetVertexs[it->second].dist = distAux;
				vetVertexs[it->second].previous = v;
				prioriQ.insert(pair<double, int>(distAux, it->second));
			}
		}
			
		v = prioriQ.begin()->second;
		prioriQ.erase(prioriQ.begin()); //pega o próximo vértices da fila
	}
	while (!prioriQ.empty());
	
	buildPath(); //se conseguiu chegar em algum final
			
	status = SUCCESS;
	elapsedTime = (clock() - clockBase)/(float)CLOCKS_PER_SEC;
	
	vetVertexs.clear();
}

void SGStar::aprocimateFinals()
{	
	double cosxLimIsBlocked[8] = {LIMIT_IS_BLOCKED, .525322*LIMIT_IS_BLOCKED, -.448074*LIMIT_IS_BLOCKED, -.996088*LIMIT_IS_BLOCKED, -.59846*LIMIT_IS_BLOCKED, .367319*LIMIT_IS_BLOCKED, .984382*LIMIT_IS_BLOCKED, .666916*LIMIT_IS_BLOCKED };
	double simxLimIsBlocked[8] = {.0, .850904*LIMIT_IS_BLOCKED, .893997*LIMIT_IS_BLOCKED, .0883687*LIMIT_IS_BLOCKED, -.801153*LIMIT_IS_BLOCKED, -.930095*LIMIT_IS_BLOCKED, -.176046*LIMIT_IS_BLOCKED, .745133*LIMIT_IS_BLOCKED };
	
	double centerX = finalpos.getX();
	double centerY = finalpos.getY();
	Vertex aux;
		
	for (int j=0; j<8; j++) {
		aux.point.setX(centerX+cosxLimIsBlocked[j]);
		aux.point.setY(centerY+simxLimIsBlocked[j]);
	
		if (!isBlocked(aux.point)) {
			aux.dist = INFINITY;
			aux.previous = -1;					
			vetVertexs.push_back(aux);
			
			numFinals++;
		}
	}
}

// incializa vetor de vertices
void SGStar::initVertexs()
{
	Vertex aux;
	Point points[4];
	
	for (unsigned int i=0; i<obstacles.size(); i++) {
		// cria os 4 pontos do obstáculo
		makePoints(obstacles[i].pos, points);
		
		// insere os 4 pontos do obstaculo no vetor de vertices
		for (int j=0; j<4; j++) {
			if (!isBlocked(points[j])) {
				aux.dist=INFINITY;
				aux.previous = -1;
				aux.point = points[j];
				vetVertexs.push_back(aux);
			}
		}
	}
}


//cria as listas de vertices adjacentes para cada ponto
void SGStar::createAdjList()
{
	bool chegaFim=false;
	
	for (unsigned int i=0; i<vetVertexs.size() - numFinals; i++)
	 {
		//check if can go direct to one final point
		for (int j = vetVertexs.size() - numFinals; j < vetVertexs.size(); j++)
		{
			if (!straightIsBlocked(vetVertexs[i].point, vetVertexs[j].point)) {
				vetVertexs[i].vertsAdj.insert(pair<double, int>(vetVertexs[i].point.getDistance(vetVertexs[j].point), j));
				chegaFim=true;
			}
		}
		
		if (!chegaFim)
		{		
			for (unsigned int k=i+1; k<vetVertexs.size() - numFinals; k++) 
			{
				if (!straightIsBlocked(vetVertexs[i].point, vetVertexs[k].point)) {
					vetVertexs[i].vertsAdj.insert(pair<double, int>(vetVertexs[i].point.getDistance(vetVertexs[k].point), k));
				}
			}
		}
	}			
}


void SGStar::buildPath()
{
	int end=0, j=0;
	double smallestDist = INFINITY;
	path.clear();
	
	//find the final point aprocimated whith the smallest distance
	for (int i = vetVertexs.size() - numFinals; i < vetVertexs.size(); i++)
	{
		if (vetVertexs[i].dist < smallestDist) {
			end = i;
			smallestDist = vetVertexs[i].dist;
		} 
	}
		
	path.push_back(vetVertexs[end].point); 		
	j = vetVertexs[end].previous;
	
	while (j!=0)  // insere os pontos intermediarios do caminho
	{
		path.insert(path.begin(), vetVertexs[j].point);
		j = vetVertexs[j].previous;
	}
	
	path.insert(path.begin(), vetVertexs[j].point); // insere o ponto inicial
	
	cout << "dist = " << vetVertexs[end].dist << endl;
}


bool SGStar::straightIsBlocked(Point p1, Point p2)
{
	double obsx,obsy;
	double dist, distToInitp1;
	double distPts = p1.getDistance(p2) + _TRESHOLD;
	double initialX = p1.getX();
	double initialY = p1.getY();
	double finalX = p2.getX();
	double finalY = p2.getY();
	double a, b, c;
	double sqrtAB;	
	bool isBlocked=false;

	//Sarrus Method to obtain parameters of line's equation
	a = (initialY - finalY);
	b = (finalX - initialX);
	c = ((initialX * finalY) - (finalX * initialY));
	
	sqrtAB = sqrt((a*a) + (b*b));
	
	//x e y aqui são os mesmos do robô, os quais devem ser iterados uma só vez
	//dist = (abs(x*Azinho + y*Bzinho + Czinho) / sqrt((Azinho*Azinho) + (Bzinho*Bzinho)))
	for(unsigned int j=0; j<obstacles.size(); j++) { //para cada obstaculo ve se ele bate na reta
		obsx = (obstacles[j].pos.getX());
		obsy = (obstacles[j].pos.getY());
		dist = (abs(obsx*a + obsy*b + c)/sqrtAB);
		distToInitp1 = p1.getDistance(obstacles[j].pos);
		
		//test if obstacle is valid (isn't out of the line segment)
		if(distToInitp1 < distPts && obstacles[j].pos.getDistance(p2) < distPts) {
			if(obstacles[j].type != BALL)
			{
				if(dist <= LIMIT_IS_BLOCKED) { //test if obstructs
					return true;
				}
			}
			else if(dist <= LIMIT_IS_BLOCKED_BALL) { //test if obstructs
						return true;
				}
		}
	}
	
	return false;
}

void SGStar::makePoints(Point p, Point aux[])
{
	double centerX = p.getX();
	double centerY = p.getY();
	double angle,mAD, mBC;
	double varX, varY;
	Point temp;
	
	varX = finalpos.getX()-initialpos.getX();
    varY = finalpos.getY()-initialpos.getY();

	angle = atan(varY / varX ) - 0.785398163; //-45°
	
	mAD = tan(angle);
	mBC = -1/mAD;

	if((abs(varX)==varX && abs(varY)==varY) || (abs(varX)!=varX && abs(varY)!=varY))
	{
		aux[3].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
		aux[3].setY((mAD*(aux[3].getX()-centerX))+centerY);
		aux[0].setX(centerX - aux[3].getX() + centerX);
		aux[0].setY((mAD*(aux[0].getX()-centerX))+centerY);
		
		if(mBC>0)
		{
			aux[1].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
			aux[1].setY((mBC*(aux[1].getX()-centerX))+centerY);
			aux[2].setX(centerX - aux[1].getX() + centerX);
			aux[2].setY((mBC*(aux[2].getX()-centerX))+centerY);
		}
		else
		{
			aux[2].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
			aux[2].setY((mBC*(aux[2].getX()-centerX))+centerY);
			aux[1].setX(centerX - aux[2].getX() + centerX);
			aux[1].setY((mBC*(aux[1].getX()-centerX))+centerY);
		}
	}
	else
	{
		aux[2].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
		aux[2].setY((mBC*(aux[2].getX()-centerX))+centerY);
		aux[1].setX(centerX - aux[2].getX() + centerX);
		aux[1].setY((mBC*(aux[1].getX()-centerX))+centerY);
		
		if(mAD>0)
		{
			aux[0].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
			aux[0].setY((mAD*(aux[0].getX()-centerX))+centerY);
			aux[3].setX(centerX - aux[0].getX() + centerX);
			aux[3].setY((mAD*(aux[3].getX()-centerX))+centerY);
		}
		else
		{
			aux[3].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
			aux[3].setY((mAD*(aux[3].getX()-centerX))+centerY);
			aux[0].setX(centerX - aux[3].getX() + centerX);
			aux[0].setY((mAD*(aux[0].getX()-centerX))+centerY);
		}
	}
	
	if(abs(varX)!=varX)
	{
		temp = aux[0];
		aux[0] = aux[3];
		aux[3] = temp;
	}
	
	if(abs(varY)==varY)
	{
		temp = aux[1];
		aux[1] = aux[2];
		aux[2] = temp;
	}
}

bool SGStar::isBlocked(Point x)
{
	for(unsigned int i=0; i<obstacles.size(); i++) {
		if ( x.getDistance(obstacles[i].pos) < LIMIT_IS_BLOCKED )
			return true;
	}
	
	return false;
}


bool SGStar::validatePath(Point newGoal, int maxvar)
{
	if(getFinalPos().getDistance(newGoal) > maxvar)
		return false;
	else {
		for(unsigned int i=0; i<path.size()-1; i++)
			if(straightIsBlocked( getPathNode(i), getPathNode(i+1)))
				return false;
	}
		
	return true;
}

vector<Point> SGStar::getPointPath()
{
	return path;
}

Point SGStar::getPathNode(int pointIndex)
{
	return path[pointIndex];
}
				
void SGStar::setInitialPos(Point pos) {
	initialpos = pos;
}		

void SGStar::setFinalPos(Point pos) {
	finalpos = pos;
}

Point SGStar::getInitialPos() {
	return initialpos;
}
		
Point SGStar::getFinalPos() {
	return finalpos;
}
