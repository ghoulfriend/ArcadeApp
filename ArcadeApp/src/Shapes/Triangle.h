/*
 * Triangle.h
 *
 *  Created on: Sep 12, 2020
 *      Author: Admin
 */

#ifndef SHAPES_TRIANGLE_H_
#define SHAPES_TRIANGLE_H_

#include "Shape.h"

class Triangle: public Shape
{
public:
	Triangle();
	Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

	inline void SetP0(Vec2D& p0){ mPoints[0] = p0; }
	inline void SetP1(Vec2D& p1){ mPoints[1] = p1; }
	inline void SetP2(Vec2D& p2){ mPoints[2] = p2; }

	inline Vec2D GetP0() const { return mPoints[0]; }
	inline Vec2D GetP1() const { return mPoints[1]; }
	inline Vec2D GetP2() const { return mPoints[2]; }

	virtual Vec2D GetCenterPoint() const override;

	virtual void MoveTo(const Vec2D& p) override;

	float Area() const;

	bool ContainsPoint(const Vec2D& p) const;

private:
	float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;
};



#endif /* SHAPES_TRIANGLE_H_ */
