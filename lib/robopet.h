#ifndef _ROBOPET_H_
#define _ROBOPET_H_

#include <cmath>

#ifdef ENABLE_WARNINGS
#define WARNING(str,...) printf("WARNING: "str, ##__VA_ARGS__)
#else
#define WARNING(str,...)
#endif

/**
 * \defgroup RoboPETLib RoboPET lib
 * \ingroup RoboPETLib
 * Definition of all the RoboPET Lib classes
 */

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
