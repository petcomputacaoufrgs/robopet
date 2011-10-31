#ifndef _SGSTAR_H_
#define _SGSTAR_H_

#include "pathplan.h"
#include "point.h"
#include <map>
#include <vector>

using namespace std;

#define _TRESHOLD (ROBOT_RADIUS_MM/2)
#define LIMIT_IS_BLOCKED (2*ROBOT_RADIUS_MM + _TRESHOLD)
#define LIMIT_IS_BLOCKED_BALL (ROBOT_RADIUS_MM + 25)
#define DIST_ROBO_POINT (3*ROBOT_RADIUS_MM*sqrt(2))
#define DIST_BOLA_POINT 200

typedef struct {
	double dist;
	multimap<double, int> vertsAdj;
	int previous;
	Point point;
} Vertex;


class SGStar : public Pathplan 
{
	public:
		SGStar();
		~SGStar();
		void run();
		
		bool validatePath(Point newGoal, int maxvar);
		
		//----- Getters & Setters -----
		Point getInitialPos();
		Point getFinalPos();
		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
		vector<Point> getPointPath();
		Point getPathNode(int pointIndex);
		
	protected:
		vector<Vertex> vetVertexs;
		int numFinals;
		
		void initVertexs();
		void createAdjList();
		void buildPath();
		bool straightIsBlocked(Point p1, Point p2);
		void makePoints(Point p, Point aux[]);
		bool isBlocked(Point x);
		void aprocimateFinals();
};

#endif
