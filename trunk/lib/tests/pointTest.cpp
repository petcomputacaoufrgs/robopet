#include "tests.h"
#include "../point.h"


RP::Point p1(0,0), p2(0,1), p3(3,2);


START_TESTS()

START_TEST("testa operador >=")

    ASSERT( p1 >= p1 == true)
    ASSERT( p2 >= p1 == true)
    ASSERT( p1 >= p2 == false)
    ASSERT( p2 >= p3 == false)

END_TEST()

END_TESTS()
