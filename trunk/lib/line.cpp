#include "line.h"
#include <cassert>

Line::Line() : _vector(), _point()
{}

Line::Line(Vector v) : _vector(v), _point()
{}

Line::Line(Vector v, Point p) : _vector(v), _point(p)
{}

Line::Line(Point p1, Point p2) : _vector(p1, p2), _point(p1)
{}

Line::Line(double a, double b) : _vector(Point(0, b), Point(1, a + b)), _point(0, b)
{}


double Line::getAngularCoefficient() const
{
	assert(_vector.getX());
	return _vector.getY() / _vector.getX();
}

double Line::getLinearCoefficient() const
{
	assert(_vector.getX());
	return _point.getY() - _point.getX() * _vector.getY() / _vector.getX();
}




void Line::setAngularCoefficient(double a)
{ *this = Line(a, getLinearCoefficient()); }

void Line::setLinearCoefficient(double b)
{ *this = Line(getAngularCoefficient(), b); }




/**************************************
M�todo que determina se duas Lines se intersectam
r: outra Line
**************************************/
bool Line::intersects(const Line &r) const
{
	return (!parallel(r) || contains(r.getPoint()));
}

/**************************************
Retorna o ponto de intersec��o de duas Lines
r: outra Line
**************************************/
Point Line::intersection(const Line &r) const
{
	assert(intersects(r));

	if(*this == r)
		return _point;
	if(!vertical())
		if(!r.vertical()) {
			double x = (r.getLinearCoefficient() - getLinearCoefficient()) / (getAngularCoefficient() - r.getAngularCoefficient());
			return Point(x, image(x));
		}
		else return Point(r.getPoint().getX(), image(r.getPoint().getX()));
	else return Point(_point.getX(), r.image(_point.getX()));
}

/**************************************
M�todo que determina se duas Lines s�o paralelas
r: outra Line
**************************************/
bool Line::parallel(const Line &r) const
{
	return _vector.linearlyDependent(r.getVector());
}

/**************************************
M�todo que determina o menor �ngulo n�o-negativo entre duas Lines (em radianos)
r: outra Line
**************************************/
double Line::angle(const Line &r) const
{
	double angulo1, angulo2;
	angulo1 = _vector.angle(r.getVector());
	angulo2 = _vector.angle(-r.getVector());

	return (angulo1 < angulo2) ? angulo1 : angulo2;
}

/**************************************
M�todo que determina se duas Lines s�o perpendiculares
r: outra Line
**************************************/
bool Line::perpendicular(const Line &r) const
{
	return (_vector.perpendicular(r.getVector()));
}

/**************************************
M�todo que determina se a reta cont�m um ponto
p: ponto
**************************************/
bool Line::contains(const Point &p) const
{
	if(vertical())
		return p.getX() == _point.getX();

	return p.getY() == image(p.getX());
}

/**************************************
Determina se uma Line � vertical
**************************************/
bool Line::vertical() const
{
	return !_vector.getX();
}

/**************************************
Determina se uma Line � horizontal
**************************************/
bool Line::horizontal() const
{
	return !_vector.getY();
}

/**************************************
M�todo que determina a imagem (y) de um valor na Line
x: valor
**************************************/
double Line::image(double x) const
{
	if(vertical())
	{
		assert(x == _point.getX());
		return _point.getY();
	}

	return getAngularCoefficient() * x + getLinearCoefficient();
}

/**************************************
M�todo que determina a pr�-imagem (x) de uma valor na Line
y: valor
**************************************/
double Line::preImage(double y) const
{
	assert(!horizontal());

	return (y - getLinearCoefficient()) / getAngularCoefficient();
}

/**************************************
M�todo que determina a dist�ncia entre um ponto e uma Line
p: ponto
**************************************/
double Line::distance(const Point &p) const
{
	Vector linePoint(_point, p);

	Vector proj = linePoint.projection(_vector);

	return (linePoint - proj).getNorm();
}

/**************************************
M�todo que determina a dist�ncia entre duas linhas
r: outra Line
**************************************/
double Line::distance(const Line &r) const
{
	if(intersects(r))
		return 0;

	return distance(r.getPoint());
}

/**************************************
Operador de == para a classe Line]
r: outra Line
****************************************/
bool Line::operator==(const Line &r) const
{
	return (intersects(r) && parallel(r));
}
