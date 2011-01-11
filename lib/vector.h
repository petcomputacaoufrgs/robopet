#ifndef _ROBOPET_VECTOR_H_
#define _ROBOPET_VECTOR_H_

#include "robopet.h"
#include "point.h"

using RP::Vector;
using RP::Point;

#include <iostream>

/**
 * 
 * \ingroup RoboPETLib
 */

class Vector : public Point
{

	  public:
		  //Constructors
		  Vector();
		  Vector(double x, double y);
		  Vector(const Point &p);
		  Vector(const Point &p1, const Point &p2);

		  /**
          Calculates the norm of the vector
          */
	      double getNorm() const;
	      
	      
	     // double calculaCosseno();

	      /**
	       @return normalized vector 
	       */
	      Vector normalize() const;

	      Vector& normalizeMe();

		/**
		 * @return true if two vectors are linearly dependents
		 */
		bool linearlyDependent(const Vector &v) const;

		/**
		 * Calculates the inner product between two normalized vectors
		 * */
		double dotProduct(const Vector &v) const;

		/**
		 * Rotate the theta vector (degrees)
		 */
		void rotate(double theta);

		/**
		 * Calculates the lowest positive angle between two vectors (in radians).

		   v: another vector
		 * */
		double angle(Vector v) const;

		/**
		   Calculates the lowest positive angle between two vectors (in degrees).

		   v: another vector
		*/
		double angleDegrees(Vector v) const;

		/**
		Function that calculates the angle clockwise between two vectors.
		
		v: another vector
		*/
		double angleCW(Vector v) const;
		
		/**
		Function that calculates the angle clockwise between two vectors (degrees)
		
		v: another vector
		*/
		double angleCWDegrees(Vector v) const;
		
		/**
		Function that calculates the angle counterclockwise between two vectors
		
		v: another vector
		*/
		double angleCCW(Vector v) const;
		
		/**
		Function that calculates the angle counterclockwise between two vectors (degrees)
		
		v: another vector
		*/
		double angleCCWDegrees(Vector v) const;

		/**
		Calculates the angle of the vector with the x-axis, (trigonometric circle)

		v: another vector
		*/
		double myAngle() const;

		/**
		Calculates the angle of the vector with the x-axis, (trigonometric circle)(degrees)

		v: another vector
		*/
		double myAngleDegrees() const;

		/**
		Determines whether two vectors are perpendicular
		
		v: another vector
		*/
		bool perpendicular(const Vector &v) const;

		/**
		Calculate the projection of the vector passed as parameter
		
		v: another vector
		*/
		Vector projection(const Vector &v) const;

		// Operators
		Vector operator+(const Vector &v) const;
		Vector operator-(const Vector &v) const;
		Vector operator-() const;
		Vector operator*(double e) const;

		friend std::ostream& operator<<(std::ostream& out, Vector v);

};

		Vector operator*(double e, const Vector &v);

#endif // _ROBOPET_VECTOR_H_

