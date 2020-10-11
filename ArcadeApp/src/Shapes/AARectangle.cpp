/*
 * AARectangle.cpp
 *
 *  Created on: Sep 13, 2020
 *      Author: Admin
 */
#include "AARectangle.h"
#include "Utils.h"
#include <cmath>

AARectangle::AARectangle():AARectangle(Vec2D::ZERO, Vec2D::ZERO)
{

}
AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}
AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}

float AARectangle::GetWidth() const
{
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}
float AARectangle::GetHeight() const
{
	return GetTopLeftPoint().GetY() - GetBottomRightPoint().GetY() + 1;
}

void AARectangle::MoveTo(const Vec2D& position)
{
	float width = GetWidth();
	float height = GetHeight();

	SetTopLeftPoint(position);
	SetBottomRightPoint(Vec2D(position.GetX() + width - 1, position.GetY() + height - 1));
}

Vec2D AARectangle::GetCenterPoint() const
{
	return Vec2D( GetTopLeftPoint().GetX() + GetWidth() / 2, GetTopLeftPoint().GetY() + GetHeight() / 2 );
}

bool AARectangle::Intersects(const AARectangle& otherRect) const
{
		return !(otherRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() ||
				otherRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX() ||
				otherRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() ||
				otherRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY()) ;
}
bool AARectangle::ContainsPoint(const Vec2D& point) const
{
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
	bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();
	return (withinX && withinY);
}
bool AARectangle::Collides(AARectangle& otherRect)
{
	return ( otherRect.GetBottomRightPoint().GetY() <= GetBottomRightPoint().GetY() );
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets)
{
	return AARectangle(rect.GetTopLeftPoint() + insets, rect.GetWidth() - (insets.GetX() * 2), rect.GetHeight() - (insets.GetY() * 2));
}

std::vector<Vec2D> AARectangle::GetPoints() const
{
	std::vector<Vec2D> vec;
	vec.push_back(mPoints[0]);
	vec.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY()));
	vec.push_back(mPoints[1]);
	vec.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));

	return vec;
}



