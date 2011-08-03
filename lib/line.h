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
		/**
		*@return The line perpendicular to this one.*/	
		Line getPerpendicular() const;
		
		/**
		*Determinate if two lines intersect themselves*/	
		bool intersects(const Line &r) const;
		
		/**
		*@return The intersection point between two lines*/
		Point intersection(const Line &r) const;
		
		/**
		*Determines if two lines are parallel*/
		bool parallel(const Line &r) const;
		
		/**
		*Determines the smallest non-negative angle between two lines (in radians)*/
		double angle(const Line &r) const;
		
		/**
		*Determines if two lines are perpendicular each other */
		bool perpendicular(const Line &r) const;
		
		/**
		*Determines if the line contains a point */
		bool contains(const Point &p) const;
		
		/**
		*Determines if a line is vertical*/
		bool vertical() const;
		
		/**
		*Determines if a line is horizontal*/
		bool horizontal() const;

        /**
		Determines the image (y) of a value in line
		@param x value*/
		double image(double x) const;

        /**
		Determines the pre-image (x) of a value on the line
		@param y value*/
		double preImage(double y) const;

        /**
		Determines the distance between a point and a line
		@param p point*/
		double distance(const Point &p) const;

        /**
		Determines the distance between two lines
		@param r another straight*/
		double distance(const Line &r) const;

		bool operator==(const Line &r) const;
		
		


	private:
	
		Vector _vector;
		Point _point;
		
};

#endif // _LINE_H_
