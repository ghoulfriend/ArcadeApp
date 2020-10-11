/*
 * Circle.cpp
 *
 *  Created on: Sep 13, 2020
 *      Author: Admin
 */
#include "Circle.h"
#include "Utils.h"

Circle::Circle():Circle(Vec2D::ZERO, 0)
{

}
Circle::Circle(const Vec2D& center, float radius)
{
	mRadius = radius;
	mPoints.push_back(center);
}

bool Circle::Intersects(const Circle& otherCircle) const
{
	return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < GetRadius() + otherCircle.GetRadius();
}
bool Circle::ContainsPoint(const Vec2D& point) const
{
	return IsLessThanOrEqual(GetCenterPoint().Distance(point), mRadius);
}

