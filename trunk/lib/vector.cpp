#include "vector.h"
#include <cassert>
#include <math.h>

#define toDegrees(x) ((x) * 180 / (float) RP::PI)
#define EPS 1e-3

Vector::Vector(): Point(0.0,0.0) {}

Vector::Vector(double xv, double yv): Point(xv,yv) {}

Vector::Vector(const Point &p): Point(p.getX(), p.getY()) {}

Vector::Vector(const Point &p1, const Point &p2) : Point(p2 - p1) {}

/******************************************************
Funcao que calcula a norma de um vetor
******************************************************/
double Vector::getNorm() const
{
    return sqrt ( square( _x ) + square( _y ) );
}

/******************************************************
Funcao que dado um vetor calcula o cosseno do angulo deste com o eixo y
retorno: cosseno do angulo (double) e -1 se a norma eh 0
******************************************************/
/*double Vector::calculaCosseno()
{
    if (calculaNorma() == 0)
       return -1;
    else
       //calculo do angulo segundo livros de calculo II
       return ( y / calculaNorma() );
}*/

/******************************************************
Funcao para normalizar um vetor
retorno: vetor normalizado
******************************************************/
Vector Vector::normalize() const
{
	  if(_x == 0 && _y == 0)
		  return *this;

    // variável contendo o valor da norma do vetor
    double norm = getNorm();

    // retorna uma cópia do vetor normalizada
    return Vector( _x / norm, _y / norm );
}

Vector& Vector::normalizeMe()
{
	  if(_x == 0 && _y == 0)
		  return *this;

	 //assert norm != 0
    // variável contendo o valor da norma do vetor
    double norm = getNorm();

    // vetor que será retornado
	  _x /= norm;
	  _y /= norm;

    // retorna o vetor normalizado
    return *this;
}

/******************************************************
Função que retorna verdadeiro se os dois vetores são linearmente dependentes
******************************************************/
#include <stdio.h>
bool Vector::linearlyDependent(const Vector &v) const
{
    Vector x(_x, _y), y(v.getX(), v.getY());
    x.normalizeMe();
    y.normalizeMe();

    //printf("EPS: %f\n\n\n\n", EPS);
	if(x.getX() != 0)
	{
		if(x.getY() != 0)
		{
			return fabs(y.getX() / x.getX() - y.getY() / x.getY()) < EPS;
		}
		else
		{
			return !y.getY();
		}
	}
	else
	{
		return !y.getX();
	}
}

// Produto interno de dois vetores
double Vector::dotProduct(const Vector &v) const
{
	return (getX() * v.getX() + getY() * v.getY());
}

/*
A funcao multiplica um vetor por uma matriz de rotacao (sentido anti) dada por [ cos(theta)   -sin(theta) ]
                                                                               [ sin(theta)    cos(tehta) ]
Multiplicando a matriz pelo vetor temos:
      x' = x cos(theta) - y sen(theta)
      y' = x sen(theta) + y cos(theta)
*/
void Vector::rotate(double theta)
{
	//Rotaciona o vetor para a esquerda (sentido AH):
	double angleRadian = theta * RP::PI / 180.0;
	double cosTheta = cos(angleRadian);
	double sinTheta = sin(angleRadian);

	double coordX = getX()*cosTheta - getY()*sinTheta;
	double coordY = getX()*sinTheta + getY()*cosTheta;

	_x = coordX;
	_y = coordY;
}

/******************************************************
Função que calcula o menor angulo positivo entre dois vetores
em radianos.
v: outro vetor
******************************************************/
double Vector::angle(Vector v) const
{
/*
        printf("(%f, %f) angle to (%f, %f)\n", _x, _y, v.getX(), v.getY());
    if(linearlyDependent(v)) {
        printf("(%f, %f) is LD to (%f, %f)\n", _x, _y, v.getX(), v.getY());
        return 0;
    }*/
	return acos(dotProduct(v)/ (float) (getNorm() * v.getNorm()));
}

/******************************************************
Função que calcula o menor angulo positivo entre dois vetores
em radianos.
v: outro vetor
******************************************************/
double Vector::angleDegrees(Vector v) const
{
	return toDegrees(angle(v));
}

/******************************************************
Função especial pra giraAntes()
angulo [0-360) com a vertical******************************************************/
#define PI 3.1415
#define debug_float(x) printf(#x ": %lf\n", (double) x)
double Vector::angleClockwise() const
{
    //debug_float(_x);
    //debug_float(_y);

    Vector v(_x, _y);
    //debug_float(v.getX());
    //debug_float(v.getY());
    v.normalizeMe();
    //debug_float(v.getX());
    //debug_float(v.getY());

    double angulo = acos(v.getX());
    double sen = asin(v.getY());

    //debug_float(angulo);
    //debug_float(sen);

    if(sen < 0)
        angulo = (2*PI - angulo);

    //debug_float(angulo);

    angulo = /*360 -*/ (angulo * 180 / PI);

    //debug_float(angulo);

    return angulo;
}

/******************************************************
Determina se dois vetores são perpendiculares
v: outro vetor
******************************************************/
bool Vector::perpendicular(const Vector &v) const
{
	return dotProduct(v) ? false : true;
}


/******************************************************
Calcula a projecao sobre o vetor passado como parametro
v: outro vetor
******************************************************/
Vector Vector::projection(const Vector &v) const
{
	assert(v.getNorm());

	if(linearlyDependent(v))
		return *this;

	return (dotProduct(v)/ sqrt( v.dotProduct(v) * this->dotProduct(*this) ) ) * v;
}

/******************************************************
Operador de adição de vetores
v: outro vetor
******************************************************/
Vector Vector::operator+(const Vector &v) const
{
	return Vector(Point(*this) + Point(v));
}

/******************************************************
Operador de subtração de vetores
v: outro vetor
******************************************************/
Vector Vector::operator-(const Vector &v) const
{
	return Vector(Point(*this) - Point(v));
}

/******************************************************
Operador de inversão de sinal
******************************************************/
Vector Vector::operator-() const
{
	return Vector(-Point(*this));
}

/******************************************************
Operador para multiplicação por escalar
e: escalar
******************************************************/
Vector Vector::operator*(double e) const
{
	return Vector(getX()*e, getY()*e);
}

/******************************************************
Operador para multiplicação por escalar
e: escalar
v: vetor
******************************************************/
Vector operator*(double e, const Vector &v)
{
	return Vector(v.getX() * e, v.getY() * e);
}

