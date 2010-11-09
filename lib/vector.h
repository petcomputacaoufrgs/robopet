#ifndef _ROBOPET_VECTOR_H_
#define _ROBOPET_VECTOR_H_

#include "robopet.h"
#include "point.h"

using RP::Vector;
using RP::Point;

#include <iostream>


class Vector : public Point
{

	  public:
		  //Constructors
		  Vector();
		  Vector(double x, double y);
		  Vector(const Point &p);
		  Vector(const Point &p1, const Point &p2);

        /******************************************************
	      Funcao que calcula a norma de um vetor
	      ******************************************************/
	      double getNorm() const;

	      /******************************************************
	      Funcao que dado um vetor calcula o cosseno do angulo deste com o eixo y
	      retorno: cosseno do angulo (double)
	      ******************************************************/
	     // double calculaCosseno();

	      /******************************************************
	      Funcao para normalizar um vetor
	      retorno: vetor normalizado
	      ******************************************************/
	      Vector normalize() const;

	      Vector& normalizeMe();

		/******************************************************
		Fun��o que retorna verdadeiro se os dois vetores s�o linearmente 				dependentes
		******************************************************/
		bool linearlyDependent(const Vector &v) const;

		// Calcula o produto interno (coseno) entre dois vetores normalizados
		double dotProduct(const Vector &v) const;

		//rotaciona o vetor theta GRAUS
		void rotate(double theta);

		/******************************************************
		Fun��o que calcula o menor angulo positivo entre dois vetores
		em radianos.
		v: outro vetor
		******************************************************/
		double angle(Vector v) const;

		/******************************************************
		Fun��o que calcula o menor angulo positivo entre dois vetores
		em graus.
		v: outro vetor
		******************************************************/
		double angleDegrees(Vector v) const;

		/******************************************************
		Fun��o que calcula o angulo no sentido hor�rio
		entre dois vetores.
		v: outro vetor
		******************************************************/
		double angleCW(Vector v) const;
		
		/******************************************************
		Fun��o que calcula o angulo no sentido hor�rio
		entre dois vetores em graus.
		v: outro vetor
		******************************************************/
		double angleCWDegrees(Vector v) const;
		
		/******************************************************
		Fun��o que calcula o angulo no sentido antihor�rio
		entre dois vetores.
		v: outro vetor
		******************************************************/
		double angleCCW(Vector v) const;
		
		/******************************************************
		Fun��o que calcula o angulo no sentido antihor�rio
		entre dois vetores em graus.
		v: outro vetor
		******************************************************/
		double angleCCWDegrees(Vector v) const;

		/******************************************************
		Calcula o angulo do vetor com o eixo x, ie angulo no
		c�rculo trigonom�trico.
		v: outro vetor
		******************************************************/
		double myAngle() const;

		/******************************************************
		Calcula o angulo do vetor com o eixo x, ie angulo no
		c�rculo trigonom�trico em graus.
		v: outro vetor
		******************************************************/
		double myAngleDegrees() const;

		/******************************************************
		Determina se dois vetores s�o perpendiculares
		v: outro vetor
		******************************************************/
		bool perpendicular(const Vector &v) const;

		/******************************************************
		Calcula a projecao sobre o vetor passado como parametro
		v: outro vetor
		******************************************************/
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

