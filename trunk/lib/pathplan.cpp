#include <iostream>
#include <stdlib.h>

#include "utils.h"

#include "pathplan.h"

using RP::Point;
using namespace std;

Pathplan::Pathplan()
{
	status = NOTHING;
}

Pathplan::~Pathplan() {}
