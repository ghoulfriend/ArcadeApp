#include "Utils.h"
#include <iostream>
#include <cmath>


bool IsEqual(float x, float y)
{
    return fabs(x - y) < EPSILON; 
}
bool IsGreaterThanOrEqual(float x, float y)
{
    return IsEqual(x,y) || x > y;
}
bool IsLessThanOrEqual(float x, float y)
{
    return IsEqual(x,y) || x < y;
}
float MillisecondsToSeconds(unsigned int milliseconds)
{
	return static_cast<float>(milliseconds) / 1000.0f;
}
