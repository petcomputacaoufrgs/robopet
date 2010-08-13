#include "point.h"

#include <stdio.h>
void Point::setX(double newX)
{
      /*if(newX < 0)
      {
      		WARNING("Tried to set x < 0 ! Turned x into default value (0).");
      		_x = 0;
      }
      else//*/
      		_x = newX;
}

void Point::setY(double newY)
{
     /*if(newY < 0)
      {
      		WARNING("Tried to set y < 0 ! Turned y into default value (0).");
      		_y = 0;
      }
      else//*/
      		_y = newY;
}

void Point::setXY(double u, double v)
{
     setX(u);
     setY(v);
}

void Point::setXY(const Point &p)
{
	setX(p.getX());
	setY(p.getY());
}


/***************************************************************
Método para calcular a distância entre o objeto e o parâmetro
retorno: uma float com o módulo da distancia
***************************************************************/
double Point::getDistance(const Point &p) const
{
       // raiz quadrada do quadrado dos catetos
       return sqrt( square( getX() - p.getX()) +  square(getY() - p.getY() ));
}

/***************************************************************
Método para calcular a distância entre o objeto e o parâmetro,
       considerando o eixo das abscissas
retorno: uma float com o módulo da distancia
***************************************************************/
double Point::getDistanceX(const Point &p) const
{
       double distance = getX() - p.getX();

       // operador ternário, calcula o modulo
       return fabs(distance);
} 

/***************************************************************
Método para calcular a dsitância entre o objeto e o parâmetro,
       considerando o eixo das ordenadas
retorno: uma float com o módulo da distancia
***************************************************************/
double Point::getDistanceY(const Point &p) const
{
       double distance = getY() - p.getY();

       // operador ternário, calcula o modulo
       return fabs(distance);
}


/***************************************************************
Operadores:

***************************************************************/

/******************************************************
Operação de comparação de pontos '<'
******************************************************/
bool Point::operator<(const Point &pos) const
{
	return getX() < pos.getX() || ((getX() == pos.getX()) && getY() < pos.getY());
}

/******************************************************
Operação de comparação de pontos '=='
******************************************************/
bool Point::operator==(const Point &pos) const
{
	if(( getX() == pos.getX() ) && ( getY() == pos.getY() ))
		return true;
	else return false;
}

/******************************************************
Operação de comparação de pontos '!='
******************************************************/
bool Point::operator!=(const Point &pos) const
{
	if(( getX() == pos.getX() ) && ( getY() == pos.getY() ))
		return false;
	else return true;
}

/******************************************************
Operador de cópia '='
******************************************************/

Point& Point::operator=(const Point &p)
{
	this->setXY(p);
	return *this;
}
/*
Point& Point::operator=(Point p)
{
	this->setXY(p.getX(), p.getY());
	return *this;
}
*/
/***************************************************************************
								Operator +
Descrição: Método de sobrePoint da operação '+' para posições

pos - Posição a ser somada

Retorno:
***************************************************************************/
Point Point::operator+(const Point &point) const
{
    Point p;

    p._x = getX() + point.getX();
    p._y = getY() + point.getY();

    return p;
}

/******************************************************
Método de sobrePoint da operacao '-'
******************************************************/
Point Point::operator-(const Point &pos) const
{
    Point p;

    p._x = getX() - pos.getX();
    p._y = getY() - pos.getY();

    return p;
}

/******************************************************
Operador de '-' unário, inversão de sinal
******************************************************/
Point Point::operator-() const
{
	Point p(-getX(),-getY());
	return p;
}

