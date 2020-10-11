#include "Star.h"
#include <cstdlib>
#include <ctime>


//Star::Star(Vec2D centerPoint, float scale)
//{
//
//}

Star::Star(Line2D startline, float scale)
{
	mSideLen = startline.Length();

	//side0 will be the very top right side -> \

	Line2D side0 = startline;
	PushLine(side0);
	PushPoint(side0.GetP0());
	PushPoint(side0.GetP1());

	Vec2D rotP1 = startline.GetP0().RotationResult(108, startline.GetP1());//Rotate P0 around P1 -> \_
	Line2D side1 = Line2D(startline.GetP1(), rotP1);
	PushLine(side1);
	PushPoint(rotP1);

	Vec2D rotP2 = startline.GetP1().RotationResult(360 - ANGLE_STAR_POINT, rotP1);//Rotate rotP1
	Line2D side2 = Line2D(rotP1, rotP2);
	PushLine(side2);
	PushPoint(rotP2);

	Vec2D rotP3 = rotP1.RotationResult(108, rotP2);
	Line2D side3 = Line2D(rotP2, rotP3);
	PushLine(side3);
	PushPoint(rotP3);

	Vec2D rotP4 = rotP2.RotationResult(360 - ANGLE_STAR_POINT, rotP3);
	Line2D side4 = Line2D(rotP3, rotP4);
	PushLine(side4);
	PushPoint(rotP4);

	Vec2D rotP5 = rotP3.RotationResult(108, rotP4);
	Line2D side5 = Line2D(rotP4, rotP5);
	PushLine(side5);
	PushPoint(rotP5);

	Vec2D rotP6 = rotP4.RotationResult(360 - ANGLE_STAR_POINT, rotP5);
	Line2D side6 = Line2D(rotP5, rotP6);
	PushLine(side6);
	PushPoint(rotP6);

	Vec2D rotP7 = rotP5.RotationResult(108, rotP6);
	Line2D side7 = Line2D(rotP6, rotP7);
	PushLine(side7);
	PushPoint(rotP7);

	Vec2D rotP8 = rotP6.RotationResult(360 - ANGLE_STAR_POINT, rotP7);
	Line2D side8 = Line2D(rotP7, rotP8);
	PushLine(side8);
	PushPoint(rotP8);

	Line2D side9 = Line2D(rotP8, side0.GetP0());
	PushLine(side9);

	//Construct the mCenterPoint -> Vec2D( mean(x), mean(y) )
	float centerX, centerY;
	int sumX = 0;
	int sumY = 0;
	for(Vec2D point : mPoints)
	{
		sumX += point.GetX();
		sumY += point.GetY();
	}
	centerX = (sumX / mPoints.size());
	centerY = (sumY / mPoints.size());

	mCenterPoint = Vec2D(centerX, centerY);

}
std::vector<Star> Star::createStars(int n, int DISPLAY_WIDTH, int DISPLAY_HEIGHT)
{
	const int MAX_STAR_SIDE_LEN = 10;
	const int MAX_ROTATION_SPEED = 100;
	std::srand(time(NULL));//seed for random operations

	std::vector<Color> colors = {Color::Red(), Color::Orange(), Color::Yellow(), Color::Magenta(), Color::Pink()};

	std::vector<Star> stars;

	for(int i = 0; i < n; ++i)
	{
		//calculate random values for each star
		int randX = rand() % DISPLAY_WIDTH;
		int randY = rand() % DISPLAY_HEIGHT;
		int len = rand() % MAX_STAR_SIDE_LEN;
		float rot = rand() % MAX_ROTATION_SPEED;
		Color color = colors[rand() % colors.size()];

		//create star with random data
		Line2D side = {Vec2D(randX, randY), Vec2D(randX + len, randY + len)};
		Star star(side);
		star.setRotationSpeed(rot);
		star.setColor(color);

		//add to return vector
		stars.push_back(star);
	}

	return stars;
}
void Star::PushPoint(Vec2D p)
{
	mPoints.push_back(p);
}
void Star::PushLine(Line2D l)
{
	mLines.push_back(l);
}
std::vector<Vec2D> Star::GetPoints() const
{
	return mPoints;
}
std::vector<Line2D> Star::GetLines() const
{
	return mLines;
}
Vec2D Star::getCenterPoint(){
	return mCenterPoint;
}
void Star::setCenterPoint(Vec2D centerpoint)
{
	mCenterPoint = centerpoint;
}
float Star::getSideLen()
{
	return mSideLen;
}

float Star::getRotationSpeed()
{
	return rotationSpeed;
}
void Star::setRotationSpeed(float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}
Color Star::getColor()
{
	return mColor;
}
void Star::setColor(Color color)
{
	mColor = color;
}


Star Star::Rotate(float angle)
{
	std::vector<Vec2D> points = GetPoints();
	Vec2D centerPoint = getCenterPoint();
	Vec2D rotP0 = points[0].RotationResult(angle, centerPoint);
	Vec2D rotP1 = points[1].RotationResult(angle, centerPoint);
	Line2D rotSide0 = {rotP0, rotP1};

	std::cout << "Centerpoint: " << getCenterPoint().GetX() << "," << getCenterPoint().GetY() << "\nOriginal points: " << points[0] << "," << points[1] << "\nRotated Points: " << rotP0 << "\t" << rotP1 << std::endl;

	Star rotatedStar(rotSide0);
	return rotatedStar;
}

void Star::moveTo(Vec2D destP)
{
	std::vector<Line2D> sides = GetLines();
	Vec2D diff(sides[0].GetP1() - sides[0].GetP0());
	Vec2D moved(diff + destP);
	Line2D newline(destP, moved);
	Star newstar(newline);
	*this = newstar;
}


