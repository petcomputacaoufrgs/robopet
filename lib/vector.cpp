#include "vector.h"
#include <cassert>
#include <math.h>

#define toDegrees(x) ((x) * 180 / (float) PI)
#define EPS 1e-3

std::ostream& operator<<(std::ostream& out, Vector v)
{
	out << "<" << v.getX() << "," << v.getY() << ">";
	return out;
}

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
	double angleRadian = theta * PI / 180.0;
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
Função que calcula o angulo no sentido horário
entre dois vetores.
v: outro vetor
******************************************************/
double angleCW(Vector v) const {
	
}

/******************************************************
Função que calcula o angulo no sentido horário
entre dois vetores em graus.
v: outro vetor
******************************************************/
double angleCWDegrees(Vector v) const {
	return toDegrees(angleCW(v));
}

/******************************************************
Função que calcula o angulo no sentido antihorário
entre dois vetores.
v: outro vetor
******************************************************/
double angleCCW(Vector v) const {
	
}

/******************************************************
Função que calcula o angulo no sentido antihorário
entre dois vetores em graus.
v: outro vetor
******************************************************/
double angleCCWDegrees(Vector v) const {
	return toDegrees(angleCCW(v));
}

double Vector::angleClockwise() const
{
    Vector v(_x, _y);

    v.normalizeMe();

    double angulo = acos(v.getX());
    double sen = asin(v.getY());

    if(sen < 0)
        angulo = (2*PI - angulo);

    angulo = /*360 -*/ (angulo * 180 / PI);

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

