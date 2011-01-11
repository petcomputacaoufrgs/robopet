#ifndef _RETA_H_
#define _RETA_H_
#include "vector.h"
#include "point.h"

#define ANGULO_ZERO 0.0000001

using RP::Line;

/**
 * Represents a line in the plane
 * \ingroup RoboPETLib
 * */

class Line
{

    public:

        Line();
        Line(Vector v);
        Line(Vector v, Point p);
        Line(Point p1, Point p2);
		Line(double a, double b);

		//----- Getters -----
		inline Vector getVector() const { return _vector; }
		inline Point getPoint() const { return _point; }
		double getAngularCoefficient() const;
		double getLinearCoefficient() const;

		//----- Setters -----
        inline void setVector(const Vector &v) { _vector = v; }
		inline void setPoint(Point p) { _point = p; }
        void setAngularCoefficient(double a);
		void setLinearCoefficient(double b);
		
		
		//----- Others -----
		bool intersects(const Line &r) const;
		Point intersection(const Line &r) const;
		bool parallel(const Line &r) const;
		double angle(const Line &r) const;
		bool perpendicular(const Line &r) const;
		bool contains(const Point &p) const;
		bool vertical() const;
		bool horizontal() const;

        /**
		Determines the image (y) of a value in line
		
		x: value
		*/
		double image(double x) const;

        /**
		Determines the pre-image (x) of a value on the line
		
		y: value
        */
		double preImage(double y) const;

        /**
		Determines the distance between a point and a line
		
		p: point
		*/
		double distance(const Point &p) const;

        /**
		Determines the distance between two lines
		
		r: another straight
        */
		double distance(const Line &r) const;

		/**
		 == operator
		 */
		bool operator==(const Line &r) const;


	private:
				Vector _vector;
				Point _point;
};

#endif // _LINE_H_
