#ifndef SHAPES_STAR_H_
#define SHAPES_STAR_H_

#include <vector>

#include "Vec2D.h"
#include "Line2D.h"
#include "Color.h"


static const float ANGLE_STAR_POINT = 36.0;

class Star
{
public:
	Star();
	Star(Vec2D centerPoint, float scale=1);
	Star(Line2D line, float scale=1);

	static std::vector<Star> createStars(int n, int DISPLAY_WIDTH, int DISPLAY_HEIGHT);

	void PushPoint(Vec2D p);
	void PushLine(Line2D l);
	std::vector<Vec2D> GetPoints() const;
	std::vector<Line2D> GetLines() const;
	Vec2D getCenterPoint();
	void setCenterPoint(Vec2D centerpoint);
	float getSideLen();
	float getRotationSpeed();
	void setRotationSpeed(float);
	Color getColor();
	void setColor(Color color);

	void moveTo(Vec2D destP);
	Star Rotate(float angle);

private:
	float mScale;
	std::vector<Line2D> mLines;
	std::vector<Vec2D> mPoints;
	float mSideLen;
	Vec2D mCenterPoint;
	float rotationSpeed;
	Color mColor;
};



#endif /* SHAPES_STAR_H_ */
