/*
 * Shape.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: Admin
 */

#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset)
{
	for(Vec2D& point : mPoints)
	{
		point = point + deltaOffset;
	}
}


