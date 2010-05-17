#ifndef _RETA_H_
#define _RETA_H_
#include "vector.h"
#include "point.h"

#define ANGULO_ZERO 0.0000001

using RP::Line;

class Line
{
	/**********************************************
	representa uma reta no plano
	**********************************************/

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

        /**************************************
		Método que determina a imagem (y) de um valor na reta
		x: valor
        **************************************/
		double image(double x) const;

        /**************************************
		Método que determina a pré-imagem (x) de uma valor na reta
		y: valor
        **************************************/
		double preImage(double y) const;

        /**************************************
		Método que determina a distância entre um ponto e uma reta
		p: ponto
        **************************************/
		double distance(const Point &p) const;

        /**************************************
		Método que determina a distância entre duas retas
		r: outra reta
        **************************************/
		double distance(const Line &r) const;

		/**************************************
		Operador de == para a classe reta]
		r: outra reta
		****************************************/
		bool operator==(const Line &r) const;

	private:
				Vector _vector;
				Point _point;
};

#endif // _LINE_H_
