#ifndef _ROBOPET_H_
#define _ROBOPET_H_

#include <cmath>

#define ENABLE_WARNINGS

#ifdef ENABLE_WARNINGS
#define WARNING(str,...) printf("WARNING: "str, ##__VA_ARGS__)
#else
#define WARNING(str,...)
#endif

namespace RP {

		static const double PI = M_PI;

		class Referee;
		class Player;
		class Vector;
		class Line;
		class Point;
		class MovingObject;
		typedef MovingObject Ball;

}

#endif
