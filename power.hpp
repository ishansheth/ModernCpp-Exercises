#ifndef POWER_FUNCTION_INCLUDE_DINGS_BUMS_SAFEGUARD
#define POWER_FUNCTION_INCLUDE_DINGS_BUMS_SAFEGUARD


#include "square.hpp"

inline double power(double i, int degree)
{
    if (degree == 2)
	return square(i);
    double res= 1;
    for (int j= 0; j < degree; ++j)
	res*= i;
    return res;
}

#endif // POWER_FUNCTION_INCLUDE_DINGS_BUMS_SAFEGUARD
