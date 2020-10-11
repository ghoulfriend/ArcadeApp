/*
 * Triangle.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: Admin
 */
#include "Triangle.h"
#include <cmath>
#include "Utils.h"
#include <vector>

Triangle::Triangle():Triangle(Vec2D::ZERO, Vec2D::ZERO, Vec2D::ZERO)//delegating constructor
{

}
Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2)
{
	mPoints.push_back(p0);
	mPoints.push_back(p1);
	mPoints.push_back(p2);
}

Vec2D Triangle::GetCenterPoint() const
{
	return Vec2D( ( mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX() ) / 3, ( mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY() ) / 3 );
}

void Triangle::MoveTo(const Vec2D& p)
{
	Vec2D diff = p - GetCenterPoint();

	const std::vector<Vec2D>points = GetPoints();

	Vec2D p0 = points[0] + diff;
	Vec2D p1 = points[1] + diff;
	Vec2D p2 = points[2] + diff;
	SetP0(p0);
	SetP1(p1);
	SetP2(p2);
}

float Triangle::Area() const
{
	return Area(GetP0(), GetP1(), GetP2());
}

bool Triangle::ContainsPoint(const Vec2D& p) const
{
	float thisArea = Area();

	float a1 = Area(p, mPoints[1], mPoints[2]);
	float a2 = Area(mPoints[0], p, mPoints[2]);
	float a3 = Area(mPoints[0], mPoints[1], p);

	return IsEqual(thisArea, a1 + a2 + a3);
}

float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const
{
	return fabs(( p0.GetX() * (p1.GetY() - p2.GetY()) + p1.GetX() * (p2.GetY() - p0.GetY()) + p2.GetX() * (p0.GetY() - p1.GetY())) / 2);
}

